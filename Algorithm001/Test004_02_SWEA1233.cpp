#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

#define MAX_NODE_CNT 10000

struct Node {
	char data;
	Node* left;
	Node* right;
};

Node node[MAX_NODE_CNT];
Node* root;

int N, Answer = 0, nodeCnt = 0, last_parent_Idx = 0;

void init() {
	root = nullptr;
	Answer = 1;
}

void getNode(int idx, char data, int lIdx, int rIdx){
	node[idx].data = data;

	if (root == nullptr) root = &node[idx];

	if (lIdx == 0) node[idx].left = nullptr;
	else node[idx].left = &node[lIdx];

	if (rIdx == 0) node[idx].right = nullptr;
	else node[idx].right = &node[rIdx];
}

void Input() {
	init();

	cin >> N;

	last_parent_Idx = (int)N / 2;

	int idx = 0, leftIdx, rightIdx;
	char data;

	while (idx < N) {
		cin >> idx;
		if (idx < last_parent_Idx) {
			cin >> data >> leftIdx >> rightIdx;
			getNode(idx, data, leftIdx, rightIdx);
		}
		else if (idx == last_parent_Idx) {
			if ((idx * 2 + 1) == N) {
				cin >> data >> leftIdx >> rightIdx;
				getNode(idx, data, leftIdx, rightIdx);
			}
			else {
				cin >> data >> leftIdx;
				getNode(idx, data, leftIdx, 0);
			}
		}
		else {
			cin >> data;
			getNode(idx, data, 0, 0);
		}
	}
}

void travel_rec(Node* node) {
	if (node == nullptr) return;
	if (Answer == 0) return;

	travel_rec(node->left);

	if (node->left != nullptr && node->right != nullptr) {
		if (node->data >= '0' && node->data <= '9') {
			Answer = 0;
			return;
		}
	}
	else if (node->left != nullptr || node->right != nullptr) {
		if (node->data >= '0' && node->data <= '9') {
			Answer = 0;
			return;
		}
	}
	travel_rec(node->right);
}


void Solution(int test_case) {
	travel_rec(root);

	cout << '#' << test_case << ' ' << Answer << endl;
}

int main(int argc, char** argv)
{
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	//cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}