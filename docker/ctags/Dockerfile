FROM centos:8 AS builder

# Use vault repo since CentOS 8 is EOL
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Install build dependencies
RUN dnf update -y && \
    dnf install -y \
    gcc make autoconf automake pkgconfig \
    libtool git \
    python3 \
    && dnf clean all

# Clone and build ctags
RUN git clone https://github.com/universal-ctags/ctags.git /ctags
WORKDIR /ctags

RUN ./autogen.sh && \
    ./configure && \
    make -j$(nproc)

# Final runtime image
FROM centos:8

# Use vault repo
RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN dnf update -y && \
    dnf install -y \
    libtool-ltdl \
    python3 \
    && dnf clean all

COPY --from=builder /ctags/ctags /usr/local/bin/ctags

CMD ["ctags", "--version"]

