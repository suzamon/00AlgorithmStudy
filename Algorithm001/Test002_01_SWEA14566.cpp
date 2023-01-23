#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

int N, maxH, Answer = 0;
int map[101][101];

deque <pair <int, pair<int, int>>> h;
queue <pair<int, int>> deadH;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_info(int time) {
	/*
	cout << "dq 정보" << endl;
	for (int i = 0; i < h.size(); i++) {
		cout << h[i].first << " 높이: " << h[i].second.first << ", " << h[i].second.second << endl;
	}
	cout << endl;
	*/
	cout << time << "초 후 맵 정보" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool compare(pair <int, pair<int, int>> a, pair <int, pair<int, int>> b) {
	return a.first < b.first;
}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy < N) return true;
	return false;
}

int find_land(int time) {
	int idx = 0, dqSize, sX, sY, nX, nY, tmpH;
	int visited[101][101] = { 0, };

	queue <pair <int, int>> q;

	dqSize = h.size();
	for (int i = 0; i < dqSize; i++) {
		tmpH = h.front().first;
		sX = h.front().second.first, sY = h.front().second.second;
		h.pop_front();
		h.push_back(make_pair(tmpH, make_pair(sX, sY)));
		if (visited[sX][sY] != 0) continue;
		idx++;
		visited[sX][sY] = idx;

		q.push(make_pair(sX, sY));
		while (!q.empty()) {
			sX = q.front().first, sY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nX = sX + dx[d], nY = sY + dy[d];
				if (!inRange(nX, nY)) continue;

				if (map[nX][nY] != 0 && visited[nX][nY] == 0) {
					visited[nX][nY] = idx;
					q.push(make_pair(nX, nY));
				}
			}
		}
	}
	/*
	print_info(time);
	cout << time << "초 후 visted 맵 정보" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << visited[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
	return idx;
}

int update_map(int time) {
	int xx, yy, remCnt = 0;

	while (!deadH.empty())deadH.pop();

	while (!h.empty()) {
		if (h.front().first > time) break;
		xx = h.front().second.first;
		yy = h.front().second.second;
		remCnt++;
		map[xx][yy] = 0;
		h.pop_front();
		deadH.push(make_pair(xx, yy));
	}
	return remCnt;
}

void reset_map(int time) {
	int xx, yy, tmpCnt;

	if (deadH.size() == N * N) {
		Answer = 1;
		while (!deadH.empty()) deadH.pop();
		return;
	}

	while (!deadH.empty()) {
		xx = deadH.front().first, yy = deadH.front().second;
		map[xx][yy] = time - 1;
		deadH.pop();
		h.push_back(make_pair(time - 1, make_pair(xx, yy)));
	}

	tmpCnt = find_land(time);
	if (tmpCnt > Answer) Answer = tmpCnt;
}

int skip_check() {
	if (h.front().first == h.back().first) {
		while (!h.empty()) h.pop_front();
		while (!deadH.empty()) deadH.pop();
		return 1;
	}
	else return 0;
}

int check_map() {
	int ret = 0;

	int row = 0, col = 0;
	for (col = 1; col < N - 1; col++) {
		if (map[row][col] != 0) continue;
		for (int col2 = col - 1; col2 >= 0; col2--) {
			row++;
			if (!inRange(row, col2)) {
				ret = 1;
				break;
			}
			if (map[row][col2] != 0) {
				ret = 1;
				break;
			}
		}
		if (ret == 0) break;
		row = 0;
		for (int col2 = col + 1; col2 < N; col2++) {
			row++;
			if (!inRange(row, col2)) {
				ret = 1;
				break;
			}
			if (map[row][col2] != 0) {
				ret = 1;
				break;
			}
		}
	}
	if (ret == 0) return ret;
	row = N - 1;
	for (col = 1; col < N - 1; col++) {
		if (map[row][col] != 0) continue;
		for (int col2 = col - 1; col2 >= 0; col2--) {
			row--;
			if (!inRange(row, col2)) {
				ret = 1;
				break;
			}
			if (map[row][col2] != 0) {
				ret = 1;
				break;
			}
		}
		if (ret == 0) break;
		row = 0;
		for (int col2 = col + 1; col2 < N; col2++) {
			row--;
			if (!inRange(row, col2)) {
				ret = 1;
				break;
			}
			if (map[row][col2] != 0) {
				ret = 1;
				break;
			}
		}
	}
	return ret;
}

void Solution() {
	int tmpCnt, flag = 0, Nflag = 0, skipFlag = 1;
	for (int time = 1; time <= maxH; time++) {
		if (skip_check() == 1) {
			if (Answer == 0) Answer = 1;
			break;
		}
		Nflag = flag + update_map(time);
		if (Nflag == flag) continue;
		if (Nflag < N && skipFlag == 1) {
			if (Nflag >= 2) {
				skipFlag = check_map();
				if (skipFlag == 1) continue;
			}
		}
		if (h.size() <= 1) {
			if (Answer < 2) {
				reset_map(time);
			}
			break;
		}
		tmpCnt = find_land(time);

		flag = Nflag;
		if (tmpCnt > Answer) Answer = tmpCnt;
	}

}

void Input() {
	while (!h.empty()) {
		h.pop_front();
	}

	cin >> N;
	maxH = 0;
	Answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			//if (maxH < map[i][j]) maxH = map[i][j];
			h.push_back(make_pair(map[i][j], make_pair(i, j)));
		}
	}

	sort(h.begin(), h.end());
	maxH = h.back().first;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}