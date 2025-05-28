FROM centos:8 AS builder

# Use CentOS 8 vault repository (since CentOS 8 is EOL)
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools and EPEL for extra packages
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

# Install build dependencies
RUN dnf install -y \
    git gcc gcc-c++ make cmake pkgconfig \
    python3 python3-devel python3-pip \
    libX11-devel libXcursor-devel libXrandr-devel libXext-devel \
    libXi-devel libXinerama-devel libXScrnSaver-devel \
    freetype-devel harfbuzz-devel fontconfig-devel \
    wayland-devel mesa-libEGL-devel mesa-libGL-devel \
    mesa-dri-drivers libxkbcommon-devel dbus-devel \
    libxkbcommon-x11-devel systemd-devel lcms2-devel cairo-devel wayland-protocols-devel
# upgrade wayland
RUN curl -L -o wayland-protocols-1.23.tar.gz "https://gitlab.freedesktop.org/wayland/wayland-protocols/-/archive/1.23.tar.gz?ref=1.23" && \
    tar xf wayland-protocols-1.23.tar.gz && \
    cd wayland-protocols-1.23 && \
    ./configure --prefix=/usr && \
    make && make install

# xxhash
RUN git clone https://github.com/Microsoft/vcpkg.git && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh && \
    ./vcpkg integrate install && \
    ./vcpkg install xxhash
ENV PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig:$PKG_CONFIG_PATH
ENV VCPKG_ROOT=/vcpkg
ENV VCPKG_DEFAULT_TRIPLET=x64-linux
ENV PKG_CONFIG_PATH=$VCPKG_ROOT/installed/$VCPKG_DEFAULT_TRIPLET/lib/pkgconfig:$PKG_CONFIG_PATH
ENV LD_LIBRARY_PATH=$VCPKG_ROOT/installed/$VCPKG_DEFAULT_TRIPLET/lib:$LD_LIBRARY_PATH

# Python 3.9
RUN dnf install -y gcc openssl-devel bzip2-devel libffi-devel xz-devel wget make
# Build Python 3.10.10 from source
RUN cd /usr/src && \
    wget https://www.python.org/ftp/python/3.10.10/Python-3.10.10.tgz && \
    tar xzf Python-3.10.10.tgz && \
    cd Python-3.10.10 && \
    ./configure --enable-optimizations && \
    make -j$(nproc) && make altinstall
RUN alternatives --install /usr/bin/python3 python3 /usr/local/bin/python3.10 2
RUN alternatives --set python3 /usr/local/bin/python3.10
RUN python3 -m ensurepip
RUN python3 -m pip install --upgrade pip setuptools wheel

# System Nerd Font
RUN mkdir -p /usr/share/fonts/nerd-fonts && \
    cd /usr/share/fonts/nerd-fonts && \
    wget https://github.com/ryanoasis/nerd-fonts/releases/download/v3.1.1/SymbolsNerdFontMono-Regular.ttf && \
    fc-cache -fv

# Clone kitty
RUN git clone https://github.com/kovidgoyal/kitty.git /kitty
WORKDIR /kitty

# Build kitty
RUN make

# Stage 2: Runtime image
FROM centos:8 AS final

# Use CentOS 8 vault repo
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

# Install runtime dependencies
RUN dnf install -y \
    libX11 libXcursor libXrandr libXext \
    libXi libXinerama libXScrnSaver \
    freetype fontconfig harfbuzz \
    wayland libxkbcommon libxkbcommon-x11 \
    mesa-libEGL mesa-libGL mesa-dri-drivers \
    dbus systemd-libs \
    python3 && \
    dnf clean all

COPY --from=builder /kitty/kitty /usr/local/bin/kitty
COPY --from=builder /kitty/terminfo /usr/local/share/terminfo
COPY --from=builder /kitty/launcher/kitty.desktop /usr/share/applications/
COPY --from=builder /kitty/launcher/kitty.png /usr/share/icons/

CMD ["/bin/bash"]

