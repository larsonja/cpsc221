#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;    

///////////////////////////////////////////////////////////////////////////////////////////////////////
struct Word{
		string word;
		int count;
		string pages;
		int height;
		vector<Word*> next;
};

Word* createWord(string n, string p, int h){
	Word* result = (struct Word*)malloc(sizeof(Word));
	result->word = n;
	result->count = 1;
	result->pages = p;
	result->height = h;
	return result;
}

void deleteWord(Word* toDelete){
	delete(toDelete);
}

void addCount(Word* myWord){
	myWord->count = myWord->count + 1;
}
void addPage(Word* myWord, int pageNumber){
	myWord->pages = myWord->pages + ',' + to_string(pageNumber);
}
string formatOutput(Word* myWord){
	string result = myWord->word + " (" + to_string(myWord->count) + ") " + myWord->pages;
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
struct slipList{
	vector<Word> list;
};

slipList* createList(Word firstWord){
	slipList* result = (struct slipList*)malloc(sizeof(slipList));
	result->list.resize(1);
	result->list.push_back(firstWord);
	return result;
}

int findWordIndex(slipList* myList, string find){
	auto iterator = myList->list.begin();
	int i = 0;
	string current = iterator->word;
	
	while(current != find && iterator != myList->list.end()){
		advance(iterator, 1);
		i++;
		current = iterator->word;
	}
	if (current == find){
		return i;
	} else {
		return -1;
	}
}

bool insertWord(slipList* myList, Word newWord){
	myList->list.resize(myList->list.size() + 1);
	int indexAddAt = findWordIndex(myList, newWord.word);
	if (indexAddAt == -1){
		return false;
	}
	auto iterator = myList->list.begin();
	advance(iterator, indexAddAt);
	myList->list.emplace(iterator);
	return true;
}

void printToFile(slipList* myList, string fileName){
	ofstream myFile;
	myFile.open(fileName);
	int i= 1;
	auto iterator = myList->list.begin();
	
	while( (unsigned) i <= (myList->list.size())){
		myFile<<formatOutput(&(*iterator));
		myFile<< '\n';
		advance(iterator,1);
		i++;
	}
}
	
	
///////////////////////////////////////////////////////////////////////////////////////////////////////


// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX

int randBit(void) {             // return a "random" bit
  static int bitsUpperBd=0;
  static int bits;              // store bits returned by rand()
  if( bitsUpperBd == 0 ) {      // refresh store when empty
    bitsUpperBd = RAND_MAX;
    bits = rand();
  }
  int b = bits & 1;
  bits >>= 1;
  bitsUpperBd >>= 1;
  return b;
}


// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
          it == line.begin() || it+1 == line.end() ||
          !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
        *it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

void print(ostream & output, string & word) {
  output << word << endl;
}

int main(int argc, char *argv[]) {
  if( argc != 3 ) {
    cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
    exit(1);
  }

  ifstream fin;
  fin.open(argv[1]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  ofstream fout;
  fout.open(argv[2]);
  if( !fout.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  string line, word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
      print(fout, word);
    }
  }
}
