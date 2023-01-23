/*
ȫ���̴� ����� �������� �տ� �Ӿ� N x M �̷� (Hx, Hy) ��ġ���� ����
�����簡 ���� �̷��� Ż�� ��ġ(Ex, Ey)�� �˰� �ִ�.
������ �̷ο��� ������ �����簡 ��ġ�� ���� �־� ȫ���̰� Ż���ϱ� �����
ȫ���̴� �������� �����ǿ��� ��ģ �����̰� �־�, ���� ��� ���� �� �ִ�. ������ �����̴� �� �� ���� ��� ����
�̶�, ȫ���̸� ���� �̷ο��� Ż���� �� �ִ��� �˾ƺ���, �� �� �ִٸ� ���� ���� ����� �Ÿ� D�� ������ �˾ƺ���.

N M
Hx Hy
Ex Ey
N X M ���

2 �� N �� 1000, 2 �� M �� 1000
1 �� Hx, Hy, Ex, Ey �� 1000
(Hx, Hy)�� (Ex, Ey)
����� 0�� 1�θ� �̷���� �ְ�, 0�� �� ĭ, 1�� ���̴�.

-> BFS�� ����


1. Input() : startPos[2], endPos[2], map[1001][1001]

2. Solution()
	1. find_exit(int startX, startY)
		-> BFS�� ���� -> queue <int, int, int, int> x, y, �Ÿ�, ������� ����
		-> �� ���� �˻� �� ���̸� �̵��ؼ� queue �߰� �ƴϸ�, ���� ��� X�� ���� ��� -> flag
		-> ���� ����� ��쿡�� visited���� '2'�� ��
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
int startPos[2] = { 0, };
int exitPos[2] = { 0, };
int map[1002][1002] = { 0, };
int visited[1002][1002] = { 0, };

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void find_exit(int startX, int startY) {
	queue < pair<pair<int, int>, pair<int, int>>> q;
	q.push(make_pair(make_pair(startX, startY), make_pair(0, 0)));
	
	int length, magicFlag, nextX, nextY;
	while (!q.empty()) {
		startX = q.front().first.first;
		startY = q.front().first.second;
		length = q.front().second.first;
		magicFlag = q.front().second.second;
		q.pop();
		if (startX == exitPos[0] && startY == exitPos[1]) {
			Answer = length;
			break;
		}

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > M) continue;

			if (map[nextX][nextY] == 1 && magicFlag == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] == 2;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, 1)));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = magicFlag + 1;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, magicFlag)));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 2 && magicFlag ==0) {
				visited[nextX][nextY] = magicFlag + 1;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, magicFlag)));
			}
		}
	}
}

void Solution() {

	find_exit(startPos[0], startPos[1]);
}

void Input() {
	cin >> N >> M;
	cin >> startPos[0] >> startPos[1];
	cin >> exitPos[0] >> exitPos[1];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();
	if (Answer == 0) Answer = -1;
	cout << Answer << endl;

	return 0;
}