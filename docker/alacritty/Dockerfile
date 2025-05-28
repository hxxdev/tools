FROM centos:8 AS builder

# Use CentOS 8 vault repo (CentOS 8 is EOL)
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools and EPEL for extra packages
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

# Install dependencies for building Alacritty
RUN dnf install -y \
    git gcc gcc-c++ make cmake pkgconfig \
    freetype-devel fontconfig-devel \
    mesa-libGL-devel mesa-libEGL-devel \
    libxcb-devel xcb-util-devel xcb-util-wm-devel xcb-util-keysyms-devel \
    python3 python3-pip \
    cairo-devel pango-devel \
    glib2-devel \
    zlib-devel \
    libxkbcommon-devel \
    dbus-devel \
    libXi-devel \
    libXi

# Install Rust via rustup
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Clone Alacritty repo
RUN git clone https://github.com/alacritty/alacritty.git /alacritty
WORKDIR /alacritty

# Build release version
RUN cargo build --release

# Stage 2: runtime image
FROM centos:8 AS final

# Use vault repo
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools and EPEL
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

# Runtime dependencies for Alacritty
RUN dnf install -y \
    freetype fontconfig \
    mesa-libGL mesa-libEGL \
    libxcb xcb-util xcb-util-wm xcb-util-keysyms \
    python3 \
    cairo pango \
    glib2 \
    libxkbcommon \
    dbus \
    zlib \
    libXcursor \
    libxkbcommon-x11 \
    mesa-dri-drivers \
    mesa-libGL mesa-libGLU mesa-libEGL mesa-dri-drivers libglvnd libglvnd-glx libX11 libXext libXdamage libxshmfence libXxf86vm \
    xorg-x11-server-Xvfb \
    libXi && \
    dnf clean all

#ENV DISPLAY=:99
#ENV LIBGL_ALWAYS_SOFTWARE=1

COPY --from=builder /alacritty/target/release/alacritty /usr/local/bin/alacritty
#CMD Xvfb :99 -screen 0 1024x768x24 & \
#    /usr/local/bin/alacritty
CMD Xvfb :99 -screen 0 1024x768x24 & \
    DISPLAY=:99 LIBGL_ALWAYS_SOFTWARE=1 /usr/local/bin/alacritty

