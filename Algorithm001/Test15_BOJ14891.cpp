#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, K, Answer = 0;
char wheel[5][8];
int cmd[101][2];
deque <pair <int, int>> dq;

void print_info(int time) {
	cout << time << "ÃÊ ÈÄ" << endl;
	for (int i = 1; i < 5; i++) {
		cout << i << "¹øÂ° ÈÙ" << endl;
		for (int j = 0; j < 8; j++) {
			cout << wheel[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	int score = 1;
	Answer = 0;
	if (wheel[1][0] == '1') {
		Answer = Answer + score;
	}

	for (int i = 2; i < 5; i++) {
		score = score * 2;
		if (wheel[i][0] == '1') {
			Answer = Answer + score;
		}
	}

}

void rotate_wheel(int idx, int dir) {
	queue <char> q;
	
	if (dir == 1) {
		q.push(wheel[idx][7]);
		for (int i = 0; i < 7; i++) {
			q.push(wheel[idx][i]);
		}
	}
	else {
		for (int i = 1; i < 8; i++) {
			q.push(wheel[idx][i]);
		}
		q.push(wheel[idx][0]);
	}

	for (int i = 0; i < 8; i++) {
		wheel[idx][i] = q.front();
		q.pop();
	}
}

void find_rotate_idx(int time) {
	int sIdx, sDir;
	sIdx = cmd[time][0], sDir = cmd[time][1];

	dq.push_back(make_pair(sIdx, sDir));

	switch (sIdx) {
	case 1:
		if (wheel[1][2] != wheel[2][6]) {
			dq.push_back(make_pair(2, -sDir));
			if (wheel[2][2] != wheel[3][6]) {
				dq.push_back(make_pair(3, sDir));
				if (wheel[3][2] != wheel[4][6]) {
					dq.push_back(make_pair(4, -sDir));
				}
			}
		}
		break;
	case 2:
		if (wheel[2][6] != wheel[1][2]) {
			dq.push_back(make_pair(1, -sDir));
		}
		if (wheel[2][2] != wheel[3][6]) {
			dq.push_back(make_pair(3, -sDir));
			if (wheel[3][2] != wheel[4][6]) {
				dq.push_back(make_pair(4, sDir));
			}
		}
		break;
	case 3:
		if (wheel[3][6] != wheel[2][2]) {
			dq.push_back(make_pair(2, -sDir));
			if (wheel[2][6] != wheel[1][2]) {
				dq.push_back(make_pair(1, sDir));
			}
		}
		if (wheel[3][2] != wheel[4][6]) {
			dq.push_back(make_pair(4, -sDir));
		}
		break;
	case 4:
		if (wheel[4][6] != wheel[3][2]) {
			dq.push_back(make_pair(3, -sDir));
			if (wheel[3][6] != wheel[2][2]) {
				dq.push_back(make_pair(2, sDir));
				if (wheel[2][6] != wheel[1][2]) {
					dq.push_back(make_pair(1, -sDir));
				}
			}
		}
		break;
	}
}

void Solution() {
	int time, idx, dir;	
	for (time = 0; time < K; time++) {
		find_rotate_idx(time);
		while (!dq.empty()) {
			idx = dq.front().first, dir = dq.front().second;
			dq.pop_front();
			rotate_wheel(idx, dir);
		}

		//print_info(time);
	}

	find_answer();
	cout << Answer << endl;
}

void Input() {
	string str;
	for (int i = 1; i < 5; i++) {
		cin >> str;
		for (int j = 0; j < 8; j++) {
			wheel[i][j] = str.at(j);
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> cmd[i][0] >> cmd[i][1];
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}