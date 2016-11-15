#include <vector>

using namespace std;

class CodeTree {
    
	int* freqArray;
	std::vector<Node> v;

  public:
    void printTree ();
    void printCode ();
    void addNode (Node nodeToAdd);
};

CodeTree::CodeTree (int* freq){
	freqArray = freq;
}

void addNode (Node nodeToAdd){
	v.pushback(nodeToAdd);
}

//function prototype
void printChar( int ch );


void printTree(){

 	int leftChild = 2 * node + 1;
    int rightChild = 2 * node + 2;

    if (size <= 0) return;

    /*for (int i =0; i< d; i++){
        cout << '*';
    }*/


    if (rightChild < size){
        printHeap(heap, size, rightChild, d+1);
    }

    cout << std::setw(3*d) << heap[node] << endl;

    if (leftChild < size){
        printHeap(heap, size, leftChild, d+1);
    }

}


void printCode() {
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

	for (int count=0; count < v.length(); count ++){
		std::cout << printChar(v[count]->character) << ":" << binNumber << endl;
		binNumber++;
	}
}


void gToLSort(int[] arrayToSort){

	for (int z = 0; z < arrayToSort.length(); z++){
		std::cout << arrayToSort[z];
	}
	std::cout << endl;

	int i, j;
	int first, temp;
	int length = arrayToSort.length();

	for (i = numLength - 1; i > 0; i--){
		first = 0;
		for (j=1; j<i; j++){
			if (num[j]<num[first])
			first=j;
		}
		temp = num[first];
		num[first] = num[i];
		num[i] = temp;
	}

	for (int z = 0; z < arrayToSort.length(); z++){
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

