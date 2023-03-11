#include "withdrawCash.h"
#include <iostream>
using namespace std;
void withdrawCash::withdrawMoney()
{
	if (RemainingMoney() == 0)
	{
		cout << "This ATM is already no money, sorry!";
		return;
	}
	short option =0;
	cout << "Withdrawal options:" << endl
		<< "1 - $20" << endl
		<< "2 - $40" << endl
		<< "3 - $60" << endl
		<< "4 - $100" << endl
		<< "5 - $200" << endl
		<< "6 - Cancel transaction" << endl<<endl;
	while (option >= 7 || option <= 0)
	{ 
	cout << "Choose a withdrawal option (1-6):";
	cin >> option;
	switch (option)
	{
	case 1:
		if (cash < 20)
		{
			cout << "This ATM is already no money, sorry!";
			break;
		}
		cash -= 20;
		User::withdrawlBalance(20);
		break;
	case 2:
		if (cash < 40)
		{
			cout << "This ATM is already no $40 money, please rechoose a less money.";
			break;
		}
		cash -= 40;
		User::withdrawlBalance(40);
		break;
	case 3:
		if (cash < 60)
		{
			cout << "This ATM is already no $60 money, please rechoose a less money.";
			break;
		}
		cash -= 60;
		User::withdrawlBalance(60);
		break;
	case 4:
		if (cash < 100)
		{
			cout << "This ATM is already no $100 money, please rechoose a less money.";
			break;
		}
		cash -= 100;
		User::withdrawlBalance(100);
		break;
	case 5:
		if (cash < 200)
		{
			cout << "This ATM is already no $200 money, please rechoose a less money.";
			break;
		}
		cash -= 200;
		User::withdrawlBalance(200);
		break;
	case 6:
		break;
	default:
		cout << "Please enter (1 - 6), thanks!" << endl<<endl;
		break;
	}

	}

}
double withdrawCash::RemainingMoney() 
{
	return cash;
}

