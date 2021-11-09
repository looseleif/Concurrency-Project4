CC=gcc
CFLAGS=-std=c99 -pthread
DBFLAGS=-g

all: main.c linked_list.o linked_list.h
	$(CC) $(CFLAGS) $(DBFLAGS) -o tlist linked_list.o main.c

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c linked_list.c

clean: 
	rm -rf tlist linked_list.o
