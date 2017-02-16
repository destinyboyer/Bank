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



#include "account.h"

using namespace std;

/*---------------------------------------------------------------------------------------------------

	Default no-args constructor.

	POSTCONDITIONS:
		- instantiates Account object
		- sets accountBalance to 0
		- sets accountID to 0
		- sets accountName to an empty string
		- sets isMoneyMarket and isBond to false

---------------------------------------------------------------------------------------------------*/


Account::Account(void) {
	currentBalance = 0;		//sets currentBalance to 0
	accountID = 0;			//sets accountID to 0
	accountName = "";		//sets accountName to an empty string
	isMoneyMarket = false;	//sets isMoneyMarket to false
	isBond = false;			//sets isBond to false
};

/*------------------------------------------------------------------------------------------------

	Destructor. Since we do not allocate any dynamic memory within this class the 
	default destructor is suitable.

------------------------------------------------------------------------------------------------*/

Account::~Account(void) {

};

/*------------------------------------------------------------------------------------------------

	Getter method for the accountBalance. Method cannot change any data members.

	POSTCONDITIONS:
		- returns the currentBalance

------------------------------------------------------------------------------------------------*/

int Account::getCurrentBalance(void) const {
	return currentBalance;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the accountBalance. Method cannot change any data members.

	POSTCONDITIONS:
		- returns the beginningBalance

------------------------------------------------------------------------------------------------*/

int Account::getBeginningBalance(void) const {
	return beginningBalance;
};

/*------------------------------------------------------------------------------------------------

	Setter method for the accountBalance. Input must be greater than 0.

	PRECONDITIONS:
		- input cannot be negative

	POSTCONDITIONS:
		- sets beginningBalance equal to input
		- returns true if the input was valid

	NOTE: This function will throw a runtime error if input is less than zero

------------------------------------------------------------------------------------------------*/

bool Account::setBeginningBalance(int input) {
	if (input < 0) {	//checks to see if new balance is less than zero
		cout << " Invalid Account Balance" << endl;
	} else {
		beginningBalance = input;	//sets beginningBalance to input
		currentBalance = input;		//sets currentBalance to input
		return true;
	}
	return false;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the accountName. Method cannot change any data members.

	POSTCONDITIONS:
		- returns the accountName

------------------------------------------------------------------------------------------------*/

string Account::getAccountName(void) const {
	return accountName;
};

/*------------------------------------------------------------------------------------------------

	Getter method for the accountID. Method cannot change any data members.

	POSTCONDITIONS:
		- returns the accountID

------------------------------------------------------------------------------------------------*/

int Account::getAccountID(void) const {
	return accountID;
};

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

void Account::setAccountID(const int newID) {
	if (newID < 0 || newID > 10) {	//checks to see if newID is a valid accountID
		cout << "Invalid Account ID!" << endl;	//prints error message to the console
		return;
	} else {
		accountID = newID;		//sets accountID
		setAccountName(newID);	//sets the accountName
	}

	if (newID == 0 || newID == 1) {		//if the accountID is 0 or 1 it is a
		setToMoneyMarket();				//Money Market Account, sets bool to true
	} else if (newID == 2 || newID == 2) {	//checks if it it a bond account and
		setToBond();					//sets the bond bool to true
	}
};

/*------------------------------------------------------------------------------------------------

	Method takes in an amount and adds it to the currentAccountBalance.

	PRECONDITIONS:
		- amount cannot be negative

	POSTCONDITIONS:
		- adds amount from the currentAccountBalance
		- returns a bool indicating success

	NOTES: This method will throw a runtime error if the amount to deposit is negative.

------------------------------------------------------------------------------------------------*/

bool Account::deposit(const int amount) {
	if (amount < 0) {	//checks to see if amount is negative
		cout << " Invalid Deposit Amount!" << endl;	//prints error message
		return false;
	} else {
		currentBalance = currentBalance + amount;	//adds the amount to the accountBalance
		return true;
	}
};

/*------------------------------------------------------------------------------------------------

	Method takes in an amount and deducts it from the currentAccountBalance.

	PRECONDITIONS:
		- amount cannot be negative
		- accountBalance >= amount

	POSTCONDITIONS:
		- deducts amount from the currentAccountBalance
		- returns a bool indicating success

	NOTES: This method will throw a runtime error if there are insufficient funds in the
		   accountBalance to cover the withdrawal

------------------------------------------------------------------------------------------------*/

bool Account::withdraw(const int amount) {
	bool insufficientFunds = amount > currentBalance; //bool equal to if there are sufficient funds

	if (insufficientFunds) {	//if there are not sufficient funds throw runtime error
		cout << " Insufficient Funds in Account!" << endl;
		return false;	//return false
	} else {
		currentBalance = currentBalance - amount;	//deducts amount from accountBalance
		return true;				//returns true
	}
};

/*------------------------------------------------------------------------------------------------

	Setter method for the accountName.

	PRECONDITIONS:
		- name cannot be an empty string

	POSTCONDITIONS:
		- sets accountName equal to name

	NOTE: This method will throw a runtime error if the parameter is and empty string

------------------------------------------------------------------------------------------------*/


void Account::setAccountName(const int accountNum) {
	switch (accountNum) {
		case 0:
			accountName = "Money Market";
			break;
		case 1:
			accountName = "Prime Money Market";
			break;
		case 2:
			accountName = "Long-Term Bond";
			break;
		case 3:
			accountName = "Short-Term Bond";
			break;
		case 4:
			accountName = "500 Index Fund";
			break;
		case 5:
			accountName = "Capital Value Fund";
			break;
		case 6:
			accountName = "Growth Equity Fund";
			break;
		case 7:
			accountName = "Growth Index Fund";
			break;
		case 8:
			accountName = "Value Fund";
			break;
		case 9:
			accountName = "Value Stock Fund";
			break;
	}
};

/*------------------------------------------------------------------------------------------------

	Method returns a string printing the information for one account object. Method cannot
	change any data members. Users getters to retrieve data members and a string stream
	to convert them to a string to be returned.

------------------------------------------------------------------------------------------------*/

string Account::toString(void) const {
	ostringstream convert;
	string retVal;
	convert << setw(4) << getAccountID() << setw(27) << getAccountName() << setw(13)
		<< getBeginningBalance() << setw(13) << getCurrentBalance();
	retVal = convert.str();
	return retVal;
};

/*------------------------------------------------------------------------------------------------

	Setter method for isMoneyMarket.

	POSTCONDITIONS:
		- sets isMoneyMarket to true when called.

------------------------------------------------------------------------------------------------*/

void Account::setToMoneyMarket(void) {
	isMoneyMarket == true;	//sets isMoneyMarket to true
}

/*------------------------------------------------------------------------------------------------

	Setter method for isBond.

	POSTCONDITIONS:
		- sets isBond to true when called.

------------------------------------------------------------------------------------------------*/

void Account::setToBond(void) {
	isBond == true;			//sets isBond to true
};

/*------------------------------------------------------------------------------------------------

	Getter method for isBond. Method cannot change any data members.

	POSTCONDITIONS:
		- returns isBond

------------------------------------------------------------------------------------------------*/

bool Account::getIsBond(void) const {
	return isBond;	
};

/*------------------------------------------------------------------------------------------------

	Getter method for isMoneyMarket. Method cannot change any data members.

	POSTCONDITIONS:
		- returns isMoneyMarket

------------------------------------------------------------------------------------------------*/

bool Account::getIsMoneyMarket(void) const {
	return isMoneyMarket;
};
