CC=gcc
CPP=g++
CFLAGS=-O2 -std=c99 -g -Wall -Wextra -pedantic
CXXFLAGS=-O2 -std=c++11 -g -Wall -pedantic

all: tail wordcount clean zip

tail: tail.c tail2.cc
	$(CC) $(CFLAGS) tail.c -o tail
	$(CPP) $(CXXFLAGS) tail2.cc -o tail2

wordcount: libhtable wordcount.c io.c
	$(CC) $(CFLAGS) wordcount.c -o wordcount-dynamic -L. -lhtable
	$(CC) $(CFLAGS) wordcount.c libhtable.a -o wordcount

libhtable: htab_init.c htab_init2.c htab_clear.c htab_foreach.c htab_free.c htab_lookup_add.c htab_remove.c 
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_foreach.c -o htab_foreach-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c -o htab_remove-shared.o
	$(CC) $(CFLAGS) -fPIC -c htab_init2.c -o htab_init2-shared.o
	$(CC) $(CFLAGS) -shared -o libhtable.so  htab_init-shared.o htab_clear-shared.o htab_foreach-shared.o htab_free-shared.o htab_lookup_add-shared.o htab_remove-shared.o htab_init2-shared.o

	$(CC) $(CFLAGS) -c htab_init.c -o htab_init-static.o
	$(CC) $(CFLAGS) -c htab_clear.c -o htab_clear-static.o
	$(CC) $(CFLAGS) -c htab_foreach.c -o htab_foreach-static.o
	$(CC) $(CFLAGS) -c htab_free.c -o htab_free-static.o
	$(CC) $(CFLAGS) -c htab_lookup_add.c -o htab_lookup_add-static.o
	$(CC) $(CFLAGS) -c htab_remove.c -o htab_remove-static.o
	$(CC) $(CFLAGS) -c htab_init2.c -o htab_init2-static.o
	ar crs libhtable.a htab_init-static.o htab_clear-static.o htab_foreach-static.o htab_free-static.o htab_lookup_add-static.o htab_remove-static.o htab_init2-static.o
	ranlib libhtable.a

clean:
	rm -f htab_*-shared.o htab_*-static.o xdzils00.zip

zip: *.c *.h Makefile
	zip xdzils00.zip *.c *.cc *.h Makefile
