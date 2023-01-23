#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

int N, studentNum,Answer;
int map[21][21];
int student[401][5];
int studentState[401][2];

int dx[4] = { -1, 1, 0, 0 }; //상하좌우
int dy[4] = { 0, 0, -1, 1 }; //상하좌우	

void print_map() {
	cout << "Map 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	int sIdx, startX, startY, nextX, nextY, nearCnt, score;
	//sort(student, student + studentNum);
	Answer = 0;
	for (int i = 0; i < studentNum; i++) {
		sIdx = student[i][0];

		startX = studentState[sIdx][0];
		startY = studentState[sIdx][1];
		nearCnt = 0;
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > N) continue;
			for (int j = 1; j < 5; j++) {
				if (map[nextX][nextY] == student[i][j]) {
					nearCnt++;
					break;
				}
			}
		}

		if (nearCnt == 0) score = 0;
		else if (nearCnt >= 1) {
			score = 1;
			for (int j = 0; j < nearCnt - 1; j++) {
				score *= 10;
			}
			Answer += score;
		}
	}
}

bool compare2(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	if (a.first == b.first) {
		if (a.second.first == b.second.first) {
			return a.second.second < b.second.second;
		}
		return a.second.first < b.second.first;
	}
	return a.first > b.first;
}

bool compare1(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
	if (a.first.first == b.first.first) {
		if (a.first.second == b.first.second) {
			if (a.second.first == b.second.first) {
				return a.second.second < b.second.second;
			}
			return a.second.first < b.second.first;
		}
		return a.first.second > b.first.second;
	}
	return a.first.first > b.first.first;
}

void find_seat() {
	int studentIdx, friendIdx, friendCnt;
	int fX, fY, startX, startY, nextX, nextY, tmpFriendIdx, tmpEmptyCnt, tmpFriendCnt;
	int studendX, studentY;

	deque <pair <pair<int, int>, pair<int, int>>> priority1;
	deque <pair <int, pair<int, int>>> priority2;

	for (int i = 0; i < studentNum; i++) {
		//cout << i << "번째 학생 앉힌 후" << endl;
		//print_map();

		studentIdx = student[i][0];

		if (i == 0) {
			map[2][2] = studentIdx;
			studentState[studentIdx][0] = 2;
			studentState[studentIdx][1] = 2;
			continue;
		}

		friendCnt = 0;
		for (int j = 1; j < 5; j++) {
			friendIdx = student[i][j];
			if (studentState[friendIdx][0] == 0 && studentState[friendIdx][1] == 0) continue;

			//friendCnt++;
			fX = studentState[friendIdx][0];
			fY = studentState[friendIdx][1];
			for (int d1 = 0; d1 < 4; d1++) {
				startX = fX + dx[d1];
				startY = fY + dy[d1];
				if (startX <= 0 || startX > N || startY <= 0 || startY > N || map[startX][startY] != 0) continue;
				tmpFriendCnt = 0;
				tmpEmptyCnt = 0;
				for (int d2 = 0; d2 < 4; d2++) {
					nextX = startX + dx[d2];
					nextY = startY + dy[d2];
					if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > N) continue;
					
					if (nextX == fX && nextY == fY) {
						tmpFriendCnt++;
					}
					else if (map[nextX][nextY] == 0) {
						tmpEmptyCnt++;
					}
					else {
						for (int k = 1; k < 5; k++) {
							tmpFriendIdx = student[i][k];
							if (tmpFriendIdx == friendIdx) continue;
							else if (tmpFriendIdx == map[nextX][nextY]) {
								tmpFriendCnt++;
								break;
							}
						}
					}
				}
				priority1.push_back(make_pair(make_pair(tmpFriendCnt, tmpEmptyCnt), make_pair(startX, startY)));
			}
		}
		if (priority1.size() == 1) {
			studendX = priority1.front().second.first;
			studentY = priority1.front().second.second;
			priority1.pop_back();
			map[studendX][studentY] = studentIdx;
			studentState[studentIdx][0] = studendX;
			studentState[studentIdx][1] = studentY;
			continue;
		}
		else if (priority1.size() > 1) {
			sort(priority1.begin(), priority1.end(), compare1);

			studendX = priority1.front().second.first;
			studentY = priority1.front().second.second;
			map[studendX][studentY] = studentIdx;
			studentState[studentIdx][0] = studendX;
			studentState[studentIdx][1] = studentY;
			priority1.clear();
			continue;
		}

		//좋아하는 친구 모두 배치 전
		for (int row = 1; row <= N; row++) {
			for (int col = 1; col <= N; col++) {
				if (map[row][col] == 0) {
					startX = row;
					startY = col;
					tmpEmptyCnt = 0;
					for (int d = 0; d < 4; d++) {
						nextX = startX + dx[d];
						nextY = startY + dy[d];
						if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > N) continue;
						if (map[nextX][nextY] == 0) tmpEmptyCnt++;
					}
					priority2.push_back(make_pair(tmpEmptyCnt, make_pair(startX, startY)));
				}
			}
		}
		if (priority2.size() == 1) {
			studendX = priority2.front().second.first;
			studentY = priority2.front().second.second;
			priority2.pop_back();
			map[studendX][studentY] = studentIdx;
			studentState[studentIdx][0] = studendX;
			studentState[studentIdx][1] = studentY;
			continue;
		}
		else if (priority2.size() > 1) {
			sort(priority2.begin(), priority2.end(), compare2);

			studendX = priority2.front().second.first;
			studentY = priority2.front().second.second;
			map[studendX][studentY] = studentIdx;
			studentState[studentIdx][0] = studendX;
			studentState[studentIdx][1] = studentY;
			priority2.clear();
			continue;
		}

	}

	//cout << "마지막 학생 앉힌 후" << endl;
	//print_map();

}

void Solution() {
	find_seat();
	find_answer();

}

void Input() {
	cin >> N;
	studentNum = N * N;
	for (int i = 0; i < studentNum; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> student[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;

	return 0;
}