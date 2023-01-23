/*
2'50''25'''

마법사 상어는 파이어볼, 토네이도, 파이어스톰, 물복사버그, 비바라기, 블리자드 마법을 할 수 있다.
오늘은 기존에 배운 물복사버그 마법의 상위 마법인 복제를 배웠고, 4 × 4 크기의 격자에서 연습하려고 한다.
(r, c)는 격자의 r행 c열을 의미한다. 격자의 가장 왼쪽 윗 칸은 (1, 1)이고, 가장 오른쪽 아랫 칸은 (4, 4)이다.

격자에는 물고기 M마리가 있다. 각 물고기는 격자의 칸 하나에 들어가 있으며, 이동 방향을 가지고 있다.
이동 방향은 8가지 방향(상하좌우, 대각선) 중 하나이다. 마법사 상어도 연습을 위해 격자에 들어가있다.
상어도 격자의 한 칸에 들어가있다. 둘 이상의 물고기가 같은 칸에 있을 수도 있으며,
마법사 상어와 물고기가 같은 칸에 있을 수도 있다.

상어의 마법 연습 한 번은 다음과 같은 작업이 순차적으로 이루어진다.

1. 상어가 모든 물고기에게 복제 마법을 시전한다. 복제 마법은 시간이 조금 걸리기 때문에,
   아래 5번에서 물고기가 복제되어 칸에 나타난다.
2. 모든 물고기가 한 칸 이동한다. 상어가 있는 칸, 물고기의 냄새가 있는 칸, 격자의 범위를 벗어나는 칸으로는 이동할 수 없다.
   각 물고기는 자신이 가지고 있는 이동 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다.
   만약, 이동할 수 있는 칸이 없으면 이동을 하지 않는다. 그 외의 경우에는 그 칸으로 이동을 한다.
   물고기의 냄새는 아래 3에서 설명한다.
3. 상어가 연속해서 3칸 이동한다. 상어는 현재 칸에서 상하좌우로 인접한 칸으로 이동할 수 있다.
   연속해서 이동하는 칸 중에 격자의 범위를 벗어나는 칸이 있으면, 그 방법은 불가능한 이동 방법이다.
   연속해서 이동하는 중에 상어가 물고기가 있는 같은 칸으로 이동하게 된다면, 그 칸에 있는 모든 물고기는 격자에서 제외되며,
   제외되는 모든 물고기는 물고기 냄새를 남긴다.
   가능한 이동 방법 중에서 제외되는 물고기의 수가 가장 많은 방법으로 이동하며,
   그러한 방법이 여러가지인 경우 사전 순으로 가장 앞서는 방법을 이용한다. 사전 순에 대한 문제의 하단 노트에 있다.
4. 두 번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라진다.
5. 1에서 사용한 복제 마법이 완료된다. 모든 복제된 물고기는 1에서의 위치와 방향을 그대로 갖게 된다.

격자에 있는 물고기의 위치, 방향 정보와 상어의 위치, 그리고 연습 횟수 S가 주어진다.
S번 연습을 모두 마쳤을때, 격자에 있는 물고기의 수를 구해보자.

입력
첫째 줄에 물고기의 수 M, 상어가 마법을 연습한 횟수 S가 주어진다.
둘째 줄부터 M개의 줄에는 물고기의 정보 fx, fy, d가 주어진다. (fx, fy)는 물고기의 위치를 의미하고, d는 방향을 의미한다.
방향은 8 이하의 자연수로 표현하고, 1부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 이다.
마지막 줄에는 sx, sy가 주어지며, 상어가 (sx, sy)에 있음을 의미한다.
격자 위에 있는 물고기의 수가 항상 1,000,000 이하인 입력만 주어진다.

출력
S번의 연습을 마친 후 격자에 있는 물고기의 수를 출력한다.

제한
1 ≤ M ≤ 10
1 ≤ S ≤ 100
1 ≤ fx, fy, sx, sy ≤ 4
1 ≤ d ≤ 8
두 물고기 또는 물고기와 상어가 같은 칸에 있을 수도 있다.

M, S,
struct Fish{int x,y,dir, state}
deque <Fish> fish;
deque <Fish> addFish;
deque <int> map[5][5]

struct Nextpos{
	int dirArr[3], fishCnt;
}


int shark[2], scent[5][5];
int dx[9], dy[9] = ←, ↖, ↑, ↗, →, ↘, ↓, ↙
int sharkDx[5], sharkDy[5] = ↑, ←, ↓, →
int sharkDir[3];

1. Input()
	M, S, fish.push_back(), shark[0~1], NextPos sharkNextPos = {0, 0, 0, 0};
2. Solution()
	1) int time;
	2) for(time=1; time<=S; time++)
	3) void magic_fish()
		1) for(int i=0; i<fish.size(); i++) addFish.push_back(fish[i]) & map[fish[i].x][fish[i].y].pop_front();
	4) move_fish()
		1) int sX, sY, state, sD, nX, nY, nD, fishSize, cnt;
		2) fishSize = fish.size();
		3) for(int i=0; i<fishSize; i++){
		4) state = fish.front().state;
		5) if(state==1) fish.pop_front() & continue;
		6) sX = fish.front().x, sY = fish.front().y, sD = fish.front().dir, nD = sD;
		7) fish.pop_front(), cnt = 0;
		8) while(1) {
		9) cnt++;
		10) if(cnt==9) break;
		11) nX = sX + dx[nD], nY = sY + dy[nD];
		12) if(inRange(nX, nY) && scent[nX][nY] == 0 && (nX!= shark[0] && nY != shark[1])) break;
		13) nD = change_dir(nD);
		15) }
		16) if(cnt==9) fish.push_back({sX, sY, sD, state), map[sX][sY].push_back(i)continue;
		17) fish.push_back({nX, nY, nD, state), map[nX][nY].push_back(i);
		18 }
	5) sharkNextPos '1', '1', '1', '0'으로 셋업
	5) move_shark(int cnt)
		1) if(cnt==3)
		2) int sX, sY, nX, nY, fishCnt = 0;
		3) sX = shark[0], sY= shark[1];
		4) for(int i=0; i<3; i++) {
		5) nX = sX + sharkDx[sharkDir[i]], nY = sY + sharkDy[sharkDir[i]];
		6) if(!inRange(nX, nY)) return;
		7) if(map[nX][nY].size() >0) fishCnt = fishCnt + map[nX][nY].size();
		8) }
		10) if(sharkNextPos.fishCnt == 0) sharkNextPos 교체
		11) else if(sharkNextPos.fishCnt < fishCnt) -> sharkNextPos 교체
		12) return;
		13) for(int d=1; d<=4; d++){
		14) sharkDir[cnt] = d;
		15) move_shark(cnt+1);
		16) }
	6) nextPos대로 상어 이동 & 가는 길에 물고기 있으면 scent[nX][nY] = 3으로 셋업
	6) dec_scent()
		1) for(int x=1; x<=4; x++)
		2) for(int y=1; y<=4; y++)
		3) if(scent[x][y] > 0) scent[x][y]--;
	7) void add_fish()
		1) int addSize = addFish.size();
		2) for(int i=0; i<addSize; i++)
		3) fish.push_back(addFish.front());
		4) addFish.pop_front();

* int change_dir(int dir)
	1) int nDir;
	2) if(dir > 1) nDir = dir -1;
	3) else nDir = 8;
	4) return nDir;
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int M, S;
long Answer = 0;

struct Fish {
	int x, y, dir, state, s;
	Fish(int x, int y, int dir, int state, int s) {
		this->x = x;
		this->y = y;
		this->dir = dir;
		this->state = state;
		this->s = s;
	}
};

struct NextPos {
	int dirArr[3], fishCnt;
	NextPos(int a, int b, int c, int d) {
		this->dirArr[0] = a;
		this->dirArr[1] = b;
		this->dirArr[2] = c;
		this->fishCnt = d;
	}
};

deque <Fish> fish;
deque <Fish> addFish;
deque <pair<int, int>> map[5][5][9];

int shark[2], sharkDir[3], scent[5][5] = { 0, };
NextPos sharkNextPos = { 0, 0, 0, 0 };

int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int sharkDx[5] = { 0, -1, 0, 1, 0 };
int sharkDy[5] = { 0, 0, -1, 0, 1 };

void print_info() {
	cout << "정보 출력" << endl;
	cout << "상어 위치: (" << shark[0] << ", " << shark[1] << ')'<<endl;
	for (int i = 0; i < fish.size(); i++) {
		cout << '(' << fish[i].x << ", " << fish[i].y << ") 위치에 "<< i<<"번 물고기 방향: " << fish[i].dir << ", 상태: " << fish[i].state << endl;
	}

	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 0) {
					for (int idx = 0; idx < map[x][y][d].size(); idx++) {
						cout << '(' << x << ", " << y << ") 위치에 " << d<<"방향을 가진 "<< map[x][y][d][idx].first << "번 " << map[x][y][d][idx].second << " 사이즈 물고기 존재" << endl;
					}
				}
			}

		}
	}
}

bool inRange(int x, int y) {
	if (x < 1 || x>4 || y < 1 || y>4) return false;
	return true;
}

int change_dir(int dir) {
	int nDir;
	if (dir > 1) nDir = dir - 1;
	else nDir = 8;
	return nDir;
}

void dec_scent() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			if(scent[x][y] > 0) scent[x][y]--;
		}
	}
}

void remove_fish() {
	int fishSize = fish.size();
	Fish f = { 0, 0,0,0, 0 };
	for (int i = 0; i < fishSize; i++) {
		f = fish.front();	
		fish.pop_front();
		if (f.state == 1) {
			continue;
		}
		fish.push_back(f);
	}
}

void reset_map() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 0) {
					while (!map[x][y][d].empty()) map[x][y][d].pop_front();
				}
			}
		}
	}
	int x, y, d, s;
	for (int i = 0; i < fish.size(); i++) {
		x = fish[i].x, y = fish[i].y, d = fish[i].dir, s = fish[i].s;
		map[x][y][d].push_back(make_pair(i, s));
	}
}

void add_fish() {
	int addSize = addFish.size();
	for (int i = 0; i < addSize; i++) {
		fish.push_back(addFish.front());
		//map[addFish.front().x][addFish.front().y][addFish.front().dir].push_back(make_pair(idx, addFish.front().s));
		addFish.pop_front();
	}

	reset_map();
}

void union_fish() {
	int fishIdx, fishSize,mapSize, unionIdx, tmpSize, flag = 0;
	for (int x = 1; x <=4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 1) {
					if (flag == 0) flag = 1;
					mapSize = map[x][y][d].size();
					for (int i = 0; i < mapSize; i++) {
						if (i == 0) {
							unionIdx = map[x][y][d].front().first;
							fishSize = map[x][y][d].front().second;
							map[x][y][d].pop_front();
							continue;
						}
						tmpSize = map[x][y][d].front().second;
						fishIdx = map[x][y][d].front().first;
						map[x][y][d].pop_front();
						fish[fishIdx].state = 1;
						fishSize = fishSize + tmpSize;
					}
					fish[unionIdx].s = fishSize;
					map[x][y][d].push_back(make_pair(unionIdx, fishSize));
				}
			}
		}
	}
	if(flag == 1) remove_fish();
	return;
}

void magic_fish() {
	for (int i = 0; i < fish.size(); i++) {
		addFish.push_back(fish[i]);
	}
}

void move_shark(int cnt) {
	if (cnt == 3) {
		int sX, sY, nX, nY, fishCnt = 0;
		int visited[5][5] = { 0, };
		nX = shark[0], nY = shark[1];
		for (int i = 0; i < 3; i++) {
			nX = nX + sharkDx[sharkDir[i]], nY = nY + sharkDy[sharkDir[i]];
			if (!inRange(nX, nY)) return;

			if (visited[nX][nY] == 0) {
				for (int d = 1; d <= 8; d++) {
					if (map[nX][nY][d].size() == 0) continue;
					for (int tmpIdx = 0; tmpIdx < map[nX][nY][d].size(); tmpIdx++) {
						fishCnt = fishCnt + map[nX][nY][d][tmpIdx].second;
					}
				}
				visited[nX][nY] = 1;
			}
			visited[nX][nY] = 1;
		}
		if (sharkNextPos.fishCnt == -1) {
			for (int i = 0; i < 3; i++) {
				sharkNextPos.dirArr[i] = sharkDir[i];
			}
			sharkNextPos.fishCnt = fishCnt;
		}
		else if (sharkNextPos.fishCnt < fishCnt) {
			for (int i = 0; i < 3; i++) {
				sharkNextPos.dirArr[i] = sharkDir[i];
			}
			sharkNextPos.fishCnt = fishCnt;
		}
		return;
	}

	for (int d = 1; d <= 4; d++) {
		sharkDir[cnt] = d;
		move_shark(cnt + 1);
	}
}


void sim_shark() {
	int sX, sY, nX, nY, tmpIdx, tmpSize;
	nX = shark[0], nY = shark[1];
	for (int i = 0; i < 3; i++) {
		nX = nX + sharkDx[sharkNextPos.dirArr[i]];
		nY = nY + sharkDy[sharkNextPos.dirArr[i]];
		for (int d = 1; d <= 8; d++) {
			if (map[nX][nY][d].size() > 0) {
				scent[nX][nY] = 3;
				tmpSize = map[nX][nY][d].size();
				for (int j = 0; j < tmpSize; j++) {
					tmpIdx = map[nX][nY][d].front().first;
					map[nX][nY][d].pop_front();
					fish[tmpIdx].state = 1;
				}
			}
		}
	}
	shark[0] = nX, shark[1] = nY;
}

void move_fish() {
	int sX, sY, state, sD, nX, nY, nD, fishSize, cnt, s;
	fishSize = fish.size();
	for (int i = 0; i < fishSize; i++) {
		state = fish.front().state;
		if (state == 1) {
			fish.pop_front();
			continue;
		}
		sX = fish.front().x, sY = fish.front().y, sD = fish.front().dir, nD = sD, s = fish.front().s;
		fish.pop_front();
		map[sX][sY][sD].pop_front();
		cnt = 0;

		while (1) {
			cnt++;
			if (cnt == 9) break;
			nX = sX + dx[nD], nY = sY + dy[nD];
			if (inRange(nX, nY) && scent[nX][nY] == 0 && (nX != shark[0] || nY != shark[1])) break;
			nD = change_dir(nD);
		}

		if (cnt == 9) {
			fish.push_back({ sX, sY, sD, state, s });
			map[sX][sY][sD].push_back(make_pair(i, s));
			continue;
		}
		fish.push_back({ nX, nY, nD, state, s });
		map[nX][nY][nD].push_back(make_pair(i, s));
	}
}

void find_answer() {
	Answer = 0;
	for (int i = 0; i < fish.size(); i++) {
		Answer = Answer + fish[i].s;
	}
}

void Solution() {
	int time;
	for (time = 1; time <= S; time++) {
		//cout << time << "초 후" << endl;
		union_fish();
		//print_info();
		magic_fish();
		move_fish();
		//cout << "물고기 이동 후" << endl;
		//print_info();
		sharkNextPos = { 0, 0, 0, -1 };
		move_shark(0);
		sim_shark();
		//cout << "상어 이동 후" << endl;
		//print_info();
		dec_scent();
		remove_fish();
		add_fish();
		//cout << "물고기 복제 후" << endl;
		//print_info();
	}

	find_answer();
	cout << Answer << endl;
}

void Input() {
	cin >> M >> S;
	int x, y, dir, state, idx;
	idx = 0;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> dir;
		state = 0;
		fish.push_back({ x, y, dir, state, 1 });
		map[x][y][dir].push_back(make_pair(idx, 1));
		idx++;
	}

	cin >> shark[0] >> shark[1];
}

int main(void) {
	Input();
	//print_info();
	Solution();
	return 0;
}