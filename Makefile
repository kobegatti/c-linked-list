# Makefile for building the executable

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -Werror -std=c99

# Set the default executable name if not provided
EXEC = starterLinkedList
TEST = testLinkedList

# List of source files (You can modify this list as needed)
SRC = main.c node.c utils.c
OBJ = $(SRC:.c=.o)

SRCTEST = test.c node.c utils.c
OBJTEST = $(SRCTEST:.c=.o)

# Default target: build the executable
all: $(EXEC) $(TEST)

# Link the object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

$(TEST): $(OBJTEST)
	$(CC) $(OBJTEST) -o $(TEST)

# Compile the source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build artifacts
clean:
	rm -f $(OBJ) $(OBJTEST) $(EXEC) $(TEST)

run_main: $(EXEC)
	./$(EXEC)

run_test: $(TEST)
	./$(TEST)

# Phony targets
.PHONY: all clean
