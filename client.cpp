/*---------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

		The Client class stores data for one Client. Each Client object has 10 Account objects that
	are stored in an Account array. Client objects can withdraw and deposit funds from accounts by
	utilizing functions with the same name that are member functions of the Account class. All error
	checking for appropriate funds are done by the Account object. The Client object is responsible
	for transferring funds between Accounts. The data members for a Client object are set via
	setData(ifstream&). setData will use the setters as helper methods to ensure that the
	data is valid. If data is incorrectly formatted the setData() function will return false
	indicating that the Client object may not behave reliably.

	PRECONDITIONS:
		- data used to set Client is properly formatted for use with this class

---------------------------------------------------------------------------------------------------*/

//imports header file
#include "client.h"

/*------------------------------------------------------------------------------------------------

	Setter method for the ClientID. Should be a number that is unique to the Client.

	PRECONDITIONS:
		- input must be greater than 0
		- input must be 4 digits long

	POSTCONDITIONS:
		- sets the clientID equal to the input
		- returns true if the input is valid

	NOTES:	Will print an error message if the input is not valid

------------------------------------------------------------------------------------------------*/

bool Client::setClientID(int input) {

	if (input < 999 || input > 10000) {	//checks if input is valid
		cout << "Invalid Client ID!";	//prints error message
		return false;					//returns false
	}
	clientID = input;	//sets clientID to the input
	return true;		//returns true
};

/*------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates new Client object
		- sets firstName and lastName to empty strings
		- sets ClientID to 0

------------------------------------------------------------------------------------------------*/

Client::Client(void) {
	firstName = "";
	lastName = "";
	clientID = 0;
	for (int index = 0; index < numberOfAccounts; index++) {
		accounts[index] = NULL;
	}

};

/*------------------------------------------------------------------------------------------------

	Destructor

	PRECONDITIONS:
		- Client's data members must have been set with setData()

	POSTCONDITIONS:
		- deletes all memory that was dynamically allocated for the Client

------------------------------------------------------------------------------------------------*/

Client::~Client(void) {
	transactionHistory.makeEmpty();		//clears the transactionHistory queue

	//for loop that deletes each of the accounts and sets the index to NULL
	for(int index = 0; index < numberOfAccounts; index++) {
		delete accounts[index];
		accounts[index] = NULL;
	}
};

/*------------------------------------------------------------------------------------------------

	Overloaded copy constructor. Uses the overloaded assignment operator to make a deep copy.

------------------------------------------------------------------------------------------------*/

Client::Client(const Client& toCopy) {
	*this = toCopy;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the lastName. Cannot change any data.

	POSTCONDITIONS:
		- returns the lastName

------------------------------------------------------------------------------------------------*/

string Client::getLastName(void) const {
	return lastName;	//returns last name
};

/*------------------------------------------------------------------------------------------------

	Getter method for the firstName. Cannot change any data.

	POSTCONDITIONS:
		- returns the firstName

------------------------------------------------------------------------------------------------*/

string Client::getFirstName(void) const {
	return firstName;	//returns the firstName
};

/*------------------------------------------------------------------------------------------------

	Getter method for the clientID. Method cannot change any data.

	PRECONDITIONS:
		- clientID has been set by setData()

	POSTCONDITIONS:
		- returns the accountID

------------------------------------------------------------------------------------------------*/

int Client::getClientID(void) const {
	return clientID;	//returns clientID
};

/*------------------------------------------------------------------------------------------------

	This method takes in a file stream and uses the setter methods as helper functions
	to populate the data members for an instantiated Client object. If setData() returns
	false the Client should not be expected to behave normally.

	PRECONDITIONS:
		- file stream must contain data formatted for Client objects

	POSTCONDITIONS:
		- populates the data members of the Client calling object
		- returns true if setting all data members was successful

	NOTES:	Error messages will be printed if input to set data members is not suitable. If
			there is a negative balance when attempting to set an Account's initial balance
			then the Account will be initialized to 0.

------------------------------------------------------------------------------------------------*/

bool Client::setData(ifstream & inFile) {

	string tempFirst;		//temp variable to hold first name
	string tempLast;		//temp variable to hold last name
	int tempAccountID;		//temp variable to hold accountID
	int tempBalance;		//temp variable to hold accountBalance

	bool success = false;	//bool variable to be returned

	inFile >> tempLast;		//inputs data into tempLast

	if (inFile.eof()) {		//checks if the eof has been reached
		return success;		//returns false	
	}

	//inputs data in to other temp variables
	inFile >> tempFirst >> tempAccountID >> tempBalance;

	//bool variables that hold the return value of the setter functions
	bool setID = setClientID(tempAccountID);	//calls setter to set the clientID
	bool setLast = setLastName(tempLast);		//calls setter to set the lastName
	bool setFirst = setFirstName(tempFirst);	//calls setter to set the firstName
	bool setAccount;							//bool variable to indicate success in setting accounts

	//attempts to set accounts if all setters were successful
	if (setID == true && setLast == true && setFirst == true) {

		//for loop to iterate over the accounts array
		for (int accountIndex = 0; accountIndex < numberOfAccounts; accountIndex++) {
			accounts[accountIndex] = new Account;	//creates new Account object at the accountIndex
			accounts[accountIndex]->setAccountID(accountIndex);	//sets the Account's ID to the accountIndex
			
			//attempts to set the beginning balance
			setAccount = accounts[accountIndex]->setBeginningBalance(tempBalance);
			
			if (setAccount == false) {	//if the beginning balance was not successfully set
				accounts[accountIndex]->setBeginningBalance(0);	//it is initialized to 0
			}
			if (accountIndex != 9) {	//inputs the next account balance in to the 
				inFile >> tempBalance;	//temporary variable as long as it is not the last account
			}

		}
		success = true;	//sets success to true if we have reached this point
	}
	return success;	//returns success
};


/*------------------------------------------------------------------------------------------------

	Method prints the Client's information to cout. The information included is the 
	Client's ID, their first and last name, and the account number, account name
	and beginning and ending balances of each Account. This method uses Account's
	toString method. Method cannot change any data members.

	PRECONDITIONS:
		- object must have previously had data members set by setData

	POSTCONDITIONS:
		- prints calling object's information to cout

-------------------------------------------------------------------------------------------------*/

void Client::toString(void) const {
	ostringstream convert;		//string stream to conver information to string
	ostringstream first;		//string stream to conver information to string
	string firstRow;			//temp string variable

	first << getClientID();		//gets the clientID
	firstRow = first.str();		//converts the string

	//prints the Client ID
	cout << setw(12) << "Client ID: ";
	cout << firstRow << endl;

	//prints the Client's Last Name
	cout << setw(12) << "Last Name: ";
	cout << getLastName() << endl;

	//prints the Client's Last Name
	cout << "First Name: ";
	cout << getFirstName() << endl << endl;

	//Prints out the Header for the Client's Accounts

	cout << "Account" << setw(23) << "Account"
		<< setw(18) << "Beginning"
		<< setw(13) << "Ending" << endl;

	cout << setw(7) << "Number"
		<< setw(21) << "Name"
		<< setw(19) << "Balance"
		<< setw(15) << "Balance" << endl << endl;

	//for loop that iterates over the accounts calling toString on each account
	for (int accountIndex = 0; accountIndex < numberOfAccounts; accountIndex++) {
		cout << accounts[accountIndex]->toString() << endl;
	}
	cout << endl;		//return carriage
};

/*------------------------------------------------------------------------------------------------

	Setter method for the lastName. Takes in a string as input.

	PRECONDITIONS:
		- string cannot be empty

	POSTCONDITIONS:
		- sets the lastName equal to the input
		- returns false if input is invalid

	NOTES:	Method will print an error message if the input is an empty string and
			will return false.

------------------------------------------------------------------------------------------------*/

bool Client::setLastName(string input) {
	if (input == "") {	//checks to make sure that the input is valid
		cout << "Last Name Cannot be an Empty String!";	//prints error message
		return false;
	}
	lastName = input;	//sets last name to the input
	return true;
};

/*------------------------------------------------------------------------------------------------

	Setter method for the firstName. Takes in a string.

	PRECONDITIONS:
		- string cannot be empty

	POSTCONDITIONS:
		- sets the firstName equal to the input

	NOTES:	Method will print an error message if the input is an empty string and
			will return false.

------------------------------------------------------------------------------------------------*/

bool Client::setFirstName(string input) {
	if (input == "") {	//checks to see that the input is valid
		cout << "First Name Cannot be an Empty String!";	//prints an error message
		return false;
	}
	firstName = input;	//sets firstName to the input
	return true;
};


/*-------------------------------------------------------------------------------------------------

	Method compares two Client object and returns which is greater. The calling object is the
	left hand argument and the parameter is the right hand argument. Client objects are compared
	by their accountID

	PRECONDITIONS:
		- both Client object have valid data members

	POSTCONIDTIONS:
		- returns true if the calling object has a greater accountID than the parameter

--------------------------------------------------------------------------------------------------*/

bool Client::operator>(const Client& toCompare) const {
	if (this->getClientID() > toCompare.getClientID()) {	//checks accountID's
		return true;	//returns true if calling object's accountID is greater
	} else {
		return false;	//returns false otherwise
	}
};

/*-------------------------------------------------------------------------------------------------

	Method compares two Client object and returns which is greater. The calling object is the
	right hand argument and the parameter is the left hand argument. Client objects are compared
	by their accountID

	PRECONDITIONS:
		- both Client object have valid data members

	POSTCONIDTIONS:
		- returns true if the calling object has a lesser accountID than the parameter

--------------------------------------------------------------------------------------------------*/

bool Client::operator<(const Client& toCompare) const {
	return !(*this > toCompare);	//returns the opposite of the overloaded > operator
};

/*-------------------------------------------------------------------------------------------------

	Method compares two Client objects for equality. Clients are compared based on their
	accountID's since each ID should be unique

	PRECONDITIONS:
		- both Client object have valid data members

	POSTCONIDTIONS:
		- returns true if the two Client accountID's are equal

--------------------------------------------------------------------------------------------------*/

bool Client::operator==(const Client& toCompare) const {
	return (this->getClientID() == toCompare.getClientID());
};

/*------------------------------------------------------------------------------------------------

	Method takes in an amount and an accountNumber. The accountNumber is equal to the index of
	the account in the accounts array. Calls that Account object's withdraw method, passing
	the amount to that function. Error checks to make sure accountIndex is greater than zero and less
	than ten. Also checks if the specified account has suffient funds to withdraw parameter amount.
	Checks if the accountIndex isBond or isMoneyMarket. If withdraw amount is greater than the balance,
	it will subtract the difference from other moneyMarket or bond account if it can cover the
	difference. Anytime a withdraw transaction occurs a string with a description of the transaction
	is popped onto specific clients transactionHistory queue.

	PRECONDITIONS:
		- amount >= 0

	POSTCONDITIONS:
		- deducts amount from the appropriate Account

	NOTES:	will print an error message if the Account ID is not valid

------------------------------------------------------------------------------------------------*/

bool Client::withdraw(const int accountIndex, const int amount) {
	//check to see if the Account ID is valid
	if (accountIndex < 0 || accountIndex > 10) {
		cout << "Invalid Account ID in Withdraw!";
		return false;
	}

	//bool variables. One to hold whether the withdrawal was successful.
	//the other variables will be used to check if funds from another
	//like type account can be used to cover the balance if
	//there are not sufficient funds
	bool sufficientFunds = accounts[accountIndex]->withdraw(amount);
	bool isMoneyMarket;
	bool isBond;
	bool success = false;
	int tempAmount = amount;

	//variables that will be used to add to the transactionHistory
	ostringstream convert;
	string toHistory;


	if (sufficientFunds) {	//if there were sufficient funds
		success = true;		//the withdrawal was successful

		//adds description of the transaction to the transactionHistory
		convert << "$" << amount << " was withdrawn from " << accounts[accountIndex]->getAccountName();
		toHistory = convert.str();
		transactionHistory.push(toHistory);
	} else {
		//checks to see if the Account is a Money Market or bond
		//Account and can use funds from a like type account to cover
		//the remaining balance
		isMoneyMarket = accounts[accountIndex]->getIsMoneyMarket();
		isBond = accounts[accountIndex]->getIsBond();

		//amount that still needs to be withdrawn
		tempAmount = amount - accounts[accountIndex]->getCurrentBalance();
		
		//if the Account is a money market this checks to see if there are
		//sufficient funds in other moneymarket type accounts and if so
		//uses those to cover the withdrawal
		//adds to the transaction History showing a withdrawal from each Account
		if (isMoneyMarket) {
			if (accountIndex == 0) {
				success = accounts[1]->withdraw(tempAmount);
				if (success) {
					accounts[accountIndex]->withdraw(amount - tempAmount);

					convert << "$" << amount - tempAmount << " was withdrawn from " << accounts[accountIndex]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

					convert << "$" << tempAmount << " was withdrawn from " << accounts[1]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

				}
			} else if (accountIndex == 1) {
				success = accounts[0]->withdraw(tempAmount);
				if (success) {
					accounts[accountIndex]->withdraw(amount - tempAmount);

					convert << "$" << amount - tempAmount << " was withdrawn from " << accounts[accountIndex]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

					convert << "$" << tempAmount << " was withdrawn from " << accounts[0]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);
				}
			}
		//if the Account is a bond market this checks to see if there are
		//sufficient funds in other moneymarket type accounts and if so
		//uses those to cover the withdrawal
		//adds to the transaction History showing a withdrawal from each Account
		} else if (isBond) {
			if (accountIndex == 2) {
				success = accounts[3]->withdraw(tempAmount);
				if (success) {
					accounts[accountIndex]->withdraw(amount - tempAmount);

					convert << "$" << amount - tempAmount << " was withdrawn from " << accounts[accountIndex]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

					convert << "$" << tempAmount << " was withdrawn from " << accounts[3]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

				}
			} else if (accountIndex == 3) {
				success = accounts[2]->withdraw(tempAmount);
				if (success) {
					accounts[accountIndex]->withdraw(amount - tempAmount);

					convert << "$" << amount - tempAmount << " was withdrawn from " << accounts[accountIndex]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

					convert << "$" << tempAmount << " was withdrawn from " << accounts[2]->getAccountName();
					toHistory = convert.str();
					transactionHistory.push(toHistory);

				}
			}
		}
	}
	return success;
};

/*------------------------------------------------------------------------------------------------

	Method takes in an amount and an accountNumber. The accountNumber is equal to the index of
	the account in the accounts array. Calls that Account object's deposit method, passing
	the amount to that function. Anytime a deposit transaction occurs a string with a description
	of the transaction is popped onto specific clients transactionHistory queue.

	PRECONDITIONS:
		- amount >= 0

	POSTCONDITIONS:
		- adds the amount from the appropriate Account

------------------------------------------------------------------------------------------------*/

bool Client::deposit(const int accountIndex, const int amount) {
	bool success = accounts[accountIndex]->deposit(amount);	//calls deposit on the Account

	if (success) {	//if the account successfully was able to deposit the amount
		ostringstream convert;	

		//creates string describing the transaction and adds it to the transactionHistory
		convert << "$" << amount << " was deposited into " << accounts[accountIndex]->getAccountName();
		string toHistory = convert.str();
		transactionHistory.push(toHistory);
	}
	return success;
};

/*------------------------------------------------------------------------------------------------

	Method makes a deep copy of a Client object.

------------------------------------------------------------------------------------------------*/

void Client::operator=(const Client& toCopy) {
	firstName = toCopy.getFirstName();	//copies the firstName
	lastName = toCopy.getLastName();	//copies the lastName
	clientID = toCopy.getClientID();	//copies the ClientID

	transactionHistory = toCopy.transactionHistory;	//copies the transactionHistoru

	for (int index = 0; index < numberOfAccounts - 1; index++) {	//copies each account
		accounts[index] = new Account;
		*accounts[index] = *toCopy.accounts[index];
	}
};

/*------------------------------------------------------------------------------------------------

	Method displays the transaction history of a client. Calls the toString() function within
	the bankQuueue class.

	POSTCONDITIONS:
		- displays client transaction history

------------------------------------------------------------------------------------------------*/

void Client::displayClientHistory(void) const {

	ostringstream convert;		//string stream to conver information to string
	string firstRow;			//temp string variable
	convert << getClientID();		//gets the clientID
	firstRow = convert.str();		//converts the string

	//prints header
	cout << "Transactions for Client: " << getLastName() << ", " 
		<< getFirstName() << endl;
	cout << "Client ID: " << firstRow << endl << endl;
	//prints transactions
	transactionHistory.toString();
	cout << endl << endl;
};