/*------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	Templatized Binary Search Tree. Class has fucntionality to read from a file and build a
	binary search tree. All responsibility on handling file stream data is on the objects
	that will be inserted into the binary search tree. Class uses recursion to insert,
	delete, and find objects in the tree.

------------------------------------------------------------------------------------------------*/

#ifndef binarysearchtree_h
#define binarysearchtree_h


#include <string>
#include <iostream>

using namespace std;

template<class Object>

class BinarySearchTree {

	private:

	struct Node{

		Object* data;	//pointer to data
		Node* left;		//pointer to left subtree
		Node* right;	//pointer to right subtree

		//two constructors
		Node() : data(NULL), left(NULL), right(NULL) {};
		Node(Object* d, Node* l, Node* r) : data(d), left(l), right(r) {}
	};

	public:

	BinarySearchTree(void);		//default no-args constructo
	~BinarySearchTree(void);	//destructor

	bool insert(Object* toInsert);		//inserts an object
	bool retrieve(const Object& target, Object*& retrieved) const;	//retrieves an object
	void display(void) const;		//displays all nodes
	void clear(void);				//deletes all nodes
	bool isEmpty(void) const;		//returns bool if tree is empty
	void buildTree(ifstream& inFile);	//builds tree

	private:
	
	Node* root;	//root Node of tree

	Node* recInsert(Node* current, Object* toInsert);	//helper function ro recursively insert
	void recClear(Node* current);						//helper function ro recursively delete Nodes
	void toString(Node* current) const;					//helper function ro recursively print information
	bool recRetrieve(Node* current, const Object& target, Object*& retrieved) const;	//helper function ro recursively retrieve a Node
};

#endif // !binarysearchtree_h

/*------------------------------------------------------------------------------------------------

	Method calls toString to recursively move over each Node in the BST printing
	each Node's information. Method cannot change any data members.

------------------------------------------------------------------------------------------------*/


template <typename Object>
void BinarySearchTree<Object>::display(void) const {
	if (root == NULL) {	//checks if the tree is empty
		return;
	}
	toString(root);	//calls toString
};

/*------------------------------------------------------------------------------------------------

	Method recursively moves over each Node in the BST printing each Node's information.
	Method cannot change any data members.

	POSTCONDITIONS:
		- must be called by display

------------------------------------------------------------------------------------------------*/

template <typename Object>
void BinarySearchTree<Object>::toString(Node* current) const {
	if (current == NULL) {	//checks if we have reached an empty leaf
		return;
	} else {
		toString(current->left);	//prints all information if left subtrees
		current->data->toString();	//prints current subtree
		toString(current->right);	//prints all information in right subtrees
	}
};

/*------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates BinarySearchTree object
		- initializes root to NULL

------------------------------------------------------------------------------------------------*/


template <typename Object>
BinarySearchTree<Object>::BinarySearchTree(void) {
	root = NULL;	//initiates root to NULL
};

/*------------------------------------------------------------------------------------------------

	Takes in an Object* and calls retrieve to ensure that the Object is not already inserted
	in the binary search tree. If this is false recInsert is called to create a new node and
	insert the Object in to the tree.

	PRECONDITIONS:
		- toInsert cannot be NULL
		- toInsert cannot already be in the binary search tree

	POSTCONDITIONS:
		- adds new Node containing toInsert to the BST
		- returns a bool value indicating success

	NOTES:	It is the responsibility of the Object to provide functionality for comparing
			equality.

------------------------------------------------------------------------------------------------*/

template <typename Object>
bool BinarySearchTree<Object>::insert(Object* toInsert) {
	Object* temp;				//temp objects to use for retrieve
	Object temp2 = *toInsert;

	if (toInsert == NULL) {	//checks if toInsert is NULL
		return false;
	} 

	if (retrieve(temp2, temp)) {	//attempts to retrieve a node eqaul to toInsert
		return false;				//if this is false, returns false
	}
	
	root = recInsert(root, toInsert);	//calls recInsert to insert a new node in the tree
	return true;
};

/*------------------------------------------------------------------------------------------------

	Takes in an Object* and recursively traverses the tree comparing the Object with the current
	node until the appropriate spot for insertion is reached. Creates a new node and
	inserts the Object in to the tree.

	PRECONDITIONS:
		- must be called by insert()

	POSTCONDITIONS:
		- adds new Node containing toInsert to the BST

	NOTES:	It is the responsibility of the Object to provide functionality for comparing
			equality.

------------------------------------------------------------------------------------------------*/

template <typename Object>
typename BinarySearchTree<Object>::Node* BinarySearchTree<Object>::recInsert(Node* current, Object* toInsert) {
	if (current == NULL) {	//chceks if we have reached the bottom of the tree
		current = new Node(toInsert, NULL, NULL);	//creates a new node
	} else if (*current->data > *toInsert) {	//checks if toInsert is greater than current
		current->left = recInsert(current->left, toInsert);	//if so goes to the left
	} else {	//otherwise recursively travles to the right
		current->right = recInsert(current->right, toInsert);
	} 
	return current;	//returns current
};

/*------------------------------------------------------------------------------------------------

	Returns a bool value indicating if the binary search tree is empty (root == NULL).
	Cannot change any data members.

	POSTCONDITIONS:
		- returns a bool value indicating if root == NULL

------------------------------------------------------------------------------------------------*/

template <typename Object>
bool BinarySearchTree<Object>::isEmpty(void) const {
	return root == NULL;
};

/*------------------------------------------------------------------------------------------------

	Calls recClear to recusively delete each node in the binary search tree and dealloacate
	any dynamically allocated memory.

	POSTCONDITIONS:
		- deallocates all dynamically allocated memory and deletes all nodes in the tree
		- sets root to NULL

	NOTES:	It is the responsibility of the Object's destructors to know how to deallocate any
			memory dynamically allocated by the Object in the Node.

------------------------------------------------------------------------------------------------*/

template <typename Object>
void BinarySearchTree<Object>::clear(void) {
	if (isEmpty()) {	//checks if the list is already empty
		return;			//returns
	}
	recClear(root);		//calls recClear
	root = NULL;		//sets root to NULL
};

/*------------------------------------------------------------------------------------------------

	Recusively traveses the BST deleting each node in the binary search tree and dealloacating
	any dynamically allocated memory.

	POSTCONDITIONS:
		- deallocates all dynamically allocated memory and deletes all nodes in the tree
	
	NOTES:	It is the responsibility of the Object's destructors to know how to deallocate any
			memory dynamically allocated by the Object in the Node.

------------------------------------------------------------------------------------------------*/

template <typename Object>
void BinarySearchTree<Object>::recClear(Node* current) {
	if (current != NULL) {	//base case
		recClear(current->right);	//recursively travels to the right
		recClear(current->left);	//recursively travels the left subtree
		delete current;				//deletes current
	}
};

/*------------------------------------------------------------------------------------------------

	Calls recRetrieve to recusively traverse nodes in the tree and compare them to the
	first parameter. The second parameter is set equal to the node that contains the target
	object, or NULL if it cannot be found.

	POSTCONDITIONS:
		- recursively searches tree for Node containing object equal to first parameter
		- second parameter is set equal to found object or NULL
		- returns bool indicating if Object was found

	NOTES:	It is the responsibility of the Object to know how to compare for equality

------------------------------------------------------------------------------------------------*/

template <typename Object>
bool BinarySearchTree<Object>::retrieve(const Object& target, Object*& retrieved) const {
	return recRetrieve(root, target, retrieved);	//calls recRetrieve
};

/*------------------------------------------------------------------------------------------------

	Calls recRetrieve to recusively traverse nodes in the tree and compare them to the
	first parameter. The second parameter is set equal to the node that contains the target
	object, or NULL if it cannot be found.

	POSTCONDITIONS:
		- recursively searches tree for Node containing object equal to first parameter
		- second parameter is set equal to found object or NULL
		- returns bool indicating if Object was found

	NOTES:	It is the responsibility of the Object to know how to compare for equality

------------------------------------------------------------------------------------------------*/

template <typename Object>
bool BinarySearchTree<Object>::recRetrieve(Node* current, const Object& target, Object*& retrieved) const {
	bool successful = false;
	if ( current == NULL) {	//checks if we have reached the bottom of the tree
		return false;		//returns false
	}

	if (target == *current->data) {	//checks if current is equal to target
		retrieved = current->data;	//sets second parameter equal to current
		successful = true;				//returns true
	} else if (*current->data < target) {	//if current is less than target search the right
		recRetrieve(current->right, target, retrieved);
	} else {	//otherwise search to the left
		recRetrieve(current->left, target, retrieved);
	}
	return successful;	//returns whether we found the Obejct in the tree
};

/*------------------------------------------------------------------------------------------------

	This method takes in a file stream and hands the file stream to Objects. Obejcts have
	the responsibility to properly handle the file stream to populate data members. Objects
	members are then added to the Binary Search Tree via the insert function.

	PRECONDITIONS:
		- file stream must contain data formatted for Object

	POSTCONDITIONS:
		- builds Binary Search Tree of Objects

------------------------------------------------------------------------------------------------*/

template <typename Object>
void BinarySearchTree<Object>::buildTree(ifstream& infile) {
	Object* ptr;	//creates new Object*
	bool isValid;	//bool indicating if the data was valid for the Object

	//loops until the end of file is reached, creating new objects
	//setting data and attempting to insert them in to the BST
	for (;;) {
		ptr = new Object;
		isValid = ptr->setData(infile);	//hands filestream to Object to populate it

		if (infile.eof()) {	//breaks out of loop if the end of file is reached
			delete ptr;
			break;
		}

		if (isValid) {		//if Object was populated with data
			insert(ptr);	//insert into the Binary Search Tree
		} else {
			delete ptr;		//otherwise delete the Object
		}
	}
}


/*------------------------------------------------------------------------------------------------

	Destructor. Calls clear to deallocate all dynamically allocated memory.

	POSTCONDITIONS:
		- deallocates all dynamically allocated memory and deletes all nodes in the tree
		- sets root to NULL

	NOTES:	It is the responsibility of the Object's destructors to know how to deallocate any
			memory dynamically allocated by the Object in the Node.

------------------------------------------------------------------------------------------------*/

template <typename Object>
BinarySearchTree<Object>::~BinarySearchTree() {
	clear();	//calls clear
};

