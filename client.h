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


#ifndef client_h
#define client_h

//imports necessary classes
#include "account.h"
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include "myQueue.h"

using namespace std;

class Client {

	public:

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

	bool setClientID(const int input);

	/*------------------------------------------------------------------------------------------------

		Default no-args constructor.

		POSTCONDITIONS:
			- instantiates new Client object
			- sets firstName and lastName to empty strings
			- sets ClientID to 0


	------------------------------------------------------------------------------------------------*/

	Client(void);

	/*------------------------------------------------------------------------------------------------

		Overloaded copy constructor. Uses the overloaded assignment operator to make a deep copy.

	------------------------------------------------------------------------------------------------*/

	Client(const Client& toCopy);

	/*------------------------------------------------------------------------------------------------

		Destructor

		PRECONDITIONS:
			- Client's data members must have been set with setData()

		POSTCONDITIONS:
			- deletes all memory that was dynamically allocated for the Client

	------------------------------------------------------------------------------------------------*/

	~Client(void);

	/*------------------------------------------------------------------------------------------------

		Getter method for the lastName. Cannot change any data.

		POSTCONDITIONS:
			- returns the lastName

	------------------------------------------------------------------------------------------------*/

	string getLastName(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the firstName. Cannot change any data.

		POSTCONDITIONS:
			- returns the firstName

	------------------------------------------------------------------------------------------------*/

	string getFirstName(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the clientID. Method cannot change any data.

		PRECONDITIONS:
			- clientID has been set by setData()

		POSTCONDITIONS:
			- returns the accountID

	------------------------------------------------------------------------------------------------*/

	int getClientID(void) const;

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

	bool setData(ifstream& inFile);


	/*------------------------------------------------------------------------------------------------
		
		Method prints the Client's information to cout. The information included is the
		Client's ID, their first and last name, and the account number, account name
		and beginning and ending balances of each Account. This method uses Account's
		toString method. Method cannot change any data members.

		PRECONDITIONS:
			- object must have previously had data members set by setData

		POSTCONDITIONS:
			- prints calling object's information to cout

	------------------------------------------------------------------------------------------------*/

	void toString(void) const;

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

	bool deposit(const int accountNumber, const int amount);

	/*------------------------------------------------------------------------------------------------

		Method takes in an amount and an accountNumber. The accountNumber is equal to the index of
		the account in the accounts array. Calls that Account object's withdraw method, passing
		the amount to that function

		PRECONDITIONS:
			- amount >= 0

		POSTCONDITIONS:
			- deducts amount from the appropriate Account

	------------------------------------------------------------------------------------------------*/

	bool withdraw(const int accountNumber, const int amount);

	/*------------------------------------------------------------------------------------------------

		Method displays the transaction history of a client. Calls the toString() function within
		the bankQuueue class.

		POSTCONDITIONS:
			- displays client transaction history

	------------------------------------------------------------------------------------------------*/

	void displayClientHistory(void) const;

	//overloaded equality operators
	bool operator==(const Client& toCompare) const;
	bool operator>(const Client& toCompare) const;
	bool operator<(const Client& toCompare) const;
	//overloaded assignment operator
	void operator=(const Client& toCompare);

	private:

	static const int numberOfAccounts = 10;			//final variable equal to the number of Accounts
	string firstName;								//variable to hold first name
	string lastName;								//variable to hold last name
	int clientID;									//variable to hold accountID
	myQueue<string> transactionHistory;				//queue to log Client's transaction history
	Account* accounts[numberOfAccounts];			//array to hold Account objects for the Client

	private:

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

	bool setLastName(string input);

	/*------------------------------------------------------------------------------------------------

		Setter method for the firstName. Takes in a string.

		PRECONDITIONS:
			- string cannot be empty

		POSTCONDITIONS:
			- sets the firstName equal to the input

		NOTES:	Method will print an error message if the input is an empty string and
				will return false.

	------------------------------------------------------------------------------------------------*/

	bool setFirstName(string input);

};

#endif // !client_h
