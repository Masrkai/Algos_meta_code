# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Algos_meta_code CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header files
set(SOURCE_FILES src/main.cpp )
#set(HEADER_FILES include/Recursive_Combination.hpp include/Recursive_Combination.hpp)

# Define executable
add_executable(Algos_meta_code
               ${SOURCE_FILES}
               #${HEADER_FILES}
              )

# Find and link pthread library
find_package(Threads REQUIRED)
target_link_libraries(Algos_meta_code PRIVATE Threads::Threads)

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)