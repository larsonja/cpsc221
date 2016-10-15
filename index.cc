#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;    

//WORD STRUCTURE AND FUNCTION CALLS/////////////////////////////////////////////////////////

//Don't need to worry about this stuff right now
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
// SLIP LIST STRUCTURE AND FUNCTION CALLS //////////////////////////////////////////////////
struct slipList{
	vector<Word> list;
};

//Don't need to destroy as when we exit the program is when we would delete this
// so no need to do more work
slipList* createList(Word firstWord){
	slipList* result = (struct slipList*)malloc(sizeof(slipList));
	result->list.resize(1);
	result->list.push_back(firstWord);
	return result;
}

//Used to find the index FIND in the list given, if it's not there returns -1
int find(slipList* myList, string find){
	Word* baseWord = myList->list.data();
	while(baseWord->word != newWord){
		int h = baseWord->height;
		while((baseWord->next[h] != NULL) && h > 0){
			if (newWord.compare(baseWord->next[h]->word) < 0){
				baseWord = baseWord->next[h]->word);
			} else if (newWord.compare(baseWord->next[h]->word) = 0) {
				//found it;
			}
			h--;
		}
		baseWord = baseWord->next[0];
	}
	if (correctPoint != NULL){
		return distance(myList->list.data(), correctPoint);
	} else {
		return -1;
	}
}

//Used to insert NEWWORD into the given list
void insert(slipList* myList, Word newWord){
	vector<Word> wordsToUpdate;
	Word* baseWord = myList->list.data();
	while(baseWord->word != newWord){
		int h = baseWord->height;
		while((baseWord->next[h] != NULL) && h >= 0){
			if (newWord.compare(baseWord->next[h]->word) < 0){
				baseWord = baseWord->next[h]->word);
			} else if (newWord.compare(baseWord->next[h]->word) = 0) {
				//found it
				
			} else {
				//word is past where we want to go
				if (h == 0){
					Word* temp = wordsToUpdate.pop_back();
					if((newWord.compare(temp) < 0 && newWord.compare(baseWord->word) > 0)){
					//found where it needs to go
						int height = 0;
						while (height < newWord->height){//////////////////////////////
							Word* p = new Word*;
							*p = temp;
							newWord->next.resize(newWord->next.size() + 1);
							newWord.push_back(p);
						}
					} else {
						wordsToUpdate.push_back(&temp);
					}
				}
				wordsToUpdate.resize(wordsToUpdate.size() + 1);
				wordsToUpdate.push_back(&baseWord);
			}
			h--;
		}
		baseWord = baseWord->next[0];
	}
}

// Used to print a list to file
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

  ifstream fin;//input file name
  fin.open(argv[1]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  ofstream fout; //output file name
  fout.open(argv[2]);
  if( !fout.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  int firstWord = 1;

  int pageNum = 1;
  int lineNum = 1;

  string line, word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
	processLine(line)
	lineCount++;
	if (lineNum % 40 == 0){ //gets the lineNumber
		pageNum++; //gets the pageNumber
	}
	//should process shit in the line here
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
    	Word createdWord = createWord(word,pageNum.to_string(),0) //create the word here with pages and height ** TODO: don't know where to get height from...
    	addPage(createdWord, pageNum); //add page found at for createdWord
    	if (firstWord == 1){ //if first run, create the list
    		skipList myList = createList(createdWord);
    		firstWord--; //increment count
    	}
    	else //else insert the word into the list
    		insert(myList = createdWord);
      print(fout, word);
    }
  }
}
