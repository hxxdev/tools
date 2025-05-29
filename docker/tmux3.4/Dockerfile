FROM centos:8 AS builder

# Use vault repo since CentOS 8 is EOL
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Install build dependencies
RUN dnf update -y && \
    dnf install -y \
    gcc make automake autoconf pkgconfig \
    libevent-devel ncurses-devel git \
    bison && \
    dnf clean all

# Clone and build tmux
RUN git clone --branch 3.4 --depth 1 https://github.com/tmux/tmux.git /tmux
WORKDIR /tmux

RUN sh autogen.sh && \
    ./configure && \
    make -j$(nproc)

# Final runtime image
FROM centos:8

# Use vault repo
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN dnf update -y && \
    dnf install -y \
    libevent ncurses && \
    dnf clean all

COPY --from=builder /tmux/tmux /usr/local/bin/tmux

CMD ["tmux"]

