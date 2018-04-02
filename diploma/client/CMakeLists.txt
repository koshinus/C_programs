cmake_minimum_required(VERSION 3.5)
project(client)

set( CMAKE_C_STANDARD 11 )

set( SOURCE_FILES utilities.h utilities.c client.c)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -luv")

add_executable(client ${SOURCE_FILES})
target_link_libraries(client uv)
