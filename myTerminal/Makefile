OBJ_DIRECTORY_NAME = obj

CSRC = $(shell find ./ -name "*.c")
OBJ = $(patsubst %.c, %.o, $(CSRC))

all: obj $(OBJ)

%.o: %.c
	-@ $(CC) $(CFLAGS) -c ./$< -o $(OBJ_DIRECTORY_NAME)/$(notdir $@)

obj:
	-@ mkdir -p $(OBJ_DIRECTORY_NAME)

.PHONY: clean
clean:
	-@ rm -rf ./obj/