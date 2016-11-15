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
        int setChar(int charCode) {this->character = charCode;}
        int setFreq(int frequency) {this->freq = frequency;}
        int getChar(const Node& node) {return character;}
        int getFreq(const Node& node) {return frequency;}
};

void swapDown(vector<Node>) {
    
}

int main (int argc, char* argv[]) {
    
}