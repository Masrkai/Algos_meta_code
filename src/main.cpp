
#include <iostream>
#include <vector>
#include <cassert>


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
      // Check for invalid input parameters
      if (size <= 0 || minimum_num > maximum_num) {
          cerr << "Invalid parameters for random array generation!" << endl;
          return nullptr; // Return null pointer to indicate error
      }

      // Allocate memory for the array
      int* arr = new int[size];

      // Generate random numbers within the specified range and store them in the array
      for (int i = 0; i < size; i++) {
          // Generate a random integer between 0 and (maximum_num - minimum_num) inclusive
          int random_num = rand() % (maximum_num - minimum_num + 1);
          // Add the minimum number to the random number to get a number within the desired range
          arr[i] = minimum_num + random_num;
      }

      return arr; // Return the pointer to the generated array
  }
  //--------------------------------------------------------->
};

const int maxQueue = 100; // Define the maximum size of the queue

template <class queueElementType>
class Queue {
private:
    queueElementType queueArray[maxQueue]; // Array to store queue elements
    int front; // Index of the front element
    int rear;  // Index of the rear element

    // Helper function to compute the next position in a circular manner
    int nextPos(int p) {
        return (p == maxQueue - 1) ? 0 : p + 1;
    }

public:
    // Constructor
    Queue() : front(0), rear(0) {}

    // Check if the queue is empty
    bool isEmpty() {
        return front == rear;
    }

    // Check if the queue is full
    bool isFull() {
        return nextPos(rear) == front;
    }

    // Add an element to the rear of the queue
    void enqueue(queueElementType e) {
        assert(!isFull()); // Ensure the queue is not full
        queueArray[rear] = e; // Insert element at the rear
        rear = nextPos(rear); // Move rear to the next position
    }

    // Remove and return the element from the front of the queue
    queueElementType dequeue() {
        assert(!isEmpty()); // Ensure the queue is not empty
        queueElementType result = queueArray[front]; // Get the front element
        front = nextPos(front); // Move front to the next position
        return result;
    }

    // Return the front element without removing it
    queueElementType getFront() {
        assert(!isEmpty()); // Ensure the queue is not empty
        return queueArray[front]; // Return the front element
        }
};



class HashTable {

public:

    // Define a structure to hold Person data
    struct PersonData {
        string lastName;    // Person's last name
        string firstName;   // Person's first name
        string hireDate;    // Person's hire date in MM-DD-YYYY format
    };

    // Enum to represent the status of each slot in the hash table
    enum SlotType { Empty, Deleted, InUse };

    // Structure to represent a slot in the hash table
    struct Slot {
        SlotType status;    // Status of the slot (Empty, Deleted, InUse)
        int key;            // Key stored in the slot (Person ID)
        PersonData data;  // Data associated with the key
    };

    static const int maxTable = 11; // Size of the hash table (prime number to reduce collisions)
    Slot hashTableArray[maxTable];  // Array to represent the hash table
    int entries; // Number of valid entries (slots marked as InUse) in the hash table

    // Hash function to calculate the index for a given key
    int hash(int key) {
        return key % maxTable; // Simple division hashing
    }

    // Helper function to determine the next position in the hash table (linear probing)
    int probe(int pos) {
        if (pos == maxTable - 1) // If at the end of the table, wrap around to the beginning
            return 0;
        else
            return pos + 1; // Otherwise, move to the next position
    }

    // Private method to search for a key in the hash table
    bool search(int searchKey, int& pos) {
        while (hashTableArray[pos].status != Empty) { // Continue searching until an empty slot is found
            if (hashTableArray[pos].status == InUse && hashTableArray[pos].key == searchKey) {
                return true; // Key found
            } else {
                pos = probe(pos); // Move to the next position using linear probing
            }
        }
        return false; // Key not found
    }

    // Constructor to initialize the hash table
    HashTable() : entries(0) {
        for (int i = 0; i < maxTable; i++) {
            hashTableArray[i].status = Empty; // Mark all slots as Empty
        }
    }

    // Method to check if the hash table is empty
    bool isEmpty() const {
        return entries == 0; // True if no entries are in use
    }

    // Method to check if the hash table is full
    bool isFull() const {
        return entries == maxTable - 1; // True if only one slot is left empty
    }

    // Method to get the total size of the hash table
    int getSize() const {
        return maxTable; // Return the total number of slots
    }

    // Method to get the current number of valid entries in the hash table
    int getLength() const {
        return entries; // Return the number of slots marked as InUse
    }

    // Method to insert a new key and data into the hash table
    void insert(int insertKey, const PersonData& insertData) {
        assert(entries < maxTable - 1); // Ensure the table is not full
        int pos = hash(insertKey); // Calculate the home address for the key

        if (!search(insertKey, pos)) { // If the key does not exist in the table
            pos = hash(insertKey); // Recalculate the home address
            while (hashTableArray[pos].status == InUse) { // Find the next available slot
                pos = probe(pos);
            }
            // Insert the key and data into the available slot
            hashTableArray[pos].status = InUse;
            hashTableArray[pos].key = insertKey;
            hashTableArray[pos].data = insertData;
            entries++; // Increment the number of entries
        } else {
            // If the key exists, update the data
            hashTableArray[pos].data = insertData;
        }
    }

    // Method to lookup data associated with a key in the hash table
    bool lookup(int lookupKey, PersonData& lookupData) {
        int pos = hash(lookupKey); // Calculate the home address for the key
        if (search(lookupKey, pos)) { // If the key is found
            lookupData = hashTableArray[pos].data; // Retrieve the data
            return true;
        } else {
            return false; // Key not found
        }
    }

    // Method to delete a key and its associated data from the hash table
    void deleteKey(int deleteKey) {
        int pos = hash(deleteKey); // Calculate the home address for the key
        if (search(deleteKey, pos)) { // If the key is found
            hashTableArray[pos].status = Deleted; // Mark the slot as Deleted
            entries--; // Decrement the number of entries
        }
    }

    // Method to print the contents of the hash table
    void dump() const {
        for (int i = 0; i < maxTable; i++) { // Iterate through all slots
            cout << i << "\t";
            switch (hashTableArray[i].status) { // Check the status of each slot
                case InUse:
                    cout << "In Use\t" << hashTableArray[i].key << endl; // Print InUse slots
                    break;
                case Deleted:
                    cout << "Deleted\t" << hashTableArray[i].key << endl; // Print Deleted slots
                    break;
                case Empty:
                    cout << "Empty" << endl; // Print Empty slots
                    break;
            }
        }
        cout << endl << "Table size: " << getSize() << ", Number of current entries: " << getLength() << endl;
    }
};




class LinkedList {
    private:
      // Node structure for the linked list
      struct Node {
        int data; // Data stored in the node
        Node* next; // Pointer to the next node in the list

        // Constructor to initialize a node with a given value
        Node(int value) : data(value), next(nullptr) {}
      };

      Node* head; // Pointer to the head of the linked list
      Node* tail; // Pointer to the tail of the linked list

    public:
      // Default constructor to initialize an empty linked list
      LinkedList() : head(nullptr) {}

      // Destructor to deallocate memory and prevent memory leaks
      ~LinkedList() {
        while (head != nullptr) { // Iterate through the list and delete each node
          Node* temp = head; // Store the current head node
          head = head->next; // Move the head pointer to the next node
          delete temp; // Delete the current head node
        }
      }

        // Insert a new node at the beginning of the linked list
        void insertAtStart(int value) {
            // Create a new node with the given value
            Node* newNode = new Node(value);
            // Set the next pointer of the new node to the current head
            newNode->next = head;
            // Update the head pointer to point to the new node
            head = newNode;
        }
//--------------------------------------------------------------------------------------->

        // Insert a new node at the end of the linked list
        void insertAtEnd(int value) {
            // Create a new node with the given value
            Node* newNode = new Node(value);

            // If the list is empty, set the new node as the head
            if (head == nullptr) {
                head = newNode;
            } else {
                // Traverse the list to find the last node
                Node* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                // Set the next pointer of the last node to the new node
                current->next = newNode;
            }
        }
//--------------------------------------------------------------------------------------->

    // Insert at a specific position (0-based index)
    void insertAtPosition(int value, int position) {
        // Check if the position is valid (non-negative)
        if (position < 0) {
            cout << "Invalid position. Position should be non-negative." << endl;
            return;
        }

        // Handle special case: inserting at the beginning
        if (position == 0) {
            insertAtStart(value);
            return;
        }

        // Create a new node to be inserted
        Node* newNode = new Node(value);

        // Initialize a pointer to traverse the list
        Node* current = head;
        int currentPos = 0;

        // Iterate through the list until we reach the position just before the insertion point
        while (current != nullptr && currentPos < position - 1) {
            current = current->next;
            currentPos++;
        }

        // Check if the specified position is within the list's bounds
        if (current == nullptr) {
            cout << "Position out of bounds. The list has only " << currentPos << " elements." << endl;
            delete newNode; // Clean up the unused node
            return;
        }

        // Insert the new node at the desired position
        newNode->next = current->next; // Link the new node to the next node
        current->next = newNode; // Link the current node to the new node
    }
//--------------------------------------------------------------------------------------->

  // Remove the first node in the list
  void removeFirst() {
      // Check if the list is empty
      if (head == nullptr) {
          cout << "List is empty. Nothing to remove." << endl;
          return;
      }

      // Store a reference to the node to be deleted
      Node* toDelete = head;

      // Update the head pointer to point to the next node
      head = head->next;

      // Deallocate the memory of the deleted node
      delete toDelete;
  }
//--------------------------------------------------------------------------------------->

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
//--------------------------------------------------------------------------------------->

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
//--------------------------------------------------------------------------------------->

    // Print the list
    void print() const {
        // Initialize a pointer to traverse the list
        Node* current = head;

        // Iterate through the list, printing the data of each node
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        // Print a newline character to separate the list from other output
        cout << endl;
    }

//--------------------------------------------------------------------------------------->

    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Make the list empty
    void makeEmpty() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
//--------------------------------------------------------------------------------------->

    // Reverse the linked list
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
            while (current != nullptr) {
                nextNode = current->next;
                current->next = prev;
                prev = current;
                current = nextNode;
            }
        head = prev;
    }
//--------------------------------------------------------------------------------------->

    // Detect if the list is circular
    bool isCircular() const {
        if (isEmpty()) return false;
        Node* Firstptr = head;
        Node* Secondptr = head;
            while (Secondptr != nullptr && Secondptr->next != nullptr) {
                Firstptr = Firstptr->next;
                Secondptr = Secondptr->next->next;
                if (Firstptr == Secondptr) {
                    return true;
                }
            }
        return false;
    }
//--------------------------------------------------------------------------------------->

    // Compare two linked lists
    bool compare(const LinkedList& other) const {
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data != current2->data) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return (current1 == nullptr && current2 == nullptr);
    }
//--------------------------------------------------------------------------------------->
    // Remove duplicates from a sorted list
    void removeDuplicates() {
        if (isEmpty()) return;
        Node* current = head;
        while (current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }


//--------------------------------------------------------------------------------------->
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
      while (left < right ) {  // Should be: while (left <= right)
          // More robust mid calculation to prevent integer overflow
          int mid = left + (right - left) / 2;
          if (arr[mid] == target) {
              return mid;
          }else if (arr[mid] < target){
                left = mid;
          }else {
              right = mid;                            // DEFECT 2: Doesn't decrease right boundary properly
          }                                          // Should be: right = mid - 1
      }

    cout << "Not Found" << endl;
  }

  //--------------------------------------------------------->

    // Linear Search: Iterative
  static int linearSearch(int arr[], int size, int target) {
      for (int i = 0; i < size; i++) {
          if (arr[i] == target) {
              return i;  // Return the index of the target
          }
      }
      return -1;  // Return -1 if target not found
  }
  //--------------------------------------------------------->

  // Linear Search: Recursive
  static int recursiveLinearSearch(int arr[], int size, int target, int index = 0) {
      if (index >= size) {
          return -1;  // Base case: target not found
      }
      if (arr[index] == target) {
          return index;  // Base case: target found
      }
      return recursiveLinearSearch(arr, size, target, index + 1);  // Recursive case
  }
};

// Sorting algorithms
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

    Queue<int> q; // Create a queue of integers

    // Enqueue some elements
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    // Display the front element
    cout << "Front element: " << q.getFront() << endl;

    // Dequeue elements and print them
    cout << "Dequeuing elements:" << endl;
    while (!q.isEmpty()) {
        cout << q.dequeue() << endl;
    }

    separate();

//-------------------------------------------------------------------------------------------------->

  srand(static_cast<unsigned int>(time(0))); // Seed for random numbers

  // Generate a random array
  int size = 20;
  int minimum_num = 1, maximum_num = 100;
  int* randomArray = ArrayHelper::generateRandomArray(size, minimum_num, maximum_num);

  cout << "Randomly generated array: ";
  ArrayHelper::printArray(randomArray, size);

  // Sort the array
  SortingAlgorithms::bubbleSort(randomArray, size);

  cout << "Sorted random array: ";
  ArrayHelper::printArray(randomArray, size);

  separate();

  // Search in the array
  int target = randomArray[19]; // Picking a value from the array
  int searchResult = SearchAlgorithms::binarySearch(randomArray, size, target);
  if (searchResult != -1) {
    cout << "BinarySearch found " << target << " at index " << searchResult << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  int searchResult2 = SearchAlgorithms::linearSearch(randomArray, size, target);
  if (searchResult2 != -1) {
    cout << "linearSearch found " << target << " at index " << searchResult << endl;
  } else {
    cout << "Element " << target << " not found" << endl;
  }

  int searchResult3 = SearchAlgorithms::recursiveLinearSearch(randomArray, size, target);
  if (searchResult3 != -1) {
    cout << "Recursive linearSearch found " << target << " at index " << searchResult << endl;
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

//-------------------------------------------------------------------------------------------------->


 HashTable PersonTable; // Create a hash table for Person records

    // Predefined Person data
    vector<tuple<int, string, string, string>> Persons = {
        {101, "John", "Doe", "01-01-2020"},
        {102, "Jane", "Smith", "02-15-2019"},
        {103, "Alice", "Johnson", "03-10-2021"},
        {104, "Bob", "Brown", "04-05-2018"},
        {105, "Charlie", "Davis", "05-20-2022"}
    };


    // Automatically insert Person records into the hash table
    cout << "Inserting records..." << endl;
    for (const auto& emp : Persons) {
        int empId = get<0>(emp);
        string firstName = get<2>(emp);
        string lastName = get<1>(emp);
        string hireDate = get<3>(emp);

        PersonTable.insert(empId, { lastName, firstName, hireDate });
        cout << "Person record added: ID " << empId << " - " << firstName << " " << lastName << endl;
    }
    cout << endl;

   separate();


    // Display the size and number of entries in the hash table
    cout << "Table size: " << PersonTable.getSize() << ", Number of current entries: " << PersonTable.getLength() << endl << endl;

    // Automatically lookup an Person by ID
    int lookupId = 103; // Lookup Person with ID 103
    cout << "Looking up Person with ID " << lookupId << "..." << endl;
    HashTable::PersonData lookupData;
    if (PersonTable.lookup(lookupId, lookupData)) {
        cout << "Person found!" << endl;
        cout << "First Name: " << lookupData.firstName << endl;
        cout << "Last Name: " << lookupData.lastName << endl;
        cout << "Hire Date: " << lookupData.hireDate << endl;
    } else {
        cout << "Person with ID " << lookupId << " not found!" << endl;
    }
    cout << endl;

  separate();

    // Automatically delete an Person record by ID
    int deleteId = 102; // Delete Person with ID 102
    cout << "Deleting using ID " << deleteId << "..." << endl;
    PersonTable.deleteKey(deleteId);
    cout << "Person with ID " << deleteId << " deleted." << endl << endl;

  separate();

    // Lookup again to confirm deletion
    cout << "Looking up using ID " << deleteId << " to confirm deletion..." << endl;
    if (PersonTable.lookup(deleteId, lookupData)) {
        cout << "Person found!" << endl;
        cout << "First Name: " << lookupData.firstName << endl;
        cout << "Last Name: " << lookupData.lastName << endl;
        cout << "Hire Date: " << lookupData.hireDate << endl;
    } else {
        cout << "Person with ID " << deleteId << " not found!" << endl;
    }
    cout << endl;

    // Dump the contents of the hash table
    cout << "Hash Table Contents: " << endl;
    PersonTable.dump();

  return 0;
}
