#include <iostream>
#include <vector>
#include <cstdlib>	// provides atoi()
#include <iomanip>	// provides std::setw()
#include <cstdio>	// provides sprintf()
#include "unit.h"

typedef unsigned int uint;

/**
 * A tree node.
 */
struct Node {
  int key;
  Node * left;
  Node * right;
};

/**
 * A visitor that can be used to traverse the tree. This is an abstract class;
 * you can't instantiate it directly.
 */
class Visitor {
public:
  virtual ~Visitor() { }
  virtual void visit(Node* node, int level) = 0;
};

/**
 * Creates a new Node with key=key, left=l, and right=r.
 */
Node* createNode( int key, Node* l = NULL, Node* r = NULL ) {
  Node* result = new Node;
  result->key = key;
  result->left = l;
  result->right = r;
  return result;
}

/**
 * Deletes all nodes in the tree rooted at root and sets root to NULL.
 */
void deleteTree( Node*& root ) {
  if ( root != NULL ) {
    deleteTree( root->left );
    deleteTree( root->right );
    delete root;
    root = NULL;
  }
}

/**
 * Recursively find a node with key 'key'.
 */
Node * find(Node *r, int key) {
  if (r == NULL) return r;
  if (key < r->key)
    return find(r->left, key);
  if (key > r->key)
    return find(r->right, key);
  return r;
}

/**
 * Finds the parent of node in the tree rooted at rootNode
 */
Node* find_parent(Node* r, Node* node) {
  if ( r == NULL || r == node ) {
    return NULL;
  } else if ( r->left == node || r->right == node ) {
    return r;
  } else if (node->key < r->key) {
    return find_parent(r->left, node);
  } else {
    return find_parent(r->right, node);
  }
}

/**
 * Deletes a node containing 'key' in the tree rooted at 'root'.
 */
bool delete_node(Node*& root, int key) {
  // find target node to delete
  Node* target = find(root, key);
  if (!target) return false;

  // find parent of target
  Node* parent = find_parent(root, target);

  // case 1: target is a leaf or has only a right child
  if (target->left == NULL) {
    // set parent's child pointer
    if (parent != NULL) {
      if ( parent->left == target )
	parent->left = target->right;
      else
	parent->right = target->right;
    } else
      root = target->right;
  }

  // case 2: target has only left child
  else if (target->right == NULL) {
    // set parent's child pointer
    if (parent != NULL) {
      if ( parent->left == target )
	parent->left = target->left;
      else
	parent->right = target->left;
    } else
      root = target->left;
  }

  // case 3: target has two children
  else {
    /**
     * THIS SECTION NEEDS TO BE IMPLEMENTED ********************
     *
     * Add the missing lines here to make the function complete. (Hint: To
     * remain a valid binary tree, you must replace 'target' with either
     * its predecessor or its successor. To make the lab more easy to test,
     * PLEASE USE THE PREDECESSOR.)
     */
    Node* predecessor = target->left; //take the left branch
    while(predecessor->right != NULL){ //while it has right branches
        predecessor = predecessor->right; //go down the right side
    }
    
    Node* parentOfPred = find_parent(root, predecessor); //find the parent or right most
    target->key = predecessor->key; //reassign target key
    
    if(parentOfPred->left == predecessor){ //now try the left side nodes
        parentOfPred->left == predecessor->left; //if there's a left, take it
    } else {
        parentOfPred->right = predecessor->right; //otherwise it'll be the right
    }
    delete predecessor; //no longer need temp anymore
  }

  // free target
  delete target;
  return true;
}

/**
 * Inserts key 'key' into the tree rooted at 'root'.
 */
void insert(Node *& root, int key) {
  if( root == NULL ) {
    root = createNode(key);
  } else if( root->key == key ) {
    std::cerr << "Duplicate key \"" << key << "\" not inserted." << std::endl;
  } else if( key < root->key ) {
    insert(root->left, key);
  } else {
    insert(root->right, key);
  }
}

/**
 * Prints out the tree sideways.
 */
void printTree( Node * r, int d = 0 ) {
  if( r == NULL ) return;
  printTree( r->right, d+1 );
  std::cout << std::setw( 3 * d ) << ""; // output 3 * d spaces
  std::cout << r->key << std::endl;
  printTree( r->left, d+1 );
}

/**
 * Returns the number of nodes in the tree rooted at root.
 */
int numNodes( Node* root ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
  if (root != NULL){ //if not null, has more to count, so +1 and keep going
      return 1 + numNodes(root->right) + numNodes(root->left);
  } else { //nothing more to count and this doesn't exist so +0
      return 0;
  }
}

/**
 * Returns the number of leaves in the tree rooted at root.
 */
int numLeaves( Node* root ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
  if (root == NULL){
    return 0; //doesn't exist so doesn't count
  }
  if (root->right == NULL && root->left == NULL){
    return 1; //it's a leaf by definition
  }
  //otherwise recurse past it
  return numLeaves(root->right) + numLeaves(root->left);

}

/**
 * Returns the height of node x.
 */
int height( Node* x ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
    if (x == NULL){ //null is -1
        return -1;
    }
    if (x->right == NULL & x->left == NULL){ //plain node = 0
        return 0;
    }
    int right = height(x->right); //get right and left heights
    int left = height(x->left);
    
    if (left > right){ //use whichever is bigger to form the largest height
        return 1 + left;
    } else {
        return 1 + right;
    }
    
}

/**
 * Returns the depth of node x in the tree rooted at root.
 */
int depth( Node* root, Node* x ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
    //like height but is relative
    if (root == NULL || root == x){ //definition shows 0
        return 0;
    }
    if (x->key > root->key){
        return 1 + depth(x, root->right);
    } else {
        return 1 + depth(x, root-left);
    }

}

/**
 * Traverse a tree rooted at rootNode in-order and use 'v' to visit each node.
 */
void in_order( Node* rootNode, int level, Visitor& v ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
    if (rootNode != NULL){
        in_order(rootNode->left, 1 + level, v);
        v.visit(rootNode, level);
        in_order(rootNode->right, 1 + level, v);
    }
}

/**
 * Traverse a tree rooted at rootNode pre-order and use 'v' to visit each node.
 */
void pre_order( Node* rootNode, int level, Visitor& v ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
    if (rootNode != NULL){
        v.visit(rootNode, level);
        in_order(rootNode->left, 1 + level, v);
        in_order(rootNode->right, 1 + level, v);
    }
}

/**
 * Traverse a tree rooted at rootNode post-order and use 'v' to visit each node.
 */
void post_order( Node* rootNode, int level, Visitor& v ) {
  /**
   * THIS FUNCTION NEEDS TO BE IMPLEMENTED ********************
   */
    if (rootNode != NULL){
        in_order(rootNode->left, 1 + level, v);
        in_order(rootNode->right, 1 + level, v);
        v.visit(rootNode, level);
    }
}


///////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////

/**
 * Might be useful in your testing.
 */
class PrintVisitor : public Visitor {
  void visit(Node* node, int level) {
    std::cout << "Level " << level << ": ( " << node->key << " )" << std::endl;
  }
};

/**
 * Insert your own custom tests and print statements here to test your
 * implementation. These will be executed if you supply the tree keys on the
 * command line. For marking, you will execute the program without arguments,
 * and it will run the automated tests.
 */
void runMain(Node*& tree, std::vector<int> keys) {
  /*
   * CHANGE THIS CODE ALL YOU LIKE. This is your test space.
   */
  std::cout << "Full Tree:" << std::endl;
  printTree(tree);
  std::cout << std::endl;

  std::cout << "number of Nodes  = " << numNodes(tree) << std::endl;
  std::cout << "number of Leaves = " << numLeaves(tree) << std::endl;
  std::cout << "height of tree   = " << height(tree) << std::endl;
  std::cout << std::endl;
  for (unsigned int i = 0; i < keys.size(); ++i) {
    std::cout << "height(" << keys[i] << ") = " << height(find(tree, keys[i])) << std::endl;
    std::cout << "depth(" << keys[i] << ") = " << depth(tree, find(tree, keys[i])) << std::endl;
  }
  std::cout << std::endl;

  PrintVisitor v;
  std::cout << "In-order traversal:" << std::endl;
  in_order(tree, 0, v);
}

///////////////////////////////////////////////////////////////////////////////
// DO NOT ALTER BEYOND THIS POINT
///////////////////////////////////////////////////////////////////////////////

/** values to use for tests */
int keysArr[] =		{5, 3, 2, 1, 6, 8, 4, 7, 9};
int heightArr[] =	{3, 2, 1, 0, 2, 1, 0, 0, 0};
int depthArr[] =	{0, 1, 2, 3, 1, 2, 2, 3, 3};
int inArr[] =		{1, 2, 3, 4, 5, 6, 7, 8, 9};
int preArr[] =		{5, 3, 2, 1, 4, 6, 8, 7, 9};
int postArr[] =		{1, 2, 4, 3, 7, 9, 8, 6, 5};
std::vector<int> keys(keysArr, keysArr + sizeof(keysArr) / sizeof(int));
std::vector<int> heights(heightArr, heightArr + sizeof(heightArr) / sizeof(int));
std::vector<int> depths(depthArr, depthArr + sizeof(depthArr) / sizeof(int));
std::vector<int> inOrder(inArr, inArr + sizeof(inArr) / sizeof(int));
std::vector<int> preOrder(preArr, preArr + sizeof(preArr) / sizeof(int));
std::vector<int> postOrder(postArr, postArr + sizeof(postArr) / sizeof(int));

class TestVisitor : public Visitor {
public:
  std::vector<int> q;
  void visit(Node* node, int level) {
    q.push_back(node->key);
  }
};

/**
 * Runs the tests for marking. You can run it yourself to check your solution.
 */
void runTests(Node*& tree, std::vector<int> keys) {
  Unit unit;
  TestVisitor v;

  std::cout << "Testing Tree:" << std::endl;
  printTree(tree);
  std::cout << std::endl;

  unit.assertEquals("Number of nodes", 9, numNodes(tree));
  unit.assertEquals("Number of leaves", 4, numLeaves(tree));
  unit.assertEquals("Height", 3, height(tree));

  std::string h("height");
  std::string d("depth");
  for (unsigned int i = 0; i < keys.size(); ++i) {
    unit.assertEquals(h+"("+std::to_string(keys[i])+")",
                      heights[i], height(find(tree, keys[i])));
    unit.assertEquals(d+"("+std::to_string(keys[i])+")",
                      depths[i], depth(tree, find(tree, keys[i])));
  }

  v.q.clear();
  in_order(tree, 0, v);
  unit.assertvectorEquals("In-order traversal", inOrder, v.q);
  v.q.clear();
  pre_order(tree, 0, v);
  unit.assertvectorEquals("Pre-order traversal", preOrder, v.q);
  v.q.clear();
  post_order(tree, 0, v);
  unit.assertvectorEquals("Post-order traversal", postOrder, v.q);

  //Delete a leaf
  unit.assertNonNull("Finding 9 (a leaf)", find(tree, 9));
  delete_node(tree, 9);
  unit.assertNull("Deleting 9 (a leaf)", find(tree, 9));
  unit.assertEquals("Number of nodes", 8, numNodes(tree));
  unit.assertEquals("Number of leaves", 3, numLeaves(tree));
  unit.assertEquals("Height", 3, height(tree));

  //Delete a node with one child
  unit.assertNonNull("Finding 2 (a node with one child)", find(tree, 2));
  delete_node(tree, 2);
  unit.assertNull("Deleting 2 (a node with one child)", find(tree, 2));
  unit.assertEquals("Number of nodes", 7, numNodes(tree));
  unit.assertEquals("Number of leaves", 3, numLeaves(tree));
  unit.assertEquals("Height", 3, height(tree));

  //Delete a node with two children
  unit.assertNonNull("Finding 3 (a node with two children)", find(tree, 3));
  delete_node(tree, 3);
  unit.assertNull("Deleting 3 (a node with two children)", find(tree, 3));
  unit.assertEquals("Number of nodes", 6, numNodes(tree));
  unit.assertEquals("Number of leaves", 2, numLeaves(tree));
  unit.assertEquals("Height", 3, height(tree));

  //Delete root
  unit.assertNonNull("Finding 5 (the root)", find(tree, 5));
  delete_node(tree, 5);
  unit.assertNull("Deleting 5 (the root)", find(tree, 5));
  unit.assertEquals("Number of nodes", 5, numNodes(tree));
  unit.assertEquals("Number of leaves", 2, numLeaves(tree));
  unit.assertEquals("Height", 3, height(tree));
	
  //Additional tests for delete, height, depth
	
  Node* tree2 = NULL;
  insert(tree2, 7);
  insert(tree2, 9);
  insert(tree2, 5);
  insert(tree2, 1);
	
  //Test height, depth
  Node* node_9 = find(tree2, 9);
  unit.assertEquals("Height of 9", 0, height(node_9));
  unit.assertEquals("Depth of 9", 1, depth(tree2, node_9));
  Node* node_1 = find(tree2, 1);
  unit.assertEquals("Height of 1", 0, height(node_1));
  unit.assertEquals("Depth of 1", 2, depth(tree2, node_1));
	
  // delete root with 2 children, left child of root is predecessor with 1 child
  delete_node(tree2, 7);
  unit.assertEquals("Number of nodes", 3, numNodes(tree2));
  unit.assertEquals("Number of leaves", 2, numLeaves(tree2));
  unit.assertEquals("Height", 1, height(tree2));
	
  // delete root with 2 children, left child of root is not predecessor, predecessor has 1 child
  insert(tree2, 4);
  insert(tree2, 2);
  delete_node(tree2, 5);
  unit.assertEquals("Number of nodes", 4, numNodes(tree2));
  unit.assertEquals("Number of leaves", 2, numLeaves(tree2));
  unit.assertEquals("Height", 2, height(tree2));

  deleteTree(tree2);

  std::cout << std::endl;
  unit.printResults();
}

/**
 * Runs custom code if given command line arguments, otherwise runs tests.
 */
int main( int argc, char *argv[] ) {
  Node *tree = NULL;

  bool custom = argc > 1;
  if (custom) {	// if keys given on command line, run tests
    keys.clear();
    for (int i=0; i < argc-1; ++i) {
      keys.push_back(atoi(argv[i+1]));
    }
  }

  for (unsigned int i=0; i < keys.size(); ++i) {
    insert(tree, keys[i]);
  }

  if (custom) {
    runMain(tree, keys);
  } else {
    runTests(tree, keys);
  }

  // Free up allocated memory
  deleteTree(tree);
  return 0;
}

