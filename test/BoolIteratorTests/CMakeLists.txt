# common utils for testing BoolIterator and ReverseBoolIterator
add_library(BoolIterator-UT-utils
            BoolIterator-UT-utils.cpp)


target_link_libraries(BoolIterator-UT-utils
                      gtest_main)

target_include_directories(BoolIterator-UT-utils
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR})

# target for test of BoolIterator
add_executable(BoolIterator-UT
               BoolIterator-UT.cpp)

target_include_directories(BoolIterator-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(BoolIterator-UT
                      gtest_main
                      BoolIterator-UT-utils)

target_compile_options(BoolIterator-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(BoolIterator-UT
                        PRIVATE
                        cxx_std_20)
