#include <iostream>
#include <cstdlib> // for atoi

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {// remember, argv[0] is the program name
		cerr << "Wrong number of arguments!" << endl;
		return 1;
	}
	int n = atoi(argv[1]);
	for(int i = 1; i <= n; i++) {
		cout << "I 25" << endl;
		cout << "F 25" << endl;
		cout << "R 25" << endl;
	}
	return 0;
}
