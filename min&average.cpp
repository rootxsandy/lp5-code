#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to find the minimum value in parallel using reduction
int parallelMin(const vector<int>& arr) {
    int minVal = arr[0];

    // Perform parallel reduction using OpenMP
    #pragma omp parallel for reduction(min: minVal)
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    return minVal;
}

// Function to compute the average value in parallel using reduction
double parallelAverage(const vector<int>& arr) {
    int sum = 0;

    // Perform parallel reduction using OpenMP
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }

    double average = static_cast<double>(sum) / arr.size();
    return average;
}

int main() {
    vector<int> arr = {9, 5, 7, 1, 3};

    // Find the minimum value in parallel
    int minVal = parallelMin(arr);
    cout << "Minimum value: " << minVal << endl;

    // Compute the average value in parallel
    double average = parallelAverage(arr);
    cout << "Average value: " << average << endl;

    return 0;
}
