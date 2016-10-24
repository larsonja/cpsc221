all :  bst.cc unit.o 
	g++ -Wall -g -std=c++11 bst.cc unit.o -o bst

unit.o : unit.cc unit.h  
	g++ -Wall -g -c unit.cc -o unit.o 

clean:
	rm -f unit.o 
	rm -f bst
	rm -fr bst.dSYM/* 
	rmdir bst.dSYM 
