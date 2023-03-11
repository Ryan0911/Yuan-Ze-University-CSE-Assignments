#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct cluster {
	int number = -1;
	int combine = -1;
};
void sorting(cluster *p, int line);
void swap(cluster &a, cluster &b, int smaller);
void get_pos(int &a, int &b, string content);
void compare(int a, int b, cluster *area, int line, int count);
cluster &get_one(cluster *area, int n, int line);
int main(int argc, char* argv[])
{
	ifstream merge, labels, height;
	int line = 0; string temp;
	int count = 1;
	//merge.open(argv[1]);
	//labels.open(argv[2]);
	labels.open(argv[2]);
	//labels.open("./10_labels.txt");
	while (getline(labels, temp)) {
		if (temp == "")
			continue;
		line++;
	}
	labels.close();
	cluster * pos = new cluster[line + 1];

	pos[0].number = -1;
	pos[0].combine = -1;
	labels.open(argv[2]);
	//labels.open("./10_labels.txt");
	while (getline(labels, temp)) {
		while (temp.find('"') != string::npos)
			temp.replace(temp.find('"'), 1, "");
		pos[count].number = stoi(temp);
		count++;
	}
	labels.close();
	/*get labels*/
	int a = 0; int b = 0; int size = line + 1;
	int group = 10; //從line 往下遞減 到10時終止
	count = 1;
	merge.open(argv[1]);
	//merge.open("./10_merge.txt");
	while (getline(merge, temp)) {
		if (temp == "")
			continue;
		if (line == group)
			break;
		get_pos(a, b, temp);
		compare(a, b, pos, size, count);
		count++;
		line--;
	}
	merge.close();
	sorting(pos, size);
	for (int i = 0; i < size; i++) {
		if (pos[i].number == -1)
			continue;
		if (i != size - 1)
			cout << pos[i].number << " ";
		else
			cout << pos[i].number;
	}
	delete[] pos;
	//system("PAUSE");
	return 0;
}
void sorting(cluster *p, int line) {
	//由大排至小 
	cluster temp;
	for (int i = line - 1; i > 0; i--) {
		for (int j = 0; j <= i - 1; j++) {
			if (p[j].number > p[j + 1].number)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}
void swap(cluster &a, cluster &b, int count) {
	if (a.number < b.number) {
		b.number = -1;
		b.combine = -1;
		a.combine = count;
	}
	else if (a.number >= b.number) {
		a.number = -1;
		a.combine = -1;
		b.combine = count;
	}
}
void get_pos(int &a, int &b, string content) {
	int begin = 0;
	int end = 0;
	end = content.find(',');
	a = stoi(content.substr(begin, end - begin));
	begin = end + 1;
	b = stoi(content.substr(begin));
}
void compare(int a, int b, cluster *area, int line, int count) {
	cluster *a_pos = nullptr;	cluster *b_pos = nullptr;
	if (a < 0) {
		a *= -1;
		a_pos = &area[a];
	}
	else if (a > 0) {
		a_pos = &get_one(area, a, line);
	}
	if (b < 0) {
		b *= -1;
		b_pos = &area[b];
	}
	else if (b > 0) {
		b_pos = &get_one(area, b, line);
	}
	swap(a_pos[0], b_pos[0], count);
}
cluster &get_one(cluster *area, int n, int line) {
	for (int i = 1; i <= line; i++) {
		if (area[i].combine == n)
		{
			return area[i];
		}
	}
}