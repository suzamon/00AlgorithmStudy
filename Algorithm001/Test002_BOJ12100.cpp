/*
4x4 ���� -> �� ���� �� �ϳ� �̵�
�̵� �� ���� ���� ������ ������
�� ���� �̵����� �̹� ������ ����� �� ������ �� ����
�Ȱ��� ���� �� ���� �ִ� ��쿡�� �̵��Ϸ��� �ϴ� ���� ĭ�� ���� ��������.
�ִ� 5�� �̵��ؼ� ���� �� �ִ� ���� ū ����� ��


1. DFS -> 5�� �̵� ���� ��Ž

2. Simulation
	1) �̵��ϴ� ���⺰�� �����ϴ� row, col ���ϱ�
	2) Queue�� �ֱ� & �ִ� ���ڶ� �տ� �־��� ���� �� -> ���� flag = 0 �̸� ��ġ��
	3) ���⺰�� ���� ��, �� ���ϱ� & ť ������� �ֱ�

���̴� ���
1. N��ŭ Ƚ�� �ݺ��̸� ����

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = 0;
int map[21][21],copyMap[21][21], arr[5];

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

int Simualtion(int dir) {
	int row, col, retMax = 0;
	deque <pair<int, int>> dq;

	switch (dir) {
	case 0://��
		for (col = 0; col < N; col++) {
			for (row = 0; row < N; row++) {
				if (copyMap[row][col] == 0)continue;
				else if (dq.empty()) dq.push_back(make_pair(copyMap[row][col], 0));
				else if (dq.back().first == copyMap[row][col] && dq.back().second == 0) {
					dq.pop_back();
					dq.push_back(make_pair(copyMap[row][col] * 2, 1));
				}
				else dq.push_back(make_pair(copyMap[row][col], 0));
				copyMap[row][col] = 0;
			}
			row = 0;

			while (!dq.empty()) {
				copyMap[row][col] = dq.front().first;
				dq.pop_front();
				if (copyMap[row][col] > retMax) retMax = copyMap[row][col];
				row++;
			}
		}
		//print_map();
		break;
	case 1://��
		for (col = 0; col < N; col++) {
			for (row = N-1; row >= 0; row--) {
				if (copyMap[row][col] == 0)continue;
				else if (dq.empty()) dq.push_back(make_pair(copyMap[row][col], 0));
				else if (dq.back().first == copyMap[row][col] && dq.back().second == 0) {
					dq.pop_back();
					dq.push_back(make_pair(copyMap[row][col] * 2, 1));
				}
				else dq.push_back(make_pair(copyMap[row][col], 0));
				copyMap[row][col] = 0;
			}
			row = N - 1;

			while (!dq.empty()) {
				copyMap[row][col] = dq.front().first;
				dq.pop_front();
				if (copyMap[row][col] > retMax) retMax = copyMap[row][col];
				row--;
			}
		}
		//print_map();
		break;
	case 2://��
		for (row = 0; row < N; row++) {
			for (col = 0; col < N; col++) {
				if (copyMap[row][col] == 0)continue;
				else if (dq.empty()) dq.push_back(make_pair(copyMap[row][col], 0));
				else if (dq.back().first == copyMap[row][col] && dq.back().second == 0) {
					dq.pop_back();
					dq.push_back(make_pair(copyMap[row][col] * 2, 1));
				}
				else dq.push_back(make_pair(copyMap[row][col], 0));
				copyMap[row][col] = 0;
			}
			col = 0;

			while (!dq.empty()) {
				copyMap[row][col] = dq.front().first;
				dq.pop_front();
				if (copyMap[row][col] > retMax) retMax = copyMap[row][col];
				col++;
			}
		}
		//print_map();
		break;
	case 3://��
		for (row = 0; row < N; row++) {
			for (col = N - 1; col >= 0; col--) {
				if (copyMap[row][col] == 0)continue;
				else if (dq.empty()) dq.push_back(make_pair(copyMap[row][col], 0));
				else if (dq.back().first == copyMap[row][col] && dq.back().second == 0) {
					dq.pop_back();
					dq.push_back(make_pair(copyMap[row][col] * 2, 1));
				}
				else dq.push_back(make_pair(copyMap[row][col], 0));
				copyMap[row][col] = 0;
			}
			col = N - 1;

			while (!dq.empty()) {
				copyMap[row][col] = dq.front().first;
				dq.pop_front();
				if (copyMap[row][col] > retMax) retMax = copyMap[row][col];
				col--;
			}
		}
		//print_map();
		break;
	}

	return retMax;
}

void DFS(int cnt) {
	if (cnt == 5) {
		//for (int i = 0; i < 5; i++) cout << arr[i] << ' ';
		//cout << endl;
		int maxValue = 0;
		copy_map();
		for (int i = 0; i < 5; i++) {
			maxValue = Simualtion(arr[i]);
			if (i == 4 && maxValue > Answer) Answer = maxValue;
		}

		return;
	}

	for (int i = 0; i < 4; i++) {
		arr[cnt] = i;
		DFS(cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < 4; i++) {
		arr[0] = i;
		DFS(1);
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

int main(void) {
	Input();

	Solution();
	/*
	copy_map();
	cout << Simualtion(3) << endl;
	cout << Simualtion(0) << endl;
	cout << Simualtion(0) << endl;
	*/

	cout << Answer << endl;
	return 0;
}