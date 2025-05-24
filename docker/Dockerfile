FROM almalinux:8 AS builder

# Vault repo 세팅 (기존 미러 dead 문제 대응)
#RUN sed -i 's|mirrorlist=|#mirrorlist=|g' /etc/yum.repos.d/CentOS-*.repo && \
#    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*.repo

RUN dnf clean all && dnf makecache

# 필수 개발 도구 및 EPEL 설치
RUN dnf install -y epel-release && \
    dnf update -y && dnf makecache
RUN dnf config-manager --set-enabled powertools
#RUN dnf config-manager --set-enabled codeready-builder-for-rhel-8-$(arch)-rpms

RUN dnf search perl
RUN dnf search xcb

# 필요한 기본 라이브러리 설치
RUN dnf install -y \
    wayland-devel git cmake gcc gcc-c++ fontconfig-devel freetype-devel \
    libxcb-devel libxkbcommon-devel libX11-devel libXcursor-devel libtool \
    libXrandr-devel libXi-devel curl openssl-devel mesa-libGL-devel \
    zlib-devel wget pkgconfig python3 autoconf automake perl-core \
    xcb-util xcb-util-devel xcb-util-renderutil libX11-xcb libxcb-devel xcb-util-image xcb-util-keysyms xcb-util-wm libxcb

# xorg-util-macros 설치 (xcb-util 의존)
#RUN curl -LO https://xorg.freedesktop.org/releases/individual/util/util-macros-1.19.3.tar.gz && \
#    tar xf util-macros-1.19.3.tar.gz && \
#    cd util-macros-1.19.3 && ./configure && make && make install

ENV ACLOCAL_PATH=/usr/local/share/aclocal

# libxcb-util 소스 빌드
#RUN git clone --recurse-submodules https://gitlab.freedesktop.org/xorg/lib/libxcb-util.git && \
#    cd libxcb-util && ./autogen.sh && make && make install
RUN ls /usr/share/doc/xcb-util
# pkgconfig 경로 환경변수 설정
ENV PKG_CONFIG_PATH="/usr/local/lib:/usr/share/doc:/usr/local/lib64/pkgconfig:/usr/local/lib/pkgconfig:/usr/lib64/pkgconfig:/usr/lib/pkgconfig:$PKG_CONFIG_PATH"
RUN pkg-config --list-all
# Rust 설치 (rustup)
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# wezterm 클론 & 빌드
RUN git clone https://github.com/wez/wezterm.git /wezterm
WORKDIR /wezterm

RUN ./get-deps || true && \
    cargo build --release

FROM almalinux:8 AS final
COPY --from=builder /wezterm/target/release/wezterm /usr/local/bin/wezterm
CMD ["/bin/bash"]

