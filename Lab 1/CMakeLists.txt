# Lab 1/CMakeLists.txt

# 1. Create a library for MyArray
add_library(MyArray_Base
        MyArray.cpp
        MyArray.h
)

# 2. Tell CMake that anyone using MyArray_Base needs access to Lab 1's header folder
target_include_directories(MyArray_Base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 3. Lab 1's own executable
add_executable(MyArray_main
        main.cpp
)
target_link_libraries(MyArray_main PRIVATE MyArray_Base)