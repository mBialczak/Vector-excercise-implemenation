cmake_minimum_required(VERSION 3.14)
project(Vector-excercise-implementation-tests
        LANGUAGES CXX)

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()


set(TESTED_LIBRARY_DIR
   "${CMAKE_CURRENT_SOURCE_DIR}/../src")

set(EXECUTABLE_OUTPUT_PATH
    "../")

add_subdirectory(BoolIteratorTests)
add_subdirectory(DefaultAllocatorTests)
add_subdirectory(ReverseIteratorTests)
add_subdirectory(ReverseIteratorBoolTests)
add_subdirectory(removeTests)
add_subdirectory(VectorTests)
add_subdirectory(VectorBoolTests)

add_test(NAME BoolIterator-UT COMMAND BoolIterator-UT)
add_test(NAME DefaultAllocator-UT COMMAND DefaultAllocator-UT)
add_test(NAME ReverseIterator-UT COMMAND ReverseIterator-UT)
add_test(NAME ReverseIteratorBool-UT COMMAND ReverseIteratorBool-UT)
add_test(NAME removeFunction-UT COMMAND removeFunction-UT)
add_test(NAME Vector-MT COMMAND Vector-MT)
add_test(NAME VectorBool-MT COMMAND VectorBool-MT)
