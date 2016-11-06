#include "Hashtable.h"
#include <cstdlib>
#include <iostream>
#include <cassert> 

using namespace std; 

Hashtable::Hashtable(int size) {
	//constructor
	int prime = nextPrime( size ); 
	_size = size;
	if (prime != size) { 
	  cout << "Warning: size = " << size << " is not a prime number." << endl; 
/* uncomment these if you want */ 
//	  cout << "Using " << prime << " instead." << endl; 
//	  _size = prime; 
	}
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	_table = new int [ _size ];
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}
void Hashtable::clear(void) {
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}    
    

Hashtable::~Hashtable() {
	//deconstructor
	delete[] _table;
}

void Hashtable::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	_totalProbes += p;
	_numInserts += 1;
}

void Hashtable::printStats() {
	cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			_totalProbes << "/" << _numInserts;
	cout <<", size = "<< _size;
	cout <<", failures = " << _numFailures << endl;
}

float Hashtable::probeRate() {
	return (float)_totalProbes / (float)_numInserts;
}

int Hashtable::hash(int k) {
	return k % _size;
}

int Hashtable::hashAlt(int k) {
	return ((this->_size >> 3) + 3) - (k % ((this->_size >> 3) + 3));
}

void Hashtable::qinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with quadratic probing and hash(k) = k % _size.

	// Tips:
	// - Look at the lecture slides if you don't remember how to implement these.
	// - You need to prevent against infinite loops. You should limit the number
	// of times you probe and print an error message upon exceeding this limit.
	// - You're welcome to add new declarations to hash.h, add to the constructor,
	// include libraries, or anything else you need. 
	// - You're also welcome to modify the main() method to automate your testing.

    // ************* ADD YOUR CODE HERE *******************
	
	int probe = hash(k);
	int i = 1;
	while(this->_table[probe] != EMPTY && this->_table[probe] != k){
		if(i > this->_size){ //Try as many times as there are spaces in the array, hopefully we find one
			_numFailures += 1; 
			cout << "Warning: qinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
			exit(-1);
		}
		probe = (probe + 2*i - 1) % this->_size;
		i++;
	}
	this->tallyProbes(i);
	this->_table[probe] = k;
}

void Hashtable::linsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with linear probing and hash(k) = k % _size.

    // ************* ADD YOUR CODE HERE *******************
    
	int probe = hash(k);
	int i = 1;
	while(this->_table[probe] != EMPTY && this->_table[probe] != k){
		if(i > this->_size){ //Try as many times as there are spaces in the array, hopefully we find one
			_numFailures += 1; 
			cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
			exit(-1);
		}
		probe = (probe + 1) % this->_size;
		i++;
	}
	this->tallyProbes(i);
	this->_table[probe] = k;
}

void Hashtable::dinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with double hashing. Use the existing hash function
	// and also implement a second hash function.

    // ************* ADD YOUR CODE HERE *******************

	int probe = hash(k);
	int probeAlt = hashAlt(k);
	int i = 1;
	while(this->_table[probe] != EMPTY && this->_table[probe] != k){
		if(i > this->_size){ //Try as many times as there are spaces in the array, hopefully we find one
			_numFailures += 1; 
			cout << "Warning: dinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
			exit(-1);
		}
		probe = (probe + probeAlt) % this->_size;
		i++;
	}
	this->tallyProbes(i);
	this->_table[probe] = k;    
}

void Hashtable::print() {
	// Print the content of the hash table.

	for (int i=0; i<_size; i++) {
		cout<<"["<<i<<"] ";
		if (_table[i] != EMPTY)
			cout << _table[i];
		cout << endl;
	}
}

bool Hashtable::checkValue(int k, int i) {
	// Check if value k is at index i. Use this to help you with testing.

	return (_table[i] == k);
}

int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if (n == 2) return true;
    if (n % 2 == 0) return false;  
    return isPrime( n, 3 ); 
}
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    return isPrime( n, divisor + 2 ); 
}

