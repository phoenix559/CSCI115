//
// Created by phoenix559 on 9/24/26.
//

#ifndef CSCI115_RECURSIVE_SORT_H
#define CSCI115_RECURSIVE_SORT_H
#include "MyArray.h"

#endif //CSCI115_RECURSIVE_SORT_H
class Lab5:public MyArray {
private:
  void merge_sort_starter();

public:
  void merge_sort(int low, int high);
  void merge(int low, int mid, int high);
  void quick_sort();
};