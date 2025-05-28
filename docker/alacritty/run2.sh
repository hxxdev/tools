#!/bin/bash
xhost +local:docker  # allow X11


docker run -it alacritty-centos:latest
