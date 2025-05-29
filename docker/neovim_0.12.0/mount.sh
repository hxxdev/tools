docker run \
  -v $(pwd)/out:/out \
  neovim-centos:latest \
  /bin/bash -c "cp /usr/local/bin/neovim* /out/"
