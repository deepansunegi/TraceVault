CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude
SRC = src/main.c src/vault.c src/storage.c src/sha256.c src/utils.c

all: tracevault

tracevault: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o tracevault

test: tests/test_sha256.c src/sha256.c
	$(CC) $(CFLAGS) tests/test_sha256.c src/sha256.c -o test_sha256
	./test_sha256

clean:
	rm -f tracevault test_sha256 *.o

.PHONY: all test clean
