// Author: Dr. Al-Haj
// ECCS 2671: Data Structures and Algorithms 1
// Date: November 2019

// Use this code to submit your assignment #6.

#include <iostream>
#include <vector>

using namespace std;

// Binary Search Tree
class BSTree {

private:
	struct node {
		int data;				// key data
		node* left;			// a pointer to the left subtree
		node* right;		// a pointer to the right subtree

		// destructor to free memory used by node objects
		~node() {
			delete left;
			delete right;
			cout << "a node is deleted..." << endl;
		}
	};

	// a pointer to the root node, it is declared as a private
	// so users cant access it directly.
	node* root;

	// these functions are declared in the private section
	// to be used inside the class as utility functions,
	// user can't use them.
	node* createNode(const int data);
	void insertNodeUtil(const int data, node* subTreePtr);
	void printInOrderUtil(node* subTreePtr);
	bool findKeyUtil(const int key, node* subTreePtr);

	// insert any utility function you implement here
	//void storeTree(vector<node*> &nodes, node* treeRoot);
	node* getBalancedCopyUtil(int nodes[], int start, int end);


public:
	BSTree();
	~BSTree();
	void insertNode(const int addData);
	void printInOrder();
	bool findKey(const int key);

	void getBalancedCopy(BSTree);
};

// Constructor -- initialize root pointer to nullptr
BSTree::BSTree() {

	root = nullptr;
}

// Destructor -- deallocate all reserved space
BSTree::~BSTree() {

	delete root;
}


// a utility function to create a new node and returns a pointer
// pointing at the created node
BSTree::node* BSTree::createNode(const int addData) {

	node* newNode = new node;

	newNode->data = addData;
	newNode->left = nullptr;
	newNode->right = nullptr;

	return newNode;
}

// node insertion is done recursively, that's why we have
// a utility function that has two parameters: data + pointer
// user can access this function but not the utility function
void BSTree::insertNode(const int addData) {

	insertNodeUtil(addData, root);
}

// this function uses recursion to find the right place for
// new node to be inserted. Every subtree is considered a tree.

// To control the recursion, we need to pass private information
// as a parameter, that's why this function is not declared as public.

// Divide-an-Conquer: sub-problem <==> sub-tree
void BSTree::insertNodeUtil(const int data, node* subTreePtr) {

	if (root == nullptr) {
		root = createNode(data);
	}
	// check the left side of the tree
	else if (data <= subTreePtr->data) {
		// keep going to the left until we find a node that has no left child
		if (subTreePtr->left == nullptr) {
			subTreePtr->left = createNode(data);
		}
		else { // keep going left
			insertNodeUtil(data, subTreePtr->left);
		}
	}
	// check the right side of the tree
	else {//if(data > subTreePtr->data){
		if (subTreePtr->right == nullptr) {
			subTreePtr->right = createNode(data);
		}
		else { // keep going right
			insertNodeUtil(data, subTreePtr->right);
		}

	}
}

// in-order traversal: Left-Parent-Right
// we use a recursive utility function
void BSTree::printInOrder() {

	printInOrderUtil(root);
	cout << endl;

}

// utility function to traverse a tree recursively
// in-order traversal:
// 1) explore left side - 2) print parent node - 3) expolre right side
void BSTree::printInOrderUtil(node* subTreePtr) {

	if (root == nullptr) {
		cout << "The TREE is Empty ..." << endl;
	}
	else {
		// 1) explore left side
		if (subTreePtr->left != nullptr) {
			printInOrderUtil(subTreePtr->left);
		}

		// 2) print node
		cout << subTreePtr->data << " ";

		// 3) expolre right side
		if (subTreePtr->right != nullptr) {
			printInOrderUtil(subTreePtr->right);
		}
	}

}


// Search for a key in a binary search tree
bool BSTree::findKey(const int key) {

	// use the recursive utility function
	return findKeyUtil(key, root);
}

// Utility function to find a key
bool BSTree::findKeyUtil(const int key, node* subTreePtr) {

	// check if the tree is empty.
	if (root == nullptr) {
		cout << "Key (" << key << ") is NOT found, it is an empty tree ..." << endl;
		return false;
	}

	// base case 1: no subtree, this case applies when you check left and
	// right subtrees of a leaf node. There are no subtrees, right!!
	if (subTreePtr == nullptr) {
		cout << "Key (" << key << ") is NOT found" << endl;
		return false;
	}
	// base case 2: we found the key
	else if (subTreePtr->data == key) {
		cout << "Key (" << key << ") is FOUND" << endl;
		return true;
	}
	// key is less than the data in this node, search in the left subtree
	else if (key < subTreePtr->data) {
		return findKeyUtil(key, subTreePtr->left);
	}
	// key is larger than the data in this node, search in the right subtree
	else { //if(key > subTreePtr->data)
		return findKeyUtil(key, subTreePtr->right);
	}
}

/*void BSTree::storeTree(vector<node*> &nodes, node* treeRoot)
{
	if (treeRoot == nullptr)
		return;
	// store node in order in an array
	storeTree(nodes, treeRoot->left);
	nodes.push_back(treeRoot);
	storeTree(nodes, treeRoot->right);
}*/

void BSTree::getBalancedCopy(BSTree tree)
{
	// store the nodes of a given tree in order
	int nodes[13] = { 5, 10, 20, 25, 30, 35, 45, 55, 60, 65, 70, 80, 90 };

	int n = 13;
	tree.root = getBalancedCopyUtil(nodes, 0, n - 1);
}

BSTree::node* BSTree::getBalancedCopyUtil(int nodes[], int start, int end)
{
	// make the middle element the root
	int mid = (start + end) / 2;
	node* newRoot = new node();
	newRoot->data = nodes[mid];
	while (start <= end)
	{
		// construct the new tree
		newRoot->left = getBalancedCopyUtil(nodes, start, mid - 1);
		newRoot->right = getBalancedCopyUtil(nodes, mid + 1, end);
	}

	return newRoot;
}


int main() {

	// numbers are stored in an array for simplicity
	const int arraySize = 13;
	int testData[arraySize] = { 5, 10, 20, 25, 30, 35, 45, 55, 60, 65, 70, 80, 90 };


	// create a BST object, myTree
	BSTree myTree;

	// print empty tree and report its height
	myTree.printInOrder();

	// insert the numbers to myTree one-by-one
	for (int i = 0; i < arraySize; i++) {
		myTree.insertNode(testData[i]);
	}

	// print the tree using in-order traversal
	myTree.printInOrder();

	BSTree myTree2;

	myTree2 = myTree;

	myTree.getBalancedCopy(myTree2);

	myTree2.printInOrder();

	// create a display function that prints some information about tree structure
	// you need to show that your getBalancedCopy function works. 

	// wait for keypress to close because Visual Studio likes to close my windows
	do
	{
		cout << '\n' << "Press a key to continue...";
	} while (cin.get() != '\n');

	return 0;
}
