#include "huftree.h"
//
void heapify(std::vector<Node> heap, int i) {
    int left = 2*i;
    int right = 2*i + 1;
    int largest = i;
    
    int lF = heap[left].getFreq();
    int rF = heap[right].getFreq();
    int laF = heap[largest].getFreq();
    int s = heap.size();
    
    if (left <= s - 1 && lF > laF) {
        largest = left;
    }
    if (right <= s - 1 && rF > laF){
        largest = right;
    }
    if (largest != i){
        swap(heap[i], heap[largest]);
        heapify(heap, largest);
    }
}

void heapUp(std::vector<Node> heap, int index){
    if (index == 0) return;
    int iF = heap[index].getFreq();
    int jF = heap[(index-1)/2].getFreq();
    if (iF > jF){
        //swap them and run again
        swap(heap[index], heap[index-1]);
        heapUp(heap, (index-1)/2);
    }
}

void insert(std::vector<Node> heap, Node toInsert){
    heap.push_back(toInsert);
    heapUp(heap, heap.size() - 1);
}

void usage() {
  std::cerr << "Usage: huftree text.txt" << std::endl;
  throw std::exception();
}


int main (int argc, char* argv[]) {
  if( argc != 2 ) {
    usage();
  }

  int freq[256] = { 0 };    // array initialized to 0
  
  std::ifstream fin( argv[1] );
  if( fin.is_open() ) {
    char ch;
    while (fin >> std::noskipws >> ch) {    // don't skip whitespace
      freq[(int)ch]++;
    }

    fin.close();
  }

  int numChars = 0;
  std::vector<Node> vectorOfNodes;

  for (int i=0; i<256; i++){
        if (freq[i] > 0){
            node i;
            i.setChar(i);
            i.setFreq(freq[i]);
            vectorOfNodes.push_back(i);
            numChars++;
        }

  }

  for (int i=0; i< numChars; i++){
    heapify(vectorOfNodes, i);
  }

//idea is to have a vector of nodes (where each node contains the character and its frequency)
//then with the list we are able to put them in the order using heapify etc.
//then the first character will be the one that is our 00 and the next will be 01 and so forth
//we then can print the code and from there construct our tree and print tree etc.


  CodeTree ct;
  ct.setVector(vectorOfNodes);
  ct.addFreqArray(freq);
  ct.printTree();
  ct.printCode();

  return 0;
}