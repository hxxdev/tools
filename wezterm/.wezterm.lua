
local wezterm = require 'wezterm'
local config = wezterm.config_builder()
function scheme_for_appearance(appearance)
  if appearance:find "Dark" then
    return "Catppuccin Mocha"
  else
    return "Catppuccin Latte"
  end
end
-- Default
config.default_prog = { "wsl.exe" }
config.default_domain = 'WSL:Ubuntu-24.04'
-- Tabs
config.hide_tab_bar_if_only_one_tab = false
config.tab_bar_at_bottom = false
config.show_new_tab_button_in_tab_bar = true
config.use_fancy_tab_bar = false
-- Background
config.window_background_opacity = 0.15
config.window_background_image = '\\\\wsl.localhost\\Ubuntu-24.04\\home\\hxxdev\\dev\\tools\\wallpapers\\Nord-niivu-UNSPLASH-IGN_11.jpg'
-- Themes
config.colors = {
  -- The default text color
  --foreground = 'silver',
  -- The default background color
  background = 'black',

  -- Overrides the cell background color when the current cell is occupied by the
  -- cursor and the cursor style is set to Block
  cursor_bg = '#52ad70',
  -- Overrides the text color when the current cell is occupied by the cursor
  cursor_fg = 'black',
  -- Specifies the border color of the cursor when the cursor style is set to Block,
  -- or the color of the vertical or horizontal bar when the cursor style is set to
  -- Bar or Underline.
  cursor_border = '#52ad70',

  -- the foreground color of selected text
  selection_fg = 'black',
  -- the background color of selected text
  selection_bg = '#fffacd',

  -- The color of the scrollbar "thumb"; the portion that represents the current viewport
  scrollbar_thumb = '#222222',

  -- The color of the split lines between panes
  split = '#444444',

  ansi = {
    'black',
    'maroon',
    'green',
    'olive',
    'navy',
    'purple',
    'teal', 
    'silver',
  },
--   brights = {
--     'grey', -- files
--     'red', -- warnings
--     'lime', -- commands
--     'yellow', -- important text
--     '#4F7399', -- directories
--     'fuchsia', -- usually less used, no direct ls mapping
--     'aqua', -- symbolic links in `ls
--     'white', -- default bright foreground
--   }, 
  brights = {
  '#d67ba8',  -- grey (used here for username segment – soft rose pink)
  '#e69761',  -- red (used for `/tools` – warm peach)
  '#ebcb8b',  -- lime (used for `main` – creamy pastel yellow)
  '#a3be8c',  -- yellow (used for `!?` – soft green)
  '#b48ead',  -- fuchsia (used in separators – lavender purple)
  '#88c0d0',  -- blue (used for `base` – muted sky blue)
  '#81a1c1',  -- aqua (used for right side – powder blue)
  '#d8dee9',  -- white (text – light icy white)
  },

  -- Arbitrary colors of the palette in the range from 16 to 255
  indexed = { [136] = '#af8700' },

  -- Since: 20220319-142410-0fcdea07
  -- When the IME, a dead key or a leader key are being processed and are effectively
  -- holding input pending the result of input composition, change the cursor
  -- to this color to give a visual cue about the compose state.
  compose_cursor = 'orange',

  -- Colors for copy_mode and quick_select
  -- available since: 20220807-113146-c2fee766
  -- In copy_mode, the color of the active text is:
  -- 1. copy_mode_active_highlight_* if additional text was selected using the mouse
  -- 2. selection_* otherwise
  copy_mode_active_highlight_bg = { Color = '#000000' },
  -- use `AnsiColor` to specify one of the ansi color palette values
  -- (index 0-15) using one of the names "Black", "Maroon", "Green",
  --  "Olive", "Navy", "Purple", "Teal", "Silver", "Grey", "Red", "Lime",
  -- "Yellow", "Blue", "Fuchsia", "Aqua" or "White".
  copy_mode_active_highlight_fg = { AnsiColor = 'Black' },
  copy_mode_inactive_highlight_bg = { Color = '#52ad70' },
  copy_mode_inactive_highlight_fg = { AnsiColor = 'White' },

  quick_select_label_bg = { Color = 'peru' },
  quick_select_label_fg = { Color = '#ffffff' },
  quick_select_match_bg = { AnsiColor = 'Navy' },
  quick_select_match_fg = { Color = '#ffffff' },

  input_selector_label_bg = { AnsiColor = 'Black' }, -- (*Since: Nightly Builds Only*)
  input_selector_label_fg = { Color = '#ffffff' }, -- (*Since: Nightly Builds Only*)

  launcher_label_bg = { AnsiColor = 'Black' }, -- (*Since: Nightly Builds Only*)
  launcher_label_fg = { Color = '#ffffff' }, -- (*Since: Nightly Builds Only*)
}
config.font = wezterm.font("Hack Nerd Font", { weight = "Regular", italic = false })
config.color_scheme = scheme_for_appearance(wezterm.gui.get_appearance())
config.font_size = 16

-- Key Bindings
config.leader = { key="b", mods="CTRL" }
config.keys = {
    { key = "a", mods = "LEADER|CTRL",  action=wezterm.action{SendString="\x01"}},
    { key = "-", mods = "LEADER",       action=wezterm.action{SplitVertical={domain="CurrentPaneDomain"}}},
    { key = "\\",mods = "LEADER",       action=wezterm.action{SplitHorizontal={domain="CurrentPaneDomain"}}},
    { key = '%', mods = "LEADER|SHIFT", action=wezterm.action{SplitVertical={domain="CurrentPaneDomain"}}},
    { key = '"', mods = "LEADER|SHIFT", action=wezterm.action{SplitHorizontal={domain="CurrentPaneDomain"}}},
    { key = "o", mods = "LEADER",       action="TogglePaneZoomState" },
    { key = "z", mods = "LEADER",       action="TogglePaneZoomState" },
    { key = "c", mods = "LEADER",       action=wezterm.action{SpawnTab="CurrentPaneDomain"}},
    { key = "h", mods = "LEADER",       action=wezterm.action{ActivatePaneDirection="Left"}},
    { key = "j", mods = "LEADER",       action=wezterm.action{ActivatePaneDirection="Down"}},
    { key = "k", mods = "LEADER",       action=wezterm.action{ActivatePaneDirection="Up"}},
    { key = "l", mods = "LEADER",       action=wezterm.action{ActivatePaneDirection="Right"}},
    { key = "H", mods = "LEADER|SHIFT", action=wezterm.action{AdjustPaneSize={"Left", 5}}},
    { key = "J", mods = "LEADER|SHIFT", action=wezterm.action{AdjustPaneSize={"Down", 5}}},
    { key = "K", mods = "LEADER|SHIFT", action=wezterm.action{AdjustPaneSize={"Up", 5}}},
    { key = "L", mods = "LEADER|SHIFT", action=wezterm.action{AdjustPaneSize={"Right", 5}}},
    { key = 'h', mods = 'ALT',          action=wezterm.action.ActivatePaneDirection 'Left'},
    { key = 'l', mods = 'ALT',          action=wezterm.action.ActivatePaneDirection 'Right'},
    { key = 'k', mods = 'ALT',          action=wezterm.action.ActivatePaneDirection 'Up'},
    { key = 'j', mods = 'ALT',          action=wezterm.action.ActivatePaneDirection 'Down'},
    { key = "1", mods = "LEADER",       action=wezterm.action{ActivateTab=0}},
    { key = "2", mods = "LEADER",       action=wezterm.action{ActivateTab=1}},
    { key = "3", mods = "LEADER",       action=wezterm.action{ActivateTab=2}},
    { key = "4", mods = "LEADER",       action=wezterm.action{ActivateTab=3}},
    { key = "5", mods = "LEADER",       action=wezterm.action{ActivateTab=4}},
    { key = "6", mods = "LEADER",       action=wezterm.action{ActivateTab=5}},
    { key = "7", mods = "LEADER",       action=wezterm.action{ActivateTab=6}},
    { key = "8", mods = "LEADER",       action=wezterm.action{ActivateTab=7}},
    { key = "9", mods = "LEADER",       action=wezterm.action{ActivateTab=8}},
    { key = "&", mods = "LEADER|SHIFT", action=wezterm.action{CloseCurrentTab={confirm=true}}},
    { key = "d", mods = "LEADER",       action=wezterm.action{CloseCurrentPane={confirm=true}}},
    { key = "x", mods = "LEADER",       action=wezterm.action{CloseCurrentPane={confirm=true}}}
}

return config