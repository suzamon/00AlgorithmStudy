/*
N��Nũ���� ���� �ְ�, ���� 1��1���� ĭ���� �������� �ִ�. ������ ������ ���� �ϳ��� �����ϸ�,
r�� c���� �ִ� ���󿡴� A[r][c]���� ��� �ִ�. ������ ���� ���̿��� ���漱�� �����Ѵ�.
��� ����� 1��1 ũ���̱� ������, ��� ���漱�� ���簢�� �����̴�.

���ú��� �α� �̵��� ���۵Ǵ� ���̴�.

�α� �̵��� �Ϸ� ���� ������ ���� ����ǰ�, �� �̻� �Ʒ� ����� ���� �α� �̵��� ���� ������ ���ӵȴ�.

���漱�� �����ϴ� �� ������ �α� ���̰� L�� �̻�, R�� ���϶��, �� ���� �����ϴ� ���漱�� ���� �Ϸ� ���� ����.
���� ���ǿ� ���� ������ϴ� ���漱�� ��� ���ȴٸ�, �α� �̵��� �����Ѵ�.
���漱�� �����־� ������ ĭ���� �̿��� �̵��� �� ������, �� ���� ���� �Ϸ� ������ �����̶�� �Ѵ�.
������ �̷�� �ִ� �� ĭ�� �α����� (������ �α���) / (������ �̷�� �ִ� ĭ�� ����)�� �ȴ�. ���ǻ� �Ҽ����� ������.
������ ��ü�ϰ�, ��� ���漱�� �ݴ´�.
�� ������ �α����� �־����� ��, �α� �̵��� ��ĥ ���� �߻��ϴ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N, L, R�� �־�����. (1 �� N �� 50, 1 �� L �� R �� 100)
��° �ٺ��� N���� �ٿ� �� ������ �α����� �־�����. r�� c���� �־����� ������ A[r][c]�� ���̴�. (0 �� A[r][c] �� 100)
�α� �̵��� �߻��ϴ� �ϼ��� 2,000�� ���� �۰ų� ���� �Է¸� �־�����.

���
�α� �̵��� ��ĥ ���� �߻��ϴ��� ù° �ٿ� ����Ѵ�.

int N, L, R, Answer, map[51][51], union[51][51]
deque <pair <int, int>> p[251];

1. Input()
	N, L, R, map[N][N]


2. Solution()
	1) find_union()
		1-1) union �ʱ�ȭ
		1-2) BFS�� �α� �� ���̰� L �̻� R �����̸�, ���� idx�� (union ���� '0'�� ��츸 Ž��)
		1-3) �� ���ϸ� idx �� return -> idx = N*N�̸� ��!
	2) change_people()
		2-1) union ���� ���� idx�� �´� �� Ž�� ��  p�� ����
		2-2) �� ����Ǹ� �� idx�� �´� ����� �ο� Ž�� �� map�� ����

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