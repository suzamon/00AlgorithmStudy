/*
4x4 보드 -> 네 방향 중 하나 이동
이동 후 같은 방향 있으면 합쳐짐
한 번의 이동에서 이미 합쳐진 블록은 또 합쳐질 수 없음
똑같은 수가 세 개가 있는 경우에는 이동하려고 하는 쪽의 칸이 먼저 합쳐진다.
최대 5번 이동해서 만들 수 있는 가장 큰 블록의 값


1. DFS -> 5번 이동 방향 완탐

2. Simulation
	1) 이동하는 방향별로 시작하는 row, col 정하기
	2) Queue에 넣기 & 넣는 숫자랑 앞에 넣어진 숫자 비교 -> 같고 flag = 0 이면 합치기
	3) 방향별로 시작 행, 열 정하기 & 큐 순서대로 넣기

줄이는 방법
1. N만큼 횟수 반복이면 제외

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
	case 0://상
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
	case 1://하
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
	case 2://좌
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
	case 3://우
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