export ROOT_DIRECTORY = ${shell pwd}

export CC = gcc
export CFLAGS = -Wall -Wextra -g -O0 -I ${ROOT_DIRECTORY}/include/

all: clean clang-format obj main

OBJS = $(shell find . -type f -name '*.o' -not -path "./tests/*")

main:
	@$(CC) $(CFLAGS) $(OBJS) -o $@

execute:
	./main

.PHONY: clean execute clang-format obj

clang-format:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i

obj:
	$(MAKE) -C myReadKey/
	$(MAKE) -C myTerm/
	$(MAKE) -C myBigChars/
	$(MAKE) -C mySimpleComputer/
	$(CC) $(CFLAGS) -c main.c

clean:
	$(MAKE) -C myReadKey/ clean
	$(MAKE) -C myTerm/ clean
	$(MAKE) -C myBigChars/ clean
	$(MAKE) -C mySimpleComputer/ clean
	rm -rf main.o
	rm -rf main