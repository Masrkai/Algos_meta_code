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
  //--------------------------------------------------------->

  static void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
  //--------------------------------------------------------->

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
  //--------------------------------------------------------->
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
    while (head != nullptr) { //> You can comment out the things between the "{}" brackets but this approach is generally more safe
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  // Insert at the beginning of the list
  void insertAtStart(int value) {
      Node* newNode = new Node(value);
      newNode->next = head;
      head = newNode;
  }
  //--------------------------------------------------------->

  // Insert at the end of the list (your existing insert function renamed)
  void insertAtEnd(int value) {
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
  //--------------------------------------------------------->

  // Insert at a specific position (0-based index)
  void insertAtPosition(int value, int position) {
      if (position < 0) {
          cout << "Invalid position. Position should be non-negative." << endl;
          return;
      }

      if (position == 0) {
          insertAtStart(value);
          return;
      }

      Node* newNode = new Node(value);
      Node* current = head;
      int currentPos = 0;

      // Move to the position just before where we want to insert
      while (current != nullptr && currentPos < position - 1) {
          current = current->next;
          currentPos++;
      }

      // Check if position is out of bounds
      if (current == nullptr) {
          cout << "Position out of bounds. The list has only " << currentPos << " elements." << endl;
          delete newNode;
          return;
      }

      // Insert the new node
      newNode->next = current->next;
      current->next = newNode;
  }
  //--------------------------------------------------------->

  // Remove the first node in the list
  void removeFirst() {
      // Check if list is empty
      if (head == nullptr) {
          cout << "List is empty. Nothing to remove." << endl;
          return;
      }

      // Store the head node and move head to next node
      Node* toDelete = head;
      head = head->next;

      // Free the memory of old head
      delete toDelete;
  }
  //--------------------------------------------------------->

  // Remove the last node in the list
  void removeLast() {
      // Case 1: Empty list
      if (head == nullptr) {
          cout << "List is empty. Nothing to remove." << endl;
          return;
      }

      // Case 2: Only one node in the list
      if (head->next == nullptr) {
          delete head;
          head = nullptr;
          return;
      }

      // Case 3: More than one node
      // We need to find the second-to-last node
      Node* current = head;
      while (current->next->next != nullptr) {
          current = current->next;
      }

      // Now current points to second-to-last node
      delete current->next;       // Delete the last node
      current->next = nullptr;    // Set the new last node's next to nullptr
  }
  //--------------------------------------------------------->

  // Remove node with specific key/value
  void removeKey(int key) {
      // Case 1: Empty list
      if (head == nullptr) {
          cout << "List is empty. Nothing to remove." << endl;
          return;
      }

      // Case 2: Key is in head node
      if (head->data == key) {
          Node* toDelete = head;
          head = head->next;
          delete toDelete;
          return;
      }

      // Case 3: Key is in rest of the list
      Node* current = head;

      // Search for node containing the key
      // Stop when either:
      // - We find the key in the next node
      // - We reach the end of the list
      while (current->next != nullptr && current->next->data != key) {
          current = current->next;
      }

      // If we reached the end without finding the key
      if (current->next == nullptr) {
          cout << "Key " << key << " not found in the list." << endl;
          return;
      }

      // Remove the node containing the key
      Node* toDelete = current->next;           // Store node to delete
      current->next = current->next->next;      // Skip over the node
      delete toDelete;                          // Free the memory
  }
  //--------------------------------------------------------->

  // Print the list
  void print() const {
    Node* current = head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << endl;
  }
  //--------------------------------------------------------->
};

// Search algorithms
class SearchAlgorithms {
public:
  static int binarySearch(int arr[], int size, int target) {
      int left = 0,right = size - 1;  // Initialize right to last index

      while (left <= right) {  // KEY DIFFERENCE 1: Uses <= to ensure all elements are checked
          // KEY DIFFERENCE 2: Simple mid calculation is fine since overflow is rare in practice
          int mid = (left + right) / 2;
          if (arr[mid] == target) {
              return mid;
          }else if (arr[mid] > target) {
              right = mid - 1;  // KEY DIFFERENCE 3: Properly reduces right boundary
          }else {
              left = mid + 1;
          }
      }
      return -1;  // KEY DIFFERENCE 4: Always returns -1 if target not found
  }
  //--------------------------------------------------------->

  // Defective Binary Search Implementation (with fixes commented)
  static int defectiveBinarySearch(int arr[], int size, int target) {
      int left = 0, right = size - 1;

      // DEFECT 1: Uses < instead of <=, which can miss checking the last element
      while (left < right) {  // Should be: while (left <= right)
          // More robust mid calculation to prevent integer overflow
          int mid = left + (right - left) / 2;
          if (arr[mid] == target) {
              return mid;
          }else if (arr[mid] < target) {
              left = mid + 1;
          }else {
              right = mid;                            // DEFECT 2: Doesn't decrease right boundary properly
          }                                          // Should be: right = mid - 1
      }
      return  -1;                                  // DEFECT 3: Final check is unreliable due to previous defects
  }
  //--------------------------------------------------------->
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
//--------------------------------------------------------->

    static void selectionSort(int arr[], int size) {
        for (int i = 0; i < size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                ArrayHelper::swap(arr, i, min_idx);
            }
        }
    }
//--------------------------------------------------------->

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
//--------------------------------------------------------->

    static void merge(int arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Create temporary arrays
        int* L = new int[n1];
        int* R = new int[n2];

        // Copy data to temporary arrays
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        // Merge the temporary arrays back into arr
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements of L[]
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copy remaining elements of R[]
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        // Free temporary arrays
        delete[] L;
        delete[] R;
    }

    static void mergeSortHelper(int arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void mergeSort(int arr[], int size) {
        mergeSortHelper(arr, 0, size - 1);
    }
//--------------------------------------------------------->

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

    static void quickSortHelper(int arr[], int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    static void quickSort(int arr[], int size) {
        quickSortHelper(arr, 0, size - 1);
    }
  //--------------------------------------------------------->
};


static int separate(){
cout << "-------------------------------------------------------------------------- "<< endl ;
return 0;
};

// Main function to demonstrate functionality
int main() {
  srand(static_cast<unsigned int>(time(0))); // Seed for random numbers

  // Generate a random array
  int size = 20;
  int minimum_num = 1, maximum_num = 100;
  int* randomArray = ArrayHelper::generateRandomArray(size, minimum_num, maximum_num);

  separate();

  cout << "Randomly generated array: ";
  ArrayHelper::printArray(randomArray, size);

  // Sort the array
  SortingAlgorithms::bubbleSort(randomArray, size);

  cout << "Sorted random array: ";
  ArrayHelper::printArray(randomArray, size);

  separate();

  // Search in the array
  int target = randomArray[5]; // Picking a value from the array
  int searchResult = SearchAlgorithms::binarySearch(randomArray, size, target);
  if (searchResult != -1) {
    cout << "BinarySearch found " << target << " at index " << searchResult << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  int searchResult2 = SearchAlgorithms::defectiveBinarySearch(randomArray, size, target);
  if (searchResult2 != -1) {
    cout << "defective BinarySearch found " << target << " at index " << searchResult << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  separate();

  // Demonstrate LinkedList
  LinkedList list;
  cout << "Adding elements to linked list..." << endl;
  for (int i = 0; i < size; i++) {
    list.insertAtEnd(randomArray[i]);
  }
  cout << "Linked list contents: ";
  list.print();

  // Remove an element
  cout << "Removing " << randomArray[2] << " from linked list." << endl;
  list.removeKey(randomArray[2]);
  cout << "Updated linked list: ";
  list.print();

  separate();

  // Cleanup
  delete[] randomArray;

  return 0;
}
