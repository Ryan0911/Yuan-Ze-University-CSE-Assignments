#include <iostream>
using namespace std;
#include "User.h"
bool User::user(unsigned int account, unsigned int PIN)
{
	if (account == userAccount1 && PIN == userPIN1)
	{
		userAvailableBalance = 1000;
		userTotalBalance = 1200;
		return true;
	}
	else if (account == userAccount2 && PIN == userPIN2)
	{
		userAvailableBalance = 200;
		userTotalBalance = 200;
		return true;
	}
	else
	{
		cout << "Please enter your correct account number and PIN" << endl << endl;
		return false;
	}
}

double User::availableBalance()
{
	return userAvailableBalance;
}

double User::totalBalance()
{
	return userTotalBalance;
}

void User::withdrawlBalance(unsigned int Num)
{
	if (Num > userAvailableBalance)
	{
		cout <<endl<< "Your ATM  doesn't have that much money, please rechoose, thank you."<<endl<<endl;
		return;
	}
	userAvailableBalance -= Num;
	userTotalBalance -= Num;
	cout << endl << "Please take your cash from the cash dispenser." << endl << endl;
}

void User::depositBalance(double Num)
{
	userTotalBalance += Num;
}
