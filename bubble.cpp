#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform bubble sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    // Perform bubble sort iterations
    for (int i = 0; i < n - 1; ++i) {
        // Flag to check if any swap occurred in this iteration
        bool swapped = false;

        // Parallelize the loop iterations using OpenMP
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            // Check if adjacent elements are in the wrong order
            if (arr[j] > arr[j + 1]) {
                // Swap the elements
                swap(arr[j], arr[j + 1]);
                
                // Set the swapped flag to true
                swapped = true;
            }
        }

        // If no swaps occurred in this iteration, the array is already sorted
        if (!swapped)
            break;
    }
}

int main() {
    vector<int> arr = {9, 5, 7, 1, 3};

    // Print the original array
    cout << "Original array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    // Perform parallel bubble sort
    bubbleSort(arr);

    // Print the sorted array
    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
