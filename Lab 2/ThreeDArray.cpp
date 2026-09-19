#include "ThreeDArray.h"

#include <iostream>


ThreeDArray::ThreeDArray() {
    slice = 0; // y
    row = 0; // x
    column = 0; // z
    matrix = nullptr;
}

ThreeDArray::ThreeDArray(int arg_n, int arg_m, int arg_l) {
    slice = arg_n;
    row = arg_m;
    column = arg_l;
    matrix = new MyArray**[slice];
    for (int i = 0; i < slice; i++) {
        matrix[i] = new MyArray*[row];
        for (int j = 0; j < row; j++) {
            matrix[i][j] = new MyArray(column,0);;
        }
    }
}

ThreeDArray::~ThreeDArray() {
    for (int i = 0; i < slice; i++) {
        for (int j = 0; j < row; j++) {
            delete matrix[i][j];
        }
        delete [] matrix[i];
    }
    delete [] matrix;
    matrix = nullptr;
}

void ThreeDArray::display() {
    for (int i = 0; i < slice; i++) {
        for (int j = 0; j < row; j++) {
            std::cout << "[ ";
            for (int k = 0; k < column; k++) {
                int value = (*matrix[i][j])[k];
                std::cout << value << " ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout <<  std::endl;
    }
}

int& ThreeDArray::at(int arg_slice, int arg_row, int arg_col){
    if (arg_slice < 0 || arg_slice >= slice) {
        throw std::out_of_range("slice out of range");
    }
    if (arg_row < 0 || arg_row >= row) {
        throw std::out_of_range("row out of range");
    }
    if (arg_col < 0 || arg_col >= column) {
        throw std::out_of_range("column out of range");
    }
    return (*matrix[arg_slice][arg_row])[arg_col];
}
int ThreeDArray::get_slice() const {
    return slice;
}
int ThreeDArray::get_row() const {
    return row;
}
int ThreeDArray::get_column() const {
    return column;
}