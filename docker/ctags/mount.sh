docker run \
  -v $(pwd)/out:/out \
  ctags-centos:latest \
  /bin/bash -c "cp /usr/local/bin/ctags* /out/"
