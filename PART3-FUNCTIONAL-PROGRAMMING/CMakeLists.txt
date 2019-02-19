CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
SET(CMAKE_C_STANDARD 99)

# Set Project Name
SET(PROJECT_NAME IEEEP3)
PROJECT(${PROJECT_NAME} C)

# Set Project Version
SET(CMAKE_PROJECT_VERSION_MAJOR 0)
SET(CMAKE_PROJECT_VERSION_MINOR 1)

# Compiler Options
IF(CMAKE_COMPILER_IS_GNUCC)
    ADD_DEFINITIONS(-Wall -Werror -pedantic -std=c99)
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# Configure Project
CONFIGURE_FILE(
        "${PROJECT_SOURCE_DIR}/templates/version.h.in"
        "${PROJECT_BINARY_DIR}/include/version.h"
)

# Get List of Source (.c) and Header (.h) Files
FILE(GLOB_RECURSE SRC_LIST FOLLOW_SYMLINKS src/*.c)
FILE(GLOB_RECURSE HEAD_FILES FOLLOW_SYMLINKS include/*.h ${PROJECT_BINARY_DIR}/include/*.h)

# Set the Include Directory
INCLUDE_DIRECTORIES(
        "${PROJECT_SOURCE_DIR}/include/"
        "${PROJECT_BINARY_DIR}/include/"
)

# Configure the Project to Execute and Install
ADD_EXECUTABLE(${PROJECT_NAME} src/main.c ${SRC_LIST})
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)