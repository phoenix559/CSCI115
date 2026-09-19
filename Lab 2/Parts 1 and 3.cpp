#include <iostream>
#include <cmath>
// Part 1
int f1_recursive( int i, const int n ) {
    if (i > n)
        return 0;
    return (2*i + 9) + f1_recursive(i+1,n);

}

int f1_iterative(int i,int n) {
    int f1 = 0;
    for ( i; i <= n; i++)
        f1 += (2*i + 9);
    return f1;
}

int f2_recursive( int i, int n ) {
    int f2 = 0;
    if (i > n)
        return 0;
    return 5*(std::pow(i,3)) + std::pow(i,2) + f2_recursive(i+1,n);
}

int f2_iterative( int i, int n ) {

    int f2 = 0;
    for (i; i <= n; i++)
        f2 += 5*(std::pow(i,3)) + std::pow(i,2);
    return f2;
}

double f3_recursive( int i, int n ) {

    if (i > n)
        return 0;
    return 1/sqrt(5 * i) + f3_recursive(i+1,n);
}
double f3_iterative( int i, int n ) {
    double f3 = 0.0;
    for (i; i <= n; i++) {
        f3 += 1/sqrt(5*i);
    }
    return f3;
}


void run_part_1() {
    int i = 0;
    int n = 100;

    std::cout << "\nSum of (2*i + 9) from 0 to 100 = 11009" << std::endl;
    std::cout << "Recursive: " << f1_recursive(i, n) << "\n";
    std::cout << "Iterative: " << f1_iterative(i, n) << "\n";

    std::cout << "\nSum of (5*i^3 + i^2) from 0 to 100 = 127850850" << std::endl;
    std::cout << "Recursive: " << f2_recursive(i, n) << "\n";
    std::cout << "Iterative: " << f2_iterative(i, n) << "\n";
    i = 1;
    n = 500;
    std::cout << "\nSum of (5*i)^(-1/2) from 0 to 500 = 19.3569" << std::endl;
    std::cout << "Recursive: " << f3_recursive(i, n) << "\n";
    std::cout << "Iterative: " << f3_iterative(i, n) << "\n";
}

//Part 3
void Fib(int x, int* result) {
    if (result !=  nullptr) {
        int curr = 1;
        if (x < 0)
            curr = -1; // error index
        else if (x == 0)
            curr = 0;
        else if (x > 1){ // skipped x==1 as it returns default curr = 1;
            int prev = 0, next = 0;
            for (int i = 2; i <= x; i++) {
                next = curr + prev;
                prev = curr;
                curr = next;
            }
        }
        *result = curr;
    }
}
void test_fib() {
    int test_numbers[5] ={-4,0,1,5,12}, expected[5] = {-1,0,1,5,144};
    int result = 0;
    std::cout << "\n\nFibonacci Itterative:" << std::endl;
    std::cout << "Number tested\t Expected\t Calculated Value" << std::endl;
    for (int i = 0; i < 5; i++) {
        Fib(test_numbers[i], &result);
        std::cout <<  test_numbers[i] << "\t\t\t\t\t" << expected[i] << "\t\t\t" << result << std::endl;
    }
}

int main() {
    run_part_1();
    test_fib();
    return 0;
}