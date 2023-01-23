#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

int N, M, K, Answer;
deque <int> map[51][51];
deque <pair<pair<int, int>, pair<pair<int, int>, pair<int, int>>>> fireball;

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0 ,-1, -1, -1 };

void print_map() {
	cout << "맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() >= 1) {
				cout << '(' << i << ", " << j << ") 위치에 ";
				for (int k = 0; k < map[i][j].size(); k++) {
					cout << map[i][j][k] << "번 ";
				}
				cout << "파이어볼 존재" << endl;
			}
		}
	}
	cout << endl;
}

void print_fireball() {
	cout << "파이어볼 정보" << endl;
	for (int i = 0; i < fireball.size(); i++) {
		cout << i << "번 파이어볼 상태: " << fireball[i].first.first << ", 질량: " << fireball[i].first.second << ",위치 : (" << fireball[i].second.first.first << ", " << fireball[i].second.first.second << "), 속력: " << fireball[i].second.second.first << ", 방향: " << fireball[i].second.second.second << endl;
	}
	cout << endl;
}

void find_totalMass() {
	Answer = 0;
	int fSize = fireball.size();
	int fState, fM, fRow, fCol, fDir, fS;

	for (int i = 0; i < fSize; i++) {
		fState = fireball.front().first.first;
		if (fState == 1) {
			fireball.pop_front();
			continue;
		}
		fM = fireball.front().first.second;
		fireball.pop_front();

		Answer += fM;
	}
}

void union_fireball() {
	int fIdx, fState, fM, fRow, fCol, fDir, fS;
	long totalMass, totalVel;
	int totalCnt, checkFlag, totalDir;
	int nextMass, nextVel, nextDir;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() > 1) {
				totalCnt = map[i][j].size();
				totalMass = 0;
				totalVel = 0;
				
				fIdx = map[i][j].front();
				fDir = fireball[fIdx].second.second.second;
				checkFlag = fDir % 2;
				totalDir = 0;

				while (!map[i][j].empty()) {	
					fIdx = map[i][j].front();
					map[i][j].pop_front();	

					totalMass += fireball[fIdx].first.second;
					totalVel += fireball[fIdx].second.second.first;
					if (totalDir == 0) {
						fDir = fireball[fIdx].second.second.second;
						if (fDir % 2 != checkFlag) {
							totalDir = 1;
						}
					}
					fireball[fIdx].first.first = 1;
				}

				nextMass = totalMass / 5;
				if (nextMass == 0) continue;

				nextVel = totalVel / totalCnt;
				if (totalDir == 0) {
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 0))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 2))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 4))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 6))));
				}
				else if (totalDir == 1) {
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 1))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 3))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 5))));
					fireball.push_back(make_pair(make_pair(0, nextMass), make_pair(make_pair(i, j), make_pair(nextVel, 7))));
				}

			}
			else if (map[i][j].size() == 1) {
				map[i][j].pop_back();
			}
		}
	}
}

void move_fireball() {
	int fSize = fireball.size();
	int fIdx, fState, fM, fRow, fCol, fDir, fS;
	int nextRow, nextCol;

	fIdx = -1;
	for (int i = 0; i < fSize; i++) {
		fIdx++;
		fState = fireball.front().first.first;
		if (fState == 1) {
			fireball.pop_front();
			fIdx--;
			continue;
		}
		fM = fireball.front().first.second;
		fRow = fireball.front().second.first.first;
		fCol = fireball.front().second.first.second;
		fS = fireball.front().second.second.first;
		fDir = fireball.front().second.second.second;
		fireball.pop_front();

		nextRow = fRow + dx[fDir] * fS;
		nextCol = fCol + dy[fDir] * fS;

		//row 셋업
		while (nextRow < 1) {
			nextRow += N;
		}
		while (nextRow > N) {
			nextRow -= N;
		}
		//col 셋업
		while (nextCol < 1) {
			nextCol += N;
		}
		while (nextCol > N) {
			nextCol -= N;
		}


		fireball.push_back(make_pair(make_pair(fState, fM), make_pair(make_pair(nextRow, nextCol), make_pair(fS, fDir))));

		map[nextRow][nextCol].push_back(fIdx);

	}
}

void Solve() {
	int repeatCnt = 0;
	while (1) {
		repeatCnt++;
		move_fireball();
		//print_map();
		//print_fireball();

		union_fireball();
		//print_map();
		//print_fireball();

		if (repeatCnt == K) break;
	}

	find_totalMass();
}

void Input() {
	cin >> N >> M >> K;
	int tmpX, tmpY, tmpM, tmpS, tmpD;
	for (int i = 0; i < M; i++) {
		cin >> tmpX >> tmpY >> tmpM >> tmpS >> tmpD;

		fireball.push_back(make_pair(make_pair(0, tmpM), make_pair(make_pair(tmpX, tmpY), make_pair(tmpS, tmpD))));
	}
}

int main(void) {

	Input();
	//print_fireball();

	Solve();
	cout << Answer << endl;
	return 0;
}