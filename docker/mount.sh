docker run \
  -v $(pwd)/out:/out \
  wezterm-centos:latest \
  /bin/bash -c "cp /usr/local/bin/wezterm* /out/ | cp /usr/local/bin/strip-ansi-escapes /out/"
