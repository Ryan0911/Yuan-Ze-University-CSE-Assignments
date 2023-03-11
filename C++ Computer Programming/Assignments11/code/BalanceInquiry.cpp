#include "BalanceInquiry.h"
#include<iostream>
#include<iomanip>
BalanceInquiry::BalanceInquiry(int userAccountNumber, vector<Account>& atmAccounts)
	:accounts(atmAccounts),
	 accountNumber(userAccountNumber)
{

}

void BalanceInquiry::execute()
{
	Account * account2=getAccount(accountNumber, accounts);
	cout << "Balance Information:" << endl
		<< " - Available balance:$" << fixed << setprecision(2) << account2->getAvailableBalance() << endl
		<< " - Total balance:    $" << fixed << setprecision(2) << account2->getTotalBalance() << endl << endl;

}

Account * BalanceInquiry::getAccount(int accountNumber, vector<Account>& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return nullptr;
}
