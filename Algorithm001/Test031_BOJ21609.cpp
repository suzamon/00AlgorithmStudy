/*
1'26''55'''
struct BlockGroup{ int color, int rainbowCnt, int oX, int oY, int blockCnt}

dq <BlockGroup> bg;
dq <Block> b[6];

1. Input()
	N, M, map[xx][yy] && b에 넣기
2. Solution()
	1. int find_block_group(int color)
		1) int tmpSize = b[color].size()
		2) int sX, sY, nX, nY, rainbowCnt, int oX, oY, bolckCnt
		3) int visited[21][21] = {0, }, queue <pair <int ,int>> q
		3) for(int idx=0; idx<tmpSize; idx++){
		3) sX = b[color].front().x, sY = b[color].front().y & b[color].pop_front();
		4) if(visited[sX][sY] == 1 ) continue;
		5) oX = sX, oX = sY, rainbowCnt=0, blockCnt=1;
		6) q.push(make_pair(sX, sY) & visited[sX][sY] = 1;
		7) while(!q.empty()){
		8) sX= q.front().first, sY = q.front().second & q.pop()
		5) for(int d=0; d<4; d++) {
		6) nX = sX +dx[d], nY = sY+dy[d]
		7) if(!inRange(nX, nY)) continue;
		8) if(map[nX][nY] == 0) rainbowCnt++, blockCnt++, visited[nX][nY] =1 & q.push(make_pair(nX, nY))
		9) else if(map[nX][nY] == color) { blockCnt++, visited[nX][nY] =1 & q.push(make_pair(nX, nY))
		10) if(oX > nX) oX = nX, oY = nY
		11) else if(oX==nX && oY > nY) oY = nY }
		12) }
		13) if(bg.size() == 0) BolckGroup b = {color, rainbowCnt, oX, oY, blockCnt} & bg.push_back(b);
		14) else {
		15) bg[0]에 있는 blockCnt, rainbowCnt, oX, oY 비교해서 조건 만족하면 갱신
		16) }
		17) return;
	2. void gravity_force()
		1) int xx, yy, sX = N+1, sY;
		2) deque <int> dq;
		2) for(xx= N; xx>=1; xx--)
		3) for(yy=N; yy>=1; yy--) {
		4) if(map[xx][yy]= -1 || map[xx][yy] = -2) -> if(dq.size() >0 && sX != N+1)이면 내려가고
		5) else if(map[xx][yy] >= 1 && sX != N+1 && sX >xx) bq.push_back(map[xx][yy]);


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
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0 ,-1 };

struct Block {
	int x, y;
	Block(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct BlockGroup{
	int color, blockCnt, rainbowCnt, oX, oY;
	BlockGroup(int color, int blockCnt, int rainbowCnt, int oX, int oY) {
		this->color = color;
		this->blockCnt = blockCnt;
		this->rainbowCnt = rainbowCnt;
		this->oX = oX;
		this->oY = oY;
	}
};

deque <BlockGroup> bg;
deque <Block> b[6];

void print_info() {
	if (bg.size() >= 1) {
		cout << "탐색 결과" << endl;
		cout << bg[0].color << "색을 가진 BlockCnt: " << bg[0].blockCnt << ", rainbowCnt: " << bg[0].rainbowCnt << ", (" << bg[0].oX << ", " << bg[0].oY << ") 그룹" << endl;
	}

	cout << "맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == -2) cout << "X ";
			else cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int yy) {
	if (xx < 1 || xx >N || yy < 1 || yy >N) return false;
	return true;
}

void find_block() {
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] >= 1) {
				b[map[xx][yy]].push_back({ xx, yy });
			}
		}
	}
}

void rotate_map() {
	int copyMap[21][21];
	for (int yy = N; yy >= 1; yy--) {
		for (int xx = 1; xx <= N; xx++) {
			copyMap[N - yy +1][xx] = map[xx][yy];
		}
	}

	for (int xx = 1; xx <=N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			map[xx][yy] = copyMap[xx][yy];
		}
	}
}

void gravity_force() {
	int xx, yy, sX;
	deque <int> dq;

	for (yy = N; yy >= 1; yy--) {
		sX = N + 1;
		for (xx = N; xx >= 1; xx--) {
			if (sX == N+1 && (map[xx][yy] == -1 || map[xx][yy] == -2)) {
				if (map[xx][yy] == -2) sX = xx;
				else sX = xx - 1;
			}
			else if (map[xx][yy] == -1) {
				if (dq.size() >= 1 && sX != N + 1) {
					while (!dq.empty()) {
						map[sX][yy] = dq.front();
						dq.pop_front();
						sX--;
					}
				}
				sX = xx - 1;
			}
			else if (sX != N + 1 && map[xx][yy] >= 0) {
				dq.push_back(map[xx][yy]);
				map[xx][yy] = -2;
			}
		}
		if (dq.size() >= 1) {
			while (!dq.empty()) {
				map[sX][yy] = dq.front();
				dq.pop_front();
				sX--;
			}
		}
	}
}

void remove_bg() {
	int sX, sY, nX, nY, color;
	int visited[21][21] = { 0, };
	queue <pair <int, int>> q;

	color = bg[0].color;
	sX = bg[0].oX, sY = bg[0].oY;
	q.push(make_pair(sX, sY));
	visited[sX][sY] = 1;
	map[sX][sY] = -2;

	while (!q.empty()) {
		sX = q.front().first, sY = q.front().second;
		q.pop();
		for (int d = 0; d < 4; d++) {
			nX = sX + dx[d], nY = sY + dy[d];
			if ((!inRange(nX, nY)) || visited[nX][nY] == 1) continue;

			if (map[nX][nY] == 0 || map[nX][nY] == color) {
				visited[nX][nY] = 1;
				map[nX][nY] = -2;
				q.push(make_pair(nX, nY));
			}
		}
	}
	Answer = Answer + bg[0].blockCnt * bg[0].blockCnt;
}

void find_block_group(int color) {
	int tmpSize = b[color].size();
	int sX, sY, nX, nY, rainbowCnt, oX, oY, blockCnt;
	int visited[21][21] = { 0, };
	queue <pair <int, int>> q;
	for (int idx = 0; idx < tmpSize; idx++) {
		sX = b[color].front().x, sY = b[color].front().y;
		b[color].pop_front();
		if (visited[sX][sY] == 1) continue;

		oX = sX, oY = sY, rainbowCnt = 0, blockCnt = 1;
		q.push(make_pair(sX, sY));
		visited[sX][sY] = 1;
		while (!q.empty()) {
			sX = q.front().first, sY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nX = sX + dx[d], nY = sY + dy[d];
				if ((!inRange(nX, nY)) || visited[nX][nY] == 1) continue;

				if (map[nX][nY] == 0) {
					rainbowCnt++, blockCnt++;
					visited[nX][nY] = 1;
					q.push(make_pair(nX, nY));
				}
				else if (map[nX][nY] == color) {
					blockCnt++;
					visited[nX][nY] = 1;
					q.push(make_pair(nX, nY));
					if (oX > nX) {
						oX = nX, oY = nY;
					}
					else if (oX == nX && oY > nY) oY = nY;
				}
			}
		}

		if (bg.size() == 0) {
			bg.push_back({ color, blockCnt, rainbowCnt, oX, oY });
		}
		else {
			if (bg[0].blockCnt < blockCnt) {
				bg[0].color = color;
				bg[0].blockCnt = blockCnt;
				bg[0].rainbowCnt = rainbowCnt;
				bg[0].oX = oX;
				bg[0].oY = oY;
			}
			else if (bg[0].blockCnt == blockCnt) {
				if (bg[0].rainbowCnt < rainbowCnt) {
					bg[0].color = color;
					bg[0].rainbowCnt = rainbowCnt;
					bg[0].oX = oX;
					bg[0].oY = oY;
				}
				else if (bg[0].rainbowCnt == rainbowCnt) {
					if (bg[0].oX < oX) {
						bg[0].color = color;
						bg[0].oX = oX;
						bg[0].oY = oY;
					}
					else if (bg[0].oX == oX && bg[0].oY < oY) {
						bg[0].color = color;
						bg[0].oY = oY;
					}
				}
			}
		}
	}
}

void Solution() {
	while (1) {
		for (int color = 1; color <= M; color++) {
			find_block_group(color);
		}

		if (bg.size() == 0) break;
		if (bg[0].blockCnt < 2) {
			bg.pop_back();
			break;
		}
		remove_bg();
		//print_info();
		bg.pop_back();

		gravity_force();
		//print_info();
		rotate_map();
		//print_info();
		gravity_force();
		//print_info();

		find_block();
	}

	cout << Answer << endl;
}

void Input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] >= 1) b[map[i][j]].push_back({ i, j });
		}
	}
}

int main(void) {
	Input();
	Solution();
	return 0;
}