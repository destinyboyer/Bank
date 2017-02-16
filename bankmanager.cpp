/*------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	The BankManager class is a high level class that manages the interactions between
	Binary Search Tree of Clients and a queue of Transactions. This class will also log
	the Transactions that have been completed so that they can be undone if necessary.
	Note that this class manages interactions, and relies on the BinarySearchTree, Client,
	and Transaction classes to throw any errors pertaining to the suitability of data.

------------------------------------------------------------------------------------------------*/

#include "BankManager.h"

/*------------------------------------------------------------------------------------------------

	Default no-args contructor. Instantiates BankManager object

------------------------------------------------------------------------------------------------*/

BankManager::BankManager(void) {

};

/*------------------------------------------------------------------------------------------------

	Destructor. Clears the clients BST, and empties both of the queues to deallocate any
	dynamically allocated memory.

------------------------------------------------------------------------------------------------*/

BankManager::~BankManager(void) {
	clients.clear();		//deletes all nodes in the clients BST
	completed.makeEmpty();	//deletes all nodes in the completed queue
	pending.makeEmpty();	//deletes all nodes in the pending queue
};

/*------------------------------------------------------------------------------------------------

	Method takes in a file stream and passes it off to the clients BST by calling
	buildTree on clients. The clients BST has full responsibility to knowing how to properly
	handle the filestream to populate and build nodes.

------------------------------------------------------------------------------------------------*/

void BankManager::readClients(ifstream& inFile) {
	clients.buildTree(inFile);	//calls buildTree
};

/*------------------------------------------------------------------------------------------------

	Method takes in a file stream and passes it to pending BankQueue by calling
	buildQueue on pending. The BankQueue class has full responsibility to knowing how to properly
	handle the filestream to populate and build nodes.

------------------------------------------------------------------------------------------------*/

void BankManager::readTransactions(ifstream& inFile) {
	pending.buildQueue(inFile);	//calls buildQueue
};

/*------------------------------------------------------------------------------------------------

	This function completes all Transactions in the transaction queue. The function pops a
	transaction off of the transaction queue, finds the appropriate clients, and passes
	the information to the clients to carry out the transaction. The transaction is then moved
	to the Transaction stack to log that it has been completed and allow for transactions
	to be undone.

	Flow of Program:
		- transact(void) pops a Transaction object off of pending
		- program searches clients by account number via the retrieve method call on clients
		- program has both Client objects perform the appropriate transaction
		- data is handed to both Clients for them to log necessary transaction data
		- Transaction is moved to the completed

	NOTE:
		- this class is not responsible for handling errors pertaining to Transactions

------------------------------------------------------------------------------------------------*/

void BankManager::transact(void) {

	while (!pending.isEmpty()) {	//while there are still transactions to be completed

		Transaction* toTransact;	//holds one transaction object
		toTransact = pending.pop();	//pops a transaction off the pending queue

		bool canMove = false;		//bool variable to indicate if there are sufficient funds to move
		int amount = toTransact->getAmount();	//gets amount to be transacted

		Client clientOne;	//dummy client to use to search BST
		Client clientTwo;	//dummy client to use to search BST

		Client* firstClient;	//will point to found client
		Client* secondClient;	//will point to found client

		clientOne.setClientID(toTransact->getFirstClientID());	//gets the first Client
		
		//checks to see if there is a second Client involved in the transaction
		//if so uses retrieve to fetch the second Client
		if (toTransact->getSecondClientID() == 0) {
			clients.retrieve(clientOne, firstClient);
			secondClient = NULL;
		} else {
			clientTwo.setClientID(toTransact->getSecondClientID());
			clients.retrieve(clientOne, firstClient);
			clients.retrieve(clientTwo, secondClient);
		}

		//series of if statements comparing the transaction type to the
		//known transactions. Uses member functions in the Client class
		//to carry out all types of transactions and to move money
		//between accounts
		if (toTransact->getTransactionType() == 'D') {
			firstClient->deposit(toTransact->getFirstClientAccount(), amount);
			secondClient = NULL;
		} else if (toTransact->getTransactionType() == 'W') {
			firstClient->withdraw(toTransact->getFirstClientAccount(), amount);
			secondClient = NULL;
		} else if (toTransact->getTransactionType() == 'M') {
			canMove = firstClient->withdraw(toTransact->getFirstClientAccount(), amount);
			if (canMove) {
				secondClient->deposit(toTransact->getSecondClientAccount(), amount);
			}
		} else if (toTransact->getTransactionType() == 'H') {
			firstClient->displayClientHistory();
			secondClient = NULL;
		}
		//pushes the completed transaction on to the completed BankQueue
		completed.push(toTransact);
	}
};

/*------------------------------------------------------------------------------------------------

	Method prints information on all Clients stored in the clients BST by calling 
	display on the clients BST. Method cannot change any data members.

------------------------------------------------------------------------------------------------*/

void BankManager::displayClients(void) const {
	clients.display();
};

/*------------------------------------------------------------------------------------------------

	Method prints all transactions that have been completed thus far by calling toString
	on the completed BankQueue. Method cannot make changes to any data members.

------------------------------------------------------------------------------------------------*/

void BankManager::displayTransactions(void) const {
	completed.toString();
};