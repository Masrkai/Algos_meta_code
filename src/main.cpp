#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
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

  // Generate a random array with given size and range
  static int* generateRandomArray(int size, int minimum_num, int maximum_num) {
    if (size <= 0 || minimum_num > maximum_num) {
      cerr << "Invalid parameters for random array generation!" << endl;
      return nullptr;
    }
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = minimum_num + rand() % (maximum_num - minimum_num + 1);
    }
    return arr;
  }
};

// Linked List implementation
class LinkedList {
private:
  struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
  };

  Node* head;

public:
  LinkedList() : head(nullptr) {}

  ~LinkedList() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  // Insert at the end
  void insert(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
    } else {
      Node* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }
  }

  // Delete a node by value
  void remove(int value) {
    if (head == nullptr) {
      cout << "List is empty." << endl;
      return;
    }

    if (head->data == value) {
      Node* temp = head;
      head = head->next;
      delete temp;
      return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
      current = current->next;
    }

    if (current->next == nullptr) {
      cout << "Value not found in the list." << endl;
      return;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
  }

  // Print the list
  void print() const {
    Node* current = head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
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
};

// Sorting algorithms (unchanged from your code)
class SortingAlgorithms {
public:
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
      if (!swapped) {
        break;
      }
    }
  }
};

// Main function to demonstrate functionality
int main() {
  srand(static_cast<unsigned int>(time(0))); // Seed for random numbers

  // Generate a random array
  int size = 10;
  int minimum_num = 1, maximum_num = 100;
  int* randomArray = ArrayHelper::generateRandomArray(size, minimum_num, maximum_num);
  cout << "Randomly generated array: ";
  ArrayHelper::printArray(randomArray, size);

  // Sort the array
  SortingAlgorithms::bubbleSort(randomArray, size);
  cout << "Sorted random array: ";
  ArrayHelper::printArray(randomArray, size);

  // Search in the array
  int target = randomArray[5]; // Picking a value from the array
  int searchResult = SearchAlgorithms::binarySearch(randomArray, size, target);
  if (searchResult != -1) {
    cout << "Element " << target << " found at index " << searchResult << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  // Demonstrate LinkedList
  LinkedList list;
  cout << "Adding elements to linked list..." << endl;
  for (int i = 0; i < size; i++) {
    list.insert(randomArray[i]);
  }
  cout << "Linked list contents: ";
  list.print();

  // Remove an element
  cout << "Removing " << randomArray[2] << " from linked list." << endl;
  list.remove(randomArray[2]);
  cout << "Updated linked list: ";
  list.print();

  // Cleanup
  delete[] randomArray;

  return 0;
}
