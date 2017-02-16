/*------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	Templatized myQueue class functions like the STL queue but has the extended
	functionality of taking in a file stream and using it to build the queue. This class
	hands the file stream off to the objects that it holds. It is the responsibility of the
	objects in the myQueue to properly handle file stream data. myQueue adds new Nodes
	to the end of the myQueue. Each Node contains an Object* and a Node*. Nodes are popped
	from the front of the myQueue.

------------------------------------------------------------------------------------------------*/


#pragma once
#ifndef myQueue_h
#define myQueue_h

#include <exception>
#include <stdexcept>

using namespace std;

template<typename Object>
class myQueue {

	private:

	struct Node {				//Node struct
		Object data;          	//Object data
		Node* next;				//Node* to next Node in the myQueue

		Node(void) : data(NULL), next(NULL) {};			//default no-args constructor
		Node(Object d, Node* n) : data(d), next(n) {};	//constructor take Object* and Node*
	};

	Node* head;					//Node* to head of the myQueue

	public:

	myQueue(void);						//default no-args constructor
	~myQueue(void);						//destructor
	myQueue(const myQueue& toCopy);
	Object pop(void);						//pops first element in myQueue
	bool push(Object toAdd);				//pushes new Object to end of myQueue
	bool isEmpty(void) const;				//checks if head == NULL
	void makeEmpty(void);					//deletes all Nodes in myQueue
	void toString(void) const;				//prints contents of each Node
	void buildQueue(ifstream& inFile);			//builds myQueue
	void operator=(const myQueue& toCopy);		//makes a deep copy of a myQueue
	bool operator==(const myQueue& toCompare) const;	//compares two myQueue's
};

#endif


/*------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates myQueue object
		- initializes head to NULL

------------------------------------------------------------------------------------------------*/

template<typename Object>
myQueue<Object>::myQueue(void) {
	head = NULL;	//initializes head to NULL
};

/*------------------------------------------------------------------------------------------------

	Destructor. Deletes all dynamically allocated memory

	POSTCONDITIONS:
		- calls makeEmpty to delete all Nodes
		- deletes all Nodes in the list

------------------------------------------------------------------------------------------------*/

template<typename Object>
myQueue<Object>::~myQueue(void) {
	makeEmpty();	//deletes all nodes in the list and sets head == NULL
};

/*------------------------------------------------------------------------------------------------

	Makes a deep copy of a myQueue by calling the overloaded assignment operator.

------------------------------------------------------------------------------------------------*/

template<typename Object>
myQueue<Object>::myQueue(const myQueue& toCopy) {
	*this = toCopy;
};

/*------------------------------------------------------------------------------------------------

	Takes in an Object* and creates a new Node at the end of the myQueue containing the
	Object*.

	PRECONDITIONS:
		- toAdd cannot be NULL

	POSTCONDITIONS:
		- adds new Node containing toAdd to the end of the myQueue

------------------------------------------------------------------------------------------------*/

template<typename Object>
bool myQueue<Object>::push(Object toAdd) {
	if (head == NULL) {					//checks if head is NULL
		head = new Node(toAdd, NULL);	//initializes head to new Node
	} else {							//otherwise adds new node to the end of the queue
		Node* current = head;			//Node to traverse the list

		while (current->next != NULL) {	//traverses the list until it reaches the end
			current = current->next;	//increments current to the next Node
		}
		current->next = new Node(toAdd, NULL);	//adds Node to the end of the list
	}
	return true;
};

/*------------------------------------------------------------------------------------------------

	Method returns a Node* to the first element in the MyQueue. Redirects head to head->next.
	Will throw a runtime error if the myQueue is empty.

	PRECONDITIONS:
	- myQueue cannot be empty

	POSTCONDITIONS:
	- returns Node* equal to the first element in the myQueue
	- redirects head to head->next

	NOTES:	Method will print an error message to the console if the myQueue is empty

------------------------------------------------------------------------------------------------*/

template<typename Object>
Object myQueue<Object>::pop(void) {
	if (head == NULL) {							//checks if the myQueue is empty
		cout << "Empty myQueue!" << endl;		//prints an error message to the console
		return NULL;							//returns NULL
	}
	Node* retNode = head;		//Node to be returned
	head = head->next;			//sets head to the next item in the list				
	return retNode->data;		//returns the data object from the popped Node
};

/*------------------------------------------------------------------------------------------------

	Method deletes all Nodes in the myQueue

	PRECONDITIONS:
		- myQuquq cannot be empty

	POSTCONDITIONS:
		- deletes all Nodes
		- sets head = NULL

------------------------------------------------------------------------------------------------*/

template<typename Object>
void myQueue<Object>::makeEmpty(void) {
	//Node* toDelete;				//Node to traverse the myQueue

	while (!isEmpty()) {		//checks if the list is empty
		pop();
	}
	head = NULL;				//sets head to NULL
};

/*------------------------------------------------------------------------------------------------

	Prints the data in each Node to the console. Cannot change any data members.

------------------------------------------------------------------------------------------------*/

template<typename Object>
void myQueue<Object>::toString(void) const {
	if (head == NULL) {
		return;
	}
	Node* current = head;
	while (current != NULL) {
		cout << current->data << endl;
		current = current->next;
	}
};

/*------------------------------------------------------------------------------------------------

	Returns a bool value indicating if the list has no elements (head == NULL). Method
	cannot change any data members.

	POSTCONDITIONS:
		- returns head == NULL

------------------------------------------------------------------------------------------------*/


template<typename Object>
bool myQueue<Object>::isEmpty(void) const {
	return head == NULL;	//returns if head is equal to NULL
};


/*------------------------------------------------------------------------------------------------

	This method takes in a file stream and hands the file stream to Objects. Obejcts have
	the responsibility to properly handle the file stream to populate data members. Objects
	members are then added to the myQueue via the push function.

	PRECONDITIONS:
		- file stream must contain data formatted for Object

	POSTCONDITIONS:
		- builds myQueue of Objects

------------------------------------------------------------------------------------------------*/

template<typename Object>
void myQueue<Object>::buildQueue(ifstream& inFile) {
	Object* ptr;	//creates object*
	bool successfulRead;	//bool to hold if setData was successful
	bool success;		//bool to hold of insert was successful

	//loops until the end of file is reached, creating new objects
	//setting data and attempting to insert them in to the myQueue
	for (;;) {
		ptr = new Object;
		successfulRead = ptr->setData(inFile);
		if (inFile.eof()) {
			delete ptr;
			break;
		}

		if (successfulRead) {
			success = push(ptr);
		} else {
			delete ptr;
		}
		if (!success) break;
	}
};

/*------------------------------------------------------------------------------------------------

	Makes a deep copy of a myQueue by creating a deep copy of each of the contents
	of the Nodes.

	PRECONDITIONS:
		- toCopy cannot be NULL
		- toCopy cannot be equal to calling object

	POSTCONDITIONS:
		- makes a deep copy of a myQueue

------------------------------------------------------------------------------------------------*/

template<typename Object>
void myQueue<Object>::operator=(const myQueue & toCopy) {
	if (*this == toCopy) {	//checks for equality
		return;				//returns if equal
	}

	makeEmpty();	//deletes any memory allocated to this

	Node* current = toCopy.head;	//Node* to walk to copy

	while (current != NULL) {	//creates a deep copy of the node
		this->push(current->data);	//and pushes it to new list
		current = current->next;
	}
};

/*------------------------------------------------------------------------------------------------

	Compares two myQueue objects for equality.

	POSTCONDITIONS:
	- returns a bool indicating equality

------------------------------------------------------------------------------------------------*/

template<typename Object>
bool myQueue<Object>::operator==(const myQueue & toCompare) const {
	if (isEmpty() && toCompare.isEmpty()) {	//returns true if both are empty
		return true;
	} else if (isEmpty() && !toCompare.isEmpty()) {
		return false;
	} else if (!isEmpty() && toCompare.isEmpty()) {
		return false;
	}

	Node* listOne = head;
	Node* listTwo = toCompare.head;

	//walks the list, returns false at first node
	//that is not equal
	while (listOne != NULL) {
		if (listOne != listTwo) {
			return false;
		}
		listOne = listOne->next;
		listTwo = listTwo->next;

	}

};