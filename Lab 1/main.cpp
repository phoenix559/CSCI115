#include <iostream>
#include <random>

#include "MyArray.h"


void unitTest() {
    std::cout <<"Testing default constructor" << std::endl;
    MyArray arr = MyArray();
    arr.print();

    std::cout<<"\nTesting Parameterized constructor" << std::endl;
    MyArray arr2 = MyArray(5,2);
    arr2.print();

    std::cout<<"\nTesting operator [] overload:" << std::endl;
    arr2[1]=5;
    int a = arr2[1];
    std::cout<<"arr2[1]=5" << std::endl;
    arr2.print();
    std::cout << "int a = arr2[1]: "<< a << std::endl;

    MyArray arr3 = MyArray(10,0);
    for (int i = 0; i < 10; i++) {
        arr3[i] = i;
    }
    std::cout<<"Array of capacity 10 with loop filing elements with index value" << std::endl;
    arr3.print();

    std::cout<<"\nTesting copy constructor and = overload" << std::endl;
    MyArray arr4 = MyArray(arr3);
    MyArray arr5(arr3);
    MyArray arr6 = arr3;
    MyArray arr7 = MyArray();
    MyArray arr8 = MyArray(5,2);
    arr7 = arr8 = arr3;
    arr4.print();
    arr5.print();
    arr6.print();
    arr7.print();
    arr8.print();

    std::cout<<"\nTesting insert methods and that copy is deep copy"<< std::endl;
    std::cout<<"arr3.insert_sorted(3)" << std::endl;
    arr3.print();
    arr3.insert_sorted(3);
    arr3.print();

    std::cout<<"arr4.push_back(1)" << std::endl;
    arr4.print();
    arr4.push_back(1);
    arr4.print();

    std::cout<<"arr5.push_front(2)" << std::endl;
    arr5.print();
    arr5.push_front(2);
    arr5.print();

    std::cout<<"arr6.push_back(15)" << std::endl;
    arr6.print();
    arr6.push_back(15);;
    arr6.print();

    std::cout<<"arr7.push_front(7)" << std::endl;
    arr7.print();
    arr7.push_front(7);
    arr7.print();

    std::cout<<"loop of 7 arr8.insert_sorted(5)" << std::endl;
    arr8.print();
    for (int i = 0; i < 7; i++) {
        arr8.insert_sorted(5);
    }
    arr8.print();



    std::cout<<"\nTesting Deletes"<< std::endl;
    arr4.print();
    arr4.pop_back();
    std::cout<<"arr4.pop_back()" << std::endl;
    arr4.print();

    arr5.print();
    arr5.pop_front();
    std::cout<<"arr5.pop_front()" << std::endl;
    arr5.print();

    arr6.print();
    arr6.delete_at(5);
    std::cout<<"arr6.delete_at(5)" << std::endl;
    arr6.print();

    arr7.print();
    arr7.delete_first_value(7);
    std::cout<<"arr7.delete_first_value(7)" << std::endl;
    arr7.print();

    arr8.print();
    arr8.delete_all_value(5);
    std::cout<<"arr8.delete_all_value(5)" << std::endl;
    arr8.print();

    std::cout<<"\nTesting Search"<< std::endl;
    arr3.print();
    std::cout<<"linear search of 5: " << arr3.linear_search(5)<<std::endl;
    std::cout<<"Itterative Binary of 5: "<< arr3.binary_search_iterative(5)<<std::endl;
    std::cout<<"Recursive Binary of 5: " << arr3.binary_search_recursive(5)<<std::endl;
    std::cout<<"linear search of 999: " << arr3.linear_search(999)<<std::endl;
    std::cout<<"Itterative Binary of 999: "<< arr3.binary_search_iterative(999)<<std::endl;
    std::cout<<"Recursive Binary of 999: " << arr3.binary_search_recursive(999)<<std::endl;

    std::cout<<"\nTesting count_values"<< std::endl;
    for (int i = 0; i < 5; i++) {
        arr3.push_front(42);
    }
    arr3.print();
    std::cout<<"counting 42: "<< arr3.count_values(42) << std::endl;
    std::cout<<"counting 3: "<< arr3.count_values(3)<< std::endl;
    std::cout<<"counting 20: "<< arr3.count_values(20)<< std::endl;

    std::cout<<"\nTesting sort"<< std::endl;
    arr3.print();
    arr3.sort();
    arr3.print();

    arr4.print();
    arr4.sort();
    arr4.print();

    std::cout<<"\nTesting reverse" << std::endl;
    arr3.print();
    arr3.reverse();
    arr3.print();

    std::cout<<"\nTesting subarray (2,7)"<< std::endl;
    MyArray arr9 = arr3.subarray(2,7);
    arr3.print();
    arr9.print();

    std::cout<<"\nTesting unique" << std::endl;
    MyArray arr10 = MyArray(3,6);
    // 1. Create a random device and seed the engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // 2. Define your desired inclusive range [min, max]
    // Keeping the range small (e.g., 1 to 10) ensures duplicates for testing unique()
    std::uniform_int_distribution<int> dist(1, 10);

    // 3. Generate random values
    for (int i = 0; i < 20; i++) {
        int random_val = dist(gen);
        arr10.push_back(random_val);
    }
    arr10.print();
    MyArray arr11 = arr10.unique();
    arr11.print();


    std::cout<<"\nTesting sort on random arrays (prevoius ones)"<< std::endl;
    arr10.sort();
    arr11.sort();
    arr10.print();
    arr11.print();

    std::cout<<"\nattempting to break things (try:catch)" << std::endl;
    try {
        MyArray arr15 = arr3.subarray(5, 2);
    } catch (const std::out_of_range& e) {
        std::cout << "Successfully caught exception: " << e.what() << std::endl;
    }


}

#include <stdexcept>

void testExceptions() {
    std::cout << "\n===============================" << std::endl;
    std::cout << "  RUNNING EXCEPTION UNIT TESTS " << std::endl;
    std::cout << "===============================" << std::endl;

    // 1. Parameterized Constructor: initial_capacity <= 0
    std::cout << "\n[Test 1] Parameterized constructor with non-positive capacity:" << std::endl;
    try {
        MyArray invalidArr(0, 5);
        std::cout << "FAIL: Exception not thrown for capacity 0." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Caught std::invalid_argument: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught unexpected exception: " << e.what() << std::endl;
    }

    try {
        MyArray invalidArrNeg(-10, 5);
        std::cout << "FAIL: Exception not thrown for negative capacity." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Caught std::invalid_argument: " << e.what() << std::endl;
    }

    // Set up a valid array for boundary testing
    MyArray testArr(5, 10);

    // 2. operator[]: Negative index (< 0)
    std::cout << "\n[Test 2] operator[] out of bounds (negative index):" << std::endl;
    try {
        int val = testArr[-1];
        std::cout << "FAIL: Exception not thrown for index -1. Got: " << val << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: Caught std::out_of_range: " << e.what() << std::endl;
    }

    // 3. operator[]: Index equal to or exceeding length (>= length)
    std::cout << "\n[Test 3] operator[] out of bounds (index >= length):" << std::endl;
    try {
        int val = testArr[5]; // length is 5, valid indices are 0-4
        std::cout << "FAIL: Exception not thrown for index 5. Got: " << val << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: Caught std::out_of_range: " << e.what() << std::endl;
    }

    // 4. subarray: Negative start index (< 0)
    std::cout << "\n[Test 4] subarray with negative start index:" << std::endl;
    try {
        MyArray sub = testArr.subarray(-1, 3);
        std::cout << "FAIL: Exception not thrown for start = -1." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: Caught std::out_of_range: " << e.what() << std::endl;
    }

    // 5. subarray: End index out of bounds (end >= length)
    std::cout << "\n[Test 5] subarray with end index exceeding array bounds:" << std::endl;
    try {
        MyArray sub = testArr.subarray(1, 10);
        std::cout << "FAIL: Exception not thrown for end = 10." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: Caught std::out_of_range: " << e.what() << std::endl;
    }

    // 6. subarray: Inverted range (start > end)
    std::cout << "\n[Test 6] subarray with inverted range (start > end):" << std::endl;
    try {
        MyArray sub = testArr.subarray(4, 2);
        std::cout << "FAIL: Exception not thrown for start > end (4, 2)." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: Caught std::out_of_range: " << e.what() << std::endl;
    }

    std::cout << "\nAll exception tests completed safely without crashing." << std::endl;
}

void selection_sort(MyArray*);
void insert_sort(int*);
void bubble_sort(int*);

void selection_sort(MyArray* arr) {
    int length = arr->get_length();
    for (int i = 0; i < length; i++) {}
}
int main() {
    unitTest();
    testExceptions(); // created with gemini
    return 0;
}