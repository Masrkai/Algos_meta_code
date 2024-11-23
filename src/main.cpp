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
    list.insertAtEnd(randomArray[i]);
  }
  cout << "Linked list contents: ";
  list.print();

  // Remove an element
  cout << "Removing " << randomArray[2] << " from linked list." << endl;
  list.removeKey(randomArray[2]);
  cout << "Updated linked list: ";
  list.print();

  // Cleanup
  delete[] randomArray;

  return 0;
}
