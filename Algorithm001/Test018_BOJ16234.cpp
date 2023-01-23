/*
N×N크기의 땅이 있고, 땅은 1×1개의 칸으로 나누어져 있다. 각각의 땅에는 나라가 하나씩 존재하며,
r행 c열에 있는 나라에는 A[r][c]명이 살고 있다. 인접한 나라 사이에는 국경선이 존재한다.
모든 나라는 1×1 크기이기 때문에, 모든 국경선은 정사각형 형태이다.

오늘부터 인구 이동이 시작되는 날이다.

인구 이동은 하루 동안 다음과 같이 진행되고, 더 이상 아래 방법에 의해 인구 이동이 없을 때까지 지속된다.

국경선을 공유하는 두 나라의 인구 차이가 L명 이상, R명 이하라면, 두 나라가 공유하는 국경선을 오늘 하루 동안 연다.
위의 조건에 의해 열어야하는 국경선이 모두 열렸다면, 인구 이동을 시작한다.
국경선이 열려있어 인접한 칸만을 이용해 이동할 수 있으면, 그 나라를 오늘 하루 동안은 연합이라고 한다.
연합을 이루고 있는 각 칸의 인구수는 (연합의 인구수) / (연합을 이루고 있는 칸의 개수)가 된다. 편의상 소수점은 버린다.
연합을 해체하고, 모든 국경선을 닫는다.
각 나라의 인구수가 주어졌을 때, 인구 이동이 며칠 동안 발생하는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N, L, R이 주어진다. (1 ≤ N ≤ 50, 1 ≤ L ≤ R ≤ 100)
둘째 줄부터 N개의 줄에 각 나라의 인구수가 주어진다. r행 c열에 주어지는 정수는 A[r][c]의 값이다. (0 ≤ A[r][c] ≤ 100)
인구 이동이 발생하는 일수가 2,000번 보다 작거나 같은 입력만 주어진다.

출력
인구 이동이 며칠 동안 발생하는지 첫째 줄에 출력한다.

int N, L, R, Answer, map[51][51], union[51][51]
deque <pair <int, int>> p[251];

1. Input()
	N, L, R, map[N][N]


2. Solution()
	1) find_union()
		1-1) union 초기화
		1-2) BFS로 인구 수 차이가 L 이상 R 이하이면, 같은 idx로 (union 값이 '0'일 경우만 탐색)
		1-3) 다 구하면 idx 값 return -> idx = N*N이면 끝!
	2) change_people()
		2-1) union 값을 토대로 idx에 맞는 맵 탐색 후  p에 저장
		2-2) 다 저장되면 각 idx에 맞는 변경될 인원 탐색 후 map에 저장

*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, L, R, Answer = 0;
int map[51][51] = { 0, };
int unionMap[51][51] = { 0, };

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

deque <pair <int, int>> p[2500];

void print_map() {
	cout << "UnionMap" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << unionMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Init_union() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			unionMap[i][j] = 0;
		}
	}
}

void select_union(int xx, int yy, int idx) {
	queue <pair <int, int>> q;
	int sX, sY, nX, nY;

	q.push(make_pair(xx, yy));
	unionMap[xx][yy] = idx;

	while (!q.empty()) {
		sX = q.front().first;
		sY = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			nX = sX + dx[i];
			nY = sY + dy[i];
			if (nX < 0 || nX >= N || nY < 0 || nY >= N) continue;

			if (unionMap[nX][nY] == 0) {
				if ((L <= abs(map[sX][sY] - map[nX][nY])) && (abs(map[sX][sY] - map[nX][nY]) <= R)) {
					unionMap[nX][nY] = idx;
					q.push(make_pair(nX, nY));
				}
			}
		}
	}
}

int find_union() {
	int idx = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (unionMap[i][j] == 0) {
				select_union(i, j, idx);
				idx++;
			}
		}
	}
	return idx;
}

void change_people(int maxIdx) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			p[unionMap[i][j]].push_back(make_pair(i, j));
		}
	}

	int pSum, pDiv;

	for (int idx = 1; idx < maxIdx; idx++) {
		pSum = 0, pDiv = 0;
		for (int i = 0; i < p[idx].size(); i++) {
			pSum = pSum + map[p[idx][i].first][p[idx][i].second];
		}
		pDiv = pSum / p[idx].size();

		while (!p[idx].empty()) {
			map[p[idx].front().first][p[idx].front().second] = pDiv;
			p[idx].pop_front();
		}
	}

}

void Solution() {
	int flag = 0, time = 0;

	while (1) {
		if (time != 0) Init_union();

		flag = find_union();
		//print_map();
		if (flag == (N * N + 1)) break;
		time++;

		change_people(flag);
		//print_map();
	}

	cout << time << endl;
}

void Input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();

	return 0;
}