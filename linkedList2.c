#include <stdio.h> // Add the necessary header file for the 'int' data type
#include <stdlib.h> // Add the necessary header file for the 'malloc' function
#include <time.h> // Add the necessary header file for the 'time' function
int* sort (int* A, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int j = i, val = A[j];
        while (j > 0 && !(A[j-1] <= val))
        {
            A[j] = A[j-1];
            --j;
        }
        A[j] = val;
    }
    return A;
}
int isDuplicate(int* A, int n, int num)
{
    for (int i = 0; i < n; ++i)
    {
        if (A[i] == num)
        {
            return 1;
        }
    }
    return 0;
}

int main(){
    printf("started\n");
    long n = 100000;
    int* A = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {
        int num;
        do {
            num = rand() % 10000000 ;
        } while (isDuplicate(A, i, num)); // Check if the number is a duplicate
        A[i] = num;
    }

    int* B = sort(A, n);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", B[i]);
    }
    free(A);
    free(B);
    printf("finished\n");
    return 0;
    }
