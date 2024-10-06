OBJ_DIRECTORY_NAME = obj

CSRC = $(shell find ./ -name "*.c")
OBJ = $(patsubst %.c, %.o, $(CSRC))

all: obj $(OBJ) lib

%.o: %.c
	 $(CC) $(CFLAGS) -c ./$< -o $(OBJ_DIRECTORY_NAME)/$(notdir $@)

obj:
	-@ mkdir -p $(OBJ_DIRECTORY_NAME)

lib:
#heehhe
	ls ./obj/ | xargs printf "${OBJ_DIRECTORY_NAME}/%s " | xargs ar r libsimple-computer.a

.PHONY: clean
clean:
	-@ rm -rf ./obj/