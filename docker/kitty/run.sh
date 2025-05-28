xhost +local:docker  # allow X11

docker run -it \
  --env DISPLAY=$DISPLAY \
  --volume /tmp/.X11-unix:/tmp/.X11-unix \
  kitty-centos:latest \
  /usr/local/bin/kitty
