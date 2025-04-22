# Compiler and flags
CC = gcc
CFLAGS = -Wall -Ilib

# Source files
LIB_SRC = $(wildcard lib/*.c)
TEST_SRC = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, bin/%, $(TEST_SRC))

all:
	@echo "Run 'make tests' to build and run individual test executables."

tests: $(TEST_BINS)
	@echo "Built all test binaries."

# Building individual test executables
bin/%: tests/%.c $(LIB_SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS)	-o $@ $< $(LIB_SRC)

clean:
	rm -rf bin

