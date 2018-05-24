FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes install build-essential && \
    mkdir net

COPY . net
    
RUN cd net && \
    make --always-make install

EXPOSE 43152

CMD netserver --port=43152 --connections=10 --buffer=8192 --threads=4
