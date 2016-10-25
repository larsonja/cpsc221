#include <iostream>
#include <iomanip>
#include <deque>
#include <string>

using namespace std;

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are printed to the screen.
void printList(int* heap, int size) {
    for (int i = 0; i < size; i++)
        cout << heap[i] << " ";
    cout << endl;
}

// PRE:  subtrees rooted at leftChild and rightChild of i are heaps.
// POST: subtree rooted at i is a heap.
void swapDown(int* heap, int i, int size) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int min = i;
    // find who holds smallest element of i and its two children
    if (leftChild < size && heap[leftChild] < heap[min])
        min = leftChild;
    if (rightChild < size && heap[rightChild] < heap[min])
        min = rightChild;
    // if a child holds smallest element, swap i's element to that child
    // and recurse.
    if (min != i) {
        swap(heap[i], heap[min]);
        swapDown(heap, min, size);
    }
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are a heap.
void heapify(int* heap, int size) {
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are sorted in descending order.
void sort(int* heap, int size) {
    heapify(heap, size);  // Heapify algorithm
    for (int i = size - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        swapDown(heap, 0, i);
    }
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//      node is the index of the root of the current sub-tree and
//      it is at depth d in the whole heap
//POST: The first size elements of heap are printed as a tree
void printHeap(int *heap, int size, int node=0, int d=0) {
    // TODO: put your code here for Questions 1 and 2

    std::deque<string> printDeque;

    string nodeString;

    int leftChild = 2 * node + 1;
    int rightChild = 2 * node + 2;

    if (size < 0) return;

    for (int i =0; i< d; i++){
        cout << '*';
    }

    cout << heap[node] << endl;

    if (leftChild < size){
        printHeap(heap, size, leftChild, d+1);
    }

    if (rightChild < size){
        printHeap(heap, size, rightChild, d+1);
    }


/*
    std::deque<string> printDeque;

    int i=0;
    int heapCount = 1;
    int temp;
    node = heap[0];
   // printDeque.push_back(0);
    cout << node <<endl;
    d = 1; //heap is moved down 1 after printing root
    for (i=1; i<size; i++){
        if ((heap[i] > node) && (i%2 != 0)){
            cout << std::setw(3*d)<< (heap[i]) << endl;
            temp = i;
            heapCount++;
            if (heapCount > 2*d){
                d++;
                node = heap[temp];
            }
        }
        else{
            cout << std::setw(3*d) << (heap[i]) << endl;
            heapCount++;
            if (heapCount > 2*d){
                d++;
            }

        }
        

    }
    size = heapCount;
*/
    //for (std::deque<string>::iterator it = printDeque.begin(); it!=printDeque.end(); ++it){
    //    cout << *it << end;
    //}


}

//PRE:  heap points to an array representing a heap
//      key is the value to be removed from the heap
//      size is the number of elements in the heap
//POST: all elements with key value = key have been removed from
//	the heap and size is the new heap size.
void remove(int* heap, int key, int & size) {
    // TODO: put your code for Question 3 here
}

//PRE:  heap1 and heap2 contain size1 and size2 elements respectively.
//POST: output a new heap (whose size is size1+size2) containing all
//      the elements in heap1 and heap2 (including duplicates).
int* mergeHeap(int* heap1, int* heap2, int size1, int size2) {
    // TODO: replace the following line with your code for Question 4
    return NULL;
}

int input1[] = {8,3,5,6,2,9,1,7,4,0};
int input2[] = {4,6,1,8,2,3};
int input3[] = {2,2,2,2,2,2,2};

int main() {
    int size1 = sizeof(input1)/sizeof(int);
    int *heap1 = new int[size1];
    for (int i = 0; i < size1; ++i) {
        heap1[i] = input1[i];
    }

    heapify(heap1, size1);
    cout << "heap1: ";
    printList(heap1, size1);
    printHeap(heap1, size1);

    int size2 = sizeof(input2)/sizeof(int);
    int *heap2 = new int[size2];
    for (int i = 0; i < size2; ++i) {
        heap2[i] = input2[i];
    }

    heapify(heap2, size2);
    cout << "heap2: ";
    printList(heap2, size2);
    printHeap(heap2, size2);

    int size3 = sizeof(input3)/sizeof(int);
    int *heap3 = new int[size3];
    for (int i = 0; i < size3; ++i) {
        heap3[i] = input3[i];
    }

    heapify(heap3, size3);
    cout << "heap3: ";
    printList(heap3, size3);
    printHeap(heap3, size3);

    remove(heap1, 0, size1);
    cout << "heap1, remove(0): ";
    printList(heap1, size1);
    printHeap(heap1, size1);

    remove(heap2, 8, size2);
    cout << "heap2, remove(8): ";
    printList(heap2, size2);
    printHeap(heap2, size2);

    remove(heap3, 2, size3);
    cout << "heap3, remove(2): ";
    printList(heap3, size3);
    printHeap(heap3, size3);

    remove(heap3, 2, size3);
    cout << "heap3, remove(2): ";
    printList(heap3, size3);
    printHeap(heap3, size3);

    int *heap = mergeHeap(heap1, heap2, size1, size2);
    int size = size1 + size2;

    if (heap != NULL) {
        cout << "merged: ";
        printList(heap, size);
        printHeap(heap, size);
        
        remove(heap, 2, size);
        
        cout << "remove(2): ";
        printList(heap, size);
        printHeap(heap, size);
        
        delete[] heap;
    }
    
    delete[] heap1;
    delete[] heap2;
    delete[] heap3;
    
    return 0;
}