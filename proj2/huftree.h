#ifndef HUF_TREE_H
#define HUF_TREE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "codetree.h"
#include <iomanip>
#include <string>
#include <deque>

using namespace std;

class Node{
    private:
        int character; //ASCII code of the char
        int freq; //frequency at which is appears
    public:
        void setChar(int charCode) {this->character = charCode;}
        void setFreq(int frequency) {this->freq = frequency;}
        int getFreq(void) {return this->freq;}
        int getChar(const Node& node) {return this->character;}
        int getCharacter() {return character;}
        
};


void heapify(vector<Node> heap, int i);

void heapUp(vector<Node> heap, int index);

void insert(vector<Node> heap, Node toInsert);

void usage();

int main (int argc, char* argv[]);

#endif