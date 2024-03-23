#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int mid;
    
    while (low <= high) {
        mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            low = mid + 1;

        else
            high = mid - 1;
    }

    // 如果元素不存在於陣列中返回 -1
    return -1;
}

int main(){
    int arr[100];
    srand((unsigned)time(0));

    for(int i = 0; i < 100; i++){
        arr[i] = rand() % 1000; 
    }
    sort(arr, arr + 100);

    int target = arr[50];
    
    int result = binarySearch(arr, 100, target);
    if (result != -1)
        cout << "Element found at index " << result << endl;
    else
        cout << "Element not found in the array" << endl;

    return 0;
}
