#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int Answer;
int map[17][17];
int startPos[2];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int BFS() {
	int startX, startY, nextX, nextY, retflag = 0;
	int visited[16][16] = { 0, };
	queue <pair<int, int >> q;

	q.push(make_pair(startPos[0], startPos[1]));
	visited[startPos[0]][startPos[1]] = 1;

	while (!q.empty()) {
		startX = q.front().first;
		startY = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX < 0 || nextX >= 16 || nextY < 0 || nextY >= 16) continue;

			if (visited[nextX][nextY] == 0 && map[nextX][nextY] != 1) {
				if (map[nextX][nextY] == 3) {
					retflag = 1;
					break;
				}
				q.push(make_pair(nextX, nextY));
				visited[nextX][nextY] = 1;
			}
		}

		if (retflag == 1) break;
	}

	if (!q.empty()) {
		while (!q.empty()) {
			q.pop();
		}
	}

	return retflag;

}

void Solution() {
	Answer = BFS();
}

void Input() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			scanf("%1d", &map[i][j]);
			if (map[i][j] == 2) {
				startPos[0] = i;
				startPos[1] = j;
			}
		}
	}
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