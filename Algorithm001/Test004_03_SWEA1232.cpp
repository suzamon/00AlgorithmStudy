#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

#define MAX_NODE 10000

using namespace std;

struct Node {
	string data;
	Node* left;
	Node* right;
};

int N;
long Answer = 0;

Node node[MAX_NODE];
Node* root;

queue <string> q;

void addNode(int idx, string data, int left, int right) {
	node[idx].data = data;

	if(left != 0) node[idx].left = &node[left];
	else node[idx].left = nullptr;

	if(right != 0) node[idx].right = &node[right];
	else node[idx].right = nullptr;

	if (root == nullptr) root = &node[idx];

	return;
}

void init() {
	root = nullptr;
}

bool find_int(string data) {
	switch (data.at(0)) {
	case '+': case '-':	case '*': case '/':
		return false;
		break;
	default:
		return true;
		break;
	}
}

void Input() {
	string data;
	int i, idx, left, right;

	for (i = 1; i <= N; i++) {
		cin >> idx >> data;
		if (!find_int(data)) {
			cin >> left >> right;
			addNode(idx, data, left, right);
		}
		else {
			addNode(idx, data, 0, 0);
		}
	}
}

int travel_rec(Node* rt) {
	long total = 0, left = 0, right = 0;
	if (rt->left != nullptr) {
		if (find_int(rt->left->data)) {
			left = stoi(rt->left->data);
		}
		else {
			left = travel_rec(rt->left);
		}
	}

	string data = rt->data;

	if (rt->right != nullptr) {
		if (find_int(rt->right->data)) {
			right = stoi(rt->right->data);
		}
		else {
			right = travel_rec(rt->right);
		}
	}

	switch (data.at(0)) {
	case '+':
		total = left + right;
		break;
	case '-':
		total = left - right;
		break;
	case '*':
		total = left * right;
		break;
	case '/':
		total = (long) left / right;
		break;
	}
	return total;
}

void Solution(int test_case) {
	Answer = travel_rec(root);

	cout << '#' << test_case << ' ' << Answer << endl;
}


int main(int argc, char** argv)
{
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		cin >> N;
		Input();
		Solution(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}