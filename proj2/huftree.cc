#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
//#include "codetree.cc"
#include <iomanip>
#include <string>
#include <deque>

using namespace std;

class Node{
    private:
        int character; //ASCII code of the char
        int freq; //frequency at which is appears
    public:
        void setChar(int charCode) {this->character = charCode;}
        void setFreq(int frequency) {this->freq = frequency;}
        int getFreq(void) {return this->freq;}
        int getChar(const Node& node) {return this->character;}
        int getCharacter() {return character;}
        
};

//
void heapify(vector<Node> heap, int i) {
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

void heapUp(vector<Node> heap, int index){
    if (index == 0) return;
    int iF = heap[index].getFreq();
    int jF = heap[(index-1)/2].getFreq();
    if (iF > jF){
        //swap them and run again
        swap(heap[index], heap[index-1]);
        heapUp(heap, (index-1)/2);
    }
}

void insert(vector<Node> heap, Node toInsert){
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
  
  CodeTree ct = CodeTree( freq );

  ct.printTree();
  ct.printCode();

  return 0;
}