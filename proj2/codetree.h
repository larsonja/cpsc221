#ifndef CODE_TREE_H
#define CODE_TREE_H
#include <vector>
#include <iostream>
#include "huftree.cc"
using namespace std;


//function prototype
void printChar( int ch );

class CodeTree {
    
	int* freqArray;
	std::vector<Node> v;

  public:
  	void printTree();
    void printTree2 (std::vector<Node> v, int length, int node=0, int d=0);
    void printCode ();
    void addNode (Node nodeToAdd);
    void addFreqArray(int* array);
    void setVector(std::vector<Node> vector);
};

//void CodeTree::addFreqArray(int * array);

void gToLSort(int arrayToSort[], int size);

void printChar( int ch );










#endif
