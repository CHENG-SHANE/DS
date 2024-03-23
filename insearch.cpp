#include <iostream>
using namespace std;

int* sort (int* A, int n){ 
    for (int i = 1; i < n; ++i) { 
        int j = i, val = A[j]; 
        while (j > 0 && !(A[j-1] <= val)) { 
            A[j] = A[j-1]; --j; 
        } 
        A[j] = val; 
    } 
return A; 
}

int main(){ 
    int A[] = { 12, 11, 13, 9, 6 }; 
    int n = 5;
    sort(A, n);                                                          
    for (int i = 0; i < n; ++i) 
        cout << A[i] << " ";
    
return 0; 
}