FROM ubuntu:18.04

RUN apt-get update \
    && apt-get -y upgrade \
    && apt-get -y install make build-essential git jq curl ansible

RUN echo "deb [arch=amd64] https://packages.microsoft.com/repos/azure-cli/ bionic main" | tee /etc/apt/sources.list.d/azure-cli.list

RUN curl -o microsoft.asc https://packages.microsoft.com/keys/microsoft.asc \
    && apt-key add microsoft.asc \
    && apt-get update \
    && apt-get -y install apt-transport-https azure-cli

RUN curl -o /usr/bin/oe-engine https://oejenkins.blob.core.windows.net/oejenkins/oe-engine \
    && chmod +x /usr/bin/oe-engine
RUN useradd --create-home -u 1001 azureuser
