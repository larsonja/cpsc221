#include <iostream>
#include <ctime>
#include <cstdlib>

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
        int sum = 0;
        for(int m=1; m<=n; m++){
            sum += n-1 + c(m-1) + c(n-m);
        }
        return sum;
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
    int curComparisons = 0;
    
    for(int j=0; j<NREPS; ++j){
        totalComps = 0;
        
        // change the following code
        x = new int[NN];
        
        for (int i=0; i<NN; ++i) {
            x[i] = rand() % NN;
        }
        
        quicksort(0, NN-1);
        
        for (int i=0; i<NN; ++i) {
            std::cout << x[i] << " ";
        }
        averageComps += totalComps;
        quicsortComparisons += c(NN);
        std::cout << std::endl;
        
        delete[] x;
    }
    averageComps = averageComps/REP;
    quicsortComparisons = quicsortComparisons/REP;
    
    std::cout << averageComps << " " << quicsortComparisons << '\n';
    
	return 0;
}
