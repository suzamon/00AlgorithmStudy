/*
N��N ũ���� ������ ����� M������ �Ʊ� ��� 1������ �ִ�. ������ 1��1 ũ���� ���簢�� ĭ���� �������� �ִ�.
�� ĭ���� ����Ⱑ �ִ� 1���� �����Ѵ�.

�Ʊ� ���� ������ ��� ũ�⸦ ������ �ְ�, �� ũ��� �ڿ����̴�.
���� ó���� �Ʊ� ����� ũ��� 2�̰�, �Ʊ� ���� 1�ʿ� �����¿�� ������ �� ĭ�� �̵��Ѵ�.

�Ʊ� ���� �ڽ��� ũ�⺸�� ū ����Ⱑ �ִ� ĭ�� ������ �� ����, ������ ĭ�� ��� ������ �� �ִ�.
�Ʊ� ���� �ڽ��� ũ�⺸�� ���� ����⸸ ���� �� �ִ�. ����, ũ�Ⱑ ���� ������ ���� �� ������,
�� ����Ⱑ �ִ� ĭ�� ������ �� �ִ�.

�Ʊ� �� ���� �̵����� �����ϴ� ����� �Ʒ��� ����.

�� �̻� ���� �� �ִ� ����Ⱑ ������ ���ٸ� �Ʊ� ���� ���� ���� ������ ��û�Ѵ�.
���� �� �ִ� ����Ⱑ 1�������, �� ����⸦ ������ ����.
���� �� �ִ� ����Ⱑ 1�������� ���ٸ�, �Ÿ��� ���� ����� ����⸦ ������ ����.
�Ÿ��� �Ʊ� �� �ִ� ĭ���� ����Ⱑ �ִ� ĭ���� �̵��� ��, �������ϴ� ĭ�� ������ �ּڰ��̴�.
�Ÿ��� ����� ����Ⱑ ���ٸ�, ���� ���� �ִ� �����, �׷��� ����Ⱑ �����������, ���� ���ʿ� �ִ� ����⸦ �Դ´�.
�Ʊ� ����� �̵��� 1�� �ɸ���, ����⸦ �Դµ� �ɸ��� �ð��� ���ٰ� �����Ѵ�.
��, �Ʊ� �� ���� �� �ִ� ����Ⱑ �ִ� ĭ���� �̵��ߴٸ�, �̵��� ���ÿ� ����⸦ �Դ´�.
����⸦ ������, �� ĭ�� �� ĭ�� �ȴ�.

�Ʊ� ���� �ڽ��� ũ��� ���� ���� ����⸦ ���� �� ���� ũ�Ⱑ 1 �����Ѵ�.
���� ���, ũ�Ⱑ 2�� �Ʊ� ���� ����⸦ 2���� ������ ũ�Ⱑ 3�� �ȴ�.

������ ���°� �־����� ��, �Ʊ� �� �� �� ���� ���� ���� ������ ��û���� �ʰ� ����⸦ ��Ƹ��� �� �ִ���
���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� ������ ũ�� N(2 �� N �� 20)�� �־�����.

��° �ٺ��� N���� �ٿ� ������ ���°� �־�����. ������ ���´� 0, 1, 2, 3, 4, 5, 6, 9�� �̷���� �ְ�,
�Ʒ��� ���� �ǹ̸� ������.

0: �� ĭ
1, 2, 3, 4, 5, 6: ĭ�� �ִ� ������� ũ��
9: �Ʊ� ����� ��ġ
�Ʊ� ���� ������ �� ���� �ִ�.

���
ù° �ٿ� �Ʊ� �� ���� ���� ������ ��û���� �ʰ� ����⸦ ��Ƹ��� �� �ִ� �ð��� ����Ѵ�.

N, map[21][21]
shark[4] = x, y, size, ���� �����
deque <pair <int, pair <int, int>>> nextPos;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

1. Input()
	N, map[N][N], shark[3]

2. Solution()
	1) while(1) & time = 0
	2) int find_next() ; BFS�� Ž��, 1�̸� ��� �̵� & time++, 0�̸� ���� �� time ���
		2-1) queue <pair <int, pair<int, int>>> p�� time, ��� ���� ��ġ ���� & sharkSize�� shark[2] ����
		2-2) while(!q.empty())�� �־� Ž��
		2-2-1) Ž���� ��, nextPos�� size�� 1���� ũ�� ���� time ���� ���ؼ� ũ�� return;
		2-3) �����Ͽ� Ž�� (���� ū ����⳪ map�� ����� ����)
		2-4) �����Ͽ� Ž������ ��, �ڱ⺸�� ���� ����� ������ nextPos�� �ֱ�
		2-5) 2-4)���� ���� nextPos�� size�� 1���� ũ�� time���� x, y�� ��
		2-6) ���� �� �����ϸ� nextPos ����, �ƴϸ� 2-2-1)���� �ݺ�
		2-7) nextPos size ��ȯ
	3) int move_shark(int time)
		3-1) nextPos ���� �°Բ� ��� �̵� �� �ҿ� �ð� ���ϱ�
		3-2) �ҿ� �ð� ��ȯ
	4) 2) ��ȯ ���� '0'�̸� time �� ���
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, Answer = 0;
int map[21][21] = { 0, };
int shark[4] = { 0, };

deque < pair <int, pair<int, int>>> nextPos;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int move_shark() {
	int nT, nX, nY;
	nT = nextPos.front().first;
	nX = nextPos.front().second.first;
	nY = nextPos.front().second.second;
	map[nX][nY] = 0;
	nextPos.pop_front();

	shark[0] = nX;
	shark[1] = nY;
	shark[3]++;
	if (shark[2] == shark[3]) {
		shark[2]++;
		shark[3] = 0;
	}

	return nT;
}

int find_next() {
	int visited[21][21] = { 0, };
	int sharkSize = shark[2];
	queue < pair <int, pair<int, int>>> q;
	q.push(make_pair(0, make_pair(shark[0], shark[1])));
	visited[shark[0]][shark[1]] = 1;

	int sT, sX, sY, nT, nX, nY;

	while (!q.empty()) {
		sT = q.front().first;
		sX = q.front().second.first;
		sY = q.front().second.second;
		q.pop();
		
		for (int d = 0; d < 4; d++) {
			nX = sX + dx[d];
			nY = sY + dy[d];
			nT = sT + 1;
			if (nX < 0 || nX >= N || nY < 0 || nY >= N) continue;
			if (visited[nX][nY] == 1) continue;
			if (nextPos.size() == 1 && nextPos.front().first < nT) continue;

			if (map[nX][nY] < sharkSize && map[nX][nY] > 0) {
				if (nextPos.size() == 0) {
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first > nT) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first == nT && nextPos.front().second.first > nX) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first == nT && nextPos.front().second.first == nX && nextPos.front().second.second > nY) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
			}
			else if (map[nX][nY] == sharkSize || map[nX][nY] == 0) {
				q.push(make_pair(nT, make_pair(nX, nY)));
				visited[nX][nY] = 1;
			}

		}
	}

	return nextPos.size();
}

void Solution() {
	int flag = 0, time = 0;
	while (1) {
		flag = find_next();
		if (flag == 0) break;

		time = time + move_shark();
	}

	cout << time << endl;
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark[0] = i;
				shark[1] = j;
				shark[2] = 2;
				map[i][j] = 0;
			}
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}