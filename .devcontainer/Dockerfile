# Available versions: https://github.com/devcontainers/images/tree/main/src/cpp
FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-22.04

# Container arguments
ARG BOOST_VERSION=1.86.0

# Add additional packages
RUN apt update && apt install -y clang-format

# Set the locale
RUN locale-gen en_US.UTF-8

# Install Boost
RUN cd /tmp && \
    BOOST_VERSION_MOD=$(echo $BOOST_VERSION | tr . _) && \
    wget https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    tar --bzip2 -xf boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    cd boost_${BOOST_VERSION_MOD} && \
    ./bootstrap.sh --prefix=/usr/local && \
    ./b2 install \
        --with-filesystem \
        --with-regex \
        --with-serialization \
        --build-type=minimal \
        --link=static && \
    cd /tmp && \
    rm -rf /tmp/boost_${BOOST_VERSION_MOD}
