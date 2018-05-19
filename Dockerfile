FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes install git && \
    apt-get --assume-yes install build-essential && \
    git clone https://github.com/mem-memov/net.git && \
    cd net && \
    make --always-make

CMD ./netserver
