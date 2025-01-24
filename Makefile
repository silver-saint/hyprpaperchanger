# Compiler and linker
CC = clang

# Debug flags (max warnings, debugging symbols)
DEBUG_FLAGS = -Wall -Wextra -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion -g

# Release flags with highest optimizations
RELEASE_FLAGS = -Wall -Wextra -O3 -flto -march=native -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion

# Define the build directory and output executable
BUILD_DIR = build
EXEC = $(BUILD_DIR)/my_program

# Recursively find all C source files in the current directory and all subdirectories
SRC_FILES = $(shell find . -name "*.c")
# Create object file paths in the build directory
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# Default target: build the executable in debug mode and then run it
all: debug run

# Rule to create the debug build
debug: CFLAGS = $(DEBUG_FLAGS)
debug: $(EXEC)

# Rule to create the release build
release: CFLAGS = $(RELEASE_FLAGS)
release: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)  # Create the build directory if it doesn't exist
	$(CC) $(OBJ_FILES) -o $(EXEC)

# Rule to create object files from C files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Create the directory structure inside build
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the application after build
run: $(EXEC)
	@echo "Running the application..."
	./$(EXEC)

# Clean up the build files
clean:
	rm -rf $(BUILD_DIR)

# Rebuild the project (use 'make rebuild debug' or 'make rebuild release')
rebuild: clean all
