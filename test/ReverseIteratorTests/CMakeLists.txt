add_executable(ReverseIterator-UT
               ReverseIterator-UT.cpp)

target_include_directories(ReverseIterator-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(ReverseIterator-UT
                      gtest_main)

target_compile_options(ReverseIterator-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(ReverseIterator-UT
                        PRIVATE
                        cxx_std_20)
