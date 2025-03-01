import { debounce } from 'lodash';
import { PropsWithChildren, useCallback, useEffect, useRef, useState } from 'react';
import { useSelector } from 'react-redux';

import { BackgroundByLayersV2 } from '../../../../seelenweg/components/BackgroundByLayers/infra';

import { selectDefaultOutput } from '../application';

import { AnimatedPopover } from '../../../../shared/components/AnimatedWrappers';
import { Icon } from '../../../../shared/components/Icon';
import { useWindowFocusChange } from '../../../../shared/hooks';
import { MediaMixerView } from './DeviceView';
import { MediaMainView } from './MainView';
import { VolumeControl } from './VolumeControl';

import './index.css';

function MediaControls() {
  const [deviceId, setDeviceId] = useState<string | null>(null);
  const [view, setView] = useState<string>('main');

  return (
    <BackgroundByLayersV2 className="media-control" onContextMenu={(e) => e.stopPropagation()}>
      {view === 'main' || !deviceId ? (
        <MediaMainView
          setViewDeviceId={(id) => {
            setDeviceId(id);
            setView('mixer');
          }}
        />
      ) : (
        <MediaMixerView deviceId={deviceId} onBack={() => setView('main')} />
      )}
    </BackgroundByLayersV2>
  );
}

export interface MediaControlProps extends PropsWithChildren {
  setActive: (value: boolean) => void;
}

export function WithMediaControls({ children, setActive }: MediaControlProps) {
  const [openControls, setOpenControls] = useState(false);
  const [openNotifier, setOpenNotifier] = useState(false);

  const defaultOutput = useSelector(selectDefaultOutput);

  const firstLoad = useRef(true);

  const closeVolumeNotifier = useCallback(
    debounce(() => setOpenNotifier(false), 2000),
    [],
  );

  useEffect(() => {
    setActive(openControls || openNotifier);
  }, [openControls || openNotifier]);

  useEffect(() => {
    if (!defaultOutput) {
      return;
    }

    if (firstLoad.current) {
      firstLoad.current = false;
      return;
    }

    if (!openControls && !openNotifier) {
      setOpenNotifier(true);
    }
    closeVolumeNotifier();
  }, [defaultOutput?.volume]);

  useWindowFocusChange((focused) => {
    if (!focused) {
      setOpenControls(false);
    }
  });

  return (
    <AnimatedPopover
      animationDescription={{
        openAnimationName: 'media-open',
        closeAnimationName: 'media-close',
      }}
      open={openControls}
      trigger="click"
      onOpenChange={(open) => {
        setOpenControls(open);
        if (open) {
          setOpenNotifier(false);
        }
      }}
      arrow={false}
      content={<MediaControls />}
      destroyTooltipOnHide
    >
      <AnimatedPopover
        animationDescription={{
          openAnimationName: 'media-notifier-open',
          closeAnimationName: 'media-notifier-close',
        }}
        open={openNotifier}
        arrow={false}
        trigger={[]}
        destroyTooltipOnHide
        content={
          <BackgroundByLayersV2
            className="media-notifier"
            onContextMenu={(e) => e.stopPropagation()}
          >
            {defaultOutput && (
              <VolumeControl
                value={defaultOutput.volume}
                deviceId={defaultOutput.id}
                icon={
                  <Icon
                    iconName={defaultOutput.muted ? 'IoVolumeMuteOutline' : 'IoVolumeHighOutline'}
                  />
                }
                withPercentage={true}
              />
            )}
          </BackgroundByLayersV2>
        }
      >
        {children}
      </AnimatedPopover>
    </AnimatedPopover>
  );
}
