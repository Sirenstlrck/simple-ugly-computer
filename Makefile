export ROOT_DIRECTORY = ${shell pwd}

export CC = gcc
export CFLAGS = -Wall -Wextra -g -O0 -I ${ROOT_DIRECTORY}/include/

all: clean clang-format obj main test

OBJS = $(shell find . -type f -name '*.o' -not -path "./tests/*")

main:
	@$(CC) $(CFLAGS) $(OBJS) -o $@

execute:
	./main

.PHONY: clean execute clang-format obj test

clang-format:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i

obj:
	$(MAKE) -C myReadKey/
	$(MAKE) -C myTerminal/
	$(MAKE) -C myBigChars/
	$(MAKE) -C mySimpleComputer/
	$(MAKE) -C myConsole/ 
	@$(CC) $(CFLAGS) -c main.c

clean:
	$(MAKE) -C myReadKey/ clean
	$(MAKE) -C myTerminal/ clean
	$(MAKE) -C myBigChars/ clean
	$(MAKE) -C mySimpleComputer/ clean
	$(MAKE) -C myConsole/ clean
	$(MAKE) -C tests/ clean
	rm -rf main.o
	rm -rf main

test: obj
	./scripts/BuildAndRunTests.sh