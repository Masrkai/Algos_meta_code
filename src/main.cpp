#include <iostream>
using namespace std;

// Utility functions for array operations
class ArrayHelper {
public:
    // Swap two elements in an array
    static void swap(int arr[], int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Print the contents of an array
    static void printArray(int arr[], int size) {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Generate a random array with values in a specified range
    static int* generateRandomArray(int size, int minVal, int maxVal) {
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = minVal + (rand() % (maxVal - minVal + 1));
        }
        return arr;
    }
};

// Dynamic array implementation
class ArrayList {
private:
    int* arr;
    int capacity;
    int size;

    // Resize the internal array to a new capacity
    void resize(int newCapacity) {
        int* newArr = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:
    ArrayList(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        arr = new int[capacity];
    }

    ~ArrayList() {
        delete[] arr;
    }

    // Add a new element to the array
    void add(int value) {
        if (size == capacity) resize(capacity * 2);
        arr[size++] = value;
    }

    // Remove an element at a specific index
    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return;
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    // Get an element at a specific index
    int get(int index) const {
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return -1;
        }
        return arr[index];
    }

    // Replace an element at a specific index
    void set(int index, int value) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return;
        }
        arr[index] = value;
    }

    // Get the current size of the array
    int getSize() const {
        return size;
    }

    // Print the contents of the array
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Linked list node structure
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// Linked list implementation
class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    // Add a new element to the front of the list
    void addFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Add a new element to the back of the list
    void addBack(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Remove the front element
    void removeFront() {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        size--;
    }

    // Remove the back element
    void removeBack() {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }

    // Get the first element of the list
    int getFront() const {
        return head ? head->data : -1;
    }

    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get the size of the list
    int getSize() const {
        return size;
    }

    // Print the contents of the list
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Test program
int main() {
    // Seed the random number generator
    srand(time(0));

    // Test ArrayHelper
    cout << "Testing ArrayHelper:" << endl;
    int* randomArray = ArrayHelper::generateRandomArray(10, 1, 100);
    ArrayHelper::printArray(randomArray, 10);
    delete[] randomArray;

    // Test ArrayList
    cout << "\nTesting ArrayList:" << endl;
    ArrayList arrayList;
    for (int i = 0; i < 5; i++) {
        arrayList.add(i * 10);
    }
    arrayList.print();
    arrayList.remove(2);
    arrayList.print();

    // Test LinkedList
    cout << "\nTesting LinkedList:" << endl;
    LinkedList linkedList;
    for (int i = 0; i < 5; i++) {
        linkedList.addBack(i * 10);
    }
    linkedList.print();
    linkedList.removeFront();
    linkedList.addFront(5);
    linkedList.print();

    return 0;
}
