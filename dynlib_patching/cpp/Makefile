CC=g++

DLL_SRC=foo_lib.cpp
DLL_NAME=foo
DLL_CFLAGS=-shared -Wall -Werror -fpic

SRC=main.cpp
BIN=main
CFLAGS=-Wall
LDFLAGS=-ldl

all: dll bin

dll:
	$(CC) $(DLL_CFLAGS) $(DLL_SRC) -o lib$(DLL_NAME).so

bin:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)
