#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#define EMPTY -1	// indicates an empty slot (so don't hash -1)

class Hashtable {
public:
	Hashtable(int size);
	~Hashtable();
	int hash(int key);
	int hashAlt(int key);
	void qinsert(int key);
	void linsert(int key);
	void dinsert(int key);
	void print();
	void printStats();
	float probeRate();
	void clear(); 
	bool checkValue(int key, int index);

private:
	int* _table;
	int _size;
	int _totalProbes;
	int _numInserts;
	int _numFailures;
	
	void tallyProbes(int p);	
	int nextPrime(int n);
	bool isPrime(int n);
	bool isPrime(int n, int divisor); 
};

#endif
