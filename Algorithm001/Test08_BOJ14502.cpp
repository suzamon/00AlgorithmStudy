/*
����
��ü�� ġ������ ���̷����� �����ϴ� �����ҿ��� ���̷����� ����Ǿ���.
������ ���̷����� ���� ������ �ʾҰ�, ���̷����� Ȯ���� ���� ���ؼ� �����ҿ� ���� ������� �Ѵ�.

�����Ҵ� ũ�Ⱑ N��M�� ���簢������ ��Ÿ�� �� ������, ���簢���� 1��1 ũ���� ���簢������ �������� �ִ�.
�����Ҵ� �� ĭ, ������ �̷���� ������, ���� ĭ �ϳ��� ���� �����Ѵ�.

�Ϻ� ĭ�� ���̷����� �����ϸ�, �� ���̷����� �����¿�� ������ �� ĭ���� ��� �������� �� �ִ�.
���� ���� �� �ִ� ���� ������ 3���̸�, �� 3���� ������ �Ѵ�.

���� ���, �Ʒ��� ���� �����Ұ� ���� ��츦 ���캸��.

2 0 0 0 1 1 0
0 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 0 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0
�̶�, 0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ���̴�.
�ƹ��� ���� ������ �ʴ´ٸ�, ���̷����� ��� �� ĭ���� �������� �� �ִ�.

2�� 1��, 1�� 2��, 4�� 6���� ���� ����ٸ� ������ ����� �Ʒ��� �������� �ȴ�.

2 1 0 0 1 1 0
1 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 1 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0

���̷����� ���� ���� ����� �Ʒ��� ��������.

2 1 0 0 1 1 2
1 0 1 0 1 2 2
0 1 1 0 1 2 2
0 1 0 0 0 1 2
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0
���� 3�� ���� ��, ���̷����� ���� �� ���� ���� ���� �����̶�� �Ѵ�. ���� �������� ���� ������ ũ��� 27�̴�.

�������� ������ �־����� �� ���� �� �ִ� ���� ���� ũ���� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 8)
��° �ٺ��� N���� �ٿ� ������ ����� �־�����.
0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ��ġ�̴�. 2�� ������ 2���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.
�� ĭ�� ������ 3�� �̻��̴�.

���
ù° �ٿ� ���� �� �ִ� ���� ������ �ִ� ũ�⸦ ����Ѵ�.

N, M, Answer = 0;
int map[9][9], copyMap[9][9];
deque <pair <int, int>> emptyPos;
int wallIdx[3];
int dx[4], dy[4] -> ��, ��, ��, ��


Input()
	N, M, map[N][M], emptyPos
Solution()
	if(emptyPos.size()==3) return;
	for(int i=0; i<emptyPos.size() - 2; i++){
	wallIdx[0] = i;
	DFS(i+1, 1);
	}

void DFS(int sIdx, int cnt){
	if(cnt==3) {
	copy_map();
	for(int i=0; i<3; i++){
	copyMap[emptyPos[wallIdx[i]].first][emptyPos[wallIdx[i]].second] = 1;
	}
	simulation();
	return;
	}
	for(int i = sIdx; i < emptyPos.size(); i++){
	wallIdx[cnt] = i;
	DFS(i+1, cnt + 1);
	}
}

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
int map[9][9], copyMap[9][9];
deque <pair <int, int>> emptyPos;
deque <pair <int, int>> virusPos;
deque <pair <int, int>> wallPos;

int wallIdx[3];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_map() {
	cout << emptyPos.size() << endl;
	cout << "Answer: " << Answer << endl;
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << copyMap[i][j]<< ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int yy) {
	if (xx < 0 || xx >= N || yy < 0 || yy >= M) return false;
	return true;
}

int simulation() {
	int retCnt = 0, sX, sY, nX, nY;
	queue <pair <int, int>> q;
	for (int i = 0; i < virusPos.size(); i++) {
		retCnt++;
		q.push(make_pair(virusPos[i].first, virusPos[i].second));
		while (!q.empty()) {
			sX = q.front().first, sY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nX = sX + dx[d], nY = sY + dy[d];
				if (!inRange(nX, nY)) continue;
				if (copyMap[nX][nY] == 0) {
					copyMap[nX][nY] = 2;
					retCnt++;
					q.push(make_pair(nX, nY));
				}
			}
		}
	}
	return retCnt;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void DFS(int sIdx, int cnt) {
	if (cnt == 3) {
		copy_map();
		for (int i = 0; i < 3; i++) {
			copyMap[emptyPos[wallIdx[i]].first][emptyPos[wallIdx[i]].second] = 1;
		}
		int emptyCnt = emptyPos.size() - 3 + virusPos.size();
		int virusCnt = simulation();
		emptyCnt = emptyCnt - virusCnt;
		if (Answer < emptyCnt) {
			Answer = emptyCnt;
			//if (Answer == 25) print_map();
		}
		return;
	}
	for (int i = sIdx; i < emptyPos.size(); i++) {
		wallIdx[cnt] = i;
		DFS(i + 1, cnt + 1);
	}
}

void Solution() {
	if (emptyPos.size() == 3) return;
	for (int i = 0; i < emptyPos.size() - 2; i++) {
		wallIdx[0] = i;
		DFS(i + 1, 1);
	}

}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) emptyPos.push_back(make_pair(i, j));
			else if(map[i][j] == 2) virusPos.push_back(make_pair(i, j));
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}