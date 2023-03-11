#pragma once
class User
{
public:
	bool user(unsigned int account , unsigned int PIN);
	double availableBalance();
	double totalBalance();
	void withdrawlBalance(unsigned int Num);
	void depositBalance(double Num);
private:
	unsigned int userAccount1 = 12345;
	unsigned int userPIN1 = 54321;
	unsigned int userAccount2 = 98765;
	unsigned int userPIN2 = 56789;
	double userAvailableBalance = 0;
	double userTotalBalance = 0;
};
