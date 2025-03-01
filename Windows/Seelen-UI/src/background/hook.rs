use std::{
    collections::HashMap,
    path::PathBuf,
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc,
    },
    thread::JoinHandle,
    time::{Duration, Instant},
};

use itertools::Itertools;
use lazy_static::lazy_static;
use parking_lot::Mutex;
use seelen_core::handlers::SeelenEvent;
use serde::Serialize;
use tauri::Emitter;
use windows::Win32::{
    Foundation::HWND,
    UI::{
        Accessibility::{SetWinEventHook, HWINEVENTHOOK},
        WindowsAndMessaging::{
            DispatchMessageW, GetMessageW, TranslateMessage, EVENT_MAX, EVENT_MIN, MSG,
        },
    },
};

use crate::{
    error_handler::Result,
    event_manager, log_error,
    modules::{
        input::{domain::Point, Mouse},
        virtual_desk::{get_vd_manager, VirtualDesktopEvent, VirtualDesktopManager},
    },
    seelen::{get_app_handle, Seelen, SEELEN},
    seelen_weg::SeelenWeg,
    seelen_wm_v2::instance::WindowManagerV2,
    state::{application::FULL_STATE, domain::AppExtraFlag},
    trace_lock,
    utils::spawn_named_thread,
    windows_api::{window::Window, WindowEnumerator, WindowsApi},
    winevent::WinEvent,
};

lazy_static! {
    static ref HOOK_MANAGER_SKIPPER: Arc<Mutex<HookManagerSkipper>> =
        Arc::new(Mutex::new(HookManagerSkipper::default()));
    pub static ref WINDOW_DICT: Arc<Mutex<HashMap<isize, WindowCachedData>>> =
        Arc::new(Mutex::new(HashMap::new()));
}

pub static LOG_WIN_EVENTS: AtomicBool = AtomicBool::new(false);

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct WindowCachedData {
    pub hwnd: isize,
    pub monitor: usize,
    pub maximized: bool,
    pub fullscreen: bool,
}

impl From<&Window> for WindowCachedData {
    fn from(w: &Window) -> Self {
        WindowCachedData {
            hwnd: w.address(),
            monitor: w.monitor().address(),
            maximized: w.is_maximized(),
            fullscreen: w.is_fullscreen(),
        }
    }
}

#[derive(Serialize, Clone)]
#[serde(rename_all = "camelCase")]
pub struct FocusedApp {
    hwnd: isize,
    title: String,
    name: String,
    exe: Option<PathBuf>,
    umid: Option<String>,
    is_maximized: bool,
}

#[derive(Debug)]
pub struct HookManagerSkipperItem {
    hwnd: isize,
    event: WinEvent,
    expiry: Instant,
    skipped: bool,
}

#[derive(Debug, Default)]
pub struct HookManagerSkipper {
    to_skip: Vec<HookManagerSkipperItem>,
}

impl HookManagerSkipper {
    /// this function is intended to be called before ejecuting a actions that will
    /// trigger some window event, so the skipper will be removed after 1 second
    /// if no event is emitted in that interval
    pub fn skip(&mut self, event: WinEvent, hwnd: isize) {
        self.to_skip.push(HookManagerSkipperItem {
            hwnd,
            event,
            expiry: Instant::now() + Duration::from_millis(1000),
            skipped: false,
        });
    }

    fn cleanup(&mut self) {
        self.to_skip
            .retain(|s| !s.skipped && s.expiry > Instant::now());
    }

    /// returns true if the event should be skipped
    fn should_skip(&mut self, event: WinEvent, hwnd: isize) -> bool {
        if let Some(item) = self
            .to_skip
            .iter_mut()
            .find(|s| s.hwnd == hwnd && s.event == event && !s.skipped && s.expiry > Instant::now())
        {
            item.skipped = true;
            return true;
        }
        false
    }
}

pub struct HookManager;

event_manager!(HookManager, (WinEvent, Window));

impl HookManager {
    /// this will be called without waiting for the event to be processed
    /// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwineventhook#remarks
    extern "system" fn raw_win_event_hook_recv(
        _hook_handle: HWINEVENTHOOK,
        event: u32,
        origin: HWND,
        id_object: i32,
        _id_child: i32,
        _id_event_thread: u32,
        _dwms_event_time: u32,
    ) {
        if id_object != 0 || !Seelen::is_running() {
            return;
        }

        log_error!(Self::event_tx().send((WinEvent::from(event), Window::from(origin))));

        if FULL_STATE.load().is_weg_enabled() {
            // raw events should be only used for a fastest and immediately processing
            log_error!(SeelenWeg::process_raw_win_event(event, origin));
        }
    }

    pub fn run_with_async<F, T>(f: F) -> JoinHandle<T>
    where
        F: FnOnce(&mut HookManagerSkipper) -> T,
        F: Send + 'static,
        T: Send + 'static,
    {
        std::thread::spawn(move || f(&mut *trace_lock!(HOOK_MANAGER_SKIPPER)))
    }

    fn log_event(event: WinEvent, origin: Window) {
        if event == WinEvent::ObjectLocationChange || !LOG_WIN_EVENTS.load(Ordering::Acquire) {
            return;
        }
        let event_value = {
            #[cfg(dev)]
            {
                use owo_colors::OwoColorize;
                event.green()
            }
            #[cfg(not(dev))]
            {
                &event
            }
        };
        log::debug!("{:?} | {:?}", event_value, origin,);
    }

    fn process_event(event: WinEvent, origin: Window) {
        Self::log_event(event, origin);

        {
            let mut skipper = trace_lock!(HOOK_MANAGER_SKIPPER);
            if skipper.should_skip(event, origin.address()) {
                if LOG_WIN_EVENTS.load(Ordering::Acquire) {
                    log::debug!("Skipping WinEvent::{:?}", event);
                }
                skipper.cleanup();
                return;
            }
        }

        if event == WinEvent::SystemForeground
            || event == WinEvent::SyntheticMaximizeStart
            || event == WinEvent::SyntheticMaximizeEnd
        {
            let process = origin.process();
            let result = get_app_handle().emit(
                SeelenEvent::GlobalFocusChanged,
                FocusedApp {
                    hwnd: origin.address(),
                    title: origin.title(),
                    name: origin
                        .app_display_name()
                        .unwrap_or(String::from("Error on App Name")),
                    exe: process.program_path().ok(),
                    umid: origin.app_user_model_id().map(|umid| umid.to_string()),
                    is_maximized: origin.is_maximized(),
                },
            );
            log_error!(result);
        }

        if let VirtualDesktopManager::Seelen(vd) = get_vd_manager().as_ref() {
            log_error!(vd.on_win_event(event, &origin), event);
        }

        let app_state = FULL_STATE.load();
        if app_state.is_weg_enabled() {
            std::thread::spawn(move || {
                log_error!(SeelenWeg::process_global_win_event(event, &origin), event);
            });
        }

        if app_state.is_window_manager_enabled() {
            std::thread::spawn(move || {
                log_error!(WindowManagerV2::process_win_event(event, &origin), event);
            });
        }

        {
            let mut seelen = trace_lock!(SEELEN);
            if let Some(wall) = seelen.wall_mut() {
                log_error!(wall.process_win_event(event, &origin), event);
            }
        };

        let mut seelen = trace_lock!(SEELEN);
        for instance in seelen.instances_mut() {
            if let Some(toolbar) = instance.toolbar_mut() {
                log_error!(toolbar.process_win_event(event, &origin), event);
            }
            if let Some(weg) = instance.weg_mut() {
                log_error!(weg.process_individual_win_event(event, &origin), event);
            }
        }
    }
}

pub fn init_win_event_hook_sanitizer() -> Result<()> {
    let mut dict = trace_lock!(WINDOW_DICT);
    dict.clear();
    WindowEnumerator::new().for_each_v2(|w| {
        dict.insert(w.address(), WindowCachedData::from(&w));
    })?;

    // this should be the first subscription or it will not work correctly
    HookManager::subscribe(|(event, origin)| match event {
        WinEvent::ObjectCreate => {
            let mut dict = trace_lock!(WINDOW_DICT);
            dict.insert(origin.address(), WindowCachedData::from(&origin));
        }
        WinEvent::ObjectDestroy => {
            let mut dict = trace_lock!(WINDOW_DICT);
            dict.remove(&origin.address());
        }
        _ => {}
    });
    Ok(())
}

pub fn register_win_hook() -> Result<()> {
    log::trace!("Registering Windows and Virtual Desktop Hooks");

    spawn_named_thread("WinEventHook", move || unsafe {
        SetWinEventHook(
            EVENT_MIN,
            EVENT_MAX,
            None,
            Some(HookManager::raw_win_event_hook_recv),
            0,
            0,
            0,
        );

        init_win_event_hook_sanitizer().expect("Failed to init win event hook sanitizer");

        HookManager::subscribe(|(event, mut origin)| {
            if event == WinEvent::SystemForeground {
                origin = Window::get_foregrounded(); // sometimes event is emited with wrong origin
            }

            HookManager::process_event(event, origin);
            if let Ok(synthetics) = event.get_synthetics(&origin) {
                for synthetic_event in synthetics {
                    HookManager::process_event(synthetic_event, origin)
                }
            }
        });

        let mut msg: MSG = MSG::default();
        while GetMessageW(&mut msg, None, 0, 0).as_bool() {
            let _ = TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    })?;

    let (sender, receiver) = std::sync::mpsc::channel::<VirtualDesktopEvent>();
    get_vd_manager().listen_events(sender)?;
    spawn_named_thread("VirtualDesktopEventHook", move || {
        for event in receiver {
            log_error!(process_vd_event(event))
        }
    })?;

    spawn_named_thread("MouseEventHook", || {
        let handle = get_app_handle();
        let mut last_pos = Point::default();
        loop {
            if let Ok(pos) = Mouse::get_cursor_pos() {
                if last_pos != pos {
                    let _ = handle.emit(SeelenEvent::GlobalMouseMove, &[pos.get_x(), pos.get_y()]);
                    last_pos = pos;
                }
            }
            std::thread::sleep(Duration::from_millis(66)); // 15 FPS
        }
    })?;

    Ok(())
}

pub fn process_vd_event(event: VirtualDesktopEvent) -> Result<()> {
    if FULL_STATE.load().is_window_manager_enabled() {
        log_error!(WindowManagerV2::process_vd_event(&event));
    }

    match event {
        VirtualDesktopEvent::DesktopCreated(_)
        | VirtualDesktopEvent::DesktopDestroyed {
            destroyed: _,
            fallback: _,
        }
        | VirtualDesktopEvent::DesktopMoved {
            desktop: _,
            old_index: _,
            new_index: _,
        }
        | VirtualDesktopEvent::DesktopNameChanged(_, _) => {
            let desktops = get_vd_manager()
                .get_all()?
                .iter()
                .map(|d| d.as_serializable())
                .collect_vec();
            get_app_handle().emit(SeelenEvent::WorkspacesChanged, &desktops)?;
        }

        VirtualDesktopEvent::DesktopChanged { new, old: _ } => {
            get_app_handle().emit(SeelenEvent::ActiveWorkspaceChanged, new.id())?;
        }
        VirtualDesktopEvent::WindowChanged(window) => {
            let hwnd = HWND(window as _);
            if WindowsApi::is_window(hwnd) {
                if let Some(config) = FULL_STATE.load().get_app_config_by_window(hwnd) {
                    let vd = get_vd_manager();
                    if config.options.contains(&AppExtraFlag::Pinned)
                        && !vd.is_pinned_window(window)?
                    {
                        vd.pin_window(window)?;
                    }
                }
            }
        }
        _ => {}
    }

    Ok(())
}
