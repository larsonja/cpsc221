#include <utility>
#include <iostream>

int bitsort(int *A, int n);

using namespace std;
int main (void){
	int A[] = {1,1,1,0,0,0};

	for (int i =0; i < 6; i++){
		cout << A[i] << ",";
	}
	cout << endl;

	int Answer = bitsort(A,6);

	cout << Answer << endl;

	for (int i =0; i < 6; i++){
		cout << A[i] << ",";
	}
	cout << endl;
}

// Sort an array A of 0’s and 1’s so the 0’s come before the 1’s
// using swapping. The size of the array is n.
int bitsort(int *A, int n) {
int i=0;
int j=n-1;
while( i != j) {
	if( A[i] == 0 ) {
		i++;
	} else if( A[j] == 1) {
		j--;
	} else {
		std::swap( A[i], A[j] );
		}
	}
return j;
}

/*
Console printout:
e2y8@bowen:assign2$ ./q3.o
1,1,1,0,0,0,
3
0,0,0,1,1,1,
*/