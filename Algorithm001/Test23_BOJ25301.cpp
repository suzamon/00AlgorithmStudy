#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, K, Answer = 0;
int map[21][21] = { 0, };
int teamMap[21][21] = { 0, };

struct Person {
	int idx, x, y, tNum, cnt;
	Person* bP;
	Person* nP;
};

deque <Person*> team[5];
deque <Person> dq;

int dx[5] = { 0, 0, -1, 0, 1 };
int dy[5] = { 0, 1, 0, -1, 0 };

bool inRange(int xx, int yy) {
	if (xx >= 1 && xx <= N && yy >= 1 && yy <= N) return true;
	return false;
}

void print_info() {
	Person* p;

	for (int idx = 0; idx < M; idx++) {
		cout << idx << "¹ø ÆÀ Á¤º¸ " << endl;
		p = team[idx].front();
		while (1) {
			cout << p->cnt<<"¹øÂ° »ç¶÷: (" << p->x << ", " << p->y << ") " << endl;
			if (p->nP == nullptr) break;
			p = p->nP;
		}
	}
	cout << endl;
	cout << "¸Ê Á¤º¸" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "ÆÀ ¸Ê Á¤º¸" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << teamMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

}

void find_team(int tIdx) {
	int sX, sY, nX, nY, d, flag = 0, cnt, idx;
	int visited[21][21] = { 0, };

	Person bP, nP;
	
	queue <pair <int, pair<int, int>>> q;
	bP = *team[tIdx].front();
	q.push(make_pair(1, make_pair(bP.x, bP.y)));
	visited[bP.x][bP.y] = 1;
	teamMap[bP.x][bP.y] = tIdx + 1;
	cnt = 1;

	while (!q.empty()) {
		idx = q.front().first;
		sX = q.front().second.first, sY = q.front().second.second;
		q.pop();
		if (map[sX][sY] == 3) break;
		for (d = 1; d <= 4; d++) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY) || visited[nX][nY] == 1 || map[nX][nY] > 3) continue;
			
			if (map[nX][nY] == idx || map[nX][nY] == idx + 1) {
				cnt++;
				nP.idx = map[nX][nY], nP.x = nX, nP.y = nY, nP.cnt = cnt, nP.tNum = tIdx, nP.nP = nullptr;
				
				if (flag == 0) nP.bP = team[tIdx].front();
				else nP.bP = &dq.back();
				
				teamMap[nX][nY] = tIdx + 1;
				dq.push_back(nP);
				
				if (flag == 0) team[tIdx].front()->nP = &dq.back();
				else {
					(*dq.back().bP).nP = &dq.back();
				}

				if (flag == 0) flag = 1;
				bP = nP;
				q.push(make_pair(nP.idx, make_pair(nX, nY)));
				visited[nX][nY] = 1;
				break;
			}
		}
	}

}

void move_team(int idx) {
	//Person* bP = team[idx].front();
	Person* nP = team[idx].front();
	int sX, sY, nX, nY, d, flag = 0;
	
	while (1) {
		if (flag == 0) {
			sX = nP->x, sY = nP->y;
			for (d = 1; d <= 4; d++) {
				nX = sX + dx[d], nY = sY + dy[d];
				if (!inRange(nX, nY)) continue;

				if (map[nX][nY] == 3 || map[nX][nY] == 4) {
					teamMap[nX][nY] = idx + 1;
					map[nX][nY] = nP->idx;
					nP->x = nX, nP->y = nY;
					break;
				}
			}
			nP = nP->nP;
			flag++;
		}
		else {
			nX = nP->x, nY = nP->y;
			nP->x = sX, nP->y = sY;
			map[sX][sY] = nP->idx;
			if (nP->nP == nullptr) {
				sX = team[idx].front()->x, sY = team[idx].front()->y;
				if (sX != nX || sY != nY) {
					teamMap[nX][nY] = 0;
					map[nX][nY] = 4;
				}
				break;
			}
			sX = nX, sY = nY;
			nP = nP->nP;
		}
		
	}


}

void find_score(int xx, int yy, int pIdx, int tIdx) {
	int score;

	Person* p = team[tIdx].front()->nP;

	if (pIdx == 1 && xx == team[tIdx].front()->x && yy == team[tIdx].front()->y) {
		Answer = Answer + team[tIdx].front()->cnt * team[tIdx].front()->cnt;
	}
	else {
		while (1) {
			if (pIdx == p->idx && xx == p->x && yy == p->y) {
				Answer = Answer + (p->cnt*p->cnt);
				break;
			}
			p = p->nP;
			if (p == nullptr) break;
		}
	}
	
	Person* bP;
	Person* nP;
	p = team[tIdx].front();
	int cnt = 1;

	while (p->nP != nullptr) {
		p = p->nP;
	}
	team[tIdx].front() = p;

	while (1) {
		bP = p->bP;
		nP = p->nP;

		p->cnt = cnt;
		p->bP = p->nP;
		p->nP = bP;

		if (p->idx == 1) {
			p->idx = 3;
			map[p->x][p->y] = p->idx;
		}
		else if (p->idx == 3) {
			p->idx = 1;
			map[p->x][p->y] = p->idx;
		}

		if (bP == nullptr) break;

		p = bP;
		cnt++;
	}
	//cout << Answer << endl;
}

void move_ball(int round) {
	int row, col, d;

	if (round <= N) {
		d = 1;
		row = round;
		col = 1;
	}
	else if (round <= 2 * N) {
		d = 2;
		row = N;
		col = round - N;
	}
	else if (round <= 3 * N) {
		d = 3;
		row = N - (round - 2 * N) + 1;
		col = N;
	}
	else if (round <= 4 * N) {
		d = 4;
		row = 1;
		col = N - (round - 3 * N) + 1;
	}
	int nX = row, nY = col, retIdx = -1;
	while (1) {
		if (map[nX][nY] >= 1 && map[nX][nY] <= 3) {
			//cout << nX << ", " << nY << "¿¡ " << teamMap[nX][nY] << "ÆÀ ¸ÂÀ½" << endl;
			find_score(nX, nY, map[nX][nY], teamMap[nX][nY] - 1);
			break;
		}
		nX = nX + dx[d], nY = nY + dy[d];
		if (!inRange(nX, nY)) break;
	}

}

void Solution() {
	for (int i = 0; i < M; i++) find_team(i);
	//print_info();

	int time, round = 0;
	for (time = 1; time <= K; time++) {
		for (int i = 0; i < M; i++) move_team(i);
		//print_info();

		round++;
		if (round > 4 * N) round = round - 4 * N;
		move_ball(round);
		//print_info();
	}
	cout << Answer << endl;
}

void Input() {
	int tIdx = 0, idx = 0;
	Person head;
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				head.x = i, head.y = j, head.tNum = tIdx, head.idx = map[i][j], head.cnt = 1;
				head.bP = nullptr, head.nP = nullptr;
				dq.push_back(head);
				team[tIdx].push_back(&dq.back());
				tIdx++;
			}
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}