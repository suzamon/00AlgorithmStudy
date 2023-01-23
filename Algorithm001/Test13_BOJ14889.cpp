#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

#define MAX_N 21

using namespace std;

int N, Answer = -1, teamACnt = 0, teamBCnt = 0;
int arr[MAX_N][MAX_N], teamA[MAX_N], teamB[MAX_N];

int find_diff() {
	int tmpIdx, tmpIdx2, sumA = 0, sumB = 0;

	for (int i = 1; i <= teamACnt; i++) {
		tmpIdx = teamA[i];
		for (int j = 1; j <= teamACnt; j++) {
			tmpIdx2 = teamA[j];
			if (tmpIdx == tmpIdx2) continue;
			sumA = sumA + arr[tmpIdx][tmpIdx2];
		}
	}

	for (int i = 1; i <= teamBCnt; i++) {
		tmpIdx = teamB[i];
		for (int j = 1; j <= teamBCnt; j++) {
			tmpIdx2 = teamB[j];
			if (tmpIdx == tmpIdx2) continue;
			sumB = sumB + arr[tmpIdx][tmpIdx2];
		}
	}

	int retDiff = abs(sumA - sumB);
	return retDiff;
}

void findTeam(int idx) {
	if (idx > N) {
		int teamDiff = find_diff();
		if (Answer == -1) Answer = teamDiff;
		else if (Answer > teamDiff) Answer = teamDiff;
		//if (Answer == 0) {
		//	cout << "TEST" << endl;
		//}
		return;
	}

	for (int i = 1; i <= 2; i++) {
		if (i == 1 && teamACnt < N / 2) {
			teamA[teamACnt + 1] = idx;
			teamACnt++;
			findTeam(idx + 1);
			teamACnt--;
		}
		else if (i == 2 && teamBCnt < N / 2) {
			teamB[teamBCnt + 1] = idx;
			teamBCnt++;
			findTeam(idx + 1);
			teamBCnt--;
		}
	}
}

void Solution() {
	for (int i = 1; i <= 2; i++) {
		if (i == 1) {
			teamA[teamACnt + 1] = 1;
			teamACnt++;
			findTeam(2);
			teamACnt--;
		}
		else {
			teamB[teamBCnt + 1] = 1;
			teamBCnt++;
			findTeam(2);
			teamBCnt--;
		}
	}

	cout << Answer << endl;
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

}


int main(void) {
	Input();
	Solution();
	return 0;
}