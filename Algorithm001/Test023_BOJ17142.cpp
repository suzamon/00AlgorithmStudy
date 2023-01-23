/*
인체에 치명적인 바이러스를 연구하던 연구소에 승원이가 침입했고, 바이러스를 유출하려고 한다.
바이러스는 활성 상태와 비활성 상태가 있다. 가장 처음에 모든 바이러스는 비활성 상태이고,
활성 상태인 바이러스는 상하좌우로 인접한 모든 빈 칸으로 동시에 복제되며, 1초가 걸린다.
승원이는 연구소의 바이러스 M개를 활성 상태로 변경하려고 한다.

연구소는 크기가 N×N인 정사각형으로 나타낼 수 있으며, 정사각형은 1×1 크기의 정사각형으로 나누어져 있다.
연구소는 빈 칸, 벽, 바이러스로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다.
활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.

연구소의 상태가 주어졌을 때, 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간을 구해보자.

입력
첫째 줄에 연구소의 크기 N(4 ≤ N ≤ 50), 놓을 수 있는 바이러스의 개수 M(1 ≤ M ≤ 10)이 주어진다.
둘째 줄부터 N개의 줄에 연구소의 상태가 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치이다.
2의 개수는 M보다 크거나 같고, 10보다 작거나 같은 자연수이다.

출력
연구소의 모든 빈 칸에 바이러스가 있게 되는 최소 시간을 출력한다.
바이러스를 어떻게 놓아도 모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우에는 -1을 출력한다.

N, M, virusSize, emptyPlace, Answer = -1
int map[51][51], copyMap[51][51];
int dx[4], dy[4], arr[11][2]
deque <pair <int, int>> v

1. Input() : N, M, map[N][N], v, virusSize, emptyPlace = N*N - map[i][j] != 1인곳

2. Solve() :
	1) for(int i=0; i<=virusSize - M; i++)
	2) arr[0]에 v[i] 넣고 choose_virus(1)
	3) void choose_virus(int startIdx, int cnt)
		3-1) cnt == M이면 copy_map() 함수 실행 후, sim_virus() 수행
		3-2) for(int idx = startidx; idx <virusSize; idx++) 반복하면서 arr에 넣은 후 DFS
	4) void copy_map() : 단순 맵 복사
	5) void sim_virus()
		5-1) int copyEmpty = emptyPlace, int maxTime = 0;
		5-2 int visited[51][51] = {0, }, queue <pair <int, pair<int, int>>> q;
		5-2) for(int i=0; i<M; i++) 반복하면서 queue에 넣음 & copyEmpty--
		5-3) BFS로 탐색 시작 (d=0~4 까지 탐색하면서 copyMap[nX][nY] == 0이면 시간 map에 표시)
		5-4) queue에 넣을 때 maxTime과 비교해서 크면 갱신
		5-4) 끝난 후 emptyPalce = 0일 경우에 Answer과 비교 (-1이면 갱신 아니면, 작은값)
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