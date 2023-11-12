add_executable(Vector-MT
               Vector-MT.cpp)

target_include_directories(Vector-MT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

 target_link_libraries(Vector-MT
                      gtest_main
                      gmock_main)

target_compile_options(Vector-MT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(Vector-MT
                        PRIVATE
                        cxx_std_20)
