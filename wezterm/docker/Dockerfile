FROM centos:8 AS builder
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools repo and EPEL for extra packages
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

RUN dnf search wayland
RUN dnf search xcb 

# Install build dependencies
RUN dnf install -y \
    git make gcc gcc-c++ perl curl \
    xcb-util-devel xcb-util-keysyms-devel xcb-util-image-devel xcb-util-wm-devel \
    libxkbcommon-devel libxkbcommon-x11-devel wayland-devel mesa-libEGL-devel \
    flatpak-builder xcb-util-image libX11 libXcursor libXrandr libxcb libxkbcommon xcb-util-keysyms \
    xcb-util-image \
    xcb-util \
    libxcb \
    libX11-xcb \
    libX11 \
    libxkbcommon \
    libxkbcommon-x11 \
    libwayland-egl \
    libwayland-client \
    fontconfig \
    wayland-devel \
    freetype fontconfig mesa-dri-drivers mesa-libGL libXrender libXext libXft

# Rust installation
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Clone wezterm repo
RUN git clone https://github.com/wez/wezterm.git /wezterm
WORKDIR /wezterm

# Build wezterm
RUN ./get-deps || true && \
    make build BUILD_OPTS="--release"
FROM centos:8 AS final

# Use vault repo (CentOS 8 is EOL)
RUN sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN dnf search wayland
RUN dnf search xcb 

# Add runtime dependencies
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache
RUN dnf install -y \
        xcb-util-image \
        xcb-util \
        libxcb \
        libX11-xcb \
        libX11 \
        libxkbcommon \
        libxkbcommon-x11 \
        mesa-libEGL \
        freetype \
        fontconfig \
        libXrender \
        wayland-devel \
        libwayland-egl \
        egl-wayland \
        libwayland-client \
        libXext \
        libXft \
    && dnf clean all

COPY /wezterm/target/release/wezterm /usr/local/bin/
COPY /wezterm/target/release/wezterm-gui /usr/local/bin/
COPY /wezterm/target/release/wezterm-mux-server /usr/local/bin/
COPY /wezterm/target/release/strip-ansi-escapes /usr/local/bin/


CMD ["/bin/bash"]

