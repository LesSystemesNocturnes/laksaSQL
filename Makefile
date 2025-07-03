CC=gcc
CFLAGS=-Wall -Iinclude
SRC=src/main.c src/parser.c src/tokenizer.c src/query_executor.c
OBJ=$(SRC:.c=.o)

laksa: $(SRC)
	$(CC) $(CFLAGS) -o laksa $(SRC)
clean:
	rm -f laksa
