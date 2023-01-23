/*
��ü�� ġ������ ���̷����� �����ϴ� �����ҿ� �¿��̰� ħ���߰�, ���̷����� �����Ϸ��� �Ѵ�.
���̷����� Ȱ�� ���¿� ��Ȱ�� ���°� �ִ�. ���� ó���� ��� ���̷����� ��Ȱ�� �����̰�,
Ȱ�� ������ ���̷����� �����¿�� ������ ��� �� ĭ���� ���ÿ� �����Ǹ�, 1�ʰ� �ɸ���.
�¿��̴� �������� ���̷��� M���� Ȱ�� ���·� �����Ϸ��� �Ѵ�.

�����Ҵ� ũ�Ⱑ N��N�� ���簢������ ��Ÿ�� �� ������, ���簢���� 1��1 ũ���� ���簢������ �������� �ִ�.
�����Ҵ� �� ĭ, ��, ���̷����� �̷���� ������, ���� ĭ �ϳ��� ���� �����Ѵ�.
Ȱ�� ���̷����� ��Ȱ�� ���̷����� �ִ� ĭ���� ���� ��Ȱ�� ���̷����� Ȱ������ ���Ѵ�.

�������� ���°� �־����� ��, ��� �� ĭ�� ���̷����� �۶߸��� �ּ� �ð��� ���غ���.

�Է�
ù° �ٿ� �������� ũ�� N(4 �� N �� 50), ���� �� �ִ� ���̷����� ���� M(1 �� M �� 10)�� �־�����.
��° �ٺ��� N���� �ٿ� �������� ���°� �־�����. 0�� �� ĭ, 1�� ��, 2�� ���̷����� ���� �� �ִ� ��ġ�̴�.
2�� ������ M���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.

���
�������� ��� �� ĭ�� ���̷����� �ְ� �Ǵ� �ּ� �ð��� ����Ѵ�.
���̷����� ��� ���Ƶ� ��� �� ĭ�� ���̷����� �۶߸� �� ���� ��쿡�� -1�� ����Ѵ�.

N, M, virusSize, emptyPlace, Answer = -1
int map[51][51], copyMap[51][51];
int dx[4], dy[4], arr[11][2]
deque <pair <int, int>> v

1. Input() : N, M, map[N][N], v, virusSize, emptyPlace = N*N - map[i][j] != 1�ΰ�

2. Solve() :
	1) for(int i=0; i<=virusSize - M; i++)
	2) arr[0]�� v[i] �ְ� choose_virus(1)
	3) void choose_virus(int startIdx, int cnt)
		3-1) cnt == M�̸� copy_map() �Լ� ���� ��, sim_virus() ����
		3-2) for(int idx = startidx; idx <virusSize; idx++) �ݺ��ϸ鼭 arr�� ���� �� DFS
	4) void copy_map() : �ܼ� �� ����
	5) void sim_virus()
		5-1) int copyEmpty = emptyPlace, int maxTime = 0;
		5-2 int visited[51][51] = {0, }, queue <pair <int, pair<int, int>>> q;
		5-2) for(int i=0; i<M; i++) �ݺ��ϸ鼭 queue�� ���� & copyEmpty--
		5-3) BFS�� Ž�� ���� (d=0~4 ���� Ž���ϸ鼭 copyMap[nX][nY] == 0�̸� �ð� map�� ǥ��)
		5-4) queue�� ���� �� maxTime�� ���ؼ� ũ�� ����
		5-4) ���� �� emptyPalce = 0�� ��쿡 Answer�� �� (-1�̸� ���� �ƴϸ�, ������)
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, virusSize, emptyPlace = 0, Answer = -1;
int map[51][51] = { 0, };
int copyMap[51][51] = { 0, };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int arr[11][2] = { 0, };

deque <pair<int, int>> v;

void print_copy_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void sim_virus() {
	int copyEmpty = emptyPlace;
	int maxTime = 0;
	queue <pair <int, pair <int, int>>> q;

	for (int i = 0; i < M; i++) {
		copyMap[arr[i][0]][arr[i][1]] = 2;
		q.push(make_pair(2, make_pair(arr[i][0], arr[i][1])));
	}

	int sX, sY, sT, nX, nY, nT;

	while (!q.empty()) {
		sT = q.front().first;
		sX = q.front().second.first;
		sY = q.front().second.second;
		q.pop();

		if (Answer != -1 && (sT - 2) > Answer && copyEmpty > 0) break;
		if (copyEmpty == 0) break;

		for (int d = 0; d < 4; d++) {
			nX = sX + dx[d];
			nY = sY + dy[d];
			nT = sT + 1;
			if (nX < 0 || nX >= N || nY < 0 || nY >= N) continue;

			if (copyMap[nX][nY] == 0) {
				copyMap[nX][nY] = nT;
				copyEmpty--;
				q.push(make_pair(nT, make_pair(nX, nY)));
				if (nT - 2 > maxTime) maxTime = nT - 2;
			}
			else if (copyMap[nX][nY] == -1) {
				copyMap[nX][nY] = nT;
				q.push(make_pair(nT, make_pair(nX, nY)));
				if (nT - 2 > maxTime) maxTime = nT - 2;
			}
		}

	}
	
	if (copyEmpty != 0 && !q.empty()) {
		while (!q.empty()) q.pop();
		return;
	}

	//print_copy_map();
	if (copyEmpty == 0) {
		if (!q.empty()) {
			while (!q.empty()) q.pop();
		}
		if (Answer == -1) Answer = maxTime;
		else if (Answer > maxTime) Answer = maxTime;
	}
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void choose_virus(int startIdx, int cnt) {
	if (cnt == M) {
		copy_map();
		sim_virus();
		return;
	}

	for (int idx = startIdx; idx < virusSize; idx++) {
		arr[cnt][0] = v[idx].first;
		arr[cnt][1] = v[idx].second;
		choose_virus(idx + 1, cnt + 1);
	}

}

void Solution() {
	for (int i = 0; i <= virusSize - M; i++) {
		arr[0][0] = v[i].first;
		arr[0][1] = v[i].second;
		choose_virus(i + 1, 1);
	}
}

void Input() {
	cin >> N >> M;
	emptyPlace = N * N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				map[i][j] = -1;
				v.push_back(make_pair(i, j));
				emptyPlace--;
			}
			else if (map[i][j] == 1) emptyPlace--;
		}
	}
	virusSize = v.size();
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}