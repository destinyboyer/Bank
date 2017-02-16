/*------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	Templatized BankQueue class functions like the STL queue but has the extended
	functionality of taking in a file stream and using it to build the queue. This class
	hands the file stream off to the objects that it holds. It is the responsibility of the
	objects in the BankQueue to properly handle file stream data. BankQueue adds new Nodes
	to the end of the BankQueue. Each Node contains an Object* and a Node*. Nodes are popped
	from the front of the BankQueue.

------------------------------------------------------------------------------------------------*/


#pragma once
#ifndef bankqueue_h
#define bankqueue_h

using namespace std;

template<typename Object>
class BankQueue {

	private:

	struct Node {				//Node struct
		Object* data;          	//Object* to the data in the Node
		Node* next;				//Node* to next Node in the BankQueue

		Node(void) : data(NULL), next(NULL) {};			//default no-args constructor
		Node(Object* d, Node* n) : data(d), next(n) {};	//constructor take Object* and Node*
	};

	Node* head;					//Node* to head of the BankQueue

	public:

	BankQueue(void);						//default no-args constructor
	~BankQueue(void);						//destructor
	Object* pop(void);						//pops first element in BankQueue
	bool push(Object* toAdd);				//pushes new Object to end of BankQueue
	bool isEmpty(void) const;				//checks if head == NULL
	void makeEmpty(void);					//deletes all Nodes in BankQueue
	void toString(void) const;
	void buildQueue(ifstream& inFile);		//builds BankQueue
};

#endif // !bankqueue_h

/*------------------------------------------------------------------------------------------------

	Method iterates over the BankQueue calling getDescription on each data object and
	prints this information to the console.

------------------------------------------------------------------------------------------------*/

template<typename Object>
void BankQueue<Object>::toString(void) const {
	if (head == NULL) {
		return;
	}
	Node* current = head;
	while (current != NULL) {
		cout << current->data->getDescription() << endl;
		current = current->next;
	}
};

/*------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates BankQueue object
		- initializes head to NULL

------------------------------------------------------------------------------------------------*/

template<typename Object>
BankQueue<Object>::BankQueue(void) {
	head = NULL;	//initializes head to NULL
};

/*------------------------------------------------------------------------------------------------

	Destructor

	POSTCONDITIONS:
		- calls makeEmpty to delete all Nodes
		- deletes all Nodes in the list

------------------------------------------------------------------------------------------------*/

template<typename Object>
BankQueue<Object>::~BankQueue(void) {
	makeEmpty();	//deletes all nodes in the list and sets head == NULL
};

/*------------------------------------------------------------------------------------------------

	Takes in an Object* and creates a new Node at the end of the BankQueue containing the
	Object*.

	PRECONDITIONS:
		- toAdd cannot be NULL

	POSTCONDITIONS:
		- adds new Node containing toAdd to the end of the BankQueue

------------------------------------------------------------------------------------------------*/

template<typename Object>
bool BankQueue<Object>::push(Object* toAdd) {
	if (toAdd == NULL) {	//checks if the object toAdd is NULL
		cout << "Cannot have Null Transaction type!" << endl;	//prints error message to console
		return false;
	} else {
		if (head == NULL) {					//checks if head is NULL
			head = new Node(toAdd, NULL);	//initializes head to new Node
		} else {							//otherwise adds new node to the end of the queue
			Node* current = head;			//Node to traverse the list

			while (current->next != NULL) {	//traverses the list until it reaches the end
				current = current->next;	//increments current to the next Node
			}
			current->next = new Node(toAdd, NULL);	//adds Node to the end of the list
		}
	}
	return true;
};

/*------------------------------------------------------------------------------------------------

	Method returns a Node* to the first element in the BankQueue. Redirects head to head->next.
	Will throw a runtime error if the BankQueue is empty.

	PRECONDITIONS:
		- BankQueue cannot be empty

	POSTCONDITIONS:
		- returns Node* equal to the first element in the BankQueue
		- redirects head to head->next

	NOTES:	Method will print an error message to the console if the BankQueue is empty

------------------------------------------------------------------------------------------------*/

template<typename Object>
Object* BankQueue<Object>::pop(void) {
	if (head == NULL) {							//checks if the BankQueue is empty
		cout << "Empty BankQueue!" << endl;		//prints an error message to the console
		return NULL;							//returns NULL
	}
	Object* temp = head->data;
	Node* retNode = head;		//Node to be returned
	head = head->next;			//sets head to the next item in the list	
	delete retNode;
	return temp;		//returns the data object from the popped Node
};

/*------------------------------------------------------------------------------------------------

	Method deletes all Nodes in the BankQueue

	PRECONDITIONS:
		- BankQueue cannot be empty

	POSTCONDITIONS:
		- deletes all Nodes
		- sets head = NULL

------------------------------------------------------------------------------------------------*/

template<typename Object>
void BankQueue<Object>::makeEmpty(void) {
	Node* toDelete;				//Node to traverse the BankQueue

	while (head != NULL) {		//checks if the list is empty
		toDelete = head;		//if the list is not empty, sets toDelete to head
		head = head->next;	//increments head to the next Node in the list
		delete toDelete;		//deletes toDelete
	}
	head = NULL;				//sets head to NULL
};

/*------------------------------------------------------------------------------------------------

	Returns a bool value indicating if the list has no elements (head == NULL). MEthod
	cannot change any data members.

	POSTCONDITIONS:
		- returns head == NULL

------------------------------------------------------------------------------------------------*/

template<typename Object>
bool BankQueue<Object>::isEmpty(void) const {
	return head == NULL;	//returns if head is equal to NULL
};


/*------------------------------------------------------------------------------------------------

	This method takes in a file stream and hands the file stream to Objects. Obejcts have
	the responsibility to properly handle the file stream to populate data members. Objects
	members are then added to the BankQueue via the push function.

	PRECONDITIONS:
		- file stream must contain data formatted for Object

	POSTCONDITIONS:
		- builds BankQueue of Objects

------------------------------------------------------------------------------------------------*/

template<typename Object>
void BankQueue<Object>::buildQueue(ifstream& inFile) {
	Object* ptr;		//creates new Object*
	bool successfulRead;	//bool to hold if setData was successful
	bool success;		//bool to hold of insert was successful                                 
	
	//loops until the end of file is reached, creating new objects
	//setting data and attempting to insert them in to the myQueue
	for (;;) {
		ptr = new Object;
		successfulRead = ptr->setData(inFile);
		
		if (inFile.eof()) {	//breaks out of loop if the end of file is reached
			delete ptr;
			break;
		}

		if (successfulRead) {		//if Object was populated with data
			success = push(ptr);	//push to BankQueue
		} else {
			delete ptr;				//otherwise delete the Object
		}
		if (!success) {
			break;
		}
	}
};
