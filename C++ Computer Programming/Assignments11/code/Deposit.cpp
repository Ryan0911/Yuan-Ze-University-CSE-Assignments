#include "Deposit.h"
#include<iostream>
#include<iomanip>
Deposit::Deposit(int userAccountNumber, vector<Account>& atmAccounts)
	:accountNumber(userAccountNumber),
	 accounts(atmAccounts)
{
}

void Deposit::execute()
{
	Account * account2 = getAccount(accountNumber, accounts);
	promptForDepositAmount();
	cin >> amount;
	if (amount == 0)
		return;
	amount /= 100;
	cout << endl << "Please insert a deposit envelope containing $" << fixed << setprecision(2) << amount << " in the deposit slot." << endl << endl;
	cout << "Your envelope has been received" << endl << "NOTE: The money deposited will not be available until we " << endl << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl << endl;
	account2->credit(amount);
}

Account * Deposit::getAccount(int accountNumber, vector<Account>& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return nullptr;
}

double Deposit::promptForDepositAmount() const
{
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel):";
	return 0.0;
}
