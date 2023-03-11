#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<map>
#include<queue>
using namespace std;
typedef struct xml_node {
	string label;
	xml_node *parent = NULL;
	xml_node *child = NULL;
	xml_node *sibling = NULL;
	string value;
	bool isEmptyElement = false;
	map<string, string> attribute;
};
string process_string(string s);
void setNode(xml_node*node, string label, string all_content);
void DFS(xml_node*root, string expression, string type, int &signal);
int token(string s);
bool match(string s, xml_node*node, string type);
bool print_info(xml_node*node, string assign, string type);
int target_pos(string s);
string get_attribute(string s);
bool child_finding(xml_node*root, string expression, string type);
int main(int argc, char* argv[]) {
	ifstream xml, pattern;
	xml.open(argv[1]);
	pattern.open(argv[2]);
	//xml.open("xml.txt");
	//pattern.open("pattern.txt");
	string p_expression;
	string temp;
	string all_string;
	while (getline(xml, temp)) {
		all_string += temp + '\n';
	}
	while (all_string.find('\n') != string::npos)
		all_string = all_string.replace(all_string.find('\n'), 1, " ");
	while (all_string.find(" = ") != string::npos)
		all_string = all_string.replace(all_string.find(" = "), 3, "=");
	xml.close();
	xml.open(argv[1]);
	//xml.open("xml.txt");
	xml_node *root;
	xml_node *current;
	xml_node *new_node;
	stack<string> saving;
	int begin = all_string.find('<'), end = all_string.find('>') + 1;
	root = new xml_node;
	setNode(root, all_string.substr(begin, end - begin), all_string);
	saving.push(root->label);
	string top_label; string compare;
	current = root;
	for (int i = end; !saving.empty(); i++) {
		top_label = "</" + saving.top() + '>';
		if (all_string[i] == '<') {
			begin = i;
			end = all_string.substr(i).find('>') + i + 1;
			compare = all_string.substr(begin, end - begin);
			if (compare == top_label) {
				saving.pop();
				current = current->parent;
			}
			else {
				new_node = new xml_node;
				setNode(new_node, compare, all_string.substr(i - 1));
				if (current->child == NULL) {
					current->child = new_node;
					current->child->parent = current;
					current = current->child;
				}
				else {
					current = current->child;
					for (; current->sibling != NULL; current = current->sibling);
					current->sibling = new_node;
					current->sibling->parent = current->parent;
					current = current->sibling;
				}
				saving.push(current->label);
			}
		}
		if (current != NULL)
			if (current->isEmptyElement == true) {
				saving.pop();
				current = current->parent;
			}
	}
	/*tree construct complete*/
	/*let's do DFS*/
	int record = 0;
	while (getline(pattern, p_expression)) {
		record++;
	}
	pattern.close();
	pattern.open(argv[2]);
	//pattern.open("pattern.txt");
	int record2 = 0; int success = 0;
	while (getline(pattern, p_expression)) {
		record2++;
		if (p_expression[0] == '/' && p_expression[1] != '/') {
			p_expression.insert(0, "/");
		}
		DFS(root, p_expression, "", success);
		if (success == 0)
			cout << endl;
		if (record != record2)
			cout << endl;
		success = 0;
	}
	//system("pause");
	return 0;
}
string process_string(string s) {
	queue<string> storage;
	int size = s.size(); int end = 0; int begin = 0;
	for (int i = 1, j = 0; i < size; i++, j++) {
		if (s[j] == '/' && s[i] == '/') {
			end = j;
			storage.push(s.substr(begin, end - begin));
			begin = end;
			j += 2;
			i += 2;
		}
		else if (s[j] == '/' && s[i] != '/') {
			end = j;
			storage.push(s.substr(begin, end - begin));
			begin = end;
		}
	}
	end = size;
	storage.push(s.substr(begin, end - begin));
	begin = end;
	if (storage.front() == "")
		storage.pop();
	return storage.front();
}
void setNode(xml_node*node, string label, string all_content) {
	int begin = 0; int end = 0; string c_label; string assign;
	begin = label.find("<") + 1;
	end = label.find(">");
	c_label = label.substr(begin, end - begin);
	if (label.find('=') == string::npos) {
		//set name
		node->label = c_label;
	}
	else {
		//has a class
		int pos = 0;
		string key, value; begin = 0; end = c_label.find(' '); string temp;
		node->label = c_label.substr(begin, end - begin);
		c_label = c_label.substr(end + 1);
		while (!c_label.empty() && pos < c_label.size()) {
			if (c_label[pos] == ' ' || pos == c_label.size() - 1) {
				assign = c_label.substr(begin, pos - begin);
				key = assign.substr(begin, assign.find('='));
				value = assign.substr(assign.find('=') + 1);
				while (value.find('"') != string::npos)
					value.replace(value.find('"'), 1, "");
				c_label = c_label.substr(pos + 1);
				node->attribute[key] = value;
				pos = 0;
			}
			pos++;
		}
	}
	string s_end = "</" + node->label + ">";
	if (all_content.find(s_end) == string::npos)
		node->isEmptyElement = true;
	if (node->isEmptyElement == false) {
		int c_begin = 0; int c_end = 0;
		c_begin = all_content.find(label) + label.size();
		c_end = all_content.substr(c_begin).find(s_end) + c_begin;
		node->value = all_content.substr(c_begin, c_end - c_begin);
	}

}
void DFS(xml_node*root, string expression, string type, int &signal) {
	if (root == NULL) {
		return;
	}
	xml_node *current; string c_ex;
	string next_expression;
	queue<xml_node*> p_queue;
	c_ex = process_string(expression);
	next_expression = expression.substr(c_ex.size());
	string c_type;	string type_temp;
	c_type = get_attribute(c_ex);
	if (c_type != "")
	{
		type_temp = "[@" + c_type + "]";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
		type_temp = "@" + c_type + "";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
	}
	int target = 0; int size = 0;
	current = root;
	target = target_pos(c_ex); stack<xml_node*> dfs_t; xml_node* temp;
	if (target != 0) {
		type_temp = "[" + to_string(target) + "]";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
	}
	if (expression == "/value" || expression == "/attribute") {
		if (print_info(root, type, expression))
			signal = 1;
	}
	else {
		switch (token(c_ex))
		{
		case 1:
			//selects nodes in the document from the current node
			c_ex = c_ex.substr(2);
			dfs_t.push(current);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type) == true && child_finding(temp, next_expression, c_type) == true) {
					p_queue.push(temp);
				}
				dfs_t.pop();
				if (temp->sibling && temp != root)
					dfs_t.push(temp->sibling);
				if (temp->child)
					dfs_t.push(temp->child);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					DFS(p_queue.front(), next_expression, c_type, signal);
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return;
					p_queue.pop();
				}
				if (p_queue.empty())
					return;
				DFS(p_queue.front(), next_expression, c_type, signal);
			}
			break;
		case 2:
			//select from the root node
			c_ex = c_ex.substr(1);
			if (match(c_ex, current, c_type))
				p_queue.push(current);
			if (current->child)
				dfs_t.push(current->child);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type) && child_finding(temp, next_expression, c_type))
					p_queue.push(temp);
				dfs_t.pop();
				if (temp->sibling)
					dfs_t.push(temp->sibling);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					DFS(p_queue.front(), next_expression, c_type, signal);
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return;
					p_queue.pop();
				}
				if (p_queue.empty())
					return;
				DFS(p_queue.front(), next_expression, c_type, signal);
			}
			break;
		case 3:
			//selects the parent of the current node
			c_ex = c_ex.substr(2);
			if (root->parent)
				DFS(root->parent, next_expression, c_type, signal);
			break;
		case 4:
			//selects the current node
			c_ex = c_ex.substr(1);
			DFS(root, next_expression, c_type, signal);
			break;
		case 5:
			//selects all nodes with the name
			dfs_t.push(current);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type) == true && child_finding(temp, next_expression, c_type) == true) {
					p_queue.push(temp);
				}
				dfs_t.pop();
				if (temp->sibling && temp != root)
					dfs_t.push(temp->sibling);
				if (temp->child)
					dfs_t.push(temp->child);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					DFS(p_queue.front(), next_expression, c_type, signal);
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return;
					p_queue.pop();
				}
				if (p_queue.empty())
					return;
				DFS(p_queue.front(), next_expression, c_type, signal);
			}
			break;
		}
	}
}
int token(string s) {
	if (s.find("..") != string::npos)
		return 3;
	else if (s.find(".") != string::npos)
		return 4;
	if (s[0] == '/' && s[1] == '/') {
		return 1;
	}
	else if (s[0] == '/' && s[1] != '/') {
		return 2;
	}
	else {
		return 5;
	}
}
bool match(string s, xml_node*node, string type) {
	if (s == "") {
		if (type.find('=') != string::npos) {
			string key, value;
			int begin = 0; int end = 0;
			end = type.find('=');
			key = type.substr(begin, end - begin);
			begin = end + 1;
			value = type.substr(begin);
			while (value.find("'") != string::npos)
				value.replace(value.find("'"), 1, "");
			if (node->attribute.find(key) == node->attribute.end())
				return false;
			else
			{
				if (node->attribute[key] == value)
					return true;
				else
					return false;
			}
		}
		else if (node->attribute.find(type) == node->attribute.end())
		{
			return false;
		}
		return true;
	}
	else {
		if (s == node->label) {
			if (type == "")
				return true;
			else
			{
				if (type.find('=') != string::npos) {
					string key, value;
					int begin = 0; int end = 0;
					end = type.find('=');
					key = type.substr(begin, end - begin);
					begin = end + 1;
					value = type.substr(begin);
					while (value.find("'") != string::npos)
						value.replace(value.find("'"), 1, "");
					if (node->attribute.find(key) == node->attribute.end())
						return false;
					else
					{
						if (node->attribute[key] == value)
							return true;
						else
							return false;
					}
				}
				else {
					if (node->attribute.find(type) == node->attribute.end())
					{
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}
}
bool print_info(xml_node*node, string assign, string type) {
	if (type == "/value") {
		cout << node->value << endl;
	}
	else {
		if (node->attribute.find(assign) == node->attribute.end())
			return false;
		cout << node->attribute[assign] << endl;
	}
	return true;
}
int target_pos(string s) {
	if (s.find('[') != string::npos) {
		if (s.find('@') != string::npos)
			return 0;
		else {
			int begin = 0; int end = 0;
			begin = s.find('[') + 1; end = s.find(']');
			return stoi(s.substr(begin, end - begin));
		}
	}
	else {
		return 0;
	}
}
string get_attribute(string s) {
	int begin = 0; int end = 0;
	if (s.find('@') == string::npos)
		return "";
	else {
		s = s.substr(s.find("@"));
		if (s.find(']') != string::npos)
			end = s.find(']');
		else
			end = s.size();
		begin = s.find('@') + 1;
	}
	return s.substr(begin, end - begin);
}
bool child_finding(xml_node*root, string expression, string type) {
	if (root == NULL) {
		return false;
	}
	xml_node *current; string c_ex;
	string next_expression;
	queue<xml_node*> p_queue;
	c_ex = process_string(expression);
	next_expression = expression.substr(c_ex.size());
	string c_type;	string type_temp;
	c_type = get_attribute(c_ex);
	if (c_type != "")
	{
		type_temp = "[@" + c_type + "]";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
		type_temp = "@" + c_type + "";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
	}
	int target = 0; int size = 0;
	current = root;
	target = target_pos(c_ex); stack<xml_node*> dfs_t; xml_node* temp;
	if (target != 0) {
		type_temp = "[" + to_string(target) + "]";
		if (c_ex.find(type_temp) != string::npos)
			c_ex.replace(c_ex.find(type_temp), type_temp.size(), "");
	}
	if (expression == "/value" || expression == "/attribute") {
		if (expression == "/attribute")
		{
			if (root->attribute.find(type) == root->attribute.end())
				return false;
			else
				return true;
		}
		return true;
	}
	else {
		switch (token(c_ex))
		{
		case 1:
			//selects nodes in the document from the current node
			c_ex = c_ex.substr(2);
			dfs_t.push(current);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type) == true ) {
					p_queue.push(temp);
				}
				dfs_t.pop();
				if (temp->sibling && temp != root)
					dfs_t.push(temp->sibling);
				if (temp->child)
					dfs_t.push(temp->child);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					return true;
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return false;
					p_queue.pop();
				}
				if (p_queue.empty())
					return false;
				return true;
			}
			break;
		case 2:
			//select from the root node
			c_ex = c_ex.substr(1);
			if (match(c_ex, current, c_type))
				p_queue.push(current);
			if (current->child)
				dfs_t.push(current->child);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type))
					p_queue.push(temp);
				dfs_t.pop();
				if (temp->sibling)
					dfs_t.push(temp->sibling);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					return true;
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return false;
					p_queue.pop();
				}
				if (p_queue.empty())
					return false;
				return true;
			}
			break;
		case 3:
			//selects the parent of the current node
			c_ex = c_ex.substr(2);
			if (root->parent)
				return true;
			break;
		case 4:
			//selects the current node
			c_ex = c_ex.substr(1);
			return true;
			break;
		case 5:
			//selects all nodes with the name
			dfs_t.push(current);
			while (!dfs_t.empty()) {
				temp = dfs_t.top();
				if (match(c_ex, temp, c_type) == true) {
					p_queue.push(temp);
				}
				dfs_t.pop();
				if (temp->sibling && temp != root)
					dfs_t.push(temp->sibling);
				if (temp->child)
					dfs_t.push(temp->child);
			}
			size = p_queue.size();
			if (target == 0) {
				for (int i = 0; i < size; i++) {
					return true;
					p_queue.pop();
				}
			}
			else {
				for (int i = 1; i < target; i++) {
					if (p_queue.empty())
						return false;
					p_queue.pop();
				}
				if (p_queue.empty())
					return false;
				return true;
			}
			break;
		}
	}
	return false;
}