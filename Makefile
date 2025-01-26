# Compiler and linker
CC = clang

# Default sanitizer type (set to "leak" or "thread")
SANITIZER_TYPE = leak  # Set this to "thread" to use ThreadSanitizer

# Debug flags (max warnings, debugging symbols, and all sanitizers except CFI)
DEBUG_FLAGS = -Wall -Wextra -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion -g

# Conditionally set the sanitizer flags based on the SANITIZER_TYPE variable
ifeq ($(SANITIZER_TYPE), leak)
    SANITIZER_FLAGS = -fsanitize=leak
else ifeq ($(SANITIZER_TYPE), thread)
    SANITIZER_FLAGS = -fsanitize=thread
else
    SANITIZER_FLAGS = # No sanitizer by default
endif

# Full debug flags, including AddressSanitizer (always included) and the selected sanitizer
DEBUG_FLAGS += -fsanitize=address -fsanitize=undefined $(SANITIZER_FLAGS)

# Release flags with highest optimizations (flto enabled and CFI)
RELEASE_FLAGS = -Wall -Wextra -O3 -flto -march=native -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion \
                -fsanitize=address -fsanitize=undefined -fsanitize=leak \
                -fsanitize=thread -fsanitize=cfi

# Define the build directory and output executable
BUILD_DIR = build
EXEC = $(BUILD_DIR)/hyprpaperchanger

# Recursively find all C source files in the current directory and all subdirectories
SRC_FILES = $(shell find . -name "*.c")
# Create object file paths in the build directory
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# Default target: build the executable in debug mode and then run it
all: debug run

# Rule to create the debug build (no CFI for debug)
debug: CFLAGS = $(DEBUG_FLAGS)
debug: $(EXEC)

# Rule to create the release build (with LTO and CFI)
release: CFLAGS = $(RELEASE_FLAGS)
release: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)  # Create the build directory if it doesn't exist
	$(CC) $(OBJ_FILES) -o $(EXEC) -fsanitize=address

# Rule to create object files from C files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Create the directory structure inside build
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the application after build
run: $(EXEC)
	@echo "Running the application..."
	@./$(EXEC)  # Ensure the executable is run

# Clean up the build files
clean:
	rm -rf $(BUILD_DI
