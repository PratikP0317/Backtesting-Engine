cmake_minimum_required(VERSION 3.16)

# Project name and version
project(BacktestingEngine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Debug and Release configurations
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Source files - automatically find all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Header files - automatically find all .h files in include/
file(GLOB HEADERS "include/*.h")

# Create executable
add_executable(backtesting-engine ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(backtesting-engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Create logs directory at build time
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

# Optional: Add testing support
enable_testing()

# If you want to add tests later, uncomment these lines:
# add_subdirectory(tests)

# Install targets
install(TARGETS backtesting-engine
    RUNTIME DESTINATION bin
)

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS}")
