#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

using namespace std;
int N, Answer = 0;
int map[50][50];

void Solution() {
	int mid = (N / 2) + 1;
	Answer = 0;

	int colCnt = 1;
	for (int row = 1; row <= N; row++) {
		if (row <= mid) {
			for (int col = mid - row + 1; col < mid + row; col++) {
				Answer += map[row][col];
			}
		}
		else {
			for (int col = row - mid + 1; col < N - row + mid + 1; col++) {
				Answer += map[row][col];
			}
		}

	}
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++) {
			scanf("%1d",  &map[i][j]);
		}
	}
}
int main(void) {
	int test_case;
	int T;
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;
}

