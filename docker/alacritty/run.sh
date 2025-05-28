#!/bin/bash

xhost +local:docker  # allow X11
# --env DISPLAY:=$DISPLAY \
LIBGL_ALWAYS_SOFTWARE=1 docker run -it \
  --volume /tmp/.X11-unix:/tmp/.X11-unix \
  alacritty-centos:latest \
  /usr/local/bin/alacritty
