/*
0'49''50'''
마법사 상어는 파이어볼, 토네이도, 파이어스톰, 물복사버그 마법을 할 수 있다. 오늘 새로 배운 마법은 비바라기이다.
비바라기를 시전하면 하늘에 비구름을 만들 수 있다. 오늘은 비바라기를 크기가 N×N인 격자에서 연습하려고 한다.
격자의 각 칸에는 바구니가 하나 있고, 바구니는 칸 전체를 차지한다. 바구니에 저장할 수 있는 물의 양에는 제한이 없다.
(r, c)는 격자의 r행 c열에 있는 바구니를 의미하고, A[r][c]는 (r, c)에 있는 바구니에 저장되어 있는 물의 양을 의미한다.

격자의 가장 왼쪽 윗 칸은 (1, 1)이고, 가장 오른쪽 아랫 칸은 (N, N)이다.
마법사 상어는 연습을 위해 1번 행과 N번 행을 연결했고, 1번 열과 N번 열도 연결했다.
즉, N번 행의 아래에는 1번 행이, 1번 행의 위에는 N번 행이 있고,
1번 열의 왼쪽에는 N번 열이, N번 열의 오른쪽에는 1번 열이 있다.

비바라기를 시전하면 (N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름이 생긴다. 구름은 칸 전체를 차지한다.
이제 구름에 이동을 M번 명령하려고 한다. i번째 이동 명령은 방향 di과 거리 si로 이루어져 있다.
방향은 총 8개의 방향이 있으며, 8개의 정수로 표현한다. 1부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 이다.
이동을 명령하면 다음이 순서대로 진행된다.

1. 모든 구름이 di 방향으로 si칸 이동한다.
2. 각 구름에서 비가 내려 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가한다.
3. 구름이 모두 사라진다.
4. 2에서 물이 증가한 칸 (r, c)에 물복사버그 마법을 시전한다. 물복사버그 마법을 사용하면,
   대각선 방향으로 거리가 1인 칸에 물이 있는 바구니의 수만큼 (r, c)에 있는 바구니의 물이 양이 증가한다.
	- 이때는 이동과 다르게 경계를 넘어가는 칸은 대각선 방향으로 거리가 1인 칸이 아니다.
	- 예를 들어, (N, 2)에서 인접한 대각선 칸은 (N-1, 1), (N-1, 3)이고, (N, N)에서 인접한 대각선 칸은 (N-1, N-1)뿐이다.
5 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 물의 양이 2 줄어든다.
   이때 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 한다.

M번의 이동이 모두 끝난 후 바구니에 들어있는 물의 양의 합을 구해보자.

입력
첫째 줄에 N, M이 주어진다.
둘째 줄부터 N개의 줄에는 N개의 정수가 주어진다. r번째 행의 c번째 정수는 A[r][c]를 의미한다.
다음 M개의 줄에는 이동의 정보 di, si가 순서대로 한 줄에 하나씩 주어진다.

출력
첫째 줄에 M번의 이동이 모두 끝난 후 바구니에 들어있는 물의 양의 합을 출력한다.

제한
2 ≤ N ≤ 50
1 ≤ M ≤ 100
0 ≤ A[r][c] ≤ 100
1 ≤ di ≤ 8
1 ≤ si ≤ 50

N, M, map[101][101], command[101][2]
struct Cloud{ int x, int y}
struct IncreaseCloud{ int x, int y, int cnt}
deque <Cloud> dc
deque <Cloud> removeDc;
int dx[9], dy[9] ( 1부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 이다. )

1. Input()
	N, M, map[N][M], command[M][2]

2. Solution()
	1) (N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름 추가
	2) for(time=1; time <M; time++)
	3) move_cloud(int d, int s) -> sX, sY, nX, nY
		1) for(int i=0; i<dc.size();i++)
		2) sX = dc[i].x, sY = dc[i].y;
		3) nX = sX + dx[d] * s, nY = sY + dx[d] * s;
		4) if(nX >N){ while(1) {nX = nX -N; if(nX <= N && nX >0) break;}}
		5) else if(nX < 1) { while(1) {nX = nX +N; if(nX <= N && nX >0) break;}}
		6) if(nY >N){ while(1) (nY = nY - N; if((nY <=N && (nY >0) break;}}
		7) else if(nY < 1){ while(1) (nY = nY + N; if((nY <=N && (nY >0) break;}}
		8) dc[i].x= nX, dc[i].y =nY;
	4) inc_water()
		1) int tmpSize = dc.size(), Cloud tmpC;
		2) for(int i=0; i<tmpSize;i++)
		3) tmpC = dc.front(); dc.pop_front();
		4) map[tmpC.x][tmpC.y]++;
		5) visited[tmpC.x][tmpC.y] = 1;
		6) removeDc.push_back(tmpC);
	5) magic_water() -> sX, sY, nX, nY, tmpCnt, deque <IncreaseCloud> dq;
		1) for(int i=0; i<removeDc.size();i++){
		2) tmpCnt = 0;
		2) sX = removeDc[i].x, sY = removeDc[i].y
		3) for(int d=2; d<=8; d+=2) {
		4)  nX = sX + dx[d], nY = sY + dx[d];
		5) if(!inRange(nX, nY)) continue;
		6) if(map[nX][nY] > 0) tmpCnt++;
		7) }
		8) dq.push_back({sX, sY, tmpCnt});
		9)}
		10) while(!dq.empty()) map[dq.front().x][dq.front().y] = map[dq.front().x][dq.front().y] + dq.front().cnt;
		11) dq.pop_front()
	6) make_cloud()
		1) for(int xx=1; xx<=N; xx++) for(int yy=1; yy<=N; yy++)
		2) if(map[xx][yy]>=2 && visited[xx][yy] ==0) dc.push_back({xx, yy}), visited[xx][yy] =1, map[xx][yy] -=2;
		3) while(!removeDc.empty()) visited[removeD.front().x][removeD.front().y] = 0 && removeD.pop_fronr()
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
int map[51][51], visited[51][51] = { 0, }, command[101][2];

struct Cloud {
	int x, y;
	Cloud(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct IncCloud {
	int x, y, cnt;
	IncCloud(int x, int y, int cnt) {
		this->x = x;
		this->y = y;
		this->cnt = cnt;
	}
};

deque <Cloud> dc;
deque <Cloud> removeDc;

int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

bool inRange(int xx, int yy) {
	if (xx<1 || xx>N || yy<1 || yy>N) return false;
	return true;
}

void print_info() {
	cout << "살아있는 구름" << endl;
	if (dc.size() > 0) {
		for (int i = 0; i < dc.size(); i++) {
			cout << '(' << dc[i].x << ", " << dc[i].y << ")에 구름 존재" << endl;
		}
	}
	else {
		cout << "없음" << endl;
	}

	cout << "사라진 구름" << endl;
	if (removeDc.size() > 0) {
		for (int i = 0; i < removeDc.size(); i++) {
			cout << '(' << removeDc[i].x << ", " << removeDc[i].y << ")에 사라진 구름 존재" << endl;
		}
	}
	else {
		cout << "없음" << endl;
	}

	cout << "맵 정보" << endl;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			cout << map[xx][yy] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	Answer = 0;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] >= 1) Answer = Answer + map[xx][yy];
		}
	}
	cout << Answer << endl;
}

void make_cloud() {
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] >= 2 && visited[xx][yy] == 0) {
				dc.push_back({ xx, yy });
				map[xx][yy] = map[xx][yy] - 2;
			}
		}
	}

	while (!removeDc.empty()) {
		visited[removeDc.front().x][removeDc.front().y] = 0;
		removeDc.pop_front();
	}
}

void magic_water() {
	int sX, sY, nX, nY, tmpCnt;

	deque <IncCloud> dq;
	for (int i = 0; i < removeDc.size(); i++) {
		tmpCnt = 0;
		sX = removeDc[i].x, sY = removeDc[i].y;
		for (int d = 2; d <= 8; d += 2) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY)) continue;

			if (map[nX][nY] > 0) tmpCnt++;
		}
		dq.push_back({ sX, sY, tmpCnt});
	}

	while (!dq.empty()) {
		map[dq.front().x][dq.front().y] = map[dq.front().x][dq.front().y] + dq.front().cnt;
		dq.pop_front();
	}
}

void inc_water() {
	int tmpSize = dc.size();
	Cloud tmpC = { 0, 0 };

	for (int i = 0; i < tmpSize; i++) {
		tmpC = dc.front(); 
		dc.pop_front();
		map[tmpC.x][tmpC.y]++;
		visited[tmpC.x][tmpC.y] = 1;
		removeDc.push_back(tmpC);
	}
}

void move_cloud(int d, int s) {
	int sX, sY, nX, nY;

	for (int i = 0; i < dc.size(); i++) {
		sX = dc[i].x, sY = dc[i].y;
		nX = sX + dx[d] * s, nY = sY + dy[d] * s;

		if (nX > N) { 
			while (1) { 
				nX = nX - N; 
				if (nX <= N && nX > 0) break; 
			} 
		}
		else if (nX < 1) {
			while (1) {
				nX = nX + N;
				if (nX <= N && nX > 0) break; 
			} 
		}

		if (nY > N) {
			while (1) {
				nY = nY - N;
				if (nY <= N && nY > 0) break;
			}
		}
		else if (nY < 1) {
			while (1) {
				nY = nY + N;
				if (nY <= N && nY > 0) break;
			}
		}

		dc[i].x = nX, dc[i].y = nY;
	}
}

void Solution() {
	int time;
	for (time = 0; time < M; time++) {
		move_cloud(command[time][0], command[time][1]);
		//print_info();
		inc_water();
		//print_info();
		magic_water();
		//print_info();
		make_cloud();
		//print_info();
	}

	find_answer();
}

void Input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> command[i][0] >> command[i][1];
	}

	dc.push_back({ N, 1 });
	dc.push_back({ N, 2 });
	dc.push_back({ N-1, 1 });
	dc.push_back({ N-1, 2 });
}

int main(void) {
	Input();
	Solution();
	return 0;
}