#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
int * x;
int totalComps;

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

int c (int  n){
    if(n > 1){
        int p = randint(0, n-1);
        return n-1 + c(p) + c(n-p-1);
    } else {
        return 0;
    }
}

void quicksort(int a, int b) {
	if (a >= b) return;
    
	int p = randint(a,b); // pivot
    
	swap(x[a], x[p]);
	
        int m = a;
	int i;
    
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a])
			swap(x[++m], x[i]);
        	totalComps++;
    	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 1000
#define NREPS 100

int main(int argc, char *argv[]) {
    srand(time(0));
    
    int averageComps = 0;
    int quicsortComparisons = 0;
    
    for(int j=0; j<NREPS; ++j){
        totalComps = 0;
        
        // change the following code
        x = new int[NN];
        
        for (int i=0; i<NN; ++i) {
            x[i] = rand() % NN;
        }
        
        quicksort(0, NN-1);
        
        for (int i=0; i<NN; ++i) {
            cout << x[i] << " ";
        }
	cout << endl;
        averageComps += totalComps;
        quicsortComparisons += c(NN);
        
        delete[] x;
    }
    
    cout << endl << endl;
    averageComps = averageComps/NREPS;
    quicsortComparisons = quicsortComparisons/NREPS;
    
    cout << "Ave Comp: " << averageComps << "   " << "Estimated Avg Comp: " << quicsortComparisons << '\n';
    
    return 0;
}

/*
worst case: n^2 (depends on pivot, but usually when the elements are already sorted it preforms worse)
best case : nlgn
avg case  : nlgn

it is an inplace sort as there aren't any other data structures we use other than th einitial array and a few other variables to store things as we move them

quicksort is not a stable sort, doesn't have the same output if the key is different

*/
