FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes install git && \
    apt-get --assume-yes install build-essential && \
    git clone https://github.com/mem-memov/net.git && \
    cd net && \
    make --always-make install && \
    apt-get --assume-yes purge git && \
    apt-get --assume-yes purge build-essential

EXPOSE 43152

CMD netserver -p 5000 -c 10 -b 8192 -t 4
