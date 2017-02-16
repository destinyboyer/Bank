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

#include "transaction.h"

/*------------------------------------------------------------------------------------------------

	Getter method for the firstClientAccount. Cannot change any data members.

	PRECONDITIONS:
		- setData() must have been called first or it will return 0.

	POSTCONDITIONS:
		- returns the firstClientAccount

------------------------------------------------------------------------------------------------*/

int Transaction::getFirstClientAccount(void) const {
	return firstClientAccountIndex;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the firstClientAccount. Cannot change any data members.

	PRECONDITIONS:
		- setData() must have been called first or it will return 0.

	POSTCONDITIONS:
		- returns the secondClientAccount

------------------------------------------------------------------------------------------------*/


int Transaction::getSecondClientAccount(void) const {
	return secondClientAccountIndex;
};

/*------------------------------------------------------------------------------------------------

	Setter method for the description. Method should only be called after setData(). Method
	uses a stringstream to produce a easily readable description of the transaction, including
	the transaction type, the amount of money moved, and the accounts involved.

	PRECONDITIONS:
		- setData() must be called first

	POSTCONDITIONS:
		- sets description to an easily readable description of the transaction

------------------------------------------------------------------------------------------------*/

void Transaction::setDescription(void) {
	ostringstream convert;	//stringstream to convert data members to string
	
	//series of if statements to identify the type of transaction and convert
	//data members to appropriate format for the type of transaction
	if (getTransactionType() == 'M') {
		convert << '$' << getAmount() << " moved from ClientID: " << getFirstClientID() << " Account: " << getFirstClientAccount()
			<< " to Client: " << getSecondClientID() << " to Account: " << getSecondClientAccount();
	} else if (getTransactionType() == 'D') {
		convert << '$' << getAmount() << " Deposited into Account: " << getFirstClientID();
	} else if (getTransactionType() == 'W') {
		convert << '$' << getAmount() << " Withdrawn from Account: " << getFirstClientID();
	}

	description = convert.str();	//sets description to new string
};

/*------------------------------------------------------------------------------------------------

	Setter method for the amount. Returns true if the input is valid.

	PRECONDITIONS:
		- amount must be greater than 0

	POSTCONDITIONS:
		- sets the amount equal to the input

	NOTES:	This method will print an error message if the input is not valid

------------------------------------------------------------------------------------------------*/

bool Transaction::setAmount(const int input) {
	bool successful = false;	//bool variable to be returned
	if (input < 0) {			//checks if amount is valid
		//prints error message if input is not correctly formatted
		cout << "Transaction amount cannot be negative!" << endl;
	} else {
		amount = input;		//sets amount to the input
		successful = true;	//sets successful to true
	}
	return successful;
};

/*------------------------------------------------------------------------------------------------

	Setter for firstClientID. Returns true if the input is valid

	PRECONDITIONS:
		- account number must be 5 digits long

	POSTCONDITIONS:
		- sets the firstClientID equal to the input
		- returns bool if the input was valid

	NOTES:	This method will print an error message if the input is not valid.

------------------------------------------------------------------------------------------------*/

bool Transaction::setFirstClient(const int input) {
	bool successful = false;	//bool variable to be returned
	if (input < 1000 || input > 99999) {	//checks that input is 5 digits long
		cout << "Invalid firstClient!" << endl;	//prints error message
	} else {
		int temp = input;
		temp -= input % 10;
		temp = temp / 10;
		firstClientID = temp;	//sets the firstClientID
		successful = true;		//sets successful to true
	}
	return successful;
};

/*------------------------------------------------------------------------------------------------

	Setter for secondClientID. Returns true if input is valid.

	PRECONDITIONS:
		- account number must be 5 digits long

	POSTCONDITIONS:
		- sets the secondClientID equal input
		- returns bool if the input was valid
		
	NOTES:	This method will print an error message if input is not valid

------------------------------------------------------------------------------------------------*/

bool Transaction::setSecondClient(const int input) {
	bool successful = false;	//bool variable to be returned
	if (input < 10000 || input > 99999) {	//checks that input is 5 digits long
		cout << "Invalid secondClient!" << endl;	//prints error message
	} else {
		int temp = input;
		temp -= input % 10;
		temp = temp / 10;
		secondClientID = temp;	//sets the secondClientID
		successful = true;		//sets successful to true
	}
	return successful;
};

/*------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates new Transaction object
		- sets firstClientID and secondClientID to 0

	NOTES: firstClientID and secondClientID are initialized to 0. This is done because some
		   objects of this class only involve one client. This case can be checked by comparing
		   the secondClientID == 0

------------------------------------------------------------------------------------------------*/

Transaction::Transaction(void) {
	firstClientID = 0;	//sets firstClientID to 0
	secondClientID = 0;	//sets secondClientID to 0
};

/*------------------------------------------------------------------------------------------------

	Destructor

	NOTES: Object of this class do not use any dyanmic memory. As such, the default destructor
	       is suitable.

------------------------------------------------------------------------------------------------*/

Transaction::~Transaction(void) {

};

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

bool Transaction::setData(istream& input) {
	char tempType;				//temp variable for transactionType
	int tempAmount;				//temp variable for amount
	int tempFirstClient;		//temp variable for firstClientID
	int tempSecondClient;		//temp variable for secondClientID
	bool successful = false;	//bool return variable for success

	input >> tempType;	//inputs transaction identifying char into tempType

	if (input.eof()) {
		return false;
	}

	if (tempType == 'M') {	//checks if the transaction type is 'M'
							//as this type of transaction is a special case

		//inputs data into tempFirstClient, tempAmount, and tempSecondClient
		input >> tempFirstClient >> tempAmount >> tempSecondClient;
		
		//attempts to set the firstClientID by calling setFirstClient
		//function will return a bool if tempFirstClient was a valid input
		//this is stored in the bool variable setClient
		bool setClient = setFirstClient(tempFirstClient);

		//attempts to set the secondClientID by calling setSecondClient
		//function will return a bool if tempSecondClient was a valid input
		//this is stored in the bool variable setOtherClient
		bool setOtherClient = setSecondClient(tempSecondClient);
		
		//attempts to set the amount by calling setAmount
		//function will return a bool if tempAmount was a valid input
		//this is stored in the bool variable setAmount
		bool setAmt = setAmount(tempAmount);

		transactionType = tempType;	//sets the transaction type to tempType

		//if statements check that all setters were successful
		//if all were successful to the bool successful is changed to true
		if (setClient == true && setOtherClient == true && setAmt == true) {
			successful = true;
			firstClientAccountIndex = tempFirstClient % 10; 
			secondClientAccountIndex = tempSecondClient % 10;
			setDescription();	//sets the description
		} 
	} else if (tempType == 'D' || tempType == 'W') { //checks to see if the transaction is a valid type
		
		//inputs data into tempFirstClient, tempAmount
		input >> tempFirstClient >> tempAmount;

		//attempts to set the firstClientID by calling setFirstClient
		//function will return a bool if tempFirstClient was a valid input
		//this is stored in the bool variable setClient
		bool setClient = setFirstClient(tempFirstClient);

		//attempts to set the amount by calling setAmount
		//function will return a bool if tempAmount was a valid input
		//this is stored in the bool variable setAmount
		bool setAmt = setAmount(tempAmount);

		transactionType = tempType;	//sets the transaction type to tempType


		//if statements check that all setters were successful
		//if all were successful to the bool successful is changed to true
		if (setClient == true && setAmt == true) {
			successful = true;
			firstClientAccountIndex = tempFirstClient % 10;
			setDescription();	//sets the description
		} 

	} else if (tempType == 'H') {

		//inputs data into tempFirstClient
		input >> tempFirstClient;

		//attempts to set the firstClientID by calling setFirstClient
		//function will return a bool if tempFirstClient was a valid input
		//successful is changed to the return value of setFirstClient
		successful = setFirstClient(tempFirstClient);

		transactionType = tempType;	//sets transactionType

		if (successful) {
			setDescription();	//sets description
		}

	} else {	//prints error message if transaction type was not valid
		cout << "Invalid Transaction Type!" << endl;
		string temp;			//temp string to collect rest of invalid transaction
		getline(input, temp);	//collects rest of invalid transaction
	}
	return successful;	//returns if setting the transaction data was successful (the transaction is valid)
};

/*------------------------------------------------------------------------------------------------

	Getter method for the description. Cannot change any data members.

	POSTCONDITIONS:
		- returns the description

------------------------------------------------------------------------------------------------*/

string Transaction::getDescription(void) const  {
	return description;
};

/*------------------------------------------------------------------------------------------------

		Getter method for the amount. Cannot change any data members.

		POSTCONDITIONS:
			- returns the amount

------------------------------------------------------------------------------------------------*/

int Transaction::getAmount(void) const {
	return amount;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the firstClientID. Returns an int* so that it is compatible with the
	retrieve function parameters in the BST class. Cannot change any data members.

	POSTCONDITIONS:
		- returns the firstClientID

------------------------------------------------------------------------------------------------*/

int Transaction::getFirstClientID(void) const {
	return firstClientID;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the secondClientID. Returns an int* so that it is compatible with the
	retrieve function parameters in the BST class. Cannot change any data members.

	POSTCONDITIONS:
		- returns the secondClientID

------------------------------------------------------------------------------------------------*/

int Transaction::getSecondClientID(void) const {
	return secondClientID;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the transaction type. Cannot change any data members.

	POSTCONDITIONS:
		- returns the transactionType

------------------------------------------------------------------------------------------------*/

char Transaction::getTransactionType(void) const {
	return transactionType;
};