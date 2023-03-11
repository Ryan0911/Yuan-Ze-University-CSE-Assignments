#pragma once
#include"User.h"
class withdrawCash: public User {
public:
	void withdrawMoney();
	double RemainingMoney();
private:
	double cash = 10000;
};