#include"ATM.h"
#include<iostream>
#include<iomanip>
using namespace std;
bool ATM::checkFive(unsigned int Num)
{
	int checkNum = Num;
	int record = 0;
	for (; ; )
	{
		checkNum /= 10;
		record++;
		if (checkNum == 0)
			break;
	}
	if (record == 5)
		return true;
	else
	return false;
}

bool ATM::checkAccount()
{
		system("pause");
		system("cls");//²MªÅ¿Ã¹õ
		unsigned int account = 0;
		unsigned int PIN = 0;
		cout << "Welcome!" << endl << endl
			<< "Please enter your account number:";
		cin >> account;
		cout << endl << "Enter your PIN:";
		cin >> PIN;
		cout << endl;
		if (checkFive(account) == false || checkFive(PIN) == false)
		{
			cout << "Account number and PIN just five-digit, please enter again."<<endl<<endl;
			return false;
		}
		if (User::user(account, PIN) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
}

void ATM::showBalance()
{
	cout << "Balance Information:" << endl
		<< " - Available balance:$" << fixed << setprecision(2) << User::availableBalance() << endl
		<< " - Total balance:    $"<<fixed<<setprecision(2)<<User::totalBalance()<<endl<<endl;
}





