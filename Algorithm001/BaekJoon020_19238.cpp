#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N, M;
long fuel;

int map[21][21];
int goal[403][2];
int taxi[2];

int peopleCnt = 0;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_map() {
	cout << "맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "택시 위치: (" << taxi[0] << ", " << taxi[1] <<"), 연료: "<< fuel << endl;
}

bool compare(pair <int, pair<int, int>> a, pair <int, pair<int, int>> b) {
	if (a.second.first == b.second.first) {
		a.second.second < b.second.second;
	}
	return a.second.first < b.second.first;
}

int move_sim(int nextGoal) {
	int goalX = goal[nextGoal][0], goalY = goal[nextGoal][1];

	int startX, startY, curF, nextX, nextY, goalF, retFlag;
	int visited[21][21] = { 0, };
	queue <pair <int, pair<int, int>>> q;

	startX = taxi[0];
	startY = taxi[1];
	visited[startX][startY] = 1;
	
	if (goalX == startX && goalY == startY) {
		retFlag = 1;
		return retFlag;
	}

	q.push(make_pair(0, make_pair(startX, startY)));

	goalF = -1;
	while (!q.empty()) {
		curF = q.front().first;
		startX = q.front().second.first;
		startY = q.front().second.second;
		q.pop();

		if (curF >= fuel || goalF != -1) continue;

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX > 0 && nextX <= N && nextY > 0 && nextY <= N && map[nextX][nextY] != 1 && visited[nextX][nextY] == 0) {
				if (nextX == goalX && nextY == goalY) {
					if(goalF == -1) goalF = curF + 1;
					visited[nextX][nextY] = 1;
					break;
				}
				else {
					visited[nextX][nextY] = 1;
					q.push(make_pair(curF + 1, make_pair(nextX, nextY)));
				}
			}
		}
	}

	if (goalF == -1) {
		fuel = -1;
		retFlag = 0;
	}
	else {
		taxi[0] = goalX;
		taxi[1] = goalY;

		fuel += goalF;
		retFlag = 1;
	}

	return retFlag;
}

int find_people() {
	int startX, startY, curF, nextX, nextY, goalF;
	int retPeople;
	int visited[21][21] = { 0, };
	queue <pair <int, pair<int, int>>> q;
	vector <pair <int, pair<int, int>>> v;

	startX = taxi[0];
	startY = taxi[1];
	visited[startX][startY] = 1;

	if (map[startX][startY] >= 2) {
		retPeople = map[startX][startY];
		taxi[0] = startX;
		taxi[1] = startY;
		map[taxi[0]][taxi[1]] = 0;
		return retPeople;
	}

	q.push(make_pair(0, make_pair(startX, startY)));

	goalF = -1;
	while (!q.empty()) {
		curF = q.front().first;
		startX = q.front().second.first;
		startY = q.front().second.second;
		q.pop();

		if (curF >= fuel) continue;
		if (goalF != -1 && goalF <= curF) continue;

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX > 0 && nextX <= N && nextY > 0 && nextY <= N && map[nextX][nextY] != 1 && visited[nextX][nextY] == 0 ) {
				if (map[nextX][nextY] == 0) {
					visited[nextX][nextY] = 1;
					q.push(make_pair(curF + 1, make_pair(nextX, nextY)));
				}
				else {
					visited[nextX][nextY] = 1;
					if(goalF == -1) goalF = curF + 1;
					else if (curF + 1 > goalF) continue;

					v.push_back(make_pair(map[nextX][nextY], make_pair(nextX, nextY)));
				}
			}
		}
	}
	
	if (v.size() == 0) {
		fuel = -1;
		retPeople = 0;
	}
	else if (v.size() == 1) {
		retPeople = v[0].first;
		taxi[0] = v[0].second.first;
		taxi[1] = v[0].second.second;
		map[taxi[0]][taxi[1]] = 0;
		fuel -= goalF;
	}
	else {
		sort(v.begin(), v.end(), compare);
		retPeople = v[0].first;
		taxi[0] = v[0].second.first;
		taxi[1] = v[0].second.second;
		map[taxi[0]][taxi[1]] = 0;
		fuel -= goalF;
	}

	if (v.size() > 0) v.clear();

	return retPeople;

}

void Solve() {
	int nextPeopleNum = 0, nextFlag = 0;
	int tmpCnt = 0;

	//print_map();
	peopleCnt = 0;
	while (1) {
		nextPeopleNum = find_people();
		//cout << "태울 사람 선택: " << nextPeopleNum << endl;
		//print_map();

		if (nextPeopleNum == 0) break;
		
		nextFlag = move_sim(nextPeopleNum);
		//cout << "택시 이동 후 " << endl;
		//print_map();
		if (nextFlag == 0) break;
		
		peopleCnt++;
		if (peopleCnt == M) break;
	}
}

void Input() {
	cin >> N >> M >> fuel;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	
	cin >> taxi[0] >> taxi[1];

	int peopleNum = 2, tmpX, tmpY;
	for (int i = 0; i < M; i++) {
		cin >> tmpX >> tmpY;
		map[tmpX][tmpY] = peopleNum;
		cin >> goal[peopleNum][0] >> goal[peopleNum][1];
		peopleNum++;
	}

}

int main(void) {
	Input();
	Solve();
	cout << fuel << endl;
	return 0;
}