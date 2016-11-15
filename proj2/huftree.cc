#include <iostream>
#include <fstream>
#include <algorithm>
#include "codetree.h"
#include "huftree.h"
#include <iomanip>
#include <string>
#include <deque>

using namespace std;


// PRE:  subtrees rooted at leftChild and rightChild of i are heaps.
// POST: subtree rooted at i is a heap.
void swapDown(int* heap, int* freq, int i, int size) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int min = i;
    // find who holds smallest element of i and its two children
    if (leftChild < size && freq[heap[leftChild]] < freq[heap[min]])
        min = leftChild;
    if (rightChild < size && freq[heap[rightChild]] < freq[heap[min]])
        min = rightChild;
    // if a child holds smallest element, swap i's element to that child
    // and recurse.
    if (min != i) {
        swap(heap[i], heap[min]);
        swapDown(heap, freq, min, size);
    }
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are a heap.
void heapify(int* heap, int* freq, int size) {
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, freq, i, size);
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are sorted in descending order.
void sort(int* heap, int size) {
    heapify(heap, size);  // Heapify algorithm
    for (int i = size - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        swapDown(heap, freq, 0, i);
    }
}




// Print the Huffman code tree and list of codes for a given text file.

void usage() {
  std::cerr << "Usage: huftree text.txt" << std::endl;
  throw std::exception();
}

int main( int argc, char *argv[] ) {
  if( argc != 2 ) {
    usage();
  }

  int freq[256] = { 0 };	// array initialized to 0
  
  std::ifstream fin( argv[1] );
  if( fin.is_open() ) {
    char ch;
    while (fin >> std::noskipws >> ch) {	// don't skip whitespace
      freq[(int)ch]++;
    }

    fin.close();
  }
  
  CodeTree ct = CodeTree( freq );

  ct.printTree();
  ct.printCode();

  return 0;
}



/*
so always keep track of the frequency array while dealing with the index value in the heap
[array of frequencyes, index is the character]
[array of characters, where the first element is the highest priority]
*/