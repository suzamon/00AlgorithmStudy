#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>

using namespace std;

int N, Answer = -1;
int x, y, d1, d2;

int map[21][21];
//int area[21][21];

/*
void print_area() {

}*/

void find_area() {
	int area[21][21] = { 0, };
	int sum[6] = { 0, };
	int row, col;
	/*
	if (x == 3 && y == 3 && d1 == 1 && d2 == 1) {
		cout << "A" << endl;
	}
	*/
	//경계선
	for (int c = 0; c <= d1; c++) {
		if (area[x + c][y - c] == 0) {
			area[x + c][y - c] = 5;
			sum[5] += map[x + c][y - c];
		}
	}
	for (int c = 0; c <= d2; c++) {
		if (area[x + c][y + c] == 0) {
			area[x + c][y + c] = 5;
			sum[5] += map[x + c][y + c];
		}
	}
	for (int c = 0; c <= d2; c++) {
		if (area[x + d1 + c][y - d1 + c] == 0) {
			area[x + d1 + c][y - d1 + c] = 5;
			sum[5] += map[x + d1 + c][y - d1 + c];
		}
	}
	for (int c = 0; c <= d1; c++) {
		if (area[x + d2 + c][y + d2 - c] == 0) {
			area[x + d2 + c][y + d2 - c] = 5;
			sum[5] += map[x + d2 + c][y + d2 - c];
		}
	}

	//1번째 구역
	for (row = 1; row < x + d1; row++) {
		for (col = 1; col <= y; col++) {
			if (area[row][col] == 5) break;
			area[row][col] = 1;
			sum[1] += map[row][col];
		}
	}
	//2번째 구역
	for (row = 1; row <= x + d2; row++) {
		for (col = N; col > y; col--) {
			if (area[row][col] == 5) break;
			area[row][col] = 2;
			sum[2] += map[row][col];
		}
	}
	//3번째 구역
	for (row = x + d1; row <= N; row++) {
		for (col = 1; col < y-d1+d2; col++) {
			if (area[row][col] == 5) break;
			area[row][col] = 3;
			sum[3] += map[row][col];
		}
	}
	//4번째 구역
	for (row = x + d2 + 1; row <= N; row++) {
		for (col = N; col >= y-d1+d2; col--) {
			if (area[row][col] == 5) break;
			area[row][col] = 4;
			sum[4] += map[row][col];
		}
	}
	//5번째 구역
	for (row = x; row <= x + d1 + d2; row++) {
		for (col = y - d1; col <= y + d2; col++){
			if (area[row][col] == 0) {
				area[row][col] = 5;
				sum[5] += map[row][col];
			}
		}
	}
	
	/*
	cout << "x: " << x << ", y: " << y << ", d1: " << d1 << ", d2: " << d2 << endl;
	cout << "Area Map" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << area[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
	sort(sum, sum + 6);

	if (Answer == -1) {
		Answer = abs(sum[5] - sum[1]);
	}
	else if (Answer > abs(sum[5] - sum[1])) {
		Answer = abs(sum[5] - sum[1]);
	}

}

void choose_xy() {
	for (int a = 1; a <= N - (d1 + d2); a++) {
		x = a;
		for (int b = 1 + d1; b <= N - d2; b++) {
			y = b;
			find_area();
		}
	}
}

void Solve() {
	for (int i = 1; i < N; i++) {
		d1 = i;
		for (int j = 1; j < N - d1; j++) {
			d2 = j;
			choose_xy();
		}
	}
}


void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;

	return 0;
}