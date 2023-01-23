#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

#define MAX_NODE 100000

using namespace std;

struct Node {
	int idx, childCnt;
	Node* parent;
	Node* left;
	Node* right;
};

int V, E, n1, n2, maxNodeNum = 0, sameAncestor = 0, Answer = 0;

Node node[MAX_NODE];
Node* root = &node[1];

int visited[MAX_NODE] = { 0, };

void Init() {
	for (int i = 0; i < maxNodeNum; i++) {
		visited[i] = 0;
		node[i].parent = nullptr;
		node[i].left = nullptr;
		node[i].right = nullptr;
	}
}

int find_v2(int num) {

	if (num == 1) return 1;

	int retIdx;

	int parentIdx = node[num].parent->idx;

	if (visited[parentIdx] == 1) {
		retIdx = parentIdx;
	}
	else {
		retIdx = find_v2(parentIdx);
	}

	return retIdx;
}

void find_v1(int num) {
	visited[num] = 1;

	if (num == 1) return;

	int parentIdx = node[num].parent->idx;
	find_v1(parentIdx);

}

int findChildren(int idx) {
	int total = 0, left, right;

	if (node[idx].left != nullptr) {
		if (node[idx].left->left != nullptr || node[idx].left->right != nullptr) {
			left = findChildren(node[idx].left->idx);
		}
		else {
			left = 1;
		}
	}
	else {
		left = 0;
	}

	total = 1;

	if (node[idx].right != nullptr) {
		if (node[idx].right->left != nullptr || node[idx].right->right != nullptr) {
			right = findChildren(node[idx].right->idx);
		}
		else {
			right = 1;
		}
	}
	else {
		right = 0;
	}

	total = total + left + right;

	return total;
}

void Solution(int test_case) {
	find_v1(n1);
	sameAncestor = find_v2(n2);

	Answer = findChildren(sameAncestor);

	cout << '#' << test_case << ' ' << sameAncestor << ' ' << Answer << endl;
}

void Input() {
	cin >> V >> E >> n1 >> n2;

	int v1, v2;
	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2;

		if (maxNodeNum < v1) maxNodeNum = v1;
		if (maxNodeNum < v2) maxNodeNum = v2;

		if (node[v1].left == nullptr) node[v1].left = &node[v2];
		else node[v1].right = &node[v2];

		node[v2].parent = &node[v1];
		node[v1].idx = v1;
		node[v2].childCnt = 0;
		node[v2].idx = v2;
		node[v2].childCnt = 0;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Init();
		Input();
		Solution(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}