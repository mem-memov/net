# net
in-memory graph store

Highlights:
    - no dependencies on external libraries
    - code covered with unit tests
    - fastest possible clean node removal
    - fast export to dump file
    - reusing identifies of removed nodes

Operations:
    - create node
    - remove node
    - connect nodes
    - disconnect nodes
    - show node connection

Build with:

    cd source
    make --always-make

Run tests with:

    cd tests
    make --always-make
