#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N, L, Answer = 0;

int map[101][101];
int check[101][101];
int rotMap[101][101];

void print() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "Rotate Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << rotMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void reset_check() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = rotMap[i][j];
			check[i][j] = 0;
		}
	}
}

void Check_sim(int row) {
	int beforeValue, flag = 0;

	beforeValue = map[row][0];
	for (int col = 1; col < N; col++) {
		if (map[row][col] == beforeValue) continue;
		else if (abs(map[row][col] - beforeValue) == 1) { //값이 '1'만큼 다를 때
			if (map[row][col] > beforeValue) { //뒤가 더 클 때
				flag = 0;
				if (col - L < 0) {
					flag = 1;
					break;
				}
				for (int i = 1; i <= L; i++) {
					if (map[row][col - i] != beforeValue || check[row][col - i] != 0) {
						flag = 1;
						break;
					}
					else {
						check[row][col - i] = 1;
					}
				}
				if (flag == 1) break;

				beforeValue = map[row][col];
			}
			else { // 앞이 더 클 때
				col = col - 1;
				beforeValue -= 1;
				flag = 0;
				if (col + L >= N) {
					flag = 1;
					break;
				}
				for (int i = 1; i <= L; i++) {
					if (map[row][col + i] != beforeValue || check[row][col + i] != 0) {
						flag = 1;
						break;
					}
					else {
						check[row][col + i] = 1;
					}
				}

				if (flag == 1) break;

				col = col + L;
				beforeValue = map[row][col];
			}

		}
		else {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		//cout << row << "행 이동 가능" << endl;
		Answer++;
	}
}

void Solve() {
	for (int row = 0; row < N; row++) {
			Check_sim(row);
	}
	//cout << "Rotate" << endl;
	reset_check();
	for (int row = 0; row < N; row++) {
		Check_sim(row);
	}
}

void Input() {
	cin >> N >> L;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			rotMap[j][i] = map[i][j];
		}
	}
}

int main(void) {
	Input();
	//print();
	Solve();
	cout << Answer << endl;
	return 0;
}