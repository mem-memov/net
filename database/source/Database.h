#ifndef DATABASE_H
#define DATABASE_H

struct Database;

struct Database * Database_construct();

void Database_destruct(struct Database * this);

#endif