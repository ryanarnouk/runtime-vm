cmake_minimum_required(VERSION 3.10)
project(Runtime C)

# Compiler and flags
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c11 -g")

# Directories
set(SRC_DIR src)
set(OBJ_DIR obj)
set(BIN_DIR bin)

# Source files
file(GLOB SRCS ${SRC_DIR}/*.c)

# Object files
foreach(SRC ${SRCS})
    get_filename_component(SRC_NAME ${SRC} NAME_WE)
    list(APPEND OBJS ${OBJ_DIR}/${SRC_NAME}.o)
endforeach()

# Executable
add_executable(runtime ${SRCS})

# Set output directories
set_target_properties(runtime PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

# Clean target
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJ_DIR} ${BIN_DIR}
        COMMENT "Cleaning project")

# Phony target
add_custom_target(all
        DEPENDS runtime
        COMMENT "Building project")

# Phony target for cleaning
add_custom_target(clean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJ_DIR} ${BIN_DIR}
        COMMENT "Cleaning project")

# Set the target architecture
set_target_properties(runtime PROPERTIES
        COMPILE_FLAGS "-arch arm64"
        LINK_FLAGS "-arch arm64")
