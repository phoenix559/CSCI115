# Lab 4/CMakeLists.txt

# Test executable for Sort
add_executable(test_iterative
        Sort.cpp
        # Add main.cpp or whichever file holds main() for this test
)

# This links MyArray.cpp and automatically lets Sort.cpp do: #include "MyArray.h"
target_link_libraries(test_iterative PRIVATE MyArray_Base)
