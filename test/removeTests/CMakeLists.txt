add_executable(removeFunction-UT
               remove-UT.cpp
              )

target_include_directories(removeFunction-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

 target_link_libraries(removeFunction-UT
                       gtest_main
                       gmock_main)

target_compile_options(removeFunction-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(removeFunction-UT
                        PRIVATE
                        cxx_std_20)
