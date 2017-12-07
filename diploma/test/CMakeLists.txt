cmake_minimum_required(VERSION 3.5)
project(runTests)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_FLAGS  -Wall )

#For some reason next line doesn't work, use 'target_link_libraries' instead
#set( CMAKE_EXE_LINKER_FLAGS -luv -lgtest -lpthread)
set( SOURCE_FILES RiDE_test.cpp )

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${SOURCE_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread uv gtest)
