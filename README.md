# net
in-memory graph database written with C

Highlights:
* code covered with unit tests
* fast and clean node removal
* fast export to dump file
* reusing identifies
* FastCGI
* Docker container

Dependencies:
* [kcgi](https://kristaps.bsd.lv/kcgi/)

Operations:
* create node
* remove node
* connect nodes
* disconnect nodes
* show connections of a node

Build with:
```bash
cd ./source
make --always-make
```
Run tests with:
```bash
cd ./tests
make --always-make
```