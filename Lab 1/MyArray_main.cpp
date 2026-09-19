#include <iostream>
#include <random>
/*The goal is to implement - on your own - a class array in C++ with all the related functions that could be used with it.

Submit the following files:

1. C++ file for the class Array containing:

    Constructor
    Constructor by specifying the size of the array and the default value
    Constructor by copy
    Destructor
    Insert functions
        Insert an element at the beginning
        Insert an element  at the end
        Insert an element at the correct position in a sorted array
    Delete functions
        Delete an element at the beginning
        Delete an element at the end
        Delete the element at position i
        Delete the element with value x in the array
        Delete all the elements with the value x in the array
    Search functions
        Linear search
        Binary Search iterative version
        Binary Search recursive version
    Count the number of elements that have the value x
    Reverse the element in an array
    Return a new array (sub-array of the input array) with the elements between position i and j (i>j)
    Return an array with only the unique elements of the input array

2. A C++ file with a main to test the functions == call each method of your class with an example to verify it works.*/


class MyArray {
    private:
        int* data = nullptr;
        int length = 0; // current size of the array
        int capacity = 0; // preset capacity
        void resize();
        void check_size();
        void shift_right(int startIndex);
        void shift_left(int startIndex);
        int recursive_helper(int value, int low, int high);

    public:
        MyArray();
        MyArray(int initial_capacity, int value);
        MyArray(const MyArray& other);
        ~MyArray();
        int* get_data();
        int get_length();
        int get_capacity();

    // Methods
        // inserts
        void push_back(int);
        void push_front(int);
        void insert_sorted(int value);

        // deletes
        void pop_front();
        void pop_back();
        void delete_at(int index);
        void delete_first_value(int value);
        void delete_all_value(int value);

        // search
        int linear_search(int value);
        int binary_search_iterative(int value);
        int binary_search_recursive(int value);

        // other
        int count_values(int value);
        void sort();
        void reverse();
        MyArray subarray(int start, int end);
        MyArray unique();
        void print();
        int& operator[](int index); // recommended addition from gemini for "more natural array syntax"
        MyArray& operator=(const MyArray& other);
    };

MyArray::MyArray()
{
    data = nullptr;
    length = 0;
    capacity = 0;
}

MyArray::MyArray(int initial_capacity, int value)
{
    if (initial_capacity <= 0) {
        throw std::invalid_argument("initial_capacity must be greater than 0");
    }
    length = initial_capacity;
    capacity = initial_capacity;
    data =  new int [capacity]; //instantiate new array with predetermined "capacity"

    for (int i = 0; i < capacity; i++) {
        data[i] = value; // sets value of element[0]
    }
}

MyArray::MyArray(const MyArray& other): MyArray()
{
    if (other.data != nullptr) {
        length = other.length;
        capacity = other.capacity;
        data = new int [capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
}

MyArray::~MyArray()
{
    delete[] data;
    data = nullptr;
    length = 0;
    capacity = 0;
}

int * MyArray::get_data()
{
    return data;
}

int MyArray::get_length()
{
    return length;
}

int MyArray::get_capacity()
{
    return capacity;
}
void MyArray::shift_right(int endIndex) {
    for (int i = length - 1; i >= endIndex; i--) {
        data[i+1] = data[i];
    }
}
void MyArray::shift_left(int startIndex) {
    for (int i = startIndex; i < length -1; i++) {
        data[i] = data[i + 1];
    }
}
void MyArray::push_back(int value)
{
    check_size();
    data[length] = value;
    length++;
}

void MyArray::push_front(int value)
{
    check_size();
    shift_right(0);
    data[0] = value;
    length++;
}

void MyArray::insert_sorted(int value)
{
    check_size();
    int index = 0;
    while (index < length && data[index] < value) {
        index++;
    }
    shift_right(index);
    data[index] = value;
    length++;
}

void MyArray::pop_front()
{
    if (length > 0) {
        shift_left(0);
        length--;
    }
}

void MyArray::pop_back()
{
    if (length > 0) {
        length--;
    }
}

void MyArray::delete_at(int index) {
    if (length > 0 && index >= 0 && index < length ) {
        shift_left(index);
        length--;
    }
}

void MyArray::delete_first_value(int value)
{
    int index = linear_search(value);
    if (index != -1) {
        delete_at(index);
    }
}

void MyArray::delete_all_value(int value) {
    int writeIndex = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != value) {
            data[writeIndex] = data[i];
            writeIndex++;
        }
    }
    length = writeIndex;
}

int MyArray::linear_search(int value)
{
    for (int i = 0; i < length; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1;
}

int MyArray::binary_search_iterative(int value) {
    int low = 0, high = length - 1, mid = 0;
    while (low <= high) {
        mid = (high + low) / 2;
        if (data[mid] == value) {
            return mid;
        }
        if (data[mid] > value) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1;
}

int MyArray::binary_search_recursive(int value) {
    if (length == 0) {
        return -1;
    }
    return recursive_helper(value,0,length-1);
}
int MyArray::recursive_helper(int value, int low, int high){
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;
    if (data[mid] == value) {
        return mid;
    }
    if (data[mid] > value) {
        return recursive_helper(value, low, mid - 1);
    }
    return recursive_helper(value, mid + 1, high);
}

int MyArray::count_values(int value) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] == value) {
            count++;
        }
    }
    return count;
}

void MyArray::sort()
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

void MyArray::reverse() {
    int temp = 0;
    int left = 0, right = length - 1;
    while (left < right) {
        temp = data[left];
        data[left] = data[right];
        data[right] = temp;
        left++;
        right--;
    }
}

MyArray MyArray::subarray(int start, int end) {
    if (start < 0 || end >= length || start > end) {
        throw std::out_of_range("start out of range");
    }
    int newCapacity = end - start + 1;
    int writeIndex = 0;
    MyArray newArray = MyArray(newCapacity,0);
    for (int i = start; i <= end; i++) {
        newArray.data[writeIndex] = data[i];
        writeIndex++;
    }
    return newArray;
}

MyArray MyArray::unique() {
    MyArray newArray = MyArray();
    for (int i = 0; i < length; i++) {
        int value = data[i];
        int found = newArray.linear_search(value);
        if (found == -1) {
            newArray.push_back(value);
        }
    }
    return newArray;
}

void MyArray::print()
{
    std::cout << "data = (";
        for (int i = 0; i < length; i++) {
            std::cout << data[i];
            if (i != length - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")" << std::endl;


    std::cout << "length = " << length << std::endl;
    std::cout << "capacity = " << capacity << std::endl;
}

int & MyArray::operator[](int index)
{
    if (index < 0 || index >= length) {
        throw std::out_of_range("index out of range");
    }
    return data[index];
}

MyArray & MyArray::operator=(const MyArray &other) {
    /*Step 1: Check for Self-Assignment

        Check if the current object's address matches the incoming object's address (this == &other).

        If they are the same instance (e.g., arr1 = arr1;), do nothing and return *this immediately to avoid deleting your own memory before copying.
*/
    if (this == &other) {
        return *this;
    }
    /*Step 2: Free Existing Dynamic Memory

        Because the current object already has its own allocated heap memory, release it using delete[] data;.
*/
    delete[] data;
    /*Step 3: Deep Copy the State and Data

        Copy length and capacity from other.

        If other.data is not null, allocate a new heap array: data = new int[capacity];.

        Copy every element from other.data into data using a loop (or set data = nullptr if other.data is empty).
*/
    length = other.length;
    capacity = other.capacity;
    if (other.data != nullptr) {
        data = new int[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
    else {
        data = nullptr;
    }
    /*
    Step 4: Return a Reference to the Current Object

        End the function by returning *this (enabling chained assignment like a = b = c;).
        */
    return *this;
}

void MyArray::resize() {
    int new_capacity = capacity + 10;
    int* new_data  = new int [new_capacity];
    for (int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }
    delete [] data;
    data = new_data;
    capacity = new_capacity;
}

void MyArray::check_size()
{
    if (length == capacity) {
        resize();
    }
}


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
int main() {
    unitTest();
    testExceptions(); // created with gemini
    return 0;
}