/*------------------------------------------------------------------------------------------------------

	Author:		Boyer, Destiny and Naranjo, Alex
	Date:		12/8/2016
	Project:	HW5 - Transactions
	Class:		CSS342
	Professor:	Nash

	Main for Homework 5. Creates new BankManager object and passes two file streams to this object.
	Then displays the clients built by the BankManager as well as the transactions that have been
	completed.

------------------------------------------------------------------------------------------------------*/

#include "BankManager.h"
#include <iostream>
#include <fstream>


using namespace std;

int main() {

	BankManager bank;							//creates BankManager
	ifstream clientData("hw5data.txt");			//opens clients datafile
	ifstream transactionData("hw5command.txt");	//opens the commands fils
	bank.readClients(clientData);				//hands filestream to clients BST
	bank.readTransactions(transactionData);		//hands filestream to BankQueue
	bank.transact();							//performs transactions
	bank.displayClients();						//displays client information
	bank.displayTransactions();					//displays all completed transactions
	transactionData.close();					//closes transactionData
	clientData.close();							//closes clientData

	return 0;
};