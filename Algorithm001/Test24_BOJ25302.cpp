#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, K, C, Answer = 0;

struct Tree {
	int x, y, cnt;
};

int killMap[21][21][2] = { 0, };
Tree* map[21][21] = { 0, };

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, -1, 0, 1 };
int ddx[5] = { 0, -1, 1, 1, -1 };
int ddy[5] = { 0, 1, 1, -1, -1 };

deque <Tree> tree;
deque <Tree> w;
deque <Tree> addTree;

void print_info() {
	cout << "맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == nullptr) cout << '0' << "   ";
			else if(map[i][j]->cnt >= 10  || map[i][j]->cnt == -1)cout << map[i][j]->cnt << "  ";
			else cout << map[i][j]->cnt << "   ";
		}
		cout << endl;
	}
	cout << "살충제 맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << '('<<killMap[i][j][0] << ", " << killMap[i][j][1] << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int yy) {
	if (xx >= 1 && xx <= N && yy >= 1 && yy <= N) return true;
	return false;
}

void grow_tree(int idx) {
	Tree* t = &tree[idx];

	int sX, sY, nX, nY, d, cnt = 0;
	sX = t->x, sY = t->y;
	for (d = 1; d <= 4; d++) {
		nX = sX + dx[d], nY = sY + dy[d];
		if (!inRange(nX, nY)) continue;
		if (killMap[nX][nY][0] == 0 && map[nX][nY] != nullptr && map[nX][nY]->cnt > 0) {
			cnt++;
		}
	}
	t->cnt = t->cnt + cnt;
}

void find_new_tree(int idx) {
	Tree* t = &tree[idx];

	int sX, sY, nX, nY, d, cnt = 0, val;
	sX = t->x, sY = t->y, val = t->cnt;
	deque <pair< int, int>> dq;

	for (d = 1; d <= 4; d++) {
		nX = sX + dx[d], nY = sY + dy[d];
		if (!inRange(nX, nY)) continue;
		if (killMap[nX][nY][0] == 0 && map[nX][nY] == nullptr) {
			cnt++;
			dq.push_back(make_pair(nX, nY));
		}
	}

	if (cnt == 0) {
		while (!dq.empty()) dq.pop_front();
		return;
	}

	val = (int)val / cnt;
	if (val == 0) {
		while (!dq.empty()) dq.pop_front();
		return;
	}

	while (!dq.empty()) {
		nX = dq.front().first, nY = dq.front().second;
		dq.pop_front();
		addTree.push_back({ nX, nY, val });
	}

}

void add_new_tree() {
	Tree t;

	while (!addTree.empty()) {
		t = addTree.front();
		addTree.pop_front();
		if (map[t.x][t.y] != nullptr) {
			map[t.x][t.y]->cnt = map[t.x][t.y]->cnt + t.cnt;
		}
		else {
			tree.push_back(t);
			map[t.x][t.y] = &tree.back();
		}
	}
}

int find_pos(int xx, int yy) {
	int nX, nY, dd, cnt = map[xx][yy]->cnt;

	for (dd = 1; dd <= 4; dd++) {
		nX = xx, nY = yy;
		for (int k = 0; k < K; k++) {
			nX = nX + ddx[dd], nY = nY + ddy[dd];
			if (!inRange(nX, nY) || map[nX][nY] == nullptr) break;
			if (map[nX][nY]->cnt == -1) break;
			else if (map[nX][nY]->cnt > 0) {
				cnt = cnt + map[nX][nY]->cnt;
			}
		}
	}
	return cnt;
}

void kill_simulation(int xx, int yy) {
	int nX, nY, dd, cnt = map[xx][yy]->cnt;


	map[xx][yy]->cnt = -1;
	map[xx][yy] = nullptr;
	killMap[xx][yy][0] = 1, killMap[xx][yy][1] = C + 1;

	for (dd = 1; dd <= 4; dd++) {
		nX = xx, nY = yy;
		for (int k = 0; k < K; k++) {
			nX = nX + ddx[dd], nY = nY + ddy[dd];
			if (!inRange(nX, nY)) break;
			if (map[nX][nY] == nullptr) {
				killMap[nX][nY][0] = 1, killMap[nX][nY][1] = C + 1;
				break;
			}

			if (map[nX][nY]->cnt == -1) break;
			else if (map[nX][nY]->cnt > 0) {
				cnt = cnt + map[nX][nY]->cnt;
				map[nX][nY]->cnt = -1;
				map[nX][nY] = nullptr;
				killMap[nX][nY][0] = 1, killMap[nX][nY][1] = C + 1;
			}
		}
	}

	Answer = Answer + cnt;
}

void update_map() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (killMap[i][j][0] == 1) {
				killMap[i][j][1]--;
				if (killMap[i][j][1] == 0) killMap[i][j][0] = 0;
			}
		}
	}

	int treeSize = tree.size();
	Tree t;
	for(int i=0; i<treeSize; i++){
		t = tree.front();
		tree.pop_front();
		if (t.cnt == -1) continue;
		tree.push_back(t);
	}

	Tree* tmpT;
	for (int i = 0; i < tree.size(); i++) {
		tmpT = &tree[i];
		if (map[tmpT->x][tmpT->y] == nullptr) map[tmpT->x][tmpT->y] = tmpT;
		else if (map[tmpT->x][tmpT->y] != tmpT) map[tmpT->x][tmpT->y] = tmpT;
	}
}

void kill_tree() {
	int fCnt = 0, fX = 0, fY = 0, sX, sY, sCnt = 0;
	for (int i = 0; i < tree.size(); i++) {
		sX = tree[i].x, sY = tree[i].y;
		sCnt = find_pos(sX, sY);
		if (sCnt > fCnt) {
			fCnt = sCnt, fX = sX, fY = sY;
		}
		else if (sCnt == fCnt) {
			if (fX > sX) {
				fX = sX, fY = sY;
			}
			else if (fX == sX && fY > sY) {
				fY = sY;
			}
		}
	}
	//cout << '(' << fX << ", " << fY << ") 위치: " << fCnt << endl;
	kill_simulation(fX, fY);
	update_map();

}

void Solution() {
	//print_info();
	int time;
	for (time = 1; time <= M; time++) {
		if (tree.size() == 0) break;
		for (int idx = 0; idx < tree.size(); idx++) {
			grow_tree(idx);
		}
		//print_info();

		for (int idx = 0; idx < tree.size(); idx++) {
			find_new_tree(idx);
		}
		add_new_tree();
		//print_info();
		kill_tree();
		//print_info();
	}
	cout << Answer << endl;
}

void Input() {
	int tmpVal;
	cin >> N >> M >> K >> C;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> tmpVal;
			if (tmpVal == 0) map[i][j] = nullptr;
			else if (tmpVal == -1) {
				w.push_back({ i, j, -1 });
				map[i][j] = &w.back();
			}
			else {
				tree.push_back({ i, j, tmpVal });
				map[i][j] = &tree.back();
			}
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}