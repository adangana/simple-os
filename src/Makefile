# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Source files
SRC = $(wildcard ./*.c)
LIB_SRC = $(wildcard lib/*.c)
TEST_SRC = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, bin/%, $(TEST_SRC))

OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)

all:
	@echo "Run 'make tests' to build and run individual test executables."

tests: $(TEST_BINS)
	@echo "Built all test binaries."

# Building individual test executables
bin/%: tests/%.c $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS)	-o $@ $< $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf bin *.o lib/*.o

