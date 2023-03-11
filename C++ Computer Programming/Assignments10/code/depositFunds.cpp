#include "depositFunds.h"
#include <iostream>
#include <iomanip>
using namespace std;
void depositFunds::deposit()
{
	double cent = 0;
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel):";
	cin >> cent;
	if (cent == 0)
		return;
	cent /= 100;
	cout <<endl<< "Please insert a deposit envelope containing $" << fixed << setprecision(2) << cent << " in the deposit slot."<<endl<<endl;
	cout << "Your envelope has been received" << endl << "NOTE: The money deposited will not be available until we " << endl << "verify the amount of any enclosed cash, and any enclosed checks clear."<<endl<<endl;
	depositBalance(cent);

}
