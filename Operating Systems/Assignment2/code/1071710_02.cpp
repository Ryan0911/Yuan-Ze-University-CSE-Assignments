#include<stdlib.h>
#include<stdio.h>
#include<time.h> // about system wall-clock time
#include<fstream> // file
#include<string> // string structure
#include<iostream> 
#include<pthread.h> // pthread API
#include<unistd.h> // get tid
#include<stack> // stack structure
#include<vector> // vector structure
#include <cmath>
using namespace std;
struct parameter {
	int number;
	string statement;
	pid_t tid;
	double time;
};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex4thread
int order_list(string token) {
	if (token == "+" || token == "-")
		return 2;
	else if (token == "*" || token == "/")
		return 3;
	else if (token == "(")
		return -1;
	return 0;
}
bool check_isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	return false;
}
bool check_stringOperator(string s) {
	if (s == "+" || s == "-" || s == "*" || s == "/")
		return true;
	return false;
}
bool check_isNumber(char ch) {
	if (ch >= '0' and ch <= '9') {
		return true;
	}
	return false;
}
vector<string> infix_to_vector(string s) {
	int size = s.size();
	int begin = 0; int end = 0; bool isOperand = false;
	vector<string> infix_vector;
	for (int i = 0; i < size; i++) {
		if (check_isOperator(s[i]) == true || s[i] == '(') {
			if (isOperand == true)
			{
				end = i;
				infix_vector.push_back(s.substr(begin, end - begin));
				begin = i + 1;
				isOperand = false;
				infix_vector.push_back(s.substr(i, 1));
			}
			else {
				infix_vector.push_back(s.substr(i, 1));
				begin++;
			}
		}
		else if (check_isNumber(s[i]) == true) {
			isOperand = true;
		}
		else if (s[i] == ')') {
			end = i;
			infix_vector.push_back(s.substr(begin, end - begin));
			begin = i + 1;
			isOperand = false;
			infix_vector.push_back(s.substr(i, 1));
		}
	}
	if (isOperand == true) {
		infix_vector.push_back(s.substr(begin, size - begin));
	}
	return infix_vector;
}
vector<string> infix_to_postfix(vector<string> infix) {
	int size = infix.size();
	stack<string>saving_area;
	vector<string>postfix;
	for (int i = 0; i < size; i++) {
		if (infix[i] == ")") {
			while (saving_area.top() != "(")
			{
				postfix.push_back(saving_area.top());
				saving_area.pop();
			}
			saving_area.pop();
		}
		else if (order_list(infix[i]) == 0) //operands, just push
		{
			postfix.push_back(infix[i]);
		}
		else
		{
			if (saving_area.empty() || order_list(infix[i]) == -1) { //left annotation just push
				saving_area.push(infix[i]);
			}
			else {
				if (order_list(saving_area.top()) <= order_list(infix[i])) {
					saving_area.push(infix[i]);
				}
				else {
					while (!saving_area.empty() && order_list(saving_area.top()) >= order_list(infix[i])) {
						postfix.push_back(saving_area.top());
						saving_area.pop();
					}
					saving_area.push(infix[i]);
				}
			}
		}
	}
	while (!saving_area.empty()) {
		postfix.push_back(saving_area.top());
		saving_area.pop();
	}//infix to postfix
	return postfix;
}
vector<string> reverse_infix(vector<string> s) {
	vector<string> temp;
	int size = s.size();
	for (int i = size - 1; i >= 0; i--) {
		temp.push_back(s[i]);
	}
	return temp;
}
vector<string> infix_to_prefix(vector<string> infix) {
	int size = infix.size();
	stack<string>operand_stack;
	stack<string>operator_stack;
	infix = reverse_infix(infix);
	for (int i = 0; i < size; i++) {
		if (infix[i] == "(") {
			infix[i] = ")";
			continue;
		}
		else if (infix[i] == ")") {
			infix[i] = "(";
			continue;
		}
	}
	size = infix.size();
	stack<string>saving_area;
	vector<string>postfix;
	for (int i = 0; i < size; i++) {
		if (infix[i] == ")") {
			while (saving_area.top() != "(")
			{
				postfix.push_back(saving_area.top());
				saving_area.pop();
			}
			saving_area.pop();
		}
		else if (order_list(infix[i]) == 0) //operands, just push
		{
			postfix.push_back(infix[i]);
		}
		else
		{
			if (saving_area.empty() || order_list(infix[i]) == -1) { //left annotation just push
				saving_area.push(infix[i]);
			}
			else {
				if (order_list(saving_area.top()) <= order_list(infix[i])) {
					saving_area.push(infix[i]);
				}
				else {
					while (!saving_area.empty() && order_list(saving_area.top()) > order_list(infix[i])) {
						postfix.push_back(saving_area.top());
						saving_area.pop();
					}
					saving_area.push(infix[i]);
				}
			}
		}
	}
	while (!saving_area.empty()) {
		postfix.push_back(saving_area.top());
		saving_area.pop();
	}//infix to postfix
	infix = reverse_infix(postfix);
	return infix;
}
string compute(string operand_1, string operators, string operand_2) {
	long double operands_1 = strtoull(operand_1.c_str(), NULL, 0);
	long double operands_2 = strtoull(operand_2.c_str(), NULL, 0);
	long double ans = 0;
	if (operators == "+") {
		ans = operands_1 + operands_2;
		return to_string(ans);
	}
	else if (operators == "-") {
		ans = operands_1 - operands_2;
		return to_string(ans);
	}
	else if (operators == "*") {
		ans = operands_1 * operands_2;
		return to_string(ans);
	}
	else if (operators == "/") {
		ans = operands_1 / operands_2;
		return to_string(ans);
	}
	return "0";
}
string postfix_computing(vector<string> postfix) {
	string ans; stack<string>caculate;
	int size = postfix.size();
	string operand_1, operand_2, operators;
	for (int i = 0; i < size; i++)
	{
		if (postfix[i] == "")
			continue;
		if (check_stringOperator(postfix[i]))
		{
			operators = postfix[i];
			operand_2 = caculate.top();
			caculate.pop();
			operand_1 = caculate.top();
			caculate.pop();
			caculate.push(compute(operand_1, operators, operand_2));
		}
		else
		{
			caculate.push(postfix[i]);
		}
	}
	ans = caculate.top();
	return ans;
}
string prefix_computing(vector<string> prefix) {
	string ans; stack<string>caculate;
	prefix = reverse_infix(prefix);
	int size = prefix.size();
	string operand_1, operand_2, operators;
	for (int i = 0; i < size; i++)
	{
		if (prefix[i] == "")
			continue;
		if (check_stringOperator(prefix[i]))
		{
			operators = prefix[i];
			operand_1 = caculate.top();
			caculate.pop();
			operand_2 = caculate.top();
			caculate.pop();
			caculate.push(compute(operand_1, operators, operand_2));
		}
		else
		{
			caculate.push(prefix[i]);
		}
	}
	ans = caculate.top();
	return ans;
}
bool check_infix(string statement) {
	int size = statement.size();
	bool isOperand = false;
	int operand_num = 0;
	int operator_num = 0;
	int parentness_num = 0;
	for (int i = 0; i < size; i++)
	{
		if (statement[i] == '(')
		{
			if (i == 0)
			{
				if (check_isNumber(statement[i + 1]) || statement[i + 1] == '(')
					parentness_num++;
				else
					return false;
			}
			else if (i + 1 == size)
				return false;
			else if (check_isOperator(statement[i - 1]) || statement[i - 1] == '(')
				parentness_num++;
			else
				return false;
		}
		else if (statement[i] == ')')
		{
			if (i == 0)
				return false;
			else if (i + 1 == size)
			{
				if (check_isOperator(statement[i - 1]) || statement[i - 1] == '(')
					return false;
				else
					parentness_num--;
			}
			else if (check_isNumber(statement[i - 1]) || statement[i - 1] == ')')
				parentness_num--;
			else
				return false;

		}
		else if (check_isOperator(statement[i]))
		{
			if (isOperand == true)
			{
				isOperand = false;
				operand_num++;
			}
			if (check_isNumber(statement[i - 1]) || statement[i - 1] == ')')
				operator_num++;
			else
				return false;
		}
		else if (check_isNumber(statement[i]))
		{
			if (i == 0)
				isOperand = true;
			else if (isOperand == true)
				continue;
			else
			{
				if (check_isOperator(statement[i - 1]) || statement[i - 1] == '(')
					isOperand = true;
				else
					return false;
			}
		}
		else
			return false;
	}
	if (isOperand == true)
		operand_num++;
	if ((operand_num == operator_num + 1) && parentness_num == 0)
		return true;
	return false;
}
void *work_computing(void *ptr) {
	pthread_mutex_lock(&mutex);
	clock_t start, end;
	start = clock(); // start computing
	pthread_t tid; tid = gettid();
	parameter *identify; identify = (parameter *)ptr;
	vector<string> myAnswer;
	vector<string> infix;
	string Ans;
	string expression;
	unsigned long long int tempAns = 0;
	if (check_infix(identify[0].statement) == false) {
		Ans = "syntax error";
	}
	else {
		infix = infix_to_vector(identify[0].statement);
		if (identify[0].number == 0)
		{	//prefix
			myAnswer = infix_to_prefix(infix);

			for (int i = 0; i < myAnswer.size(); i++) {
				if (myAnswer[i] == "")
					continue;
				expression += myAnswer[i] + " ";
			}
			tempAns = roundl(strtoull(prefix_computing(myAnswer).c_str(), NULL, 0));
			Ans = expression + "= " + to_string(tempAns);
		}
		else
		{	//postfix
			myAnswer = infix_to_postfix(infix);

			for (int i = 0; i < myAnswer.size(); i++) {
				if (myAnswer[i] == "")
					continue;
				expression += myAnswer[i] + " ";
			}
			tempAns = roundl(strtoull(postfix_computing(myAnswer).c_str(), NULL, 0));
			Ans = expression + "= " + to_string(tempAns);
		}
	}
	end = clock();
	double diff = (double)(end - start);// end computing
	cout << "[Child" << " " << identify[0].number + 1 << "]" << Ans << " " << diff << "ms" << "\n";
	identify[0].time = diff;
	identify[0].tid = tid;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);

}

int main(int argc, char* argv[])
{
	clock_t start, end;
	start = clock(); // start computing time
	ifstream fin;
	fin.open(argv[1]);
	/* read files*/
	string statement;
	getline(fin, statement);
	cout << "The infix input: " << statement << "\n";
	pthread_t work_thread[2];
	parameter args[2];
	/*get infix*/
	/*set work thread*/
	for (int i = 0; i < 2; i++)
	{
		args[i].number = i;
		args[i].statement = statement;
		if (pthread_create(&work_thread[i], NULL, work_computing, (void*)&args[i]) != 0) {
			cerr << "error occurred by work" << i << "\n";
		};
	}
	for (int i = 0; i < 2; i++)
	{
		pthread_join(work_thread[i], NULL);
	}
	for (int i = 0; i < 2; i++) {
		cout << "[Child" << " " << i + 1 << " " << "tid=" << args[i].tid << "] " << args[i].time << "ms\n";
	}
	end = clock();// end computing time
	double diff = (double)(end - start);
	cout << "[Main thread] " << diff << "ms\n";// 1 seconds = 1000 ms  
	return 0;
};
