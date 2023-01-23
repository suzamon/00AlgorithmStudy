/*
문제
재현시의 시장 구재현은 지난 몇 년간 게리맨더링을 통해서 자신의 당에게 유리하게 선거구를 획정했다.
견제할 권력이 없어진 구재현은 권력을 매우 부당하게 행사했고, 심지어는 시의 이름도 재현시로 변경했다.
이번 선거에서는 최대한 공평하게 선거구를 획정하려고 한다.

재현시는 크기가 N×N인 격자로 나타낼 수 있다. 격자의 각 칸은 구역을 의미하고, r행 c열에 있는 구역은 (r, c)로 나타낼 수 있다.
구역을 다섯 개의 선거구로 나눠야 하고, 각 구역은 다섯 선거구 중 하나에 포함되어야 한다.
선거구는 구역을 적어도 하나 포함해야 하고, 한 선거구에 포함되어 있는 구역은 모두 연결되어 있어야 한다.
구역 A에서 인접한 구역을 통해서 구역 B로 갈 수 있을 때, 두 구역은 연결되어 있다고 한다.
중간에 통하는 인접한 구역은 0개 이상이어야 하고, 모두 같은 선거구에 포함된 구역이어야 한다.

선거구를 나누는 방법은 다음과 같다.

1. 기준점 (x, y)와 경계의 길이 d1, d2를 정한다. (d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
2. 다음 칸은 경계선이다.
	1. (x, y), (x+1, y-1), ..., (x+d1, y-d1)
	2. (x, y), (x+1, y+1), ..., (x+d2, y+d2)
	3. (x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
	4. (x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
3. 경계선과 경계선의 안에 포함되어있는 곳은 5번 선거구이다.
4. 5번 선거구에 포함되지 않은 구역 (r, c)의 선거구 번호는 다음 기준을 따른다.
	- 1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
	- 2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
	- 3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
	- 4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N

구역 (r, c)의 인구는 A[r][c]이고, 선거구의 인구는 선거구에 포함된 구역의 인구를 모두 합한 값이다.
선거구를 나누는 방법 중에서, 인구가 가장 많은 선거구와 가장 적은 선거구의 인구 차이의 최솟값을 구해보자.

입력
첫째 줄에 재현시의 크기 N이 주어진다.
둘째 줄부터 N개의 줄에 N개의 정수가 주어진다. r행 c열의 정수는 A[r][c]를 의미한다.

출력
첫째 줄에 인구가 가장 많은 선거구와 가장 적은 선거구의 인구 차이의 최솟값을 출력한다.

제한
5 ≤ N ≤ 20
1 ≤ A[r][c] ≤ 100

map[21][21], A[21][21]

1. Input()
	N, A[N][N]

2. Soltion()
	1) x, y 선택
	2) d1, d2 조건 만족하면 simulation()
	3) Simulation()
		3-1) map에 경계선 표시
		3-2)

*/

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
		for (col = 1; col < y - d1 + d2; col++) {
			if (area[row][col] == 5) break;
			area[row][col] = 3;
			sum[3] += map[row][col];
		}
	}
	//4번째 구역
	for (row = x + d2 + 1; row <= N; row++) {
		for (col = N; col >= y - d1 + d2; col--) {
			if (area[row][col] == 5) break;
			area[row][col] = 4;
			sum[4] += map[row][col];
		}
	}
	//5번째 구역
	for (row = x; row <= x + d1 + d2; row++) {
		for (col = y - d1; col <= y + d2; col++) {
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