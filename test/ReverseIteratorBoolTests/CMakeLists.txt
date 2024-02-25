add_executable(ReverseIteratorBool-UT
               ReverseIteratorBool-UT.cpp)

target_include_directories(ReverseIteratorBool-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(ReverseIteratorBool-UT
                      gtest_main
                      BoolIterator-UT-utils)

target_compile_options(ReverseIteratorBool-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(ReverseIteratorBool-UT
                        PRIVATE
                        cxx_std_20)
