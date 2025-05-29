# Stage 1: Build Neovide
FROM centos:8 AS builder

# Set up CentOS 8 vault repo (EOL workaround)
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable EPEL and PowerTools
RUN dnf install -y epel-release dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf update -y && dnf makecache --refresh
    
#RUN dnf module list gcc
RUN dnf install -y gcc-9 gcc-c++-9
#RUN dnf module enable gcc-toolset-9 && \
#    dnf install gcc-toolset-9
# Install build dependencies
RUN dnf install -y \
    git curl cmake make gcc gcc-c++ clang \
    freetype-devel fontconfig-devel libxcb-devel \
    xcb-util xcb-util-devel xcb-util-image xcb-util-image-devel \
    libxkbcommon-devel libxkbcommon-x11-devel \
    mesa-libEGL-devel mesa-libGL-devel \
    libX11-devel libXcursor-devel libXrandr-devel libXinerama-devel libXi-devel \
    pkgconfig python3 \
    && dnf clean all

# Install dependencies for building curl
RUN dnf install -y --allowerasing \
    libnghttp2-devel libcurl libssh2-devel openssl-devel

# Update FreeType 
RUN dnf install -y --allowerasing \
    gcc gcc-c++ make \
    harfbuzz-devel \
    libpng-devel \
    bzip2-devel \
    zlib-devel
WORKDIR /deps
RUN curl -LO https://download.savannah.gnu.org/releases/freetype/freetype-2.13.2.tar.gz \
    && tar -xzf freetype-2.13.2.tar.gz \
    && cd freetype-2.13.2 \
    && ./configure --prefix=/opt/freetype \
    && make -j$(nproc) \
    && make install

# GCC >= 9
RUN dnf module enable -y gcc-toolset-11 && \
    dnf install -y gcc-toolset-11
ENV PATH="/opt/rh/gcc-toolset-11/root/usr/bin:$PATH"

ENV PKG_CONFIG_PATH="/opt/freetype/lib/pkgconfig:$PKG_CONFIG_PATH"
ENV LD_LIBRARY_PATH="/opt/freetype/lib:$LD_LIBRARY_PATH"
# Install Rust
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Install cargo dependencies for GUI
RUN rustup target add x86_64-unknown-linux-gnu

# Build curl from source
WORKDIR /tmp
RUN curl -LO https://curl.se/download/curl-8.7.1.tar.gz && \
    tar -xzf curl-8.7.1.tar.gz && \
    cd curl-8.7.1 && \
    ./configure --with-ssl --prefix=/usr/local && \
    make -j$(nproc) && make install

# Ensure the new curl is used
ENV PATH="/usr/local/bin:$PATH"
RUN curl --version

# Clone Neovide
RUN git clone https://github.com/neovide/neovide.git /neovide
WORKDIR /neovide

# Optional: Checkout a stable version
# RUN git checkout tags/0.12.3 -b build

# Build Neovide in release mode
RUN cargo build --release

# Stage 2: Runtime image
FROM centos:8 AS final

# Vault repos
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN dnf install -y epel-release dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf update -y && dnf makecache

# Install runtime dependencies
RUN dnf install -y \
    libxcb \
    xcb-util xcb-util-image \
    libX11 libXcursor libXrandr libXinerama libXi \
    freetype fontconfig \
    libxkbcommon libxkbcommon-x11 \
    mesa-libEGL mesa-libGL mesa-dri-drivers \
    libglvnd libXdamage libxshmfence libXxf86vm \
    && dnf clean all

# Copy the Neovide binary
COPY --from=builder /neovide/target/release/neovide /usr/local/bin/neovide

# Entry point
CMD ["neovide"]

