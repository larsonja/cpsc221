#include <codetree.h>

class CodeTree {
    
	int* treeHeap;

  public:
    void printTree ();
    void printCode ();
};

CodeTree::CodeTree (int* heap){
	treeHeap = heap;
}

//function prototype
void printChar( int ch );


void printTree(){


}


void printCode() {


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

