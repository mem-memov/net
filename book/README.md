Lifetime of A is equal to lifetime of B. B provides to A some helper functionality.




--------------------- source/B.h --------------------------
```c
#ifndef B_H
#define B_H

struct B;

struct B * B_construct();

void B_destruct(struct B * this);

void B_doSomthingElse(struct B * this);

#endif
```
--------------------- source/B.c --------------------------
```c
#include "B.h"

struct B
{
    
}

struct B * B_construct()
{
    struct B * this = malloc(sizeof(struct B));

    return this;
}

void B_destruct(struct B * this)
{
    free(this);
    this = NULL:
}

void B_doSomthingElse(struct B * this)
{

}
```
--------------------- source/A.h --------------------------
```c
#ifndef A_H
#define A_H

include "B.h"

struct A;

struct A * A_construct(struct B * b);

void A_destruct(struct A * this);

void A_doSomthing(struct A * this);

#endif
```
--------------------- source/A.c --------------------------
```c
#include "A.h"

struct A
{
    struct B * b;
}

struct A * A_construct(struct B * b)
{
    struct A * this = malloc(sizeof(struct A));

    this->b = b;

    return this;
}

void A_destruct(struct A * this)
{
    B_destruct(this->b);

    free(this);
    this = NULL:
}

void A_doSomthing(struct A * this)
{
    B_doSomthingElse(this->b);
}
```
--------------------- source/main.c --------------------------
```c
#include "A.h"

int main(int argc, char** argv)
{
    struct A * a = A_construct(B_construct());

    A_doSomthing(a);

    A_destruct(a);
}
```
--------------------- source/Makefile --------------------------
```Makefile
net: main.o A.o B.o
	gcc main.o A.o B.o -o application

main.o: main.c
	gcc -c main.c

A.o: A.c A.h
	gcc -c A.c

B.o: B.c B.h
	gcc -c B.c

clean:
	rm --force *.o application
```

```bash
cd source
make --always-make
./application
```




--------------------- tests/B.c --------------------------
```c
#include "../source/B.h"

#define B_MAX_CALLS 1

struct B
{
    char call;
    char * method[B_MAX_CALLS];
}

struct B * B_mock()
{
    struct B * this = malloc(sizeof(struct B));

    this->call = 0;

    char i;
    for (i = 0; i < B_MAX_CALLS; i++) {
            this->method[i] = "method not specified";
    }

    return this;
}

void B_destruct(struct B * this)
{
    free(this);
    this = NULL:
}

void B_doSomthingElse(struct B * this)
{
    this->method[this->call] = "B_doSomthingElse";

    this->call++;
}
```
--------------------- tests/main.c --------------------------
```c
#include <stdlib.h>
#include "../source/A.c"

struct A * a;

void prepareTest()
{
    b = B_mock();
    a = A_construct(b);
}

void demolishTest()
{
    A_destruct(a);
}

void it_uses_b()
{
    prepareTest();

    A_doSomthing(a);

    assert(a->b->method[0] == "B_doSomthingElse");

    demolishTest();
}

int main(int argc, char** argv)
{
    it_uses_b();

    return (EXIT_SUCCESS);
}
```
--------------------- tests/Makefile --------------------------
```Makefile
all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../source/A.c B.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
```

```bash
cd tests
make --always-make
```