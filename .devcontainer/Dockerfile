# Available versions: https://github.com/devcontainers/images/tree/main/src/cpp
FROM mcr.microsoft.com/devcontainers/cpp:ubuntu24.04

# Container arguments
ARG BOOST_VERSION=1.86.0

# Add additional packages
RUN apt update && apt install -y python3-venv binutils-dev

# Set the locale
RUN locale-gen en_US.UTF-8

