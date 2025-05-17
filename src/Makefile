# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Directories
BIN_DIR = bin
BIN_TEST_DIR = bin/tests

# Source files
SRC = $(wildcard ./*.c)
LIB_SRC = $(wildcard lib/*.c)
TEST_SRC = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, $(BIN_TEST_DIR)/%, $(TEST_SRC))

OBJ = $(filter-out ./shell.o ./va_translator.o, $(SRC:.c=.o) $(LIB_SRC:.c=.o))

all:
	@echo "Run 'make tests' to build and run individual test executables."
	@echo "Run 'make shells' to build the interactive shell executable."
	@echo "Run 'make va_taranslator' to build the VA translator executable."

tests: $(TEST_BINS)
	@echo "Built all test binaries."

# Building individual test executables
$(BIN_TEST_DIR)/%: tests/%.c $(OBJ)
	@mkdir -p $(BIN_TEST_DIR)
	$(CC) $(CFLAGS) -o $(BIN_TEST_DIR)/$(notdir $@) $< $(OBJ)

# $(BIN_TEST_DIR)/%: tests/%.c $(OBJ)
# 	@mkdir -p $(BIN_TEST_DIR)
# 	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

shell: shell.o $(OBJ) 
	@mkdir -p $(BIN_DIR) 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

va_translator: va_translator.o $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

clean:
	rm -rf bin *.o lib/*.o

