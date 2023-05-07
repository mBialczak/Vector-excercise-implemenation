cmake_minimum_required(VERSION 3.14)
project(Vector-excercise-implementation
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

add_executable(Vector-MT
               Vector-MT.cpp
)

target_link_libraries(Vector-MT
                      gtest_main
                      gmock_main
)

target_compile_options(Vector-MT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(Vector-MT
                       PRIVATE
                       cxx_std_20)

add_executable(DefaultAllocator-UT
               DefaultAllocator-UT.cpp
)

target_link_libraries(DefaultAllocator-UT
                      gtest_main
                      gmock_main
)

target_compile_options(DefaultAllocator-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(DefaultAllocator-UT
                       PRIVATE
                       cxx_std_20)

add_test(NAME DefaultAllocator-UT COMMAND DefaultAllocator-UT)
add_test(NAME VectorTests-MT COMMAND Vector-MT)
