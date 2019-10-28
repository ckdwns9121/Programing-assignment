#include <fstream>
#include <algorithm>
#include <stack>
#include <string>
#include <vector>
using namespace std;

ifstream input("tree.inp");
ofstream output("tree.out");

void preorder(vector<string> v) {
	output << "\nPreorder\n";
	int root_number = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == "(") output << "r" << root_number++ << "\n";
		else if (v[i] == " " || v[i] == ")")continue;
		else output << v[i] << "\n";
	}
}
void inorder(vector<string> v) {
	output << "Inorder\n";
	stack<int> st;
	int root_number = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == " ") continue;
		else if (v[i] == "(") st.push(root_number++);
		else if (v[i] != ")") {
			output << v[i] << "\n";
			if (!st.empty()) {
				output << "r" << st.top() << "\n";
				st.pop();
			}
		}
	}

}

int main() {

	int t;
	string str;
	input >> t;
	while (t--) {
		stack<string> temp;
		vector<string> v;
		while (true) {
			input >> str;
			v.push_back(str);
			v.push_back(" ");
			if (str == "(") temp.push(str);
			if (str == ")")temp.pop();
			if (temp.empty()) break;
		}
		for (int i = 0; i < v.size(); i++) output << v[i];
		preorder(v);
		inorder(v);

	}

	return 0;
}