cmake_minimum_required(VERSION 3.20)
SET(CMAKE_C_COMPILER clang)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)

include_directories(${LLVM_INCLUDE_DIRS})
project(lisp)
add_subdirectory(parser)
add_compile_options(-ly -ll)
include_directories('')
 
