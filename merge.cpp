#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to merge two sorted subarrays
void merge(vector<int>& arr, int low, int mid, int high) {
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    vector<int> leftArr(leftSize);
    vector<int> rightArr(rightSize);

    // Copy data to temporary arrays
    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = arr[low + i];
    for (int j = 0; j < rightSize; ++j)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the two temporary arrays back into arr
    int i = 0, j = 0, k = low;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr, if any
    while (i < leftSize) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr, if any
    while (j < rightSize) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Function to perform parallel merge sort
void parallelMergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        // Parallelize the recursive calls using OpenMP
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);
            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        // Merge the sorted subarrays
        merge(arr, low, mid, high);
    }
}

int main() {
    vector<int> arr = {9, 5, 7, 1, 3};

    // Print the original array
    cout << "Original array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    // Perform parallel merge sort
    parallelMergeSort(arr, 0, arr.size() - 1);

    // Print the sorted array
    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
