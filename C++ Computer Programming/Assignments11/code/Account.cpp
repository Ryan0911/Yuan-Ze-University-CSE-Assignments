#include "Account.h"
#include<iostream>
#include<iomanip>
Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance)
	: accountNumber(theAccountNumber),
	  pin(thePIN),
	  availableBalance(theAvailableBalance),
	  totalBalance(theTotalBalance)
{
}

bool Account::validatePIN(int userPIN) const
{
	if (userPIN == pin)
		return true;
	else
		return false;
}

double Account::getAvailableBalance() const
{
	return availableBalance;
}

double Account::getTotalBalance() const
{
	return totalBalance;
}

void Account::credit(double amount)
{

	totalBalance += amount;
}

void Account::debit(double amount)
{
	availableBalance -= amount;
	totalBalance -= amount;
}

int Account::getAccountNumber() const
{
	return accountNumber;
}
