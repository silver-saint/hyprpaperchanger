cmake_minimum_required(VERSION 3.10)
project(HyprPaperChanger)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings and debugging symbols for Debug build
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion -g")

# Enable optimizations and link-time optimizations for Release build
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -O3 -flto -march=native -Werror -pedantic -Wshadow -Wstrict-prototypes -Wundef -Wconversion")

# Define the source files
file(GLOB_RECURSE SRC_FILES "*.cpp")

# Add the executable
add_executable(hyprpaperchanger ${SRC_FILES})

# Optionally, you can specify where to place the build outputs
set_target_properties(hyprpaperchanger PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)

# Optionally, add other libraries or dependencies here
