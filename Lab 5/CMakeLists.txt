# Lab 5/CMakeLists.txt

# Test executable for Recursive_Sort
add_executable(test_recursive
        Recursive_Sort.cpp
        # Add main.cpp or whichever file holds main() for this test
)

# This links MyArray.cpp and automatically lets Recursive_Sort.cpp do: #include "MyArray.h"
target_link_libraries(test_recursive PRIVATE MyArray_Base)
