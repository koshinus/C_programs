cmake_minimum_required(VERSION 3.5)
project(diploma)

set( CMAKE_C_STANDARD 11 )

set( SOURCE_FILES main.c RiDE_server.c RiDE_server.h )

set( CMAKE_CXX_FLAGS  -Wall)
set( CMAKE_EXE_LINKER_FLAGS -luv)

add_executable(diploma ${SOURCE_FILES})
