#include <iostream>
using namespace std;

// Helper functions for array operations
class ArrayHelper {
public:
  static void swap(int arr[], int pos1, int pos2) {
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
  }

  static void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
};

// Search algorithms
class SearchAlgorithms {
public:
  // Iterative binary search
  static int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
      int middle = (left + right) / 2;

      if (arr[middle] == target) {
        return middle;
      }

      if (arr[middle] > target) {
        right = middle - 1;
      } else {
        left = middle + 1;
      }
    }

    return -1; // Target not found
  }

  // Recursive binary search
  static int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) {
      return -1;
    }

    int middle = (left + right) / 2;

    if (arr[middle] == target) {
      return middle;
    }

    if (target < arr[middle]) {
      return binarySearchRecursive(arr, left, middle - 1, target);
    }

    return binarySearchRecursive(arr, middle + 1, right, target);
  }

  // Linear search
  static int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
      if (arr[i] == target) {
        return i;
      }
    }
    return -1; // Target not found
  }

  // Recursive linear search
  static int linearSearchRecursive(int arr[], int size, int target) {
    if (size <= 0) {
      return -1;
    }

    if (arr[size - 1] == target) {
      return size - 1;
    }

    return linearSearchRecursive(arr, size - 1, target);
  }
};

// Sorting algorithms
class SortingAlgorithms {
public:
  // Bubble Sort
  static void bubbleSort(int arr[], int size) {
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
      swapped = false;
      for (int j = 0; j < size - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          ArrayHelper::swap(arr, j, j + 1);
          swapped = true;
        }
      }
      // If no swapping occurred, array is sorted
      if (!swapped) {
        break;
      }
    }
  }

  // Selection Sort
  static void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
      int minIndex = i;
      for (int j = i + 1; j < size; j++) {
        if (arr[j] < arr[minIndex]) {
          minIndex = j;
        }
      }
      if (minIndex != i) {
        ArrayHelper::swap(arr, i, minIndex);
      }
    }
  }

  // Insertion Sort
  static void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
      int key = arr[i];
      int j = i - 1;

      while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = key;
    }
  }

  // Quick Sort
  static void quickSort(int arr[], int low, int high) {
    if (low < high) {
      int pivotIndex = partition(arr, low, high);
      quickSort(arr, low, pivotIndex - 1);
      quickSort(arr, pivotIndex + 1, high);
    }
  }

private:
  static int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
      if (arr[j] <= pivot) {
        i++;
        ArrayHelper::swap(arr, i, j);
      }
    }

    ArrayHelper::swap(arr, i + 1, high);
    return i + 1;
  }
};

// Mathematical functions
class MathFunctions {
public:
  // Calculate 2^n recursively
  static int powerOfTwo(int n) {
    if (n == 0) {
      return 1;
    }
    return 2 * powerOfTwo(n - 1);
  }

  // Calculate combination (n choose k)
  static int combination(int n, int k) {
    if (k == 1) {
      return n;
    }
    if (n == k || k == 0) {
      return 1;
    }
    return combination(n - 1, k - 1) + combination(n - 1, k);
  }

  // Calculate median of an array
  static int median(int arr[], int size) {
    // First sort the array
    SortingAlgorithms::bubbleSort(arr, size);

    if (size % 2 != 0) {
      return arr[size / 2];
    }

    return (arr[(size - 1) / 2] + arr[size / 2]) / 2;
  }
};

int main() {
  // Example usage
  int testArray[] = {64, 34, 25, 12, 22, 11, 90};
  int size = sizeof(testArray) / sizeof(testArray[0]);

  cout << "Original array: ";
  ArrayHelper::printArray(testArray, size);

  // Test sorting
  SortingAlgorithms::bubbleSort(testArray, size);
  cout << "Sorted array: ";
  ArrayHelper::printArray(testArray, size);

  // Test searching
  int target = 25;
  int result = SearchAlgorithms::binarySearch(testArray, size, target);
  if (result != -1) {
    cout << "Element " << target << " found at index " << result << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  // Test math functions
  cout << "2^5 = " << MathFunctions::powerOfTwo(5) << endl;
  cout << "Median: " << MathFunctions::median(testArray, size) << endl;

  return 0;
}