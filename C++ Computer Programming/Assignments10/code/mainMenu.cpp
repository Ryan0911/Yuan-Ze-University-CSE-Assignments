#include<iostream>
using namespace std;
#include"ATM.h"

int main() {
	while (true)
	{
		ATM money;
		for (; ; )
			if (money.checkAccount() == true)
				break;
		while (true)
		{
			short option = 0;
			cout << "Main menu:" << endl
				<< "1 - View my balance" << endl
				<< "2 - Withdraw cash" << endl
				<< "3 - Deposit funds" << endl
				<< "4 - Exit" << endl;
			cout << endl << "Enter a choice:";

			while (option >= 5 || option <= 0)
			{
				cin >> option;
				cout << endl;
				switch (option)
				{
				case 1: //View my balance
					money.showBalance();
					break;
				case 2: //Withdraw cash
					money.withdrawMoney();
					break;
				case 3: //Deposit funds
					money.deposit();
					break;
				case 4: //Exit
					cout << "Exiting the system..." << endl << endl << "Thank you! Goodbye!" << endl << endl;
					break;
				default:
					cout << "Please enter a number in the range of 1 ~ 4" << endl;
					break;
				}
			}
			if (option == 4)
				break;
			
		}
		
	}
}