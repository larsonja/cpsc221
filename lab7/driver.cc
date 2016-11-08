#include "Hashtable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void usage(char* argv[]) {
	cerr << "Usage: " << argv[0] << " scheme numberOfKeys sizeOfTable" << endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int n, m;
	srand(time(0));

	if (argc == 1) {
		cout << "Running your test code..." << endl;
		/* ADD YOUR TEST CODE HERE */
		Hashtable A(10000);
		for (int i = 0; i < 7500; i++){
			A.linsert(rand() + 1);
		}
		cout << "Linear with 7500 keys and size 10000: ";
		A.printStats();

		Hashtable B(10000);
		for (int j = 0; j < 7500; j++){
			B.dinsert(rand() + 1);
		}
		cout << "Double with 7500 keys and size 10000: ";
		B.printStats();

		Hashtable C(10000);
		for (int k = 0; k < 7500; k++){
			C.qinsert(rand() + 1);
		}
		cout << "Quadratic with 7500 keys and size 10000; ";
		C.printStats();


		Hashtable D(100000);
		for (int l = 0; l < 90000; l++){
			D.linsert(rand() + 1);
		}
		cout << "Linear with 90000 keys and size 100000: ";
		D.printStats();

		Hashtable E(100000);
		for (int m = 0; m < 90000; m++){
			E.dinsert(rand() + 1);
		}
		cout << "Double with 90000 keys and size 100000: ";
		E.printStats();

		Hashtable F(100000);
		for (int n = 0; n < 90000; n++){
			F.qinsert(rand() + 1);
		}
		cout << "Quadratic with 90000 keys and size 100000; ";
		F.printStats();

		return 0;
	}
	
	if (argc != 4) {
		usage(argv);
	}
	n = atoi(argv[2]);
	m = atoi(argv[3]);
	Hashtable H(m);
	
	switch(argv[1][0]) {
	case 'l':
		for (int i=0; i<n; ++i) {
			H.linsert(rand() + 1);
		}
		//    H.print();
		cout << "Linear: ";  
		H.printStats();
		break;
	case 'q':
		for (int i=0; i<n; ++i) {
			H.qinsert(rand() + 1);
		}
		//    H.print();
		cout << "Quadratic: ";
		H.printStats();
		break;
	case 'd':
		for (int i=0; i<n; ++i) {
			H.dinsert(rand() + 1);
		}
		//    H.print();
		cout << "Double Hashing: "; 
		H.printStats();
		break;
	default:
		usage(argv);
	}
}

