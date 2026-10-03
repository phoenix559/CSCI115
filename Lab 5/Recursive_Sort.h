//
// Created by phoenix559 on 9/24/26.
//

#ifndef CSCI115_RECURSIVE_SORT_H
#define CSCI115_RECURSIVE_SORT_H
#include "MyArray.h"

#endif //CSCI115_RECURSIVE_SORT_H
class Lab5:public MyArray {
private:
  void merge_sort(int low, int high);
  int find_pivot(int low, int high);
  int partition(int pivot, int low, int high);
  void swap(int &first, int &second);
  void insertion_sort(int low, int high);
  void quick_sort(int low, int high);
public:

  void merge(int low, int mid, int high);
  void quick_sort();
  void merge_sort();
};