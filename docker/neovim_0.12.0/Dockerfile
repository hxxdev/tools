# Stage 1: Build Neovim
FROM centos:8 AS builder

# Switch to vault repo (CentOS 8 is EOL)
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools repo and EPEL for extra packages
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

# Install build dependencies
RUN dnf update -y && \
    dnf install -y \
    gcc gcc-c++ make cmake \
    ninja-build \
    gettext \
    libtool \
    autoconf \
    automake \
    pkgconfig \
    unzip \
    curl \
    git \
    tar && \
    dnf clean all

# Clone Neovim source
RUN git clone https://github.com/neovim/neovim.git /neovim
WORKDIR /neovim

# Optionally checkout a specific stable version
# RUN git checkout stable

# Build Neovim
RUN make CMAKE_BUILD_TYPE=RelWithDebInfo CMAKE_INSTALL_PREFIX=/usr/local

# Install into /usr/local (staged install)
RUN make install

# Stage 2: Runtime image
FROM centos:8

# Switch to vault repo
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Enable PowerTools repo and EPEL for extra packages
RUN dnf install -y dnf-plugins-core && \
    dnf config-manager --set-enabled powertools && \
    dnf install -y epel-release && \
    dnf update -y && dnf makecache

RUN dnf update -y && \
    dnf install -y \
    libstdc++ \
    libtool-ltdl \
    ncurses \
    gettext && \
    dnf clean all

# clipboard
RUN dnf install -y xclip xsel xclip

# Copy the built Neovim binary and support files
COPY --from=builder /usr/local /usr/local

CMD ["nvim"]

