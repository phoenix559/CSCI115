//
// Created by phoenix559 on 9/19/26.
//
#include "../Lab 1/MyArray.h"
#include <iostream>

void MyArray::insertion_sort() {
    int temp = 0;
    for (int i = 1; i < length; i++){
        int j = i;
        while (j >= 1 && data[j] < data[j - 1] ) {
            temp = data[j];
            data[j] = data[j-1];
            data[j-1] = temp;
            j--;
        }
    }
}
void MyArray::bubble_sort() {
    bool done = false;
    int j = 0;
    int temp = 0;
    while (!done) {
        done = true;
        for (int i = 0; i < length - 1 - j; i++) {
            if (data[i] > data[i+1]) {
                done = false;
                temp = data [i+1];
                data[i+1] = data[i];
                data[i] = temp;
            }
        }
        j++;
    }
}
void MyArray::selection_sort()
{
    for (int i = 0; i < length; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
        }
        int temp = data[min_index];
        data[min_index] = data[i];
        data[i] = temp;
    }
}