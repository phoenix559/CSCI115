//
// Created by phoenix559 on 9/24/26.
//
#include "Recursive_Sort.h"
// HELPER
void Lab5::swap(int &first, int &second) {
    int temp = first;
    first = second;
    second = temp;
}

// ===== MERGE SORT =====
void Lab5::merge_sort_starter() {
    int low = 0;
    int high = length - 1;
    merge_sort(low, high);
}

void ::Lab5::merge_sort(int low, int high) {
    if (low >= high) {
        return;
    }
    if ((high - low + 1) < 16) {
        insertion_sort(low, high);
        return;
    }
    int mid = low + (high - low) / 2;
    merge_sort(low, mid);
    merge_sort( mid + 1, high);
    merge(low, mid, high);

}

void Lab5::merge(int low_start, int low_end, int high_end) {
    int  high_start = low_end + 1; // setting where the "high" subarray starts
    // Find out the amount of items in both subarrays.
    int count_low = low_end - low_start + 1, count_high = high_end - high_start + 1;
    int lower_cursor = 0 ,upper_cursor = 0, destination_cursor = 0;
    MyArray temp = MyArray(count_low + count_high, 0);
    while (lower_cursor < count_low && upper_cursor < count_high) {
        if (data[low_start + lower_cursor] <= data[high_start + upper_cursor]) {
            temp[destination_cursor] = data[low_start + lower_cursor];
            destination_cursor++;
            lower_cursor++;
        }
        else {
            temp[destination_cursor] = data[high_start + upper_cursor];
            destination_cursor++;
            upper_cursor++;
        }
    }
    while (lower_cursor < count_low) {
        temp[destination_cursor] = data[low_start + lower_cursor];
        destination_cursor++;
        }

    while (upper_cursor < count_high) {
        temp[destination_cursor] = data[high_start + upper_cursor];
        destination_cursor++;
        }

    for (int i = low_start; i <= high_end; i++) {
        data[i] = temp[i - low_start];
    }

}
void Lab5::insertion_sort(int low, int high) {
    for (int i = low + 1; i <= high; i++){
        int j = i;
        while (j > low && data[j] < data[j - 1] ) {
            swap( data[j], data[j - 1] );
            j--;
        }
    }
}

// ===== QUICKSORT =====
int Lab5::find_pivot(int low, int high) {
    int mid = low + (high - low) / 2;
    if (data[low] > data[mid]) {
        swap(data[low],data[mid]);
    }
    if (data[mid] > data[high]) {
        swap(data[mid],data[high]);
    }
    if (data[low] > data[mid]) {
        swap(data[low],data[mid]);
    }
    return data[mid];

}
int Lab5::partition(int pivot, int low, int high) {
    int lower_cursor = low, upper_cursor = high;
    while (lower_cursor <= upper_cursor) {
        while (data[lower_cursor] < pivot) {
            lower_cursor++;
        }
        while (data[upper_cursor] > pivot) {
            upper_cursor--;
        }
        if (lower_cursor <= upper_cursor) {
            swap(data[lower_cursor],data[upper_cursor]);
            lower_cursor++;
            upper_cursor--;
        }
    }

    return upper_cursor;
}
void Lab5::quick_sort() {
    int low = 0, high = length - 1;
    quick_sort(low, high);
}
void Lab5::quick_sort(int low, int high) {
    if (low >= high) {
        return;
    }
    if (low == high - 1) {
        if (data[low] > data[high] ) {
            swap(data[low],data[high]);
        }
        return;
    }
    int pivot = find_pivot(low, high);
    int boundary_low = partition(pivot, low, high);
    quick_sort(low, boundary_low);
    quick_sort(boundary_low + 1, high);

}

int main() {

}