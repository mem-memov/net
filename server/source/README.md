# ndb-server

The database server gives you the ability to store a graph of connected nodes.

### Installation

First you need to instal the [ndb](https://github.com/mem-memov/ndb#ndb) library. Then procceed as follows:

```
cd repos/
git clone https://github.com/mem-memov/ndb-server
cd ndb-server/
make
sudo make install
```

To uninstall run:
```
sudo make uninstall
```

### Usage

Start the server in the directory where you are going to keep the data file.

```
cd ~
ndb-server
```
This command brings some help information to your screen as well:

```
Node Database Server is running:
 port(1): 43152.
 maximum connections(2): 10
 buffer size(3): 8192 bytes
Commands:
 create
 read my_id
 connect my_from_id my_to_id
 intersect my_id_1 my_id_2 ...
 union my_id_1 my_id_2 ...
 difference my_id_1 my_id_2 ...
 insiders my_container_id my_id_1 my_id_2 ...
 outsiders my_container_id my_id_1 my_id_2 ...
 exit
Source code: https://github.com/mem-memov/ndb-server
Press Ctrl+C to stop this server.

```

As you can see you can tweak some parameters. Pass them as arguments. Argument positions are given in parentesis.

Open a new terminal and start telnet.

```
u@upc ~ $ telnet 127.0.0.1 43152
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
create
1
create
3
create
5
connect 1 3

connect 5 3

read 1
3
intersect 1 5
3
exit
Connection closed by foreign host.
u@upc ~ $ 
```

To stop the server you can press the combination of keys Ctrl+C.

To work with multiple databases start the server in different directiories with different port numbers:
```
cd ~/userdb
ndb-server 4444

```

You can download a PHP (7.1) client for this database from [Composer Packagest](https://packagist.org/packages/mem-memov/ndb-php).
```
"mem-memov/ndb-php": "dev-master"
```
