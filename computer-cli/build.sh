#!/usr/bin/sh
make -C ../simple-computer CFLAGS=-"I../include -g -O0 "
mkdir -p ../bin/
clang -g -O0 simple_computer_cli.c -I../include -I../ -L../simple-computer/ -lsimple-computer -o ../bin/simplecomputer