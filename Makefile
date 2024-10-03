export ROOT_DIRECTORY = ${shell pwd}

export CC = gcc
export CFLAGS =  -g -O0 -I ${ROOT_DIRECTORY}/include/

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
	$(MAKE) -C read-key/
	$(MAKE) -C terminal/
	$(MAKE) -C big-chars/
	$(MAKE) -C simple-computer/
	$(MAKE) -C console/ 
	@$(CC) $(CFLAGS) -c main.c

clean:
	$(MAKE) -C read-key/ clean
	$(MAKE) -C terminal/ clean
	$(MAKE) -C big-chars/ clean
	$(MAKE) -C simple-computer/ clean
	$(MAKE) -C console/ clean
	$(MAKE) -C tests/ clean
	rm -rf main.o
	rm -rf main

test: obj
	./scripts/BuildAndRunTests.sh