FROM ubuntu:24.04 AS base

ARG DEBIAN_FRONTEND=noninteractive
COPY setup-dbg-debs.sh /setup-dbg-debs.sh
RUN bash -x setup-dbg-debs.sh
RUN apt-get update && \
    apt-get install -y sudo fish zsh nano vim cmake g++ pip wget git zip \
    lldb-14 gdb \
    llvm-14-dev llvm-14-tools clang-14 jq \
    csmith creduce libcsmith-dev \
    clang-format llvm-18-dev \
    llvm-14-dbgsym llvm-14-dev-dbgsym llvm-14-tools-dbgsym llvm-14-runtime-dbgsym clang-14-dbgsym valgrind

# The creduce shipped by ubuntu is broken and linked against the wrong LLVM version.
# This is just a source rebuild.
# In theory we could also rebuild this from source, but it takes a while to
# build and the debian build system is shit.
COPY install-creduce.sh /install-creduce.sh
RUN bash -x /install-creduce.sh ; rm /install-creduce.sh

RUN userdel -r ubuntu && useradd coco -u 1000 -m -s /bin/bash && echo "coco ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN pip3 install --break-system-packages lark llvmlite

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-14 40
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-14 40

USER coco
ENV LLVM_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-14
