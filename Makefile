# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -Werror -std=c99

ifdef DEBUG
	CFLAGS += -DDEBUG
endif

# Executables
EXEC = build/main/starterLinkedList
TEST = build/test/testLinkedList

# Source and Object files (Separate for main and test)
SRC_MAIN = main.c node.c utils.c
OBJ_MAIN = $(patsubst %.c, build/main/%.o, $(SRC_MAIN))

SRC_TEST = test.c node.c utils.c randomUtils.c
OBJ_TEST = $(patsubst %.c, build/test/%.o, $(SRC_TEST))

# Default target: build both main and test
all: build-main build-test

# Create build directories if they don't exist
$(shell mkdir -p build/main build/test)

# Custom targets for clarity
build-main: $(EXEC)  ## Build only the main executable
build-test: $(TEST)  ## Build only the test executable

# Build main executable
$(EXEC): $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) -o $(EXEC)

# Build test executable
$(TEST): $(OBJ_TEST)
	$(CC) $(OBJ_TEST) -o $(TEST)

# Compile source files into object files for main
build/main/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files into object files for test
build/test/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf build

# Run main and test
run-main: $(EXEC)
	./$(EXEC)

run-test: $(TEST)
	./$(TEST)

# Phony targets
.PHONY: all clean run-main run-test build-main build-test
