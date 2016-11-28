//
// Lab 9 = Parallel calculation of word frequency statistics using an AVL tree.
//
#include <omp.h>
#include <iostream>
#include <fstream>
#include <iomanip>	// provides setw()
#include <cstdlib>	// provides atoi()
#include <cassert>	// provides assert
#include <functional>	// provides std::function

#define REPETITIONS 10		// Number of times we repeat the task.

// ************* TODO: Pick a better cutoff value. *************
int SEQUENTIAL_CUTOFF = 0;	// Default height at which we switch from
                                // parallel to sequential code

typedef std::string KType;   // The datatype for the key of the AVL tree Node
typedef int VType;           // The datatype for the value of the AVL tree Node

struct Node {        // A Node in an AVL tree.
  KType key;         // a word
  VType value;       // the number of times the word occurs in the input
  int height;        // height of the node
  Node * left;       // pointer to the left child of the node (or NULL)
  Node * right;      // pointer to the right child of the node (or NULL)
};


// Create a new Node with the given parameters.
Node* createNode( KType key, VType value, Node* left=NULL, Node* right=NULL ) {
  Node* result = new Node;
  if( result == NULL ) return (Node*) NULL;
  result->key = key;
  result->value = value;
  result->height = 0;
  result->left = left;
  result->right = right;
  return result;
}

// Delete all the nodes in the tree rooted at *root
void deleteTree( Node*& root ) {
  if ( root != NULL ) {
    deleteTree( root->left );
    deleteTree( root->right );
    delete root;
    root = NULL;
  }
}

// Get height of a Node.
int getHeight( Node * node ) {
  return ( node != NULL ) ? (node->height) : -1;
}

// Calculate the height of a Node from its children's heights.
int calcHeight( Node * node ) {
  if ( node == NULL ) return -1;
  int left_height = getHeight( node->left );
  int right_height = getHeight( node->right );
  return ( left_height > right_height ) ? left_height + 1 : right_height + 1;
}

// Set the height of a Node.
void setHeight( Node * node, int height ) {
  if ( node == NULL ) return;
  if (node->height == height) return;
  node->height = height;
}

// Return the value of a Node.
VType getValue(Node* node) {
  assert( node );
  return node->value;
}

// Set the value of a Node.
void setValue(Node* node, VType value) {
  assert( node );
  node->value = value;
}

// "Rotate" the subtree to the left (counter-clockwise).
void rotateLeft( Node *& root ) {
  assert(root != NULL);
  assert(root->right != NULL);
  Node * temp = root->right;
  root->right = temp->left;
  temp->left = root;
  setHeight( root, calcHeight(root) );
  setHeight( temp, calcHeight(temp) );
  root = temp;
}

// "Rotate" the subtree to the right (clockwise).
void rotateRight( Node *& root ) {
  assert(root != NULL);
  assert(root->left != NULL);
  Node * temp = root->left;
  root->left = temp->right;
  temp->right = root;
  setHeight( root, calcHeight(root) );
  setHeight( temp, calcHeight(temp) );
  root = temp;
}

// doubleRotateLeft(root) is rotateRight(root->right) then rotateLeft(root).
void doubleRotateLeft( Node *& root ) {
  assert(root != NULL);
  assert(root->right != NULL);
  assert(root->right->left != NULL);
  rotateRight(root->right);
  rotateLeft(root);
}

// doubleRotateRight(root) is rotateLeft(root->left) then rotateRight(root).
void doubleRotateRight( Node *& root ) {
  assert(root != NULL);
  assert(root->left != NULL);
  assert(root->left->right != NULL);
  rotateLeft(root->left);
  rotateRight(root);
}

// Balance subtree rooted at *root.
void balance( Node *& root ) {
  if( root == NULL ) return;

  int left_height = getHeight( root->left );
  int right_height = getHeight( root->right );

  // if *root is balanced, we're done.
  if (abs(right_height - left_height) <= 1) return;

  if (right_height > left_height) {
    // asserts are often used as a kind of documentation.
    assert( right_height > 1 + left_height );
    // always check that it's OKAY to dereference the pointers.
    if (root->right && root->right->left
        && (right_height == 1 + root->right->left->height)){
      doubleRotateLeft( root );
    }
    else {
      rotateLeft( root );
    }
  }
  else {
    assert( left_height > right_height + 1 );
    if (root->left && root->left->right
        && (left_height == 1 + root->left->right->height)){
      doubleRotateRight( root );
    }
    else {
      rotateRight( root );
    }
  }
}

// Insert into tree.
void insert( KType key, VType value, Node *& root ) {
  if( root == NULL ) {  // base case
    root = createNode(key, value);
    return;
  }
  else if( key < root->key ) {
    insert( key, value, root->left );
  }
  else if( key > root->key ) {
    insert( key, value, root->right );
  }
  // update root->height if it's changed, and balance(root)
  int calcHeight_root = calcHeight( root );
  if( calcHeight_root != getHeight( root) ) {
    setHeight( root, calcHeight_root );
    balance(root);
  }
}

// Return a reference to a pointer to the Node in the tree with the given key.
Node*& findNode(KType key, Node*& root) {
  if( root == NULL ) {
    return root;
  }
  if( key < root->key ) {
    return findNode( key, root->left);
  }
  if( key > root->key ) {
    return findNode( key, root->right);
  }
  return root;
}

// Good for debugging.
// Helper to print the tree sideways.
void printTreeHelper( Node * root, int depth ) {
  if( root == NULL ) return;
  printTreeHelper( root->right, depth + 1 );
  std::cout << std::setw( 3 * depth ) << "";	// output 3 * depth spaces
  std::cout << root->key << std::endl;
  printTreeHelper( root->left, depth + 1 );
}

// Good for debugging.
// Print out the tree sideways.
void printTree( Node * root ) {
  printTreeHelper( root, 0 );
}

// Good for debugging.
// Return true iff *root is the root of a valid AVL tree.
bool isValidAVLTree( Node* root ){
  if ( root == NULL ) return true;
  if (isValidAVLTree( root->left ) && isValidAVLTree( root->right )) {
    if (abs(getHeight( root->left ) - getHeight( root->right )) > 1)
      return false;
    return true;
  }
  else return false;
}


// Calculate the stats for the whole tree given:
// the root's value and the stats for the root's left and right subtrees.
//
// This calculates the population variance.
//
// <see Wikipedia: Algorithms for calculating variance>
void updateStats( VType value,
                  double lavg, double lvar, int lcount,
                  double ravg, double rvar, int rcount,
                  double& avg, double& var, int& count ) {
  double delta, m;
  count = lcount + rcount;
  if( count > 0 ) {
    avg = (lcount * lavg + rcount * ravg)/(double)count;
    delta = lavg - ravg;
    double lm = lvar * lcount;
    double rm = rvar * rcount;
    m = lm + rm + delta * delta * lcount * rcount / (double)count;
  } else {
    avg = 0; var = 0; m = 0;
  }
  count++;
  delta = (double)(value - avg);
  avg += delta/(double)count;
  m += delta * (value - avg);
  var = m / (double)count;
}


// Calculate statistics for the subtree rooted at *root.
void findStatsSequential(Node * root, double &avg, double &var, int &count) {
  if (root == NULL) {
    avg = 0; var = 0; count = 0;
    return;
  }

  double lavg, lvar, ravg, rvar;
  int lcount, rcount;

  // Find stats in the left subtree.
  findStatsSequential(root->left, lavg, lvar, lcount);

  // Find stats in the right subtree.
  findStatsSequential(root->right, ravg, rvar, rcount);

  updateStats(root->value,
              lavg, lvar, lcount,
              ravg, rvar, rcount,
              avg, var, count);
}


// Helper for findStats.
//
// Fork off tasks to handle subtrees until you first can tell, by considering
// the height of the root, that the tree contains at most 1100 nodes
// at which point use the sequential version.
//
// Use findStatsSequential for inspiration.
//
void findStatsHelper(Node * root, double &avg, double &var, int &count) {

  // ************ TODO: Implement this! *************

	if (root == NULL) {
    avg = 0; var = 0; count = 0;
    return;
  }

  int lcount,rcount;
  double lavg, ravg, lvar, rvar;
  Node * left_search = root->left;
  Node * right_search = root->right;

  while ((getHeight(root) + getHeight(left_search) + getHeight(right_search) >= 1100)){
  	findStatsHelper(left_search, lavg, lvar, lcount);
  	findStatsHelper(right_search, ravg, rvar, rcount);
  	}

  	 updateStats(root->value,
              lavg, lvar, lcount,
              ravg, rvar, rcount,
              avg, var, count);
	
}

// Parallel version of findStatsSequential
void findStats(Node * root, double &avg, double &var, int &count) {
  // Declare OpenMP parallel region and start execution on one thread.
  // *untied* task creation (in findStatsHelper) will exploit additional
  // threads.
#pragma omp parallel
  {
  #pragma omp single
    {
      findStatsHelper(root, avg, var, count);
    }
  }
}

// Print a message on stdout about how to use this program.
void usage(const char* program) {
  std::cout << "Usage: " << program << " <filename> [cutoff]"  << std::endl;
  std::cout << "\tPrints the mean and std deviation of the distribution of words and the number of unique words in the named file."
            << std::endl;
}

// Run REPETITIONS trials of either sequential or parallel findStats
// and reports the time in seconds that this takes.
void findStatsAndReport(std::function<void(Node*, double&, double&, int&)> f,
                        Node * tree,
                        const char * type) {
  double avg, var;
  int count;

  double t1, t2;
  t1 = omp_get_wtime();
  for (int i = 0; i < REPETITIONS; i++) {
    f(tree, avg, var, count);
  }
  t2 = omp_get_wtime();

  std::cout << type << "\tmean:" << avg << "\tvar:" << var << "\tn:" << count << "\t";
  std::cout << t2 - t1 << " secs" << std::endl;
  std::cout.flush();
}

int main( int argc, char *argv[] ) {
  if (argc < 2 || argc > 3) {
    usage(argv[0]);
    return -1;
  }
  if (argc == 3) {
    SEQUENTIAL_CUTOFF = std::atoi( argv[2] );
  }

  std::fstream infile;
  infile.open( argv[1], std::fstream::in );
  if (infile.rdstate()) { // some type of error
    std::cerr<< "Error opening " << argv[1] << std::endl;
    if ((infile.rdstate() &  std::ifstream::failbit) != 0 )
      std::cerr << " failbit";
    if ((infile.rdstate() &  std::ifstream::badbit) != 0 )
      std::cerr << " badbit";
    if ((infile.rdstate() &  std::ifstream::eofbit) != 0 )
      std::cerr << " eofbit";
    std::cerr << std::endl;
    return -1;
  }

  // Tally all the words.
  Node *avlTree_root = NULL;
  std::string word;

  // foreach word, attempt to find a Node with key==word already in tree
  // if none exists, then make one, with value == 0
  // always increment the tally for the word by 1

  while (infile >> word) {
    Node* node = findNode( word, avlTree_root );
    if( node == NULL ) {
      insert( word, 1, avlTree_root );
    }
    else setValue( node, 1 + getValue(node) );
  }

  // Find stats for the word distribution, first sequential then parallel

  findStatsAndReport(&findStatsSequential, avlTree_root, "SEQUENTIAL");

  findStatsAndReport(&findStats, avlTree_root, "PARALLEL");
  std::cout << "Cutoff = " << SEQUENTIAL_CUTOFF << "\t";
  std::cout << "Number of processors = " << omp_get_num_procs() << std::endl;


  // Free up allocated memory
  deleteTree(avlTree_root);

  return 0;
}
