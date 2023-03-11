#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<time.h>
#include<string.h>
using namespace std;
struct node{
	long long int total_sec = -1;
	int year = -1; 
	int month = -1;
	int day = -1;
	int hour = -1;
	int minute = -1;
	int second = -1;
	struct node *ptr = NULL;
};
struct level2_store {
	int store_id = 0;
	long long int total_sec = -1;
};
long long int date_to_sec(int year, int month, int day, int hour, int min, int sec);
bool check_in_30_mins(long long int sec, long long int compared_sec);
bool outrange(long long int start_sec, long long int end_sec, long long int compared_sec);
bool check_in_3_days(long long int start_sec, long long int compared_sec);
int main(int argc, char* argv[]) {
	const int STORE = 11; const int PERSON = 51;
	node **footprint = new node*[PERSON];
	for (int i = 0; i < PERSON; ++i) {
		footprint[i] = new node[STORE];
	}
	bool check_list[51];
	for (int i = 0; i < 51; i++) {
		check_list[i] = false;
	}
	ifstream fin1;
	fin1.open(argv[1]);
	//fin1.open("in4.txt");
	//date range 2020-01-01 - 2021-12-31
	string target; string start_date; string end_date;
	string file_con;
	getline(fin1, file_con); target = file_con;
	getline(fin1, file_con); start_date = file_con;
	getline(fin1, file_con); end_date = file_con;
	int person = 0; int store = 0; 
	int year = 0; int month = 0; int day = 0; int hour = 0; int minute = 0; int second = 0;
	long long int total = 0;
	/*start & end setting*/
	long long int floor = 0;
	year = stoi(start_date.substr(0, 4)); month = stoi(start_date.substr(5,2)); day = stoi(start_date.substr(8, 2));
	floor = date_to_sec(year, month, day, 0, 0, 0);
	long long int upper = 0;
	year = stoi(end_date.substr(0, 4)); month = stoi(end_date.substr(5, 2)); day = stoi(end_date.substr(8, 2));
	upper = date_to_sec(year, month, day, 23, 59, 59);
	node *explore; node *new_node;
	int target_person = stoi(target.substr(2, 2));
	while (getline(fin1, file_con)) {
		//access matrix
		person = stoi(file_con.substr(2, 2)); store = stoi(file_con.substr(7, 2));
		//date
		year = stoi(file_con.substr(10, 4)); month = stoi(file_con.substr(15, 2)); day = stoi(file_con.substr(18, 2));
		//time
		hour = stoi(file_con.substr(21, 2)); minute = stoi(file_con.substr(24, 2)); second = stoi(file_con.substr(27, 2));
		//get total_sec
		total = date_to_sec(year, month, day, hour, minute, second);
		if (outrange(floor, upper, total)&&target_person == person)
			continue;
		//ok..
		if (footprint[person][store].total_sec == -1) {
			footprint[person][store].year = year; footprint[person][store].month = month; footprint[person][store].day = day;
			footprint[person][store].hour = hour; footprint[person][store].minute = minute; footprint[person][store].second = second;
			footprint[person][store].total_sec = total;
		}
		else {
			new_node = new node;
			new_node->year = year; new_node->month = month; new_node->day = day;
			new_node->hour = hour; new_node->minute = minute; new_node->second = second;
			new_node->total_sec = total;
			explore = &footprint[person][store];
			for (; explore->ptr != NULL; explore = explore->ptr);
			explore->ptr = new_node;
		}
	}
	/*建立好足跡矩陣了*/
	explore = NULL; node *explore2; node *explore3;
	queue<level2_store> level2_footprint;
	level2_store level2;
	//第一層接觸
	for (int s = 1; s < 11; s++) {
		if (footprint[target_person][s].total_sec == -1)//目標病患沒走過
			continue;
		//有走過的地方，其走過的時段都要驗一遍
		explore = &footprint[target_person][s];
		for (; explore != NULL; explore = explore->ptr) {
			for (int p = 1; p < 51; p++) {
				if (footprint[p][s].total_sec == -1 || target_person == p)
					continue;
				//someone to here...
				explore2 = &footprint[p][s];
				for (; explore2 != NULL; explore2 = explore2->ptr) {
					if (check_in_30_mins(explore->total_sec, explore2->total_sec)) {
						//first layer touch.
						check_list[p] = true;//找出所有此人三天內走過的地方
						for (int s2 = 1; s2 < 11; s2++) {
							if (footprint[p][s2].total_sec == -1) //這個人沒走過
								continue;
							explore3 = &footprint[p][s2];//這個人走過 把三天內走過時段搜出來
							for (; explore3 != NULL; explore3 = explore3->ptr) {
								if (check_in_3_days(explore2->total_sec, explore3->total_sec)) {
									level2.store_id = s2;
									level2.total_sec = explore3->total_sec;
									level2_footprint.push(level2);
								}
							}
						}
					}
				}
			}
		}
	}
	//第二層接觸
	//全部pop出來後比較是否有人在30分鐘內有接觸就可
	explore = NULL;
	int s_id = 0; long long int s_sec = 0;
	while (!level2_footprint.empty()) {
		s_id = level2_footprint.front().store_id;
		s_sec = level2_footprint.front().total_sec;
		for (int p = 1; p < 51; p++) {
			if (footprint[p][s_id].total_sec == -1)
				continue;
			explore = &footprint[p][s_id];
			for (; explore != NULL; explore = explore->ptr)
			{
				if (check_in_30_mins(s_sec, explore->total_sec))
				{
					check_list[p] = true;
				}
			}
		}
		level2_footprint.pop();
	}
	check_list[target_person] = true;
	for (int i = 1; i < 51; i++)
		if (check_list[i] == true)
		{
			if (i < 10)
				cout << "A10" << i << endl;
			else
				cout << "A1" << i << endl;
		}
	//system("PAUSE");
	return 0;
}
long long int date_to_sec(int year, int month, int day, int hour, int min, int sec) {
	struct tm test;
	memset(&test, 0, sizeof(test));
	test.tm_year = year - 1900;
	test.tm_mon = month - 1;
	test.tm_mday = day;
	test.tm_hour = hour;
	test.tm_min = min;
	test.tm_sec = sec;
	return mktime(&test);
}
bool check_in_30_mins(long long int start_sec, long long int compared_sec) {
	long long int in_minute = 0;
	in_minute = start_sec + (30 * 60);
	if (compared_sec >= start_sec && compared_sec <= in_minute)
		return true;
	return false;
}
bool check_in_3_days(long long int start_sec, long long int compared_sec) {
	long long int in_days = 0;
	in_days = start_sec + ((3 * 86400) + 24000);
	if (compared_sec >= start_sec && compared_sec <= in_days)
		return true;
	return false;
}
bool outrange(long long int start_sec, long long int end_sec, long long int compared_sec) {
	if (compared_sec >= start_sec && compared_sec <= end_sec)
		return false;
	return true;
} 