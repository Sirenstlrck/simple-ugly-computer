#!/usr/bin/sh
mkdir -p ../bin/
clang -I../include/ -g -O0 main.c -o ../bin/simpleassembler -L../simple-computer -lsimple-computer