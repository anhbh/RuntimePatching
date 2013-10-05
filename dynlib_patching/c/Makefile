CC=gcc

DLL_SRC=foo.c
DLL_OBJ=foo.o
DLL_NAME=foo
DLL_CFLAGS=-shared -Wall -Werror -fpic

SRC=main.c
BIN=main
CFLAGS=-Wall
LDFLAGS=-ldl

all: dll bin

dll:
	$(CC) $(DLL_SRC) $(DLL_CFLAGS) -o lib$(DLL_NAME).so

bin:
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

