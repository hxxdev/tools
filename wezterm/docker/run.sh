docker run -it \
  --env DISPLAY=$DISPLAY \
  --volume /tmp/.X11-unix:/tmp/.X11-unix \
  wezterm-centos \
  /usr/local/bin/wezterm
