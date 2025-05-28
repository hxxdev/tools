docker run \
  -v $(pwd)/out:/out \
  kitty-centos:latest \
  /bin/bash -c "cp /usr/local/bin/kitty* /out/ | cp /usr/local/bin/strip-ansi-escapes /out/"
