all :  huftree.cc codetree.o
    g++ -Wall -g -std=c++11 huftree.cc codetree.o -o huftree

codetree : codetree.cc codetree.h
        g++ -Wall -g -std=c++11 codetree.cc codetree.h -o codetree.o

clean:
	rm -f huftree
	rm -f codetree.o
