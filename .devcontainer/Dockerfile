FROM mcr.microsoft.com/devcontainers/base:ubuntu26.04

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
        g++ \
        clangd \
        python3 \
        python3-venv \
        pipx \
    && rm -rf /var/lib/apt/lists/*

ENV PATH="/home/vscode/.local/bin:${PATH}"

USER vscode

RUN pipx install --include-deps online-judge-verify-helper \
    && pipx inject --force online-judge-verify-helper "setuptools<81"
