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
# "../src")
# "${CMAKE_SRC_DIR}/../src")
   "${CMAKE_CURRENT_SOURCE_DIR}/../src")
# "/home/piworzoup/CodersSchool/HOMEWORK/Templates/Vector/src")

set(EXECUTABLE_OUTPUT_PATH
    "../")

# set(EXECUTABLE_OUTPUT_PATH
#     ${TESTED_LIBRARY_DIR})

add_subdirectory(DefaultAllocatorTests)
add_subdirectory(ReverseIteratorTests)
    # // TODO: REMOVE
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
# set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY
#     ${TESTED_LIBRARY_DIR})


# add_executable(Vector-MT
#                Vector-MT.cpp
# )

# Vector-MT target settings
# target_link_libraries(Vector-MT
#                       gtest_main
#                       gmock_main
# )

# target_compile_options(Vector-MT
#                        PRIVATE
#                        -Wall
#                        -Wextra
#                        -pedantic)

# target_compile_features(Vector-MT
#                        PRIVATE
#                        cxx_std_20)

# ReverseIterator-UT target settings
# add_executable(ReverseIterator-UT
#                ReverseIterator-UT.cpp
# )

add_test(NAME DefaultAllocator-UT COMMAND DefaultAllocator-UT)
add_test(NAME ReverseIterator-UT COMMAND ReverseIterator-UT)
# add_test(NAME VectorTests-MT COMMAND Vector-MT)
