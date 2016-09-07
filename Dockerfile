FROM debian:testing

RUN apt-get update -yq
RUN apt-get install -y python3.5 python3.5-dev build-essential

RUN mkdir -p /tmp/build
WORKDIR /tmp/build
COPY python-unrtf /tmp/build
RUN python3.5 setup.py install
