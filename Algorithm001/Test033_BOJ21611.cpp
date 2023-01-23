/*
1'47''15'''
상어가 있는 칸도 항상 0이 주어진다.
다음 M개의 줄에는 블리자드 마법의 방향 di와 거리 si가 한 줄에 하나씩 마법을 시전한 순서대로 주어진다.

출력
첫째 줄에 1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수)를 출력한다.

제한
3 ≤ N ≤ 49
N은 홀수
1 ≤ M ≤ 100
1 ≤ di ≤ 4
1 ≤ si ≤ (N-1)/2
칸에 들어있는 구슬이 K개라면, 구슬이 들어있는 칸의 번호는 1번부터 K번까지이다.
입력으로 주어진 격자에는 4개 이상 연속하는 구슬이 없다.

N, M, map[51][51], command[101][2], shark[2],
dx[5], dy[5] 1부터 ↑, ↓, ←, →, ddx[5], ddy[5] -> 1부터 ←, ↓, →, ↑,
struct RemovBall{ int x, y, cnt}

1. Input()
	N, M, map[N][N], command[M][2], shark[0]=shark[1] = (N+1)/2
2. Solution()
	1. magic(int d, int s)
		1) nX, nY
		2) nX = shark[0], nY = shark[1]
		3) for(int i=1; i<=s; i++)
		4) nX = nX + dx[d], nY =nY+dy[d]
		5) map[nX][nY] = 0;
	2. move_ice()
		1) int cnt=0, dir=1, sX, sY, nX, nY;
		2) nX = shark[0], nY = shark[1];
		3) deque <int> dq;
		2) while(1)
		3) cnt++
		3) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir]
		5) if(map[nX][nY] > 0) dq.push(map[nX][nY]) & map[nX][nY] = 0;
		5) if(nX==1 && nY ==1) break;
		6) }
		7) if(nX==1 && nY ==1) break;
		7) dir++;
		8) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir]
		5) if(map[nX][nY] > 0) dq.push(map[nX][nY]) & map[nX][nY] = 0;
		5) }
		6) dir++, cnt++;
		7) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir]
		5) if(map[nX][nY] > 0) dq.push(map[nX][nY]) & map[nX][nY] = 0;
		5) }
		7) dir++;
		8) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir]
		5) if(map[nX][nY] > 0) dq.push(map[nX][nY]) & map[nX][nY] = 0;
		5) }
		6) cnt = 0;
		6) while(1)
		3) cnt++
		3) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir]
		5) map[nX][nY] = dq.front(); & dq.pop_front()
		6) if(dq.size() == 0) break;
		5) if(nX==1 && nY ==1) break;
		6) }
		7) if(dq.size() == 0) break;
		8) 반복~
	3. remove_ball()
		1) int cnt=0, dir=1, sX, sY, sN=0, nX, nY, nN = 0, removeCnt = 0 ;
		2) nX = shark[0], nY = shark[1];
		3) deque <RemoveBall> dq;

		2) while(1)
		3) cnt++
		3) for(int i=0; i<cnt; i++) {
		4) nX = nX + ddx[dir], nY = nY+dd[dir], nN = map[nX][nY];
		5) if(sN==0) { sX=nX, sY = nY, nN = sN, removeCnt = 1}
		6) else if(nN == sN) { removeCnt++}
		7) else if(nN != sN) {
		8) if(removeCnt >=4) dq.push_back({sX,sY,removeCnt});
		8) sX = nX, sY = nY, nN = sN, removeCnt = 1;
		9)}
		5) if(nX==1 && nY ==1) break;
		6) }
		7) if(nX==1 && nY ==1) break;

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
int map[51][51], command[101][2], shark[2];
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };
int ddx[5] = { 0, 0, 1, 0, -1 };
int ddy[5] = { 0, -1, 0, 1, 0 };

struct RemoveBall {
	int x, y, num, removeCnt;
	RemoveBall(int x, int y, int num, int removeCnt) {
		this->x = x;
		this->y = y;
		this->num = num;
		this->removeCnt = removeCnt;
	}
};

void print_info() {
	cout << "맵 정보" << endl;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			cout << map[xx][yy] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int check_ball() {
	int cnt = 0;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] > 0) cnt++;
		}
	}
	if (cnt == 0) return 1;
	return 0;
}

int divide_ball() {
	int cnt = 0, dir = 1, nX, nY, nN, sN = 0, ballCnt = 0, exitFlag = 0;
	nX = shark[0], nY = shark[1];
	deque <pair <int, int>> dq;
	while (1) {
		cnt++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (map[nX][nY] == 0) {
				dq.push_back(make_pair(ballCnt, sN));
				exitFlag = 1;
				break;
			}
			map[nX][nY] = 0;
			if (sN == 0) {
				sN = nN;
				ballCnt = 1;
			}
			else if (nN == sN) ballCnt++;
			else {
				dq.push_back(make_pair(ballCnt, sN));
				sN = nN;
				ballCnt = 1;
			}
			if (nX == 1 && nY == 1) {
				dq.push_back(make_pair(ballCnt, sN));
				break;
			}
		}
		if (exitFlag == 1) break;
		if (nX == 1 && nY == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (map[nX][nY] == 0) {
				dq.push_back(make_pair(ballCnt, sN));
				exitFlag = 1;
				break;
			}
			map[nX][nY] = 0;
			if (nN == sN) ballCnt++;
			else {
				dq.push_back(make_pair(ballCnt, sN));
				sN = nN;
				ballCnt = 1;
			}
		}
		if (exitFlag == 1) break;
		cnt++;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (map[nX][nY] == 0) {
				dq.push_back(make_pair(ballCnt, sN));
				exitFlag = 1;
				break;
			}
			map[nX][nY] = 0;
			if (nN == sN) ballCnt++;
			else {
				dq.push_back(make_pair(ballCnt, sN));
				sN = nN;
				ballCnt = 1;
			}
		}
		if (exitFlag == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (map[nX][nY] == 0) {
				dq.push_back(make_pair(ballCnt, sN));
				exitFlag = 1;
				break;
			}
			map[nX][nY] = 0;
			if (nN == sN) ballCnt++;
			else {
				dq.push_back(make_pair(ballCnt, sN));
				sN = nN;
				ballCnt = 1;
			}
		}
		if (exitFlag == 1) break;
		dir = 1;
	}

	if (dq.size() == 0) return 0;

	int nA = 0, nB = 0;
	cnt = 0, dir = 1;
	nX = shark[0], nY = shark[1];
	exitFlag = 0;
	while (1) {
		cnt++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (nB==0) {
				map[nX][nY] = dq.front().first;
				nB = dq.front().second;
				dq.pop_front();
			}
			else {
				map[nX][nY] = nB;
				nB = 0;
				if (dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
			if (nX == 1 && nY == 1) break;
		}
		if (exitFlag == 1) break;
		if (nX == 1 && nY == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (nB==0) {
				map[nX][nY] = dq.front().first;
				nB = dq.front().second;
				dq.pop_front();
			}
			else {
				map[nX][nY] = nB;
				nB = 0;
				if (dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		if (exitFlag == 1) break;
		cnt++;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (nB == 0) {
				map[nX][nY] = dq.front().first;
				nB = dq.front().second;
				dq.pop_front();
			}
			else {
				map[nX][nY] = nB;
				nB = 0;
				if (dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		if (exitFlag == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (nB == 0) {
				map[nX][nY] = dq.front().first;
				nB = dq.front().second;
				dq.pop_front();
			}
			else {
				map[nX][nY] = nB;
				nB = 0;
				if (dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		dir = 1;
		if (exitFlag == 1) break;
	}

	while (!dq.empty()) dq.pop_front();
	return 1;
}

int remove_ball() {
	int cnt = 0, dir = 1, sX, sY, sN = 0, nX, nY, nN = 0, removeCnt = 0, exitFlag = 0;
	int retFlag = 0;
	nX = shark[0], nY = shark[1];
	deque <RemoveBall> dq;

	while (1) {
		cnt++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (sN == 0) { 
				sX = nX, sY = nY, sN = nN, removeCnt = 1;
			}
			else if (nN == sN) removeCnt++;
			else if (map[nX][nY] == 0) {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				exitFlag = 1;
				break;
			}
			else {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				sX = nX, sY = nY, sN = nN, removeCnt = 1;
			}
			if (nX == 1 && nY == 1) {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				break;
			}
		}
		if (exitFlag == 1) break;
		if (nX == 1 && nY == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (nN == sN) removeCnt++;
			else if (map[nX][nY] == 0) {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				exitFlag = 1;
				break;
			}
			else {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				sX = nX, sY = nY, sN = nN, removeCnt = 1;
			}
		}
		if (exitFlag == 1) break;

		cnt++;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (nN == sN) removeCnt++;
			else if (map[nX][nY] == 0) {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				exitFlag = 1;
				break;
			}
			else {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				sX = nX, sY = nY, sN = nN, removeCnt = 1;
			}
		}
		if (exitFlag == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (nN == sN) removeCnt++;
			else if (map[nX][nY] == 0) {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				exitFlag = 1;
				break;
			}
			else {
				if (removeCnt >= 4) dq.push_back({ sX, sY, sN, removeCnt });
				sX = nX, sY = nY, sN = nN, removeCnt = 1;
			}
		}
		dir = 1;
		if (exitFlag == 1) break;
	}

	if (dq.size() == 0) return 1;
	
	for (int i = 0; i < dq.size(); i++) Answer = Answer + (dq[i].num * dq[i].removeCnt);

	int rIdx = 0, rCnt = 0;
	exitFlag = 0;
	cnt = 0, dir = 1;
	nX = shark[0], nY = shark[1];
	while (1) {
		cnt++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (rCnt ==0 && nX == dq[rIdx].x && nY == dq[rIdx].y) {
				rCnt = dq[rIdx].removeCnt - 1;
				map[nX][nY] = 0;
				dq.pop_front();
			}
			else if (rCnt > 0) {
				map[nX][nY] = 0;
				rCnt--;
				if (rCnt == 0 && dq.size()==0) {
					exitFlag = 1;
					break;
				}
			}
			if (nX == 1 && nY == 1) break;
			
		}
		if (exitFlag == 1) break;
		if (nX == 1 && nY == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (rCnt ==0 && nX == dq[rIdx].x && nY == dq[rIdx].y) {
				rCnt = dq[rIdx].removeCnt - 1;
				map[nX][nY] = 0;
				dq.pop_front();
			}
			else if (rCnt > 0) {
				map[nX][nY] = 0;
				rCnt--;
				if (rCnt == 0 && dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		if (exitFlag == 1) break;
		cnt++;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (rCnt ==0 && nX == dq[rIdx].x && nY == dq[rIdx].y) {
				rCnt = dq[rIdx].removeCnt - 1;
				map[nX][nY] = 0;
				dq.pop_front();
			}
			else if (rCnt > 0) {
				map[nX][nY] = 0;
				rCnt--;
				if (rCnt == 0 && dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		if (exitFlag == 1) break;
		dir++;
		for (int i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir], nN = map[nX][nY];
			if (rCnt ==0 && nX == dq[rIdx].x && nY == dq[rIdx].y) {
				rCnt = dq[rIdx].removeCnt - 1;
				map[nX][nY] = 0;
				dq.pop_front();
			}
			else if (rCnt > 0) {
				map[nX][nY] = 0;
				rCnt--;
				if (rCnt == 0 && dq.size() == 0) {
					exitFlag = 1;
					break;
				}
			}
		}
		if (exitFlag == 1) break;
		dir = 1;
	}

	return 0;
}

void move_ice() {
	int cnt = 0, dir = 1, nX, nY, i;
	
	deque <int> dq;
	nX = shark[0], nY = shark[1];
	while (1) {
		cnt++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (map[nX][nY] > 0) {
				dq.push_back(map[nX][nY]);
				map[nX][nY] = 0;
			}
			if (nX == 1 && nY == 1) break;
		}
		if (nX == 1 && nY == 1) break;
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (map[nX][nY] > 0) {
				dq.push_back(map[nX][nY]);
				map[nX][nY] = 0;
			}
		}

		cnt++;
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (map[nX][nY] > 0) {
				dq.push_back(map[nX][nY]);
				map[nX][nY] = 0;
			}
		}
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			if (map[nX][nY] > 0) {
				dq.push_back(map[nX][nY]);
				map[nX][nY] = 0;
			}
		}
		dir = 1;
	}
	cnt = 0, dir = 1;
	nX = shark[0], nY = shark[1];
	while (1) {
		cnt++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			map[nX][nY] = dq.front();
			dq.pop_front();
			if (dq.size() == 0) break;
			if (nX == 1 && nY == 1) break;
		}
		if (dq.size() == 0) break;
		if (nX == 1 && nY == 1) break;
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			map[nX][nY] = dq.front();
			dq.pop_front();
			if (dq.size() == 0) break;
		}
		if (dq.size() == 0) break;

		cnt++;
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			map[nX][nY] = dq.front();
			dq.pop_front();
			if (dq.size() == 0) break;
		}
		if (dq.size() == 0) break;
		dir++;
		for (i = 0; i < cnt; i++) {
			nX = nX + ddx[dir], nY = nY + ddy[dir];
			map[nX][nY] = dq.front();
			dq.pop_front();
			if (dq.size() == 0) break;
		}
		if (dq.size() == 0) break;
		dir = 1;
	}
}

int magic(int d, int s) {
	int nX, nY, retFlag = 0;
	nX = shark[0], nY = shark[1];
	for (int i = 1; i <= s; i++) {
		nX = nX + dx[d], nY = nY + dy[d];
		if (retFlag ==0 && map[nX][nY] > 0) retFlag = 1;
		map[nX][nY] = 0;
	}
	return retFlag;
}

void Solution() {
	int flag = 0, exitFlag = 0;
	for (int i = 0; i < M; i++) {
		flag = check_ball();
		if (flag == 1) break;
		flag = magic(command[i][0], command[i][1]);
		//print_info();
		if (flag != 0) move_ice();
		//print_info();
		while (1) {
			flag = remove_ball();
			if (flag == 1) break;
			else {
				exitFlag = check_ball();
				if (exitFlag == 1) break;
			}
			move_ice();
			//print_info();
		}
		if (exitFlag == 1) break;
		flag = divide_ball();
		if (flag == 0) break;
		//print_info();
	}
	cout << Answer << endl;
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

	shark[0] = (N + 1) / 2;
	shark[1] = shark[0];
}

int main(void) {
	Input();
	Solution();
	return 0;
}