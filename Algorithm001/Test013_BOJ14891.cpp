/*
총 8개의 톱니를 가지고 있는 톱니바퀴 4개가 아래 그림과 같이 일렬로 놓여져 있다.
또, 톱니는 N극 또는 S극 중 하나를 나타내고 있다.
톱니바퀴에는 번호가 매겨져 있는데, 가장 왼쪽 톱니바퀴가 1번, 그 오른쪽은 2번, 그 오른쪽은 3번, 가장 오른쪽 톱니바퀴는 4번
이때, 톱니바퀴를 총 K번 회전시키려고 한다. 톱니바퀴의 회전은 한 칸을 기준으로 한다.
회전은 시계 방향과 반시계 방향이 있고, 아래 그림과 같이 회전한다.

톱니바퀴를 회전시키려면, 회전시킬 톱니바퀴와 회전시킬 방향을 결정해야 한다.
톱니바퀴가 회전할 때, 서로 맞닿은 극에 따라서 옆에 있는 톱니바퀴를 회전시킬 수도 있고, 회전시키지 않을 수도 있다.
톱니바퀴 A를 회전할 때, 그 옆에 있는 톱니바퀴 B와 서로 맞닿은 톱니의 극이 다르다면,
B는 A가 회전한 방향과 반대방향으로 회전하게 된다.

두 톱니바퀴의 맞닿은 부분은 초록색 점선으로 묶여있는 부분이다.
여기서, 3번 톱니바퀴를 반시계 방향으로 회전했다면, 4번 톱니바퀴는 시계 방향으로 회전하게 된다.
2번 톱니바퀴는 맞닿은 부분이 S극으로 서로 같기 때문에, 회전하지 않게 되고,
1번 톱니바퀴는 2번이 회전하지 않았기 때문에, 회전하지 않게 된다.


첫째 줄에 1번 톱니바퀴의 상태, 둘째 줄에 2번 톱니바퀴의 상태, 셋째 줄에 3번 톱니바퀴의 상태, 넷째 줄에 4번 톱니바퀴의 상태
상태는 8개의 정수로 이루어져 있고, 12시방향부터 시계방향 순서대로 주어진다. N극은 0, S극은 1로 나타나있다.

다섯째 줄에는 회전 횟수 K(1 ≤ K ≤ 100)가 주어진다.
다음 K개 줄에는 회전시킨 방법이 순서대로 주어진다.
각 방법은 두 개의 정수로 이루어져 있고, 첫 번째 정수는 회전시킨 톱니바퀴의 번호, 두 번째 정수는 방향이다.
방향이 1인 경우는 시계 방향이고, -1인 경우는 반시계 방향이다.

K번 회전시킨 이후에 네 톱니바퀴의 점수의 합을 출력한다. 점수란 다음과 같이 계산한다.

1번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 1점
2번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 2점
3번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 4점
4번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 8점

wheel[4][8], K, rot[K][2]

1. Input()
	wheel, K, rot[K][2]
2. Solution()
	1) K번 반복
	2) 첫 회전 시키는 바퀴에서 시작해서 회전할 바퀴와 회전 방향 탐색 -> dq에 저장
		-> 각각 [2]과 [6]번 비교
	3) dq에 저장된 바퀴들을 시계 or 반시계 회전
	4) K번 반복 후 점수 측정 -> 각 바퀴별 [0] 배열 탐색
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, Answer = 0;
int wheel[4][8], rot[101][2] = { 0, };
deque <pair <int, int>> r;

void find_answer() {
	int score = 1;
	for (int i = 0; i < 4; i++) {
		if(i > 0) score = score * 2;
		if(wheel[i][0] == 1) Answer = Answer + score;
	}
}

void rotate_wheel(int rotIdx, int rotDir) {
	int tmp;
	if (rotDir == 1) {
		tmp = wheel[rotIdx][7];
		for (int i = 7; i > 0; i--) {
			wheel[rotIdx][i] = wheel[rotIdx][i - 1];
		}
		wheel[rotIdx][0] = tmp;
	}
	else {
		tmp = wheel[rotIdx][0];
		for (int i = 0; i < 7; i++) {
			wheel[rotIdx][i] = wheel[rotIdx][i + 1];
		}
		wheel[rotIdx][7] = tmp;
	}
}

void find_rot(int idx) {
	int startIdx = rot[idx][0] - 1, startDir = rot[idx][1];

	r.push_back(make_pair(startIdx, startDir));

	switch (startIdx) {
	case 0:
		if (wheel[0][2] != wheel[1][6]) {
			startDir = -startDir;
			r.push_back(make_pair(1, startDir));
			if (wheel[1][2] != wheel[2][6]) {
				startDir = -startDir;
				r.push_back(make_pair(2, startDir));
				if (wheel[2][2] != wheel[3][6]) {
					startDir = -startDir;
					r.push_back(make_pair(3, startDir));
				}
			}
		}
		break;
	case 1:
		if (wheel[1][6] != wheel[0][2]) {
			r.push_back(make_pair(0, -startDir));
		}
		if (wheel[1][2] != wheel[2][6]) {
			startDir = -startDir;
			r.push_back(make_pair(2, startDir));
			if (wheel[2][2] != wheel[3][6]) {
				startDir = -startDir;
				r.push_back(make_pair(3, startDir));
			}
		}
		break;
	case 2:
		if (wheel[2][2] != wheel[3][6]) {
			r.push_back(make_pair(3, -startDir));
		}
		if (wheel[2][6] != wheel[1][2]) {
			startDir = -startDir;
			r.push_back(make_pair(1, startDir));
			if (wheel[1][6] != wheel[0][2]) {
				startDir = -startDir;
				r.push_back(make_pair(0, startDir));
			}
		}
		break;
	case 3:
		if (wheel[3][6] != wheel[2][2]) {
			startDir = -startDir;
			r.push_back(make_pair(2, startDir));
			if (wheel[2][6] != wheel[1][2]) {
				startDir = -startDir;
				r.push_back(make_pair(1, startDir));
				if (wheel[1][6] != wheel[0][2]) {
					startDir = -startDir;
					r.push_back(make_pair(0, startDir));
				}
			}
		}
	}

	while (!r.empty()) {
		rotate_wheel(r.front().first, r.front().second);
		r.pop_front();
	}

}

void Solution() {
	for (int i = 0; i < K; i++) {
		find_rot(i);
	}
	find_answer();
}

void Input() {
	int tmp;
	for (int i = 0; i < 4; i++) {
		cin >> tmp;
		for (int j = 7; j >= 0; j--) {
			wheel[i][j] = tmp % 10;
			tmp = tmp / 10;
		}
	}

	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> rot[i][0] >> rot[i][1];
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}