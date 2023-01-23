#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

#define MAX_NODE 1000000

struct Node {
	char data;
	Node* left;
	Node* right;
};

Node node[MAX_NODE];
int nodeCnt, last_parent, N;
Node* root;

Node* getNode(int idx, char x){
	node[idx].data = x;
	node[idx].left = nullptr;
	node[idx].right = nullptr;

	return &node[idx];
}

void init() {
	nodeCnt = 0;
	root = nullptr;
}

void newNode(int idx, char data, int leftIdx, int rightIdx) {
	Node* new_node = getNode(idx, data);
	if (root == nullptr) root = new_node;

	new_node->left = &node[leftIdx];
	if (rightIdx != 0) {
		new_node->right = &node[rightIdx];
	}
	else {
		new_node->right = nullptr;
	}
}

void travel_rec(Node* node) {
	if (node == nullptr) return;
	travel_rec(node->left);
	cout << node->data;
	travel_rec(node->right);
}

void Solution(int test_case) {
	cout << '#' << test_case << ' ';
	travel_rec(root);
	cout << endl;
}

void Input() {
	init();
	int idx, left, right;
	char data;

	cin >> N;
	last_parent = (int)N / 2;

	idx = 0;
	while (idx < N) {
		cin >> idx;
		if (idx <= last_parent) {
			if (idx == last_parent) {
				if ((idx * 2) + 1 == N) {
					cin >> data >> left >> right;
					newNode(idx, data, left, right);
				}
				else {
					cin >> data >> left;
					right = 0;
					newNode(idx, data, left, right);
				}
			}
			else {
				cin >> data >> left >> right;
				newNode(idx, data, left, right);
			}
		}
		else {
			cin >> data;
			Node* new_node = getNode(idx, data);
			if (root == nullptr) root = new_node;
		}

	}

}

int main(int argc, char** argv)
{
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution(test_case);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}