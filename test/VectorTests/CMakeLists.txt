add_executable(Vector-MT
               Vector-MT-assignFunction.cpp
               Vector-MT-reverseAlike.cpp
               Vector-MT-capacityChanging.cpp
               Vector-MT-comparison.cpp
               Vector-MT-construction.cpp
               Vector-MT-copyAssignment.cpp
               Vector-MT-destructor.cpp
               Vector-MT-elementAccess.cpp
               Vector-MT-emplaceBack.cpp
               Vector-MT-emplaceFunction.cpp
               Vector-MT-insertFunction.cpp
               Vector-MT-inspectingFunctions.cpp
               Vector-MT-moveAssignment.cpp
               Vector-MT-pushBack.cpp
               Vector-MT-removingElements.cpp
               Vector-MT-resize.cpp
               Vector-MT-swap.cpp
               Vector-MT-typeAlias.cpp
              )

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
