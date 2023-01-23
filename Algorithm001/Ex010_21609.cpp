/*
N��N�� ���ڿ��� ����, ������ ���, ������ ���, �Ϲ� ���, �Ϲ� ����� M���� ���� -> ���� M������ �ڿ����� ǥ��
������ ����� -1, ������ ����� 0���� ǥ��
 (i, j)�� ������ i�� ��, j�� ���� �ǹ��ϰ�, |r1 - r2| + |c1 - c2| = 1�� �����ϴ� �� ĭ (r1, c1)�� (r2, c2)�� ������ ĭ

��� �׷��� ����� ����� �����̴�.
�׷쿡�� �Ϲ� ����� ��� �ϳ� �־�� �ϸ�, �Ϲ� ����� ���� ��� ���ƾ� �Ѵ�.
������ ����� ���ԵǸ� �� �ǰ�, ������ ����� �󸶳� ����ֵ� �������. �׷쿡 ���� ����� ������ 2���� ũ�ų� ���ƾ� �ϸ�
������ �� ��Ͽ��� �׷쿡 ���� ������ ĭ���� �̵��ؼ� �׷쿡 ���� �ٸ� ��� ĭ���� �̵��� �� �־���Ѵ�.
��� �׷��� ���� ����� ������ ����� �ƴ� ��� �߿���
���� ��ȣ�� ���� ���� ��� && ���� ��ȣ�� ���� ���� ����̴�.

1. ũ�Ⱑ ���� ū ��� �׷��� ã�´�. -> ���� ����� ���Ե� ������ ����� ���� ���� ���� ��� �׷�
 -> ���� ����� ���� ���� ū �� -> ���� ���� ū ���� ã�´�.
2. 1���� ã�� ��� �׷��� ��� ����� �����Ѵ�. ��� �׷쿡 ���Ե� ����� ���� B��� ���� ��, B^2���� ȹ���Ѵ�.
3. ���ڿ� �߷��� �ۿ��Ѵ�.(������ ��� �̵� X)
4. ���ڰ� 90�� �ݽð� �������� ȸ���Ѵ�.
5. �ٽ� ���ڿ� �߷��� �ۿ��Ѵ�.

ù° �ٿ� ���� �� ���� ũ�� N, ������ ���� M�� �־�����.

��° �ٺ��� N���� �ٿ� ������ ĭ�� ����ִ� ����� ������ 1�� ����� N�� ����� ������� �־�����.
�� �࿡ ���� ������ 1������ N������ ������� �־�����.
�Է����� �־����� ĭ�� ������ -1, 0, M������ �ڿ����θ� �̷���� �ִ�.

1 �� N �� 20
1 �� M �� 5

1. Input() : N, M, map[N][M], deque rainBow <int, int>

2. Solve()
	1) find_rainbowBlock() -> ������ ��� �� ������ �ִ� ��� ����
	2) find_large_block(int startX, int startY) -> BFS�� ����(������ ��Ϻ�)
		: �̵��ϴ� ĭ ������ tmpArr[5]�� �� -> color, size, rainbowCnt, oR, oC ������!
		: �� ��������Ϻ� ���� ū ����� deque dq�� ����(color, size, rainbowCnt, oR, oC)
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
int map[21][21];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

deque <pair <int, int>> r;

deque <pair <int, pair <pair <int, int>, pair <int, int>>>> dq;

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void print() {
	cout << "������ ��� �׷�" << endl;
	for (int i = 0; i < r.size(); i++) {
		cout << r[i].first << ", " << r[i].second << endl;
	}
	cout << endl;
}

bool compare(pair <int, pair <pair <int, int>, pair <int, int>>> a, pair <int, pair <pair <int, int>, pair <int, int>>> b) {
	if (a.second.first.first == b.second.first.first) {
		if (a.second.first.second == b.second.first.second) {
			if (a.second.second.first == b.second.second.first) {
				return a.second.second.second > b.second.second.second;
			}
			return a.second.second.first > b.second.second.first;
		}
		return a.second.first.second > b.second.first.second;
	}
	return a.second.first.first > b.second.first.first;
}

bool inRange(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < N) return true;
	else return false;
}

void rotate_map() {
	int copyMap[21][21];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = copyMap[j][N - 1 - i];
		}
	}
}

void remove_map() {
	int startR = -1;
	for (int c = 0; c < N; c++) {
		startR = -1;
		for (int r = N - 1; r >= 0; r--) {
			if (startR == -1 && map[r][c] == M + 1) startR = r;
			else if (map[r][c] == -1) {
				if (r > 0 && map[r - 1][c] == M + 1) startR = r - 1;
				else startR = -1;
			}
			else if (startR != -1 && map[r][c] < M) {
				map[startR][c] = map[r][c];
				map[r][c] = M + 1;
				startR--;
			}
		}
	}
}

void remove_block(int color, int startX, int startY) {
	queue <pair <int, int>> q;
	int visited[21][21] = { 0, };
	int nextX, nextY;
	q.push(make_pair(startX, startY));
	visited[startX][startY] = 1;
	map[startX][startY] = M + 1;

	while(!q.empty()) {
		startX = q.front().first;
		startY = q.front().second;
		q.pop();
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (!inRange(nextX, nextY)) continue;

			if (map[nextX][nextY] == color && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				map[nextX][nextY] = M + 1;
				q.push(make_pair(nextX, nextY));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				map[nextX][nextY] = M + 1;
				q.push(make_pair(nextX, nextY));
			}
		}
	}
}

void find_large_block(int startX, int startY) {
	int nextX, nextY;
	int color, size, rainbowCnt, oR, oC;
	int visited[51][51] = { 0, };
	int tmpArr[5] = { 0, };
	queue <pair <int, int>> q1;
	queue <pair <int, int>> q2;

	//1. rainbowBlock Ž�� -> q2�� ����
	visited[startX][startY] = 1;
	q1.push(make_pair(startX, startY));
	q2.push(make_pair(startX, startY));

	while (!q1.empty()) {
		startX = q1.front().first;
		startY = q1.front().second;
		q1.pop();
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (!inRange(nextX, nextY)) continue;
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				q1.push(make_pair(nextX, nextY));
				q2.push(make_pair(nextX, nextY));
			}
		}
	}

	for (color = 1; color <= M; color++) {
		q1 = q2;
		size = q2.size();
		rainbowCnt = q2.size();
		oR = 21;
		oC = 21;

		while (!q1.empty()) {
			startX = q1.front().first;
			startY = q1.front().second;
			q1.pop();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!inRange(nextX, nextY)) continue;
				else if (map[nextX][nextY] == color && visited[nextX][nextY] == 0) {
					size++;
					visited[nextX][nextY] = 1;
					q1.push(make_pair(nextX, nextY));
					if (oR > nextX) {
						oR = nextX;
						oC = nextY;
					}
					else if (oR == nextX && oC > nextY) {
						oC = nextY;
					}
				}
				else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
					size++;
					rainbowCnt++;
					visited[nextX][nextY] = 1;
					q1.push(make_pair(nextX, nextY));
				}
			}
		}
		if (size == rainbowCnt || size < 2) continue;

		if (tmpArr[1] < size) {
			tmpArr[0] = color;
			tmpArr[1] = size;
			tmpArr[2] = rainbowCnt;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] < rainbowCnt) {
			tmpArr[0] = color;
			tmpArr[2] = rainbowCnt;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] == rainbowCnt && tmpArr[3] < oR) {
			tmpArr[0] = color;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] == rainbowCnt && tmpArr[3] == oR && tmpArr[4] < oC) {
			tmpArr[0] = color;
			tmpArr[4] = oC;
		}

	}
	//cout << "�ش� ������ ��Ͽ��� ���� ū ���" << endl;
	//cout << "�÷�: " << tmpArr[0] << ", ũ��: " << tmpArr[1] << ", ��������ϼ�: " << tmpArr[2] << ", ���غ��: (" << tmpArr[3] << ", " << tmpArr[4] << ')' << endl;
	if (tmpArr[0] == 0) return;
	dq.push_back(make_pair(tmpArr[0], make_pair(make_pair(tmpArr[1], tmpArr[2]), make_pair(tmpArr[3], tmpArr[4]))));
}

void find_rainbowBlock() { 
	//�����ִ� ������ ��� ����
	int visited[21][21] = { 0, };
	int size = r.size();
	int startX, startY, nextX, nextY;

	queue <pair <int, int>> q;

	for (int i = 0; i < size; i++) {
		startX = r.front().first;
		startY = r.front().second;
		r.pop_front();
		if (visited[startX][startY] == 1) continue;

		r.push_back(make_pair(startX, startY));
		visited[startX][startY] = 1;
		q.push(make_pair(startX, startY));

		while (!q.empty()) {
			startX = q.front().first;
			startY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!inRange(nextX, nextY)) continue;
				if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
					visited[nextX][nextY] = 1;
					q.push(make_pair(nextX, nextY));
				}
			}
		}
	}

}

void find_rainbow() {
	while (!r.empty()) r.pop_front();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) r.push_back(make_pair(i, j));
		}
	}
}

void Solution() {
	int time = 0, score = 0;
	/*
	find_rainbowBlock();
	print();
	while (!r.empty()) {
		//cout << "��������� Ž��: (" << r.front().first << ", " << r.front().second <<')' << endl;
		find_large_block(r.front().first, r.front().second);
		r.pop_front();
		//cout << endl;
	}
	sort(dq.begin(), dq.end(), compare);
	remove_block(dq.front().first, dq.front().second.second.first, dq.front().second.second.second);
	score += (dq.front().second.first.first * dq.front().second.first.first);
	while (!dq.empty()) dq.pop_front();
	
	cout << score << endl;
	print_map();
	*/
	//cout << "���� ū ���" << endl;
	//cout << "�÷�: " << dq.front().first << ", ������: " << dq.front().second.first.first << ", ��������ϼ�: " << dq.front().second.first.second << ", ���غ��: (" << dq.front().second.second.first << ", " << dq.front().second.second.second << ')' << endl;
	
	while (1) {
		if (time > 0) find_rainbow(); 
		find_rainbowBlock();
		while (!r.empty()) {
			find_large_block(r.front().first, r.front().second);
			r.pop_front();
		}
		if (dq.size() == 0) break;

		sort(dq.begin(), dq.end(), compare);
		remove_block(dq.front().first, dq.front().second.second.first, dq.front().second.second.second);
		score += (dq.front().second.first.first * dq.front().second.first.first);
		while (!dq.empty()) dq.pop_front();
		//print_map();
		remove_map();
		//print_map();
		rotate_map();
		//print_map();
		remove_map();
		print_map();
		cout << score << endl;
		time++;
	}
	
}

void Input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) r.push_back(make_pair(i, j));
		}
	}
}

int main(void) {
	Input();
	Solution();
	//print();
	//find_rainbowBlock();
	//print();
	return 0;
}