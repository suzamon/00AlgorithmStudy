/*
�����Ҵ� ũ�Ⱑ N��M�� ���簢������ ��Ÿ�� �� ������, ���簢���� 1��1 ũ���� ���簢������ �������� �ִ�.
�����Ҵ� �� ĭ, ������ �̷���� ������, ���� ĭ �ϳ��� ���� ����
�Ϻ� ĭ�� ���̷����� �����ϸ�, �� ���̷����� �����¿�� ������ �� ĭ���� ��� �������� �� �ִ�.
���� ���� �� �ִ� ���� ������ 3���̸�, �� 3���� ������ �Ѵ�.

�̶�, 0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ���̴�. �ƹ��� ���� ������ �ʴ´ٸ�,
���̷����� ��� �� ĭ���� �������� �� �ִ�.

���� 3�� ���� ��, ���̷����� ���� �� ���� ���� ���� �����̶�� �Ѵ�. ���� �������� ���� ������ ũ��� 27�̴�.
�������� ������ �־����� �� ���� �� �ִ� ���� ���� ũ���� �ִ��� ���ϴ� ���α׷�

ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 8)
��° �ٺ��� N���� �ٿ� ������ ����� �־�����. 0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ��ġ�̴�.
2�� ������ 2���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.
�� ĭ�� ������ 3�� �̻��̴�.

ù° �ٿ� ���� �� �ִ� ���� ������ �ִ� ũ�⸦ ����Ѵ�.

1. Input()
	N, M, map, deque virus, virusCnt, deque empty, emptyCnt

2. Solution()
	1. empty���� 3�� ���� -> DFS
	2. DFS �� copy_map
	3. Simulation -> virus���� �����¿� BFS�� ����

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, Answer = 0;
int map[9][9], copyMap[9][9], wall[3][2];

deque <pair<int, int>> v;
deque <pair <int, int>> e;

int virusCnt, emptyCnt, copyEmptyCnt;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_map() {
	
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Simulaiton() {
	int curX, curY, nextX, nextY;
	queue <pair <int, int>> q;

	for (int i = 0; i < virusCnt; i++) {
		q.push(make_pair(v[i].first, v[i].second));
	}

	while (!q.empty()) {
		curX = q.front().first;
		curY = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++) {
			nextX = curX + dx[d];
			nextY = curY + dy[d];

			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;

			if (copyMap[nextX][nextY] == 0) {
				q.push(make_pair(nextX, nextY));
				copyEmptyCnt--;
				copyMap[nextX][nextY] = 2;
			}
		}
	}

	if (Answer < copyEmptyCnt) {
		//print_map();
		Answer = copyEmptyCnt;
	}
}

void copy_map() {
	copyEmptyCnt = emptyCnt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < 3; i++) {
		copyMap[wall[i][0]][wall[i][1]] = 1;

	}
}

void DFS(int start, int cnt) {
	if (cnt == 3) {
		copy_map();
		copyEmptyCnt -= 3;

		Simulaiton();
		return;
	}

	for (int i = start; i < emptyCnt; i++) {
		wall[cnt][0] = e[i].first;
		wall[cnt][1] = e[i].second;
		DFS(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < emptyCnt - 2; i++) {
		wall[0][0] = e[i].first;
		wall[0][1] = e[i].second;
		DFS(i + 1, 1);
	}
}

void Input() {
	virusCnt = 0;
	emptyCnt = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				e.push_back(make_pair(i, j));
				emptyCnt++;
			}
			else if (map[i][j] == 2) {
				v.push_back(make_pair(i, j));
				virusCnt++;
			}
		}
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;

	return 0;
}