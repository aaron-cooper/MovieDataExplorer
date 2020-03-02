CC=gcc
CFLAGS=-Wall -ansi -pedantic
SRC_DIR=
HDR_DIR=
OBJ_DIR=
EXE_DIR=
INC_FLAG=-I./$(HDR_DIR)

HDR_FILES=common.h binary.h name.h title.h principals.h
SRC_FILES=common.c binary.c name.c title.c principals.c main.c

_HDR_FILES=$(patsubst %,$(HDR_DIR)%,$(HDR_FILES))
_OBJ_FILES=$(patsubst %.c,$(OBJ_DIR)%.o,$(SRC_FILES))


a3: $(_OBJ_FILES)
	$(CC) -o $(EXE_DIR)$@ $^ $(CFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(_HDR_FILES)
	$(CC) -c -o $@ $< $(CFLAGS) $(INC_FLAG) $(CFLAGS)

clean:
	rm $(EXE_DIR)a3 $(OBJ_DIR)*.o
