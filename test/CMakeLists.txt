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

add_subdirectory(DefaultAllocatorTests)
add_subdirectory(ReverseIteratorTests)
add_subdirectory(VectorTests)

add_test(NAME DefaultAllocator-UT COMMAND DefaultAllocator-UT)
add_test(NAME ReverseIterator-UT COMMAND ReverseIterator-UT)
add_test(NAME VectorTests-MT COMMAND Vector-MT)
