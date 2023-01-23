#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

string str;
int N, num, maxPos, Answer = 0;

char tmpArr[6], originalArr[6];
int changeIdx[10][2];

void copy_arr() {
	for (int i = 0; i < maxPos; i++) {
		tmpArr[i] = originalArr[i];
	}
}

void swap_num(int idx1, int idx2) {
	char tmp;
	tmp = tmpArr[idx1];
	tmpArr[idx1] = tmpArr[idx2];
	tmpArr[idx2] = tmp;
}

void change_int() {
	int tmp = 1;
	num = 0;
	for (int i = maxPos - 1; i >= 0; i--) {
		num += ((int)tmpArr[i] - '0') * tmp;
		tmp = tmp * 10;
	}
}

void DFS(int cnt) {
	if (cnt == N) {
		copy_arr();
		for (int i = 0; i < N; i++) {
			swap_num(changeIdx[i][0], changeIdx[i][1]);
		}
		change_int();
		if (num > Answer) Answer = num;

		return;
	}

	for (int i = 0; i < maxPos; i++) {
		for (int j = i + 1; j < maxPos; j++) {
			changeIdx[cnt][0] = i, changeIdx[cnt][1] = j;
			DFS(cnt + 1);
		}
	}
}

void Solution() {
	Answer = 0;
	DFS(0);
}

void Input() {
	cin >> str;
	cin >> N;
	maxPos = str.length();
	for (int i = 0; i < maxPos; i++) {
		originalArr[i] = str.at(i);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}