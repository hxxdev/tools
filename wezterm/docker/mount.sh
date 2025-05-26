docker run \
  -v $(pwd)/out:/out \
  wezterm-builder \
  cp /usr/local/bin/wezterm* /out/ | cp /usr/local/bin/strip-ansi-escapes /out/
