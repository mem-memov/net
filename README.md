# net
in-memory graph database written with C

Highlights:
* code covered with unit tests
* fast and clean node removal
* fast export to dump file
* reusing identifies
* Docker container

Requirements:
* Linux

Dependencies:
* pthread

Operations:
* create node
* remove node
* connect nodes
* disconnect nodes
* show connections of a node

Build with:
```bash
sudo make --always-make install
```
Run tests with:
```bash
make --always-make test
```