add_executable(BoolIterator-UT
               BoolIterator-UT.cpp)

target_include_directories(BoolIterator-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(BoolIterator-UT
                      gtest_main)

target_compile_options(BoolIterator-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(BoolIterator-UT
                        PRIVATE
                        cxx_std_20)
