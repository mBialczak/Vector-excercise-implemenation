add_executable(VectorBool-MT
            #    VectorBool-MT-assignFunction.cpp
            #    VectorBool-MT-reverseAlike.cpp
            #    VectorBool-MT-capacityChanging.cpp
            #    VectorBool-MT-comparison.cpp
               VectorBool-MT-construction.cpp
            #    VectorBool-MT-copyAssignment.cpp
            #    VectorBool-MT-destructor.cpp
               VectorBool-MT-elementAccess.cpp
            #    VectorBool-MT-emplaceBack.cpp
            #    VectorBool-MT-emplaceFunction.cpp
            #    VectorBool-MT-insertFunction.cpp
            #    VectorBool-Mt-inspectingFunctions.cpp
            #    VectorBool-MT-moveAssignment.cpp
            #    VectorBool-MT-pushBack.cpp
            #    VectorBool-MT-removingElements.cpp
            #    VectorBool-MT-resize.cpp
            #    VectorBool-MT-swap.cpp
               VectorBool-MT-typeAlias.cpp
               VectorBool-MT-utils.cpp
              )

target_include_directories(VectorBool-MT
                           PRIVATE
                           ${TESTED_LIBRARY_DIR})
# //TODO: VERIFY
target_link_libraries(VectorBool-MT
                       gtest_main
                       gmock_main)

target_compile_options(VectorBool-MT
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(VectorBool-MT
                        PRIVATE
                        cxx_std_20)
