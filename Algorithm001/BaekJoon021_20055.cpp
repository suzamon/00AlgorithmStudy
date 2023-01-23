#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N, K, Answer;
int belt[202][2];


void print_belt() {
	cout << "벨트 정보" << endl;
	for (int i = 1; i <= N; i++) {
		cout << i << "번째 벨트에서 로봇 탑승 : " << belt[i][0] << ", 내구도: " << belt[i][1] << endl;
	}
	for (int i = N + 1; i <= 2 * N; i++) {
		cout << i << "번째 벨트에서 로봇 탑승 : " << belt[i][0] << ", 내구도: " << belt[i][1] << endl;
	}
	cout << endl;
}

int check() {
	int ret = 0, cnt = 0;
	for (int i = 1; i <= 2 * N; i++) {
		if (belt[i][1] == 0) cnt++;
		if (cnt >= K) {
			ret = 1;
			break;
		}
	}
	return ret;
}

void exit_robot() {
	if (belt[N][0] == 1) {
		belt[N][0] = 0;
	}
}

void robot_start() {
	if (belt[1][0] == 0 && belt[1][1] > 0) {
		belt[1][0] = 1;
		belt[1][1]--;
	}
}

void move_belt() {
	int tmpArr[2];
	tmpArr[0] = belt[2 * N][0];
	tmpArr[1] = belt[2 * N][1];

	for (int i = 2 * N; i > 1; i--) {
		belt[i][0] = belt[i - 1][0];
		belt[i][1] = belt[i - 1][1];
	}

	belt[1][0] = tmpArr[0];
	belt[1][1] = tmpArr[1];

	exit_robot();
}

void move_robot() {
	for (int i = N; i > 1; i--) {
		if (belt[i - 1][0] == 1 && belt[i][1] > 0 && belt[i][0] == 0) {
			belt[i][0] = 1;
			belt[i][1]--;
			belt[i - 1][0] = 0;
		}
	}
	exit_robot();
}

void Solve() {
	int time = 0, extFlag = 0;
	while (1) {
		time++;
		move_belt();
		//cout << "벨트 이동 후" << endl;
		//print_belt();
		if(time > 1) move_robot();
		//cout << "로봇 이동 후" << endl;
		//print_belt();
		robot_start();
		//cout << "로봇 시작 후" << endl;
		//print_belt();
		
		extFlag = check();
		if (extFlag == 1) break;

	}

	Answer = time;

}

void Input() {
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		cin >> belt[i][1];
	}
}

int main(void) {
	Input();
	//print_belt();

	Solve();

	cout << Answer << endl;
	return 0;
}