cmake_minimum_required(VERSION 3.5)
project(diploma)

set( CMAKE_C_STANDARD 11 )

#set( RIDE_DIR ../src )

#include_directories( ${RIDE_DIR} )
#set( SOURCE_FILES ${RIDE_DIR}/RiDE_server.c ${RIDE_DIR}/RiDE_server.h )
set( SOURCE_FILES main.c RiDE_server.c RiDE_server.h )

set( CMAKE_CXX_FLAGS  -Wall)
set( CMAKE_EXE_LINKER_FLAGS -luv)

#set( EXECUTABLE_OUTPUT_PATH "../nbeans-exec" )
#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../nbeans-exec" )
add_executable(diploma ${SOURCE_FILES})
