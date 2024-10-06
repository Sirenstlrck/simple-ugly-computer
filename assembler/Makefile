OBJ_DIRECTORY_NAME = obj

CSRC = $(shell find ./ -name "*.c")
OBJ = $(patsubst %.c, %.o, $(CSRC))

all:
	-@ clang -I../include/ -g -O0 main.c -o ../bin/simpleassembler -L../simple-computer -lsimple-computer

.PHONY: clean
clean:
	-@ rm -rf '*.o'
