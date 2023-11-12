add_executable(DefaultAllocator-UT
               DefaultAllocator-UT.cpp)

target_include_directories(DefaultAllocator-UT
                           PUBLIC
                           ${TESTED_LIBRARY_DIR})

target_link_libraries(DefaultAllocator-UT
                      gtest_main
                      gmock_main
                      -Wextra
                      -pedantic)

target_compile_features(DefaultAllocator-UT
                        PRIVATE
                        cxx_std_20)
