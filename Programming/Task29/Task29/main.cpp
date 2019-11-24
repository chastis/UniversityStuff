#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

int priorityOfOperation(char op) {
	if (op == '(')return 1;
	if (op == '+' || op == '-')return 2;
	if (op == '*' || op == '/')return 3;
	if (op == '^')return 4;
	return 0;
}

string PolishNatation(string traditionNatation) {
	//TODO check is correct
	string result = "";
	stack<char> operation;
	int i;
	for (i = 0; i<traditionNatation.size(); i++) {
		if (traditionNatation[i] >= '0'&& traditionNatation[i] <= '9') {
			result.push_back(traditionNatation[i]);
		}
		else
		{
			if (traditionNatation[i] == '(') {
				operation.push('(');
			}
			else {
				if (traditionNatation[i] == ')') {
					while (operation.top() != '(')
					{
						result.push_back(operation.top());
						operation.pop();
					}
					operation.pop();
				}
				else
					if (operation.empty() || priorityOfOperation(traditionNatation[i])>priorityOfOperation(operation.top())) {
						operation.push(traditionNatation[i]);
					}

					else {
						while (!operation.empty() && priorityOfOperation(traditionNatation[i]) <= priorityOfOperation(operation.top())) {
							result.push_back(operation.top());
							operation.pop();
						}
						operation.push(traditionNatation[i]);

					}
			}

		}
	}

	while (!operation.empty()) {
		result.push_back(operation.top());
		operation.pop();

	}

	return result;
}



int getResult(string S) {
	int i;
	stack<int>nums;

	for (i = 0; i<S.size(); i++) {
		if (S[i] >= '0'&&S[i] <= '9') {
			nums.push(S[i] - '0');

		}
		else {
			int a, b, c;
			a = nums.top(); nums.pop();
			b = nums.top(); nums.pop();
			switch (S[i]) {

			case '+': c = a + b; break;
			case '-': c = b - a; break;
			case '*': c = a*b; break;
			case '/': c = b / a; break;
			case '^': c = pow(b, a); break;

			}
			nums.push(c);
		}
	}

	return nums.top();
}

int main() {

	string s;
	cout << "Enter string: ";
	cin >> s;
	int i;
	for (i = 0; i<s.size(); i++)
	{
		if (s.substr(i, 2) == "/0")
		{
			cout << "Division 0" << endl;
			return 0;
		}
	}

	string pn = PolishNatation(s);
	cout << "Polish natation of this string: " << pn << endl;
	cout << s << "=" << getResult(pn);
}
