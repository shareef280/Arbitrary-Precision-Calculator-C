CC = gcc
OUT = a.out

SRC = main.c apc_ADD_SUB.c apc_MUL.c apc_DIV.c apc_utils.c

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)