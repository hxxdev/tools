#!/bin/bash

mkdir -p out

docker run \
  -v $(pwd)/out:/out \
  tmux3.4-centos8:latest \
  /bin/bash -c "cp /usr/local/bin/tmux* /out/"
