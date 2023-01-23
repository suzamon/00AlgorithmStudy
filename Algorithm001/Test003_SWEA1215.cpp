#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

int N, Answer = 0;
char map[8][8];

int find_col(int sX, int sY) {
	int sX1, sX2, exitFlag = 0;

	if (N % 2 == 0) sX1 = sX - 1 + N / 2, sX2 = sX + N / 2;
	else if (N % 2 == 1) sX1 = sX - 1 + N / 2, sX2 = sX + (N + 1) / 2;
	for (int d = 0; d < N / 2; d++) {
		if (map[sX1 - d][sY] != map[sX2 + d][sY]) {
			exitFlag = 1;
			break;
		}
	}
	return exitFlag;
}

int find_row(int sX, int sY) {
	int sY1, sY2, exitFlag = 0;

	if (N % 2 == 0) sY1 = sY - 1 + N / 2, sY2 = sY + N / 2;
	else if (N % 2 == 1) sY1 = sY - 1 + N / 2, sY2 = sY + (N + 1) / 2;
	for (int d = 0; d < N / 2; d++) {
		if (map[sX][sY1 - d] != map[sX][sY2 + d]) {
			exitFlag = 1;
			break;
		}
	}
	return exitFlag;
}

void Solution() {
	if (N == 1) {
		Answer = 128;
		return;
	}
	Answer = 0;
	int flag = 0;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c <= 8 - N; c++) {
			flag = find_row(r, c);
			if (flag == 0) Answer++;
		}
	}

	for (int c = 0; c < 8; c++) {
		for (int r = 0; r <= 8 - N; r++) {
			flag = find_col(r, c);
			if (flag == 0) Answer++;
		}
	}

	cout << Answer << endl;
}

void Input() {
	char tmp;
	cin >> N;
	scanf("%c", &tmp);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%c", &map[i][j]);
		}
		scanf("%c", &tmp);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T = 1;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}