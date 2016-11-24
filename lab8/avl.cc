#include <iostream>
#include <sstream>
#include <iomanip>	// provides setw()
#include <cstdlib>	// provides atoi() abs()
#include <cassert> // provides assert()
#include <vector> 
#include <string> 
#include "Unit.h" 

// ********** DO NOT CHANGE ANYTHING EXCEPT: **************************
// ********** void balance( Node *& x )      WRITE THIS METHOD 
// ********** Also: you can temporariliy uncomment lines like: 
// std::cout << "rotateLeft: root->key = " << root->key << std::endl;
// ********** ****************************** **************************

Unit unit; // Unit testing framework 
std::vector<int> visitor; 
std::vector<int> expected; 

typedef int KType;

struct Node {
  KType key;
  int height;
  Node * left;
  Node * right;
};

Node* createNode( KType key, Node* l = NULL, Node* r = NULL ) {
  //
  // Creates a new Node containing key, with 'l' as its left 
  // child and 'r' as its right child, with height=0
  //
  // PRE:  key is valid, l points to a Node or is NULL and r 
  //       points to a Node or is NULL
  // POST: If there is enough free memory space, a new Node is created
  //	   and its address is returned; otherwise, NULL is returned.

  Node* result = new Node;
  if (! result) return (Node*) NULL; 
  result->key = key;
  result->height = 0;
  result->left = l;
  result->right = r;
  return result;
}

void deleteTree( Node*& root ) {
  //
  // Deletes a tree rooted at root
  //
  // PRE:  root is a valid Node address or NULL
  // POST: All the nodes in the tree rooted at root are deleted and   
  //       root is set to NULL.

  if ( root != NULL ) {
    deleteTree( root->left );
    deleteTree( root->right );
    delete root;
    root = NULL;
  }
}

int height( Node * x ) {
  //
  // Returns the height of node x or -1 if x is NULL.
  //
  if( x == NULL ) return -1;
  return x->height;
}

bool updateHeight( Node * x ) {
  //
  // Recalculates the height of x from the height of its children.
  // Returns true iff the height of x changes.
  //
  if( x == NULL ) return false;
  int m = std::max(height(x->left), height(x->right)) + 1;
  if( x->height != m ) {
    x->height = m;
    return true;
  }
  return false;
}

/** 
* "rotates" the subtree to the left (counter-clockwise)
*/ 
void rotateLeft( Node *& root ) {
  // if Unit tests have errors to report, use its insist method so 
  // even if assert() fails, the errors get reported  
  if (unit.hasErrors()) {
      unit.insistNonNull("rotateLeft Node* root", root); 
  }
  assert(root != NULL); // not wrapped in else-body (so: no doubt it happens)
  if (unit.hasErrors()) {
      unit.insistNonNull("rotateLeft Node* root->right", root->right); 
  }
  assert(root->right != NULL); // ditto 
  // --------
  // std::cout << "rotateLeft: root->key = " << root->key << std::endl;
  // --------  
  Node * temp = root->right;
  root->right = temp->left;
  temp->left = root;
  updateHeight(root);
  updateHeight(temp);
  root = temp;
}
/**
 * "rotates" the subtree to the right (clockwise)
 */
void rotateRight( Node *& root ) {
  // if Unit tests have errors to report, use its insist method so 
  // even if assert() fails, the errors get reported  
  if (unit.hasErrors()) {
      unit.insistNonNull("rotateRight Node* root", root); 
  }
  assert(root != NULL); // not wrapped in else-body (so: no doubt it happens)
  if (unit.hasErrors()) { 
      unit.insistNonNull("rotateRight Node* root->left", root); 
  }
  assert(root->left != NULL); // ditto 
  // --------
  // std::cout << "rotateRight: root->key = " << root->key << std::endl; 
  // --------
  Node * temp = root->left;
  root->left = temp->right;
  temp->right = root;
  updateHeight(root);
  updateHeight(temp);
  root = temp;
}

void doubleRotateLeft( Node *& a ) {
  // if Unit tests have errors to report, use its insist method so 
  // even if assert() fails, the errors get reported  
  if (unit.hasErrors()) { 
      unit.insistNonNull("doubleRotateLeft Node* a", a); 
  }
  assert(a != NULL); // not wrapped in else-body (so: no doubt it happens)
  // --------
  // std::cout << "doubleRotateLeft: a->key = " << a->key << std::endl; 
  // --------
  rotateRight(a->right);
  rotateLeft(a);
}

void doubleRotateRight( Node *& a ) {
// if Unit tests have errors to report, use its insist method so 
// even if assert() fails, the errors get reported  
  if (unit.hasErrors()) {
      unit.insistNonNull("doubleRotateRight Node * a", a); 
  }
  assert(a != NULL);
  // --------
  // std::cout << "doubleRotateRight: a->key = " << a->key << std::endl; 
  // --------
  rotateLeft(a->left);
  rotateRight(a);
}

// ********** DO NOT CHANGE ABOVE HERE ****************
  //
  // Check if node x is unbalanced (i.e., the heights of its
  // two children differ by more than one).  If it is, rebalance
  // at x using one of rotateLeft, rotateRight, doubleRotateLeft,
  // or doubleRotateRight, whichever is appropriate.
  //
void balance( Node *& x ) {
  //TODO: write this function  

  int nodeHeight = height(x->left) - height(x->right);

  if (nodeHeight > 1){ //x->left height > x->right height
    if (height(x->left->left) < height(x->left->right)){ //since right side child tree heavy
      doubleRotateRight(x); //double rotate due to child's child
    }
    else 
      rotateRight(x); //due to hightDifference being left heavy
  }

  if (nodeHeight < -1){ //x->right height > x->left height
    if (height(x->right->left) > height(x->right->right)){ //left side child tree heavy
      doubleRotateLeft(x); //double rotate left
    }
    else
      rotateLeft(x);  //right side is greater so rotateLeft
  } 
}
// ********** DO NOT CHANGE BELOW HERE ****************

/**
 * Insert key into the AVL tree rooted at root.
 * Restore balance if required (possibly changing root) 
 * (input root can be NULL, it just means the tree was empty) 
 */
void insert( KType key, Node *& root ) {
  // BASE CASE 
  if( root == NULL ) {
    root = createNode(key);
    return;
  }
  // either go to the left, or to the right, but ignore if already in tree
  if( key < root->key ) {
    insert( key, root->left );
  }
  // 2014W2 if key == root->key then ignore it (do not insert duplicate) 
  else if( key > root->key ) {                       
    insert( key, root->right );
  }
  // We know: descendant had a child added (in recursive call, above).
  // Now we're "unwinding" the call-stack (returning from the recursive calls, 
  // one level at a time, until we get to the original call). 
  // Do we have to rebalance at this level?
  if( updateHeight(root) ) balance(root);
}

bool contains( KType key, Node * root ) {
  //
  // Return true iff the tree contains the given key.
  //
  if ( root == NULL ) {
    return false;
  }

  if ( key < root->key ) {
    return contains( key, root->left );
  }
  else if ( key > root->key ) {
    return contains( key, root->right );
  }
  else
    return true;
}


//
// Prints out the tree sideways
//
// PRE:  r is a valid Node address 
// POST: The tree rooted at r is printed in reverse inorder with nodes  
//       indented 3 * d spaces; this produces a tree that has its root near  
//       the left side of the screen and the leaves near the right side
void printTreeHelper( Node * r, int d ) {
  if( r == NULL ) return;
  
  printTreeHelper( r->right, d+1 );
  std::cout << std::setw( 3 * d ) << "";		// output 3 * d spaces
  std::cout << r->key << std::endl;
  printTreeHelper( r->left, d+1 );
}

void printTree( Node * r ) {
  printTreeHelper( r, 0 );
}
// *******************************************
// records keys, heights, levels as tree is traversed
void visitTreeHelper( Node* root, int level, std::vector<int>& visitor){
  if (! root) return; 
  visitTreeHelper( root->right, level + 1, visitor);
  visitor.push_back( root->key ); 
  visitor.push_back( root->height ); 
  visitor.push_back( level ); 
  visitTreeHelper( root->left, level + 1, visitor);
}  
void visitTree(Node* root, std::vector<int>& visitor){ 
  visitTreeHelper( root, 0, visitor);
}
// values for default keys on tree traverals 
int traversalValues [] = { 70,0,0,
  70,1,0,10,0,1,
  70,0,1,60,1,0,10,0,1,
  70,0,1,60,2,0,20,0,2,10,1,1,
  70,0,1,60,2,0,50,0,2,20,1,1,10,0,2,
  70,0,2,60,1,1,50,2,0,30,0,2,20,1,1,10,0,2,
  70,0,2,60,1,1,50,3,0,40,0,3,30,1,2,20,2,1,10,0,2,
  70,0,2,60,1,1,50,3,0,40,0,3,30,1,2,25,0,3,20,2,1,10,0,2,
  70,0,2,60,1,1,50,3,0,40,0,3,30,1,2,27,0,3,25,2,1,20,1,2,10,0,3,
  70,0,2,60,1,1,50,3,0,40,0,3,30,1,2,27,0,3,25,2,1,20,0,3,10,1,2,5,0,3 };
void prepareExpected(int num_to_skip, int num_to_take, std::vector<int>& vv){
  vv.clear();
  for (int ii = num_to_skip; ii < num_to_skip + num_to_take; ++ ii ){ 
    vv.push_back( traversalValues [ii] ); 
  }
  return;
}
  
// keys to insert by default
int defaultKeys[] = {70, 10, 60, 20, 50, 30, 40, 25, 27, 5};

int main( int argc, char *argv[] ) {
  Node *T = NULL;
  int *keys;
  int num_keys;

  if( argc == 1 ) {	// if no command line args use default keys
    num_keys = sizeof(defaultKeys)/sizeof(int);
    keys = new int[num_keys];
    for( int i=0; i < num_keys; ++i ) {
      keys[i] = defaultKeys[i];
    }
  }
  else {		// use keys given on command line
    num_keys = argc - 1;
    keys = new int[num_keys];
    for( int i=0; i < num_keys; ++i ) {
      keys[i] = atoi(argv[i+1]);
    }
  }

  int unitOffset = 0;
  for( int i=0; i < num_keys; ++i ) {
    std::cout << "Insert: " << keys[i] << std::endl;
    insert(keys[i], T);
    std::cout << "Tree:" << std::endl;
    printTree(T);
    // use default keys for unit tests
    if (argc == 1) { 
      std::stringstream cmt;
      cmt << "contains( " << keys[i] << ") "; 
      unit.assertTrue(cmt.str(), contains( keys[i], T )); 
      visitor.clear();
      visitTree(T, visitor);
      prepareExpected( 3 * unitOffset, 3 * (i + 1), expected ); 
      unitOffset += i + 1; 
      std::stringstream fmt;
      fmt << "Tree after insert key[" << i << "] == "<< keys[i] << " "; 
      unit.assertvectorEquals(fmt.str(), expected, visitor ); 
    }
  }
  if (argc == 1) unit.printResults(); 

  // Free up allocated memory
  delete[] keys;
  deleteTree(T);

  return 0;
}

