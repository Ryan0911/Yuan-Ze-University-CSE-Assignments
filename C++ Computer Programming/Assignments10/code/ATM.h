#pragma once
#include"User.h"
#include"depositFunds.h"
#include"withdrawCash.h"
class ATM:public depositFunds {

public:
	bool checkFive(unsigned int Num);
	bool checkAccount();
	void showBalance();

private:

};