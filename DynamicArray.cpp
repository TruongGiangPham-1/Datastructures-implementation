#include <cstdio>
#include <iostream>
#include <stdexcept> // Required for standard exceptions

using namespace std;



/*
  vector<int> a(n, 0)  // initialization
  vector<int> a;       // initialize with size 0

  a.push_back(1)
  a.pop_back()
  a[i]                 // access
*/

void copy_int(int* src, int* dest, size_t src_size, size_t dest_size) {
    // assume that src < dest
    if (src_size > dest_size) {
        throw runtime_error("copy_int src is bigger than dest");
    }
    for (size_t i = 0; i < src_size; i++) {
        *(dest + i) = *(src + i);
    }
}

void fill_array(int* arr, size_t size, int val) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = val;
    }
    return;
}

typedef struct DynamicArray {
    int* a;
    // rule: if len >= cap, then allocate cap*2
    size_t cap;    // actual capacity of the allocated array
    size_t len;   // len the user see
    size_t num_realloc;
    size_t realloc_mult = 2;

    // array of size 0
    DynamicArray() {
        cap = 5;  // some albitrary capacity
        len = 0;
        a = new int[cap];
        num_realloc = 0;
    }

    // vector<int> a(size, init_value)
    DynamicArray(size_t size, int val) {
        len = size;
        cap = size*realloc_mult;  // some albitrary capacity
        a = new int[cap];
        
        fill_array(a, len, val);
        num_realloc = 0;
    }

    void push_back(int val) {
        // check if there is capacity to add
        if (len + 1 > cap) {
            // we hav to allocate
            int* biggerArray = new int[cap*realloc_mult];
            // copy elements fomr old to new
            copy_int(a, biggerArray, cap, cap*realloc_mult);
            // free them 
            delete[] a;
            a = biggerArray;
            cap = cap*realloc_mult;

            num_realloc ++;
        } 
        a[len] = val;
        len ++;
    }

    size_t size() const {
        return len;
    }
    
    // when there is const and non-const version of method. 
    // the compiler call the const one when you declare "const DynamicArray a", 
    // the compiler call the non-const one when you declare normally (non-const)
    int& operator[](int index) {  // allow lvalue assignment like arr[i] = val. 
        /*
            negative index support
            index -1 == (len - 1)
            index -2 == (len - 2)
            index -3 == (len - 3)
            ...
            index -len == (len - len) .. can wrap around
        */
        // NO BOUND CHECKING like vector []
        if (index < 0) return a[len + index];
        return a[index];  // lvalue
    }

    const int& operator[](int index) const {
        // e.g const DynamicArray a; a[i] = val is compilation error
        // in const method, you cannot reassign the the pointer "a".
        // but you can still change the data it reference.
        if (index < 0) return a[len + index];
        return a[index];  // const lvalue int&. cannot be reassigned. (enfored by the return type).
    }

    

    ~DynamicArray() {
        delete[] a;
    }



} DynamicArray;

void printArray(DynamicArray & a) {
    for (size_t i = 0; i < a.size(); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main() {
            
    DynamicArray a; 
    for (int i = 0; i < 6; i++) {
        a.push_back(i);
    }
    printArray(a);

    printf("negative index; printing backward\n");
    for (int i = 1; i <= a.size(); i++) {  // print backward using negative index:
        printf("%d ", a[-i]);
    }
    printf("\n");
    
        
    DynamicArray b(10, 4);
    printArray(b);

    for (int i = 0; i < b.size(); i++) {
        b[i] = 5;
    }
    printArray(b);
    printf("\n");

    const DynamicArray const_arr(5, 0);  // const_arr[i] = val is compile error

        


    return 0;
}



