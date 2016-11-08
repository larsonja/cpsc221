hash: Hashtable.cc Hashtable.h driver.cc
	g++ -Wall -g -c Hashtable.cc -o Hashtable.o 
	g++ -Wall -g driver.cc Hashtable.o -o hash

clean: 
	rm -f hash
	rm -f HashTable.o 
	rm -fr hash.dSYM/* 
	rmdir hash.dSYM
 
