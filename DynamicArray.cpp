#include <iostream>
#include <stdexcept> // Required for standard exceptions

using namespace std;


void printArray(int* a, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

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

typedef struct DynamicArray {
    int* a;
    // rule: if size >= cap, then allocate cap*2
    size_t cap;    // actual capacity of the allocated array
    size_t size;   // size the user see
    size_t num_realloc;
    size_t realloc_mult = 2;

    // array of size 0
    DynamicArray() {
        cap = 5;  // some albitrary capacity
        size = 0;
        a = new int[cap];
        num_realloc = 0;
    }

    void push_back(int val) {
        // check if there is capacity to add
        if (size + 1 > cap) {
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
        a[size] = val;
        size ++;
    }

} DynamicArray;


int main() {
    size_t len = 3;
            
    DynamicArray a; 
    for (int i = 0; i < 100; i++) {
        a.push_back(i);
    }
        
    printArray(a.a, a.size);
    printf("a.cap %zu, a.size %zu, num_realloc %zu\n", a.cap, a.size, a.num_realloc);
    return 0;
}
