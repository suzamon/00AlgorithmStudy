/*
�����̳� ������ 2 �̻� ������ Ȯ���� ��, �������� Ȯ���� -> �������� Ȯ���� ������ �� ��ȯ

���� ���̴� �׻� 1000 ����, �ǿ��ʰ� �� ������ ��ĭ�� �������� �ʴ´�!

������ ���̴� �ִ� 255

1. Input() : buildingHight[1000], buildingCnt

2.Solution() : 1 ~ buildingCnt ����
	1). ���� 2ĭ ~ ������ 2ĭ���� ���� ū �ǹ� ���� ã��
	2-1) 1)���� ���� ���� �ڱ� ���� ũ�⺸�� ������ ���� �ǹ��� �̵�
	2-2) 1)���� ���� ���� �ڱ� ���� ũ�⺸�� ������ (�ڱ� �ǹ� ���� - ���� ū �ǹ��� ����)�� Answer�� ����
	*find_max_height(int stdHeight, int col) : col -2 ~ col+2 (col ����)���� ���� ū �ǹ� Ž�� �� ��ȯ

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

int buildingHeight[1001];
int buildingCnt = 0, Answer = 0;

void reset_map() {
	for (int i = 1; i <= buildingCnt; i++) {
		buildingHeight[i] = 0;
	}
}

int find_max_height(int curHeight, int col) {

	int maxHeight = 0, tmpH;

	for (int i = col - 2; i <= col + 2; i++) {
		if (i == col) continue;
		if (i <= 0 && i > buildingCnt) continue;

		if (maxHeight < buildingHeight[i]) maxHeight = buildingHeight[i];
	}

	return maxHeight;
}

void Solution() {
	Answer = 0;

	int curHeight, nextHeight;
	for (int i = 3; i <= buildingCnt - 2 ; i++) {
		curHeight = buildingHeight[i];
		nextHeight = find_max_height(curHeight, i);

		if (curHeight > nextHeight) {
			Answer += (curHeight - nextHeight);
		}

	}

	reset_map();
}

void Input() {
	cin >> buildingCnt;

	for (int i = 1; i <= buildingCnt; i++) {
		cin >> buildingHeight[i];
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	T= 10;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}