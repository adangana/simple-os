# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Source files
SRC = $(wildcard ./*.c)
LIB_SRC = $(wildcard lib/*.c)
TEST_SRC = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, bin/%, $(TEST_SRC))

# Directories
BIN_DIR = bin
BIN_TEST_DIR = bin/tests

OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)

all:
	@echo "Run 'make tests' to build and run individual test executables."

tests: $(TEST_BINS)
	@echo "Built all test binaries."

# Building individual test executables
bin/%: tests/%.c $(filter-out ./main.o, $(OBJ))
	@mkdir -p $(BIN_TEST_DIR) 
	$(CC) $(CFLAGS)	-o $(BIN_TEST_DIR)/$(notdir $@) $< $(filter-out ./main.o, $(OBJ))

%.o: %.c
	@ if [ $< != "main.c" ]; then \
		$(CC) $(CFLAGS) -c -o $@ $<; \
	fi

shell: $(OBJ) 
	@mkdir -p $(BIN_DIR) 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm -rf bin *.o lib/*.o

