
/*-------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016		
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash
	
	The Transaction class is a data based class. Transaction objects can be created, and then
	the object's data members can be set via a file stream. It is assumed that the file stream
	contains data correctly formatted for use with a Transaction object. The setData function
	that takes in a file stream then uses setters to check the validity of the data. If the
	data is not valid then a runtime error will be thrown and setData will return false.

	PRECONDITIONS:
		- data used to set Transaction is properly formatted for use with this class

-------------------------------------------------------------------------------------------------*/

#ifndef transaction_h
#define transaction_h

#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Transaction {

	private:

	string description;				//string description equal to the line read from file
	int amount;						//amount to be transacted
	int firstClientID;				//firstClients accountID
	int firstClientAccountIndex;
	int secondClientID;				//secondClients ID number
	int secondClientAccountIndex;
	char transactionType;			//char identifying the type of transaction to be performed

	/*------------------------------------------------------------------------------------------------
	
		Setter method for the description. Method should only be called after setData(). Method
		uses a stringstream to produce a easily readable description of the transaction, including
		the transaction type, the amount of money moved, and the accounts involved.
		
		PRECONDITIONS:
			- setData() must be called first

		POSTCONDITIONS:
			- sets description to an easily readable description of the transaction

	------------------------------------------------------------------------------------------------*/

	void setDescription(void); 

	/*------------------------------------------------------------------------------------------------

		Setter method for the amount. Returns true if the input is valid.

		PRECONDITIONS:
			- amount must be greater than 0

		POSTCONDITIONS:
			- sets the amount equal to the input

		NOTES:	This method will print an error message if the input is not valid

	------------------------------------------------------------------------------------------------*/

	bool setAmount(const int input);

	/*------------------------------------------------------------------------------------------------

		Setter for firstClientID. Returns true if the input is valid

		PRECONDITIONS:
			- account number must be 5 digits long

		POSTCONDITIONS:
			- sets the firstClientID equal to the input
			- returns bool if the input was valid

		NOTES:	This method will print an error message if the input is not valid.

	------------------------------------------------------------------------------------------------*/

	
	bool setFirstClient(const int input);

	/*------------------------------------------------------------------------------------------------

		Setter for secondClientID. Returns true if the input is valid.

		PRECONDITIONS:
			- account number must be 5 digits long

		POSTCONDITIONS:
			- sets the secondClientID equal to input
			- returns bool if the input was valid
		
		NOTES:	This method will print an error message if input is not valid

	------------------------------------------------------------------------------------------------*/

	bool setSecondClient(const int input);
	
	public:

	/*------------------------------------------------------------------------------------------------

		Getter method for the firstClientAccount. Cannot change any data members.

		PRECONDITIONS:
			- setData() must have been called first

		POSTCONDITIONS:
			- returns the firstClientAccount

	------------------------------------------------------------------------------------------------*/

	int getFirstClientAccount(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the secondClientAccount. Cannot change any data members.

		PRECONDITIONS:
			- setData() must have been called first

		POSTCONDITIONS:
			- returns the secondClientAccount

	------------------------------------------------------------------------------------------------*/

	int getSecondClientAccount(void) const;


	/*------------------------------------------------------------------------------------------------

		Default no-args constructor.

		POSTCONDITIONS:
			- instantiates new Transaction object
			- sets firstClientID and secondClientID to 0

		NOTES: firstClientID and secondClientID are initialized to 0. This is done because some
			   objects of this class only involve one client. This case can be checked by comparing
			   the secondClientID == 0

	------------------------------------------------------------------------------------------------*/

	Transaction(void);

	/*------------------------------------------------------------------------------------------------

		Destructor

		NOTES:	Object of this class do not use any dyanmic memory. As such, the default destructor
				is suitable.

	------------------------------------------------------------------------------------------------*/
	
	~Transaction(void);

	/*------------------------------------------------------------------------------------------------

		This method takes in a file stream and uses the setter methods as helper functions
		to populate the data members for an instantiated Transaction object.

		PRECONDITIONS:
			- file stream must contain data formatted for Transaction objects

		POSTCONDITIONS:
			- populates the data members of the Transaction calling object

		NOTES:	Will print an error message if the data is incorrectly formatted. If data is
				incorrectly formatted this will be handled by going to the next line of the
				istream, ignoring all data on the incorrectly formatted line.

	------------------------------------------------------------------------------------------------*/

	bool setData(istream&);

	/*------------------------------------------------------------------------------------------------

		Getter method for the description. Cannot change any data members.

		POSTCONDITIONS:
			- returns the description

	------------------------------------------------------------------------------------------------*/

	string getDescription(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the amount. Cannot change any data members.

		POSTCONDITIONS:
			- returns the amount

	------------------------------------------------------------------------------------------------*/

	int getAmount(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the firstClientID.  Cannot change any data members.

		POSTCONDITIONS:
			- returns the firstClientID

	------------------------------------------------------------------------------------------------*/

	int getFirstClientID(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the secondClientID.  Cannot change any data members.

		POSTCONDITIONS:
			- returns the secondClientID

	------------------------------------------------------------------------------------------------*/

	int getSecondClientID(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the transaction type. Cannot change any data members.

		POSTCONDITIONS:
			- returns the transactionType

	------------------------------------------------------------------------------------------------*/

	char getTransactionType(void) const;

};
#endif