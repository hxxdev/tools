docker run \
  -v $(pwd)/out:/out \
  alacritty-centos:latest \
  /bin/bash -c "cp /usr/local/bin/alacritty* /out/"
