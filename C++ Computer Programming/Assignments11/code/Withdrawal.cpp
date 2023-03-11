#include "Withdrawal.h"
#include<iostream>
#include<iomanip>
Withdrawal::Withdrawal(int userAccountNumber, vector<Account>& atmAccounts, int & atmRemainingBills)
	:accountNumber(userAccountNumber),
	 accounts(atmAccounts),
	 remainingBills(atmRemainingBills)
{
	
}

void Withdrawal::execute()
{
	Account * account2 = getAccount(accountNumber, accounts);
	displayMenuOfAmounts();
	short option = 0;
	while (option >= 7 || option <= 0)
	{
		cout << "Choose a withdrawal option (1-6):";
		cin >> option;
		switch (option)
		{
		case 1:
			if (remainingBills < 20)
			{
				cout << endl << "This ATM is already no money, sorry!";
				break;
			}
			account2->debit(20);
			remainingBills -= 20;
			cout << endl << "Please take your cash from the cash dispenser.";
			break;
		case 2:
			if (remainingBills < 40)
			{
				cout << endl << "This ATM is already no $40 money, please rechoose a less money.";
				break;
			}
			account2->debit(40);
			remainingBills -= 40;
			cout << endl << "Please take your cash from the cash dispenser.";
			break;
		case 3:
			if (remainingBills < 60)
			{
				cout << endl << "This ATM is already no $60 money, please rechoose a less money.";
				break;
			}
			account2->debit(60);
			remainingBills -= 60;
			cout << endl << "Please take your cash from the cash dispenser.";
			break;
		case 4:
			if (remainingBills < 100)
			{
				cout << endl << "This ATM is already no $100 money, please rechoose a less money.";
				break;
			}
			account2->debit(100);
			remainingBills -= 100;
			cout << endl << "Please take your cash from the cash dispenser.";
			break;
		case 5:
			if (remainingBills < 200)
			{
				cout << endl << "This ATM is already no $200 money, please rechoose a less money.";
				break;
			}
			account2->debit(200);
			remainingBills -= 200;
			cout << endl << "Please take your cash from the cash dispenser.";
			break;
		case 6:
			break;
		default:
			cout << endl << "Please enter (1 - 6), thanks!" << endl << endl;
			break;
		}

	}
}

Account * Withdrawal::getAccount(int accountNumber, vector<Account>& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return nullptr;
}

int Withdrawal::displayMenuOfAmounts() const
{
	if (remainingBills == 0)
	{
		cout << endl << "This ATM is already no money, sorry!";
		return 0;
	}
	short option = 0;
	cout << endl << "Withdrawal options:" << endl
		<< "1 - $20" << endl
		<< "2 - $40" << endl
		<< "3 - $60" << endl
		<< "4 - $100" << endl
		<< "5 - $200" << endl
		<< "6 - Cancel transaction" << endl << endl;
	return 0;
}
