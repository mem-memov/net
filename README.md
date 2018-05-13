# net
in-memory graph store written with C

Highlights:
* no dependencies on external libraries
* code covered with unit tests
* fast and clean node removal
* fast export to dump file
* reusing identifies of removed nodes

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