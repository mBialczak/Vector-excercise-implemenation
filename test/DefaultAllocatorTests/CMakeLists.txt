add_executable(DefaultAllocator-UT
               DefaultAllocator-UT.cpp)

target_include_directories(DefaultAllocator-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(DefaultAllocator-UT
                      gtest_main
                      gmock_main)

target_compile_options(DefaultAllocator-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(DefaultAllocator-UT
                        PRIVATE
                        cxx_std_20)
