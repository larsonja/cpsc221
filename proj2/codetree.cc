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
    void printTree (std::vector<Node> v, int length, int node=0, int d=0);
    void printCode ();
    void addNode (Node nodeToAdd);
    CodeTree(int * freq);
};


CodeTree::CodeTree (int* freq){
	freqArray = freq;
}

void CodeTree::addNode (Node nodeToAdd){
	v.push_back(nodeToAdd);
}


void CodeTree::printTree(std::vector<Node> v, int length, int node, int d){
	int size = v.size();

	//int node = 0; //temp val for node for now

 	int leftChild = 2 * node + 1;
    int rightChild = 2 * node + 2;

    if (size <= 0) return;

    /*for (int i =0; i< d; i++){
        cout << '*';
    }*/


    if (rightChild < size){
        printTree(v, v.size(), rightChild, d+1);
    }

    //cout << std::setw(3*d) << v[node] << endl;

    if (leftChild < size){
        printTree(v, v.size(), leftChild, d+1);
    }

}


void CodeTree::printCode() {
/*
	int highestCount = 0;
	int charNum = 0; 
	int count = 0;
	std::vector<int> v; //vector to hold sizes

	for (int i=0; i< 256; i++){
		if (freqArray[i] > 0){
			charNum++;
			v.pushback(i); //pushback the ascii representation of the letter into vector
		}
	}

	int characters[charNum];

	for (int n: v){
		characters[count] = freqArray[n];
		count++;
	}

	*/

	int binNumber = 00;

	for (int count=0; count < v.size(); count ++){
		printChar(v[count].getCharacter());
		std::cout << ":" << binNumber << endl;
		binNumber++;
	}
}


void gToLSort(int arrayToSort[], int size){

	for (int z = 0; z < size; z++){
		std::cout << arrayToSort[z];
	}
	std::cout << endl;

	int i, j;
	int first, temp;
	int length = size;

	for (i = length - 1; i > 0; i--){
		first = 0;
		for (j=1; j<i; j++){
			if (arrayToSort[j]<arrayToSort[first])
			first=j;
		}
		temp = arrayToSort[first];
		arrayToSort[first] = arrayToSort[i];
		arrayToSort[i] = temp;
	}

	for (int z = 0; z < size; z++){
		std::cout << arrayToSort[z];
	}
	std::cout << endl;

	return;

}


void printChar( int ch ) {
	if( ch < 16 ) {
		std::cout << "x0" << std::hex << ch;
	} else if( ch < 32 || ch > 126 ) {
		std::cout << "x" << std::hex << ch;
	} else {
		std::cout << "\"" << (char)ch << "\"";
	}
}

