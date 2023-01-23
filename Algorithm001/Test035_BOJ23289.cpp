/*
3'00''....
문제
유난히 추운 날씨가 예상되는 이번 겨울을 대비하기 위해 구사과는 온풍기를 설치하려고 한다.
온풍기의 성능을 테스트하기 위해 구사과는 집을 크기가 R×C인 격자판으로 나타냈고, 1×1 크기의 칸으로 나눴다.
구사과는 뛰어난 코딩 실력을 이용해 각 칸 (r, c)의 온도를 실시간으로 모니터링하는 시스템을 개발했다.
(r, c)는 r행 c열을 의미한다.

구사과의 성능 테스트는 다음과 같은 작업이 순차적으로 이루어지며, 가장 처음에 모든 칸의 온도는 0이다.
문제의 그림에서 빈 칸은 온도가 0인 칸을 의미한다.

1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
2. 온도가 조절됨
3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
4. 초콜릿을 하나 먹는다.
5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고,
아니면 1부터 다시 시작한다.
집에 있는 모든 온풍기에서 바람이 한 번 나오는 과정을 설명하면 다음과 같다.



<그림 1>

<그림 1>은 크기가 7×8인 집에 온풍기가 (3, 1)에 설치되어 있는 상황이다.
온풍기는 바람이 나오는 방향이 있는데, 그 방향은 오른쪽, 왼쪽, 위, 아래 중 하나이다.
온풍기에서 따뜻한 바람이 한 번 나오면, 다음과 같은 영역의 온도가 칸에 적힌 값만큼 증가하게 된다.
아래 그림은 오른쪽 방향으로 바람이 나온 예시이며,
온풍기에서 바람이 나오는 방향에 따라
<그림 2>를 회전시켜서 해당하는 방향으로 바람이 나왔을 때 증가하는 온도를 구할 수 있다.



<그림 2>

온풍기에서 바람이 한 번 나왔을 때, 온풍기의 바람이 나오는 방향에 있는 칸은 항상 온도가 5도 올라간다.
그 다음 이 바람은 계속 다른 칸으로 이동해 다른 칸의 온도를 위의 그림과 같이 상승시키게 된다.
어떤 칸 (x, y)에 온풍기 바람이 도착해 온도가 k (> 1)만큼 상승했다면,
(x-1, y+1), (x, y+1), (x+1, y+1)의 온도도 k-1만큼 상승하게 된다.
이때 그 칸이 존재하지 않는다면, 바람은 이동하지 않는다. 온풍기에서 바람이 한 번 나왔을 때,
어떤 칸에 같은 온풍기에서 나온 바람이 여러 번 도착한다고 해도 온도는 여러번 상승하지 않는다.

<그림 1>의 상태에서 온풍기 바람이 한 번 불었다면, 증가하는 온도의 양은 <그림 3>과 같다.



<그림 3>

일부 칸과 칸 사이에는 벽이 있어 온풍기 바람이 지나갈 수 없다.
바람이 오른쪽으로 불었을 때 어떤 칸 (x, y)에서 (x-1, y+1)로 바람이 이동할 수 있으려면,
(x, y)와 (x-1, y) 사이에 벽이 없어야 하고, (x-1, y)와 (x-1, y+1) 사이에도 벽이 없어야 한다.
(x, y)에서 (x, y+1)로 바람이 이동할 수 있으려면 (x, y)와 (x, y+1) 사이에 벽이 없어야 한다.
마지막으로 (x, y)에서 (x+1, y+1)로 바람이 이동할 수 있으려면, (x, y)와 (x+1, y), (x+1, y)와 (x+1, y+1) 사이에 벽이 없어야 한다.

예를 들어, (3, 4)와 (3, 5) 사이에 벽이 있는 경우 온풍기에서 바람이 한 번 나왔을 때 온도는 <그림 4>와 같이 상승한다.
벽은 빨간색으로 표시했다.



<그림 4>

(3, 5)는 (3, 4), (2, 4), (4, 4)에서 바람이 이동할 수 없기 때문에, 온도가 상승하지 않는다.

만약 바람의 방향이 왼쪽인 온풍기가 (4, 7)에 있고, (3, 4)와 (3, 5) 사이에 벽,
(2, 5)와 (3, 5) 사이에 벽이 있는 경우라면 온풍기에서 바람이 한 번 나왔을 때 <그림 5>와 같이 온도가 상승한다.
<그림 6>은 바람의 방향이 아래인 온풍기가 (2, 5)에 있고,
(4, 4)와 (4, 5) 사이, (4, 4)와 (5, 4) 사이, (4, 6)과 (5, 6) 사이에 벽이 있는 경우이다.


<그림 5>	<그림 6>
구사과의 집에는 온풍기가 2대 이상 있을 수도 있다.
이 경우 각각의 온풍기에 의해서 상승한 온도를 모두 합한 값이 해당 칸의 상승한 온도이다.

예를 들어, <그림 7>은 <그림 6>과 같은 벽을 가지고 있는 집에서 바람이 방향이 위인 온풍기가 (7, 5)에 있는 경우이고,
<그림 8>는 <그림 6>과 같은 벽을 가지고 있는 집에서 바람의 방향이 아래인 온풍기가 (2, 5)에 있고,
바람의 방향이 위인 온풍기가 (7, 5)에 있는 경우이다.
<그림 8>는 같은 벽을 가지고 있는 집에서 <그림 6>의 온풍기와 <그림 7>의 온풍기가 동시에 설치된 상황이기 때문에,
각 칸의 상승한 온도는 두 그림의 값을 더한 값과 같다. 온풍기가 있는 칸도 다른 온풍기에 의해 온도가 상승할 수 있기 때문에,
 <그림 8>에서 온풍기의 위치는 표시하지 않았다.


<그림 7>	<그림 8>
온도가 조절되는 과정은 다음과 같다.

모든 인접한 칸에 대해서, 온도가 높은 칸에서 낮은 칸으로 ⌊(두 칸의 온도의 차이)/4⌋만큼 온도가 조절된다.
 온도가 높은 칸은 이 값만큼 온도가 감소하고, 낮은 칸은 온도가 상승한다.
인접한 두 칸 사이에 벽이 있는 경우에는 온도가 조절되지 않는다. 이 과정은 모든 칸에 대해서 동시에 발생한다.

다음은 온도 조절의 예시이다.



(1, 1)에서 (1, 2)와 (1, 3)으로 공기가 섞인다.



(2, 2)와 (3, 2) 사이에 벽이 있기 때문에, (3, 2)는 온도가 그대로 유지된다.



모든 칸에 대해서 동시에 온도의 조절이 발생한다.

가장 바깥쪽 칸은 1행, R행, 1열, C열에 있는 칸이다. 예를 들어, <그림 9>와 같은 경우 가장 바깥쪽 칸의 온도가 1씩 감소하면 <그림 10>과 같이 된다. 온도가 0인 칸은 온도가 감소하지 않는다.


<그림 9>	<그림 10>
방의 크기와 방에 설치된 온풍기의 정보, 벽의 위치와 조사하려고 하는 칸의 위치가 주어진다. 구사과가 먹은 초콜릿의 개수를 출력한다.

입력
첫째 줄에 세 정수 R, C, K가 주어진다. 둘째 줄부터 R개의 줄에 방의 정보가 주어진다.
i번째 줄의 j번째 정수는 (i, j)의 정보를 의미하며 다음 중 하나이다.

0: 빈 칸
1: 방향이 오른쪽인 온풍기가 있음
2: 방향이 왼쪽인 온풍기가 있음
3: 방향이 위인 온풍기가 있음
4: 방향이 아래인 온풍기가 있음
5: 온도를 조사해야 하는 칸
다음 줄에는 벽의 개수 W가 주어진다. 다음 W개의 줄에는 벽의 정보가 주어지며,
이 정보는 세 정수 x, y, t로 이루어져 있다. t가 0인 경우 (x, y)와 (x-1, y) 사이에 벽이 있는 것이고,
1인 경우에는 (x, y)와 (x, y+1) 사이에 벽이 있는 것이다.

출력
구사과가 먹는 초콜릿의 개수를 출력한다. 만약, 먹는 초콜릿의 개수가 100을 넘어가면 101을 출력한다.

제한
2 ≤ R, C ≤ 20
1 ≤ K ≤ 1,000
온풍기는 하나 이상 있고, 온도를 조사해야 하는 칸도 하나 이상 있다.
0 ≤ W ≤ R×C
1 < x ≤ R, 1 ≤ y ≤ C (t = 0)
1 ≤ x ≤ R, 1 ≤ y < C (t = 1)
온풍기가 있는 칸과 바람이 나오는 방향에 있는 칸 사이에는 벽이 없다.
온풍기의 바람이 나오는 방향에 있는 칸은 항상 존재한다.
같은 벽이 두 번 이상 주어지는 경우는 없다.

R, C, K, map[21][21], W,
wall[21][21][3] -> [1]값 '1'이면 (x, y)와 (x-1, y) 사이에 벽이 있는 것이고, [2] 값이 1인 경우에는 (x, y)와 (x, y+1) 사이 벽
struct Heater{ int x, y, dir};
struct AddAir{int x, y, cnt};
deque <pair <int, int>> check;
deque <Heater> h;
deque <AddAir> aa;
dx[5], dy[5] -> 1부터 →, ←, ↑, ↓
ddx[9], ddy[9] -> 1부터 ↗, →, ↘, ↓, ↙, ←, ↖, ↑

1. Input()
	R, C, K, map[R][C], W, wall[R][C][1~2], h.push({x, y, dir})

2. Soltion()
	1) time = 0;
	2) while(1)
	3) heater_operate()
		1) int sX, sY, nX, nY, d, dd[3];
		2) for(int i=0; i<h.size(); i++){
		3) sX = h[i].x, sY = h[i].y, d = h[i].dir;
		4) nX = sX + dx[d], dY = sY + dy[d];
		5) if(!inRange(nX, nY)) continue;
		4) find_add_pos(nX, nY, d);}
		6) while(!aa.empty) 에 맵에 증가한 공기 추가
	4) move_air()
		1) r: 1~R, c: 1~C까지 반복
		2) if(map[r][c] ==0) continue;
		3)

* find_add_pos(int sX, int sY, int d)
	1) int nX, nY, sCnt, nCnt, nDir, dd[3], visited[21][21] = {0, };
	2) if(d==1) dd[0,1,2] = 1,2,3 / if(d==2) dd[0,1,2] = 7,6,5 /
	   if(d==3) dd[0,1,2] = 7,8,1 /if(d==4) dd[0,1,2] = 3,4,5 /
	2) queue <AddAir> q;
	3) q.push({nX, nY, 5}), aa.push_back({nX, nY, 5});
	4) visited[nX][nY] = 1;
	5) while(!q.empty())
	6) sX = q.front().x, sY = q.front().y, sCnt = q.front().cnt;
	7) nCnt = sCnt -1;
	8) for(int i=0; i<3; i++)
	9) nDir = dd[i];
	10) nX= sX + ddx[nDir], nY = sY + ddy[nDir] & if(!inRange(nX, nY) || visited[nX][nY] ==1) continue;
	11) switch(nDir)
	11) case 1:
		if(d==1) {
		   if(wall[sX][sY][0] == 0 && wall[sX-1][sY][1] == 0 ) {
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt}) & visited[nX][nY] = 1;
		if(d==3){
		  if(wall[sX][sY][1] == 0 && wall[sX][sY + 1][0] == 0){
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt}) & visited[nX][nY] = 1;
		case 2:
		 if(wall[sX][sY][1] == 0) q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		case 3:
		if(d==1) {
		   if(wall[sX + 1][sY][0] == 0 && wall[sX + 1][sY][1] == 0 ) {
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		if(d==4){
		  if(wall[sX][sY][1] == 0 && wall[sX + 1][sY + 1][0] == 0){
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		case 4:
		if(wall[sX + 1][sY][0] == 0) q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		case 5:
		if(d==2) {
		   if(wall[sX + 1][sY][0] == 0 && wall[sX + 1][sY - 1][1] == 0 ) {
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		if(d==4){
		  if(wall[sX + 1][sY -1][0] == 0 && wall[sX][sY - 1][1] == 0){
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
	   case 6:
		if(wall[sX][sY-1][1] == 0) q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
	   case 7:
		if(d==2) {
		   if(wall[sX][sY][0] == 0 && wall[sX - 1][sY - 1][1] == 0 ) {
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
		if(d==3){
		  if(wall[sX][sY -1][0] == 0 && wall[sX][sY - 1][1] == 0){
			q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
	   case 8:
		if(wall[sX][sY][0] == 0) q.push({nX, nY, nCnt}) & aa.push({nX, nY, nCnt})
	12)


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int R, C, K, W, Answer = 0;
int map[21][21] = { 0, }, wall[21][21][2] = { 0, };

struct Heater {
	int x, y, dir;
	Heater(int x, int y, int dir) {
		this->x = x;
		this->y = y;
		this->dir = dir;
	}
};
struct AddAir {
	int x, y, cnt;
	AddAir(int x, int y, int cnt) {
		this->x = x;
		this->y = y;
		this->cnt = cnt;
	}
};

deque <pair <int, int>> check;
deque <Heater> h;
deque <AddAir> aa;

int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };

int ddx[9] = { 0, -1, 0, 1, 1, 1, 0, -1, -1 };
int ddy[9] = { 0, 1, 1, 1, 0, -1, -1, -1, 0 };

void print_info() {
	cout << "맵 정보" << endl;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int x, int y) {
	if (x <1 || x>R || y<1 || y>C) return false;
	return true;
}

void dec_air() {
	int r, c;
	r = 1;
	for (c = 1; c <= C; c++) if (map[r][c] > 0) map[r][c]--;
	r = R;
	for (c = 1; c <= C; c++) if (map[r][c] > 0) map[r][c]--;
	c = 1;
	for (r = 2; r <= R - 1; r++) if (map[r][c] > 0) map[r][c]--;
	c = C;
	for (r = 2; r <= R - 1; r++) if (map[r][c] > 0) map[r][c]--;
}

void move_air() {
	int r, c, sX, sY, nX, nY, sN, fN, nN, tmpDiff, flag;
	int moveMap[21][21] = { 0, };

	for (r = 1; r <= R; r++) {
		for (c = 1; c <= C; c++) {
			if (map[r][c] == 0) continue;
			if (map[r][c] < 4) {
				moveMap[r][c] = moveMap[r][c] + map[r][c];
				continue;
			}
			sX = r, sY = c, sN = map[r][c], fN = sN;
			for (int d = 2; d <= 8; d = d + 2) {
				nX = sX + ddx[d], nY = sY + ddy[d];
				if (!inRange(nX, nY)) continue;
				nN = map[nX][nY];
				switch (d) {
				case 2:
					if (wall[sX][sY][1] == 0 && sN > nN) {
						tmpDiff = sN - nN;
						tmpDiff = (int)tmpDiff / 4;
						fN = fN - tmpDiff;
						moveMap[nX][nY] = moveMap[nX][nY] + tmpDiff;
					}
					break;
				case 4:
					if (wall[sX + 1][sY][0] == 0 && sN > nN) {
						tmpDiff = sN - nN;
						tmpDiff = (int)tmpDiff / 4;
						fN = fN - tmpDiff;
						moveMap[nX][nY] = moveMap[nX][nY] + tmpDiff;
					}
					break;
				case 6:
					if (wall[sX][sY - 1][1] == 0 && sN > nN) {
						tmpDiff = sN - nN;
						tmpDiff = (int)tmpDiff / 4;
						fN = fN - tmpDiff;
						moveMap[nX][nY] = moveMap[nX][nY] + tmpDiff;
					}
					break;
				case 8:
					if (wall[sX][sY][0] == 0 && sN > nN) {
						tmpDiff = sN - nN;
						tmpDiff = (int)tmpDiff / 4;
						fN = fN - tmpDiff;
						moveMap[nX][nY] = moveMap[nX][nY] + tmpDiff;
					}
					break;
				}
			}
			moveMap[sX][sY] = moveMap[sX][sY] + fN;
		}
	}

	for (r = 1; r <= R; r++) {
		for (c = 1; c <= C; c++) {
			map[r][c] = moveMap[r][c];
		}
	}
}

void find_add_pos(int sX, int sY, int d) {
	int nX, nY, sCnt, nCnt, nDir, dd[3], visited[21][21] = { 0, };
	if (d == 1) {
		dd[0] = 1, dd[1] = 2, dd[2] = 3;
	}
	else if (d == 2) {
		dd[0] = 7, dd[1] = 6, dd[2] = 5;
	}
	else if (d == 3) {
		dd[0] = 7, dd[1] = 8, dd[2] = 1;
	}
	else if (d == 4) {
		dd[0] = 3, dd[1] = 4, dd[2] = 5;
	}

	queue <AddAir> q;
	q.push({ sX, sY, 5 });
	aa.push_back({ sX, sY, 5 });
	visited[sX][sY] = 1;

	while (!q.empty()) {
		sX = q.front().x, sY = q.front().y, sCnt = q.front().cnt;
		q.pop();
		nCnt = sCnt - 1;
		if (nCnt == 0) continue;
		for (int i = 0; i < 3; i++) {
			nDir = dd[i];
			nX = sX + ddx[nDir], nY = sY + ddy[nDir];
			if (!inRange(nX, nY) || visited[nX][nY] == 1) continue;

			switch (nDir) {
			case 1:
				if (d == 1) {
					if (wall[sX][sY][0] == 0 && wall[sX - 1][sY][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				else if (d == 3) {
					if (wall[sX][sY + 1][0] == 0 && wall[sX][sY][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
					break;
			case 2:
				if (wall[sX][sY][1] == 0) {
					q.push({ nX, nY, nCnt });
					aa.push_back({ nX, nY, nCnt });
					visited[nX][nY] = 1;
				}
				break;
			case 3:
				if (d == 1) {
					if (wall[sX + 1][sY][0] == 0 && wall[sX + 1][sY][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				else if (d == 4) {
					if (wall[sX + 1][sY + 1][0] == 0 && wall[sX][sY][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				break;
			case 4:
				if (wall[sX + 1][sY][0] == 0) {
					q.push({ nX, nY, nCnt });
					aa.push_back({ nX, nY, nCnt });
					visited[nX][nY] = 1;
				}
				break;
			case 5:
				if (d == 2) {
					if (wall[sX + 1][sY][0] == 0 && wall[sX + 1][sY - 1][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				else if (d == 4) {
					if (wall[sX + 1][sY - 1][0] == 0 && wall[sX][sY - 1][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				break;
			case 6:
				if (wall[sX][sY - 1][1] == 0) {
					q.push({ nX, nY, nCnt });
					aa.push_back({ nX, nY, nCnt });
					visited[nX][nY] = 1;
				}
				break;
			case 7:
				if (d == 2) {
					if (wall[sX][sY][0] == 0 && wall[sX - 1][sY - 1][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				else if (d == 3) {
					if (wall[sX][sY - 1][0] == 0 && wall[sX][sY - 1][1] == 0) {
						q.push({ nX, nY, nCnt });
						aa.push_back({ nX, nY, nCnt });
						visited[nX][nY] = 1;
					}
				}
				break;
			case 8:
				if (wall[sX][sY][0] == 0) {
					q.push({ nX, nY, nCnt });
					aa.push_back({ nX, nY, nCnt });
					visited[nX][nY] = 1;
				}
				break;
				}
			}
		}

	}
}
void heater_operate() {
	int sX, sY, nX, nY, d;
	for (int i = 0; i < h.size(); i++) {
		sX = h[i].x, sY = h[i].y, d = h[i].dir;
		nX = sX + dx[d], nY = sY + dy[d];
		if (!inRange(nX, nY)) continue;
		find_add_pos(nX, nY, d);
		while (!aa.empty()) {
			map[aa.front().x][aa.front().y] = map[aa.front().x][aa.front().y] + aa.front().cnt;
			aa.pop_front();
		}
		//print_info();
	}

}

int check_map() {
	int x, y, cnt = 0, retFlag = 0;
	for (int i = 0; i < check.size(); i++) {
		x = check[i].first, y = check[i].second;
		if (map[x][y] >= K) cnt++;
	}
	if (cnt == check.size()) retFlag = 1;

	return retFlag;	
}

void test_set() {
	map[1][1] = 5;
	map[1][2] = 18;
	map[1][3] = 70;
	map[2][1] = 23;
	map[2][2] = 46;
	map[2][3] = 0;
	map[3][1] = 0;
	map[3][2] = 2;
	map[3][3] = 20;
	wall[1][2][1] = 1;
	wall[3][1][1] = 1;
	wall[3][2][0] = 1;

}

void Solution() {
	Answer = 0;
	int exitFlag;

	while (1) {
		heater_operate();
		//print_info();
		move_air();
		//print_info();
		dec_air();
		//print_info();
		Answer++;
		//cout << "Answer : " << Answer << endl;
		exitFlag = check_map();
		if (exitFlag == 1) break;
		if (Answer >= 100) {
			Answer = 101;
			break;
		}
	}
	cout << Answer << endl;
}

void Input() {
	int tmp;
	cin >> R >> C >> K;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> tmp;
			if (tmp == 5) check.push_back(make_pair(i, j));
			else if (tmp >= 1 && tmp < 5)h.push_back({ i, j, tmp });
		}
	}
	int x, y, t;
	cin >> W;
	for (int i = 0; i < W; i++) {
		cin >> x >> y >> t;
		wall[x][y][t] = 1;
	}
}

int main(void) {
	Input();
	Solution();

	return 0;
}