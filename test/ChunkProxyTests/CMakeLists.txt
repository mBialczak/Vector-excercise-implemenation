add_executable(ChunkProxy-UT
               ChunkProxy-UT.cpp
              )

target_include_directories(ChunkProxy-UT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})

 target_link_libraries(ChunkProxy-UT
                       gtest_main)

target_compile_options(ChunkProxy-UT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(ChunkProxy-UT
                        PRIVATE
                        cxx_std_20)
