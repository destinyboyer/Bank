/*-------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016		
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	The Account class represents an account for use by a Client. Diiferent types of accounts
	are represented by using the bool variables isMoneyMarket and isBond. If one of these
	bool data members are initialized to true then the account is able to transfer to other
	accounts within that Client that are of the same type. Class contains functionality
	for withdrawing funds, depositing funds, and transferring funds between like accounts
	if the balance is sufficient.

-------------------------------------------------------------------------------------------------*/


#ifndef account_h
#define account_h
//imports neccessary libraries
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Account {

	public:


	/*------------------------------------------------------------------------------------------------
	
		Default no-args constructor.

		POSTCONDITIONS:
			- instantiates Account object
			- sets accountBalance to 0
			- sets accountID to 0
			- sets accountName to an empty string
			- sets isMoneyMarket and isBond to false

	------------------------------------------------------------------------------------------------*/

	Account(void);

	/*------------------------------------------------------------------------------------------------

		Destructor. Since we do not allocate any dynamic memory within this class the 
		default destructor is suitable.

	------------------------------------------------------------------------------------------------*/

	~Account(void);

	/*------------------------------------------------------------------------------------------------

		Getter method for the accountBalance. Method cannot change any data members.

		POSTCONDITIONS:
			- returns the currentBalance

	------------------------------------------------------------------------------------------------*/

	int getCurrentBalance(void) const;

	/*------------------------------------------------------------------------------------------------

		Setter method for the accountBalance. Input must be greater than 0.

		PRECONDITIONS:
			- input cannot be negative

		POSTCONDITIONS:
			- sets beginningBalance equal to input
			- returns true if the input was valid

			NOTE: This function will throw a runtime error if input is less than zero

	------------------------------------------------------------------------------------------------*/

	bool setBeginningBalance(const int input);

	/*------------------------------------------------------------------------------------------------

		Getter method for the accountName.Method cannot change any data members.

		POSTCONDITIONS:
			- returns the accountName

	------------------------------------------------------------------------------------------------*/

	string getAccountName(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for the accountID. Method cannot change any data members.

		POSTCONDITIONS:
			- returns the accountID

	------------------------------------------------------------------------------------------------*/

	int getAccountID(void) const;

	/*------------------------------------------------------------------------------------------------

		Setter method for the accountID. Also checks if the account is at a Money Market or
		Bond account index and if so sets the corresponding bool identifier to true.

		PRECONDITIONS:
			- newID <= 10
			- newID >= 0

		POSTCONDITIONS:
			- sets accountID equal to newID
			- sets bool identifier for Money Market or Bond type accounts

		NOTES: This method will throw a runtime error if the newID is not a one digit number

	------------------------------------------------------------------------------------------------*/

	void setAccountID(const int newID);

	/*------------------------------------------------------------------------------------------------

		Method takes in an amount and adds it to the currentAccountBalance.

		PRECONDITIONS:
			- amount cannot be negative

		POSTCONDITIONS:
			- adds amount from the currentAccountBalance
			- returns a bool indicating success

		NOTES: This method will throw a runtime error if the amount to deposit is negative.

	------------------------------------------------------------------------------------------------*/

	bool deposit(const int amount);

	/*------------------------------------------------------------------------------------------------

		Method takes in an amount and deducts it from the currentAccountBalance.

		PRECONDITIONS:
			- amount cannot be negative
			- accountBalance >= amount

		POSTCONDITIONS:
			- deducts amount from the currentAccountBalance
			- returns a bool indicating success

		NOTES:	This method will throw a runtime error if there are insufficient funds in the
				accountBalance to cover the withdrawal

	------------------------------------------------------------------------------------------------*/

	bool withdraw(const int amount);

	/*------------------------------------------------------------------------------------------------

		Method returns a string printing the information for one account object. Method cannot
		change any data members. Users getters to retrieve data members and a string stream
		to convert them to a string to be returned.

	------------------------------------------------------------------------------------------------*/

	string toString(void) const;

	/*------------------------------------------------------------------------------------------------

		Setter method for isMoneyMarket.

		POSTCONDITIONS:
			- sets isMoneyMarket to true when called.

	------------------------------------------------------------------------------------------------*/

	void setToMoneyMarket(void);

	/*------------------------------------------------------------------------------------------------

		Setter method for isBond.

		POSTCONDITIONS:
			- sets isBond to true when called.

	------------------------------------------------------------------------------------------------*/

	void setToBond(void);

	/*------------------------------------------------------------------------------------------------

		Getter method for the accountBalance. Method cannot change any data members.

		POSTCONDITIONS:
			- returns the beginningBalance

	------------------------------------------------------------------------------------------------*/

	int getBeginningBalance(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for isMoneyMarket. Method cannot change any data members.

		POSTCONDITIONS:
			- returns isMoneyMarket

	------------------------------------------------------------------------------------------------*/

	bool getIsMoneyMarket(void) const;

	/*------------------------------------------------------------------------------------------------

		Getter method for isBond. Method cannot change any data members.

		POSTCONDITIONS:
			- returns isBond

	------------------------------------------------------------------------------------------------*/

	bool getIsBond(void) const;



	private:

	int beginningBalance;	//stores the beginningBalance, should only be set once
	int currentBalance;		//stores currentBalance
	int accountID;			//stores the accountID, equal to the indexed position in the array
	string accountName;		//stores the account name for description purposes
	bool isMoneyMarket;		//bool variable to indicate if the account is a money market account
	bool isBond;			//bool variable to indicate if the account is a bond account

	/*------------------------------------------------------------------------------------------------

		Method sets a string description for the Account Name based on the Account Number.

		PRECONDITIONS:
			- method must be called by setAccountID

		POSTCONDITIONS:
			- sets description

	------------------------------------------------------------------------------------------------*/

	void setAccountName(const int accountNum);
};

#endif // !standardaccount_h
