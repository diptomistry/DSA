#include <iostream>
using namespace std;

// Class for binary heap
class BinaryHeap {
    private:
        int *heap; // array to store heap elements
        int capacity; // maximum possible size of heap
        int heap_size; // current size of heap
        int parent(int i); // function to return parent of i-th node
        int left(int i); // function to return left child of i-th node
        int right(int i); // function to return right child of i-th node
        void heapify_up(int i); // function to heapify upwards
        void heapify_down(int i); // function to heapify downwards
    public:
        BinaryHeap(int cap) { // constructor
            capacity = cap;
            heap_size = 0;
            heap = new int[capacity];
        }
        void make_heap(int *input, int size); // function to create heap from input array
        void insert(int key); // function to insert a node
        int get_min(); // function to get minimum key
        int extract_min(); // function to extract minimum key
        void merge(BinaryHeap &heap2); // function to merge two heaps
        void decrease_key(int i, int new_val); // function to decrease the key value of a node
        void delete_key(int i); // function to delete a node
        void display(); // function to display heap elements
};

// Function to return parent of i-th node
int BinaryHeap::parent(int i) {
    return (i - 1) / 2;
}

// Function to return left child of i-th node
int BinaryHeap::left(int i) {
    return 2 * i + 1;
}

// Function to return right child of i-th node
int BinaryHeap::right(int i) {
    return 2 * i + 2;
}

// Function to heapify upwards
void BinaryHeap::heapify_up(int i) {
    while (i != 0 && heap[parent(i)] > heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

// Function to heapify downwards
void BinaryHeap::heapify_down(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && heap[l] < heap[i]) {
        smallest = l;
    }
    if (r < heap_size && heap[r] < heap[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify_down(smallest);
    }
}

// Function to create heap from input array
void BinaryHeap::make_heap(int *input, int size) {
    for (int i = 0; i < size; i++) {
        if (heap_size == capacity) {
            cout << "Heap overflow" << endl;
            return;
        }
        heap[heap_size] = input[i];
        heap_size++;
        heapify_up(heap_size - 1);
    }
}

// Function to insert a node
void BinaryHeap::insert(int key) {
    if (heap_size == capacity) {
        cout << "Heap overflow" << endl;
        return;
    }
    heap[heap_size] = key;
    heap_size++;
    heapify_up(heap_size - 1);
}

// Function to get minimum key
int BinaryHeap::get_min() {
    return heap[0];
}

// Function to extract minimum key
int BinaryHeap::extract_min() {
    if (heap_size== 0) {
cout << "Heap underflow" << endl;
return INT_MAX;
}
int root = heap[0];
int last = heap_size - 1;
heap[0] = heap[last];
heap_size--;
heapify_down(0);
return root;
}

// Function to merge two heaps
void BinaryHeap::merge(BinaryHeap &heap2) {
for (int i = 0; i < heap2.heap_size; i++) {
if (heap_size == capacity) {
cout << "Heap overflow" << endl;
return;
}
heap[heap_size] = heap2.heap[i];
heap_size++;
}
for (int i = heap_size / 2 - 1; i >= 0; i--) {
heapify_down(i);
}
}

// Function to decrease the key value of a node
void BinaryHeap::decrease_key(int i, int new_val) {
heap[i] = new_val;
heapify_up(i);
}

// Function to delete a node
void BinaryHeap::delete_key(int i){
decrease_key(i, INT_MIN);
extract_min();
}

// Function to display heap elements
void BinaryHeap::display() {
for (int i = 0; i < heap_size; i++) {
cout << heap[i] << " ";
}
cout << endl;
}

// Driver code to test the implementation
int main() {
BinaryHeap heap(10);
int input[] = {10, 5, 3, 2, 4};
int size = sizeof(input) / sizeof(input[0]);
heap.make_heap(input, size);
cout << "Heap after creation: ";
heap.display();
heap.insert(1);
cout << "Heap after insertion of 1: ";
heap.display();

cout << "Minimum element: " << heap.get_min() << endl;

cout << "Extracted minimum element: " << heap.extract_min() << endl;
cout << "Heap after extraction of minimum element: ";
heap.display();

BinaryHeap heap2(10);
int input2[] = {8, 7, 6};
int size2 = sizeof(input2) / sizeof(input2[0]);
heap2.make_heap(input2, size2);
cout << "Second heap after creation: ";
heap2.display();

heap.merge(heap2);
cout << "Heap after merging with second heap: ";
heap.display();

heap.decrease_key(4, 1);
cout << "Heap after decreasing key of 4th element to 1: ";
heap.display();

heap.delete_key(1);
cout << "Heap after deleting 2nd element: ";
heap.display();

return 0;
}
