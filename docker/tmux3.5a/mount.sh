docker run \
  -v $(pwd)/out:/out \
  tmux-centos:latest \
  /bin/bash -c "cp /usr/local/bin/tmux* /out/"
