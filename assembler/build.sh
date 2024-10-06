#!/usr/bin/sh

clang -I../include/ -g -O0 main.c -o ../bin/simpleassembler -L../simple-computer -lsimple-computer