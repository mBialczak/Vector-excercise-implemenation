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

add_executable(Vector-ut
               Vector-ut.cpp
)

target_link_libraries(Vector-ut
                      gtest_main
                      gmock_main
)

target_compile_options(Vector-ut
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(Vector-ut
                       PRIVATE
                       cxx_std_20)

add_executable(DefaultAllocator-ut
               DefaultAllocator-ut.cpp
)

target_link_libraries(DefaultAllocator-ut
                      gtest_main
                      gmock_main
)

target_compile_options(DefaultAllocator-ut
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(DefaultAllocator-ut
                       PRIVATE
                       cxx_std_20)

gtest_discover_tests(Vector-ut)
gtest_discover_tests(DefaultAllocator-ut)