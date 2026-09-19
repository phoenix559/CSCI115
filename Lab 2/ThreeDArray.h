//
// Created by phoenix559 on 9/3/26.
//
#include "../Lab 1/MyArray.h"

#ifndef LAB_2_THREEDARRAY_H
#define LAB_2_THREEDARRAY_H
class ThreeDArray {
private:
    int slice = 0;
    int row = 0;
    int column = 0;
    MyArray*** matrix = nullptr;


public:
    ThreeDArray();
    ThreeDArray(int arg_n, int arg_m, int arg_l);
    ~ThreeDArray();
    int get_slice() const;
    int get_row() const;
    int get_column() const;
    int& at(int arg_slice, int arg_row, int arg_col);
    void display(void);
};

#endif //LAB_2_THREEDARRAY_H
