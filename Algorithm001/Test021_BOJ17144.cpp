/*
미세먼지를 제거하기 위해 구사과는 공기청정기를 설치하려고 한다.
공기청정기의 성능을 테스트하기 위해 구사과는 집을 크기가 R×C인 격자판으로 나타냈고, 1×1 크기의 칸으로 나눴다.
구사과는 뛰어난 코딩 실력을 이용해 각 칸 (r, c)에 있는 미세먼지의 양을 실시간으로 모니터링하는 시스템을 개발했다.
(r, c)는 r행 c열을 의미한다.

공기청정기는 항상 1번 열에 설치되어 있고, 크기는 두 행을 차지한다. 공기청정기가 설치되어 있지 않은 칸에는 미세먼지가 있고,
(r, c)에 있는 미세먼지의 양은 Ar,c이다.

1초 동안 아래 적힌 일이 순서대로 일어난다.

1. 미세먼지가 확산된다. 확산은 미세먼지가 있는 모든 칸에서 동시에 일어난다.
	(r, c)에 있는 미세먼지는 인접한 네 방향으로 확산된다.
	인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
	확산되는 양은 Ar,c/5이고 소수점은 버린다.
	(r, c)에 남은 미세먼지의 양은 Ar,c - (Ar,c/5)×(확산된 방향의 개수) 이다.

2. 공기청정기가 작동한다.
	공기청정기에서는 바람이 나온다.
	위쪽 공기청정기의 바람은 반시계방향으로 순환하고, 아래쪽 공기청정기의 바람은 시계방향으로 순환한다.
	바람이 불면 미세먼지가 바람의 방향대로 모두 한 칸씩 이동한다.
	공기청정기에서 부는 바람은 미세먼지가 없는 바람이고, 공기청정기로 들어간 미세먼지는 모두 정화된다.

공기청정기의 바람은 다음과 같은 방향으로 순환한다.
방의 정보가 주어졌을 때, T초가 지난 후 구사과의 방에 남아있는 미세먼지의 양을 구해보자.

입력
첫째 줄에 R, C, T (6 ≤ R, C ≤ 50, 1 ≤ T ≤ 1,000) 가 주어진다.
둘째 줄부터 R개의 줄에 Ar,c (-1 ≤ Ar,c ≤ 1,000)가 주어진다. 공기청정기가 설치된 곳은 Ar,c가 -1이고,
나머지 값은 미세먼지의 양이다. -1은 2번 위아래로 붙어져 있고, 가장 윗 행, 아랫 행과 두 칸이상 떨어져 있다.

출력
첫째 줄에 T초가 지난 후 구사과 방에 남아있는 미세먼지의 양을 출력한다.

R, C, T, map[51][51], int airCondi[2][2];
deque <pair <int, pair<int, int>>> add;

1. Input()
	R, C, T, map[R][C], dq, airCondi[2][2];

2. Solution() ; 0~T만큼 1~2 반복
	1) spread_air()
		1-1) for(int xx=0; xx<R; xx++), for(int yy=0; yy<C; yy++)
		1-2) map[xx][yy] >= 5이면, 확산 시작
		1-3) d=0~4까지 확산할 수 있는 미세먼지 찾기 & cnt에 저장
		1-4) add에 확산하는 미세먼지 크기, x, y 저장
		1-5) map[x][y]/5 * cnt만큼 map[x][y]에 빼기
		1-6) 1-1~5) 까지 반복해서 구한 add 돌면서 map에 갱신
	2) oprate_airCondi()
		2-1) 공청기 동작하는 것 구현
	3) find_answer()
		3-1) for(int xx=0; xx<R; xx++), for(int yy=0; yy<C; yy++) 탐색하면서 미세먼지 총합 구하기
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int R, C, T, Answer = 0;
int map[51][51] = { 0, }, airCondi[2][2];

deque <pair <int, pair<int, int>>> add;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print_map() {
	cout << "map" << endl;
	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			cout << map[xx][yy] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void spread_air() {
	int cnt, airSize, nX, nY;

	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			if (map[xx][yy] >= 5) {
				cnt = 0;
				airSize = map[xx][yy] / 5;

				for (int d = 0; d < 4; d++) {
					nX = xx + dx[d];
					nY = yy + dy[d];
					if (nX < 0 || nX >= R || nY < 0 || nY >= C) continue;
					if (map[nX][nY] == -1) continue;

					add.push_back(make_pair(airSize, make_pair(nX, nY)));
					cnt++;
				}

				map[xx][yy] = map[xx][yy] - (cnt * airSize);
			}
		}
	}

	while (!add.empty()) {
		map[add.front().second.first][add.front().second.second] = map[add.front().second.first][add.front().second.second] + add.front().first;
		add.pop_front();
	}
}

void oprate_airCondi() {
	int sX, sY, nX, nY, xx, yy;

	queue <int> q;

	sX = airCondi[0][0];
	sY = airCondi[0][1];
	
	q.push(map[sX][sY + 1]);
	map[sX][sY + 1] = 0;
	xx = sX;
	for (yy = sY + 2; yy < C; yy++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = C - 1;
	for (xx = sX - 1; xx >= 0; xx--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	xx = 0;
	for (yy = C - 2; yy >= 0; yy--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = sY;
	for (xx = 1; xx < sX; xx++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	q.pop();

	sX = airCondi[1][0];
	sY = airCondi[1][1];

	q.push(map[sX][sY + 1]);
	map[sX][sY + 1] = 0;
	xx = sX;
	for (yy = sY + 2; yy < C; yy++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = C - 1;
	for (xx = sX + 1; xx < R; xx++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	xx = R - 1;
	for (yy = C - 2; yy >= 0; yy--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = sY;
	for (xx = R - 2; xx > sX; xx--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	q.pop();
}

void find_answer() {
	Answer = 0;
	
	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			if (map[xx][yy] > 0) Answer = Answer + map[xx][yy];
		}
	}
}

void Solution() {
	for (int time = 0; time < T; time++) {
		spread_air();
		oprate_airCondi();
	}
	find_answer();
	cout << Answer << endl;
}

void Input() {
	int idx = 0;
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				airCondi[idx][0] = i;
				airCondi[idx][1] = j;
				idx++;
			}
		}
	}
}

int main(void) {
	Input();
	Solution();
	//spread_air();
	//print_map();
	//oprate_airCondi();
	//print_map();
	return 0;
}