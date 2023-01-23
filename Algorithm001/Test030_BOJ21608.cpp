/* 1'42''14'''
상어 초등학교에는 교실이 하나 있고, 교실은 N×N 크기의 격자로 나타낼 수 있다. 학교에 다니는 학생의 수는 N^2명이다.
오늘은 모든 학생의 자리를 정하는 날이다. 학생은 1번부터 N^2번까지 번호가 매겨져 있고, (r, c)는 r행 c열을 의미한다.
교실의 가장 왼쪽 윗 칸은 (1, 1)이고, 가장 오른쪽 아랫 칸은 (N, N)이다.

선생님은 학생의 순서를 정했고, 각 학생이 좋아하는 학생 4명도 모두 조사했다.
이제 다음과 같은 규칙을 이용해 정해진 순서대로 학생의 자리를 정하려고 한다.
한 칸에는 학생 한 명의 자리만 있을 수 있고, |r1 - r2| + |c1 - c2| = 1을 만족하는 두 칸이 (r1, c1)과 (r2, c2)를 인접하다고 한다.

1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
2. 1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
3. 2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로,
   그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.

이제 학생의 만족도를 구해야 한다. 학생의 만족도는 자리 배치가 모두 끝난 후에 구할 수 있다.
학생의 만족도를 구하려면 그 학생과 인접한 칸에 앉은 좋아하는 학생의 수를 구해야 한다.
그 값이 0이면 학생의 만족도는 0, 1이면 1, 2이면 10, 3이면 100, 4이면 1000이다.
학생의 만족도의 총 합을 구해보자.

입력
첫째 줄에 N이 주어진다. 둘째 줄부터 N^2개의 줄에 학생의 번호와 그 학생이 좋아하는 학생 4명의 번호가 한 줄에 하나씩
선생님이 자리를 정할 순서대로 주어진다.
학생의 번호는 중복되지 않으며, 어떤 학생이 좋아하는 학생 4명은 모두 다른 학생으로 이루어져 있다.
입력으로 주어지는 학생의 번호, 좋아하는 학생의 번호는 N2보다 작거나 같은 자연수이다. 어떤 학생이 자기 자신을 좋아하는 경우는 없다.

출력
첫째 줄에 학생의 만족도의 총 합을 출력한다.

제한
3 ≤ N ≤ 20

struct Student{ int idx, int prefer[4]}
struct NextPos{ int preferCnt, int emptyCnt, int x, int y}
int map[21][21], visited[21][21] ={0, };
N, dq <Student> dq;

1. Input()
	N, maxStudent, Student, dq에 넣기
2. Solution()
	1) for(int i=0; i<dq.size(); i++) insert_student(i)
	2) void insert_student(int dqIdx)
		1) if(dqIdx==0) map[2][2] = dq[dqIdx].idx & visited[2][2] = 1 & return
		2) int sX, sY, nX, nY tmpPrefer, tmpEmpty, maxPrefer = 0;
		3) deque <NextPos> possible;
		3) for(int sX=1; sX <=N; sX++) for(int sY=1;sY <=N; sY++)
		4) if(map[sX][sY] > 0) continue;
		5) tmpPrefer =0, tmpEmpty = 0;
		5) for(int d=0; d<4; d++) {
		6) nX = sX + dx[d], nY = sY + dy[d]
		6) if(!inRange(nX,nY)) continue;
		7) if(map[nX][nY] == 0) emptyCnt++;
		8) else {for(int i=0; i<4; i++) { if(map[nX][nY] == dq[dqIdx].prefer[i]) preferCnt++ & break} }
		9)}
		10) if(maxPrefer < tmpPrefer) maxPrefer = tmpPrefer
		11) else continue;
		12) sort(possible, possible + possible.cnt, compare)
		13) [0]에 위치한 map에 표기 & goodbye

*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

struct Student {
	int idx;
	int prefer[4];
	int fX, fY;


};
struct NextPos {
	int preferCnt, emptyCnt, x, y;
	/*
	bool operator <(NextPos &nextpos) {
		if (this->preferCnt == nextpos.preferCnt) {
			if (this->emptyCnt == nextpos.emptyCnt) {
				if (this->x == nextpos.x) {
					return this->y < nextpos.y;
				}
				return this->x < nextpos.y;
			}
			return this->emptyCnt > nextpos.emptyCnt;
		}
		return this->preferCnt > nextpos.preferCnt;
	}*/
};

int N, maxStudent, Answer = 0;
int map[21][21];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

deque <Student> dq;

void print_map() {
	int sX, sY;
	cout << "맵 정보" << endl;
	for (sX = 1; sX <= N; sX++) {
		for (sY = 1; sY <= N; sY++) {
			cout << map[sX][sY] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int  yy) {
	if (xx <1 || xx >N || yy <1 || yy >N) return false;
	return true;
}

void find_answer() {
	int sX, sY, nX, nY, preferCnt, tmpScore;
	Answer = 0;
	for (int dqIdx = 0; dqIdx < dq.size(); dqIdx++) {
		sX = dq[dqIdx].fX, sY = dq[dqIdx].fY;
		preferCnt = 0;
		for (int d = 0; d < 4; d++) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY)) continue;

			for (int i = 0; i < 4; i++) {
				if (map[nX][nY] == dq[dqIdx].prefer[i]) {
					preferCnt++;
					break;
				}
			}
		}

		if (preferCnt == 0) continue;
		tmpScore = pow(10, preferCnt - 1);
		Answer = Answer + tmpScore;
	}

	//cout << Answer << endl;
}

bool compare(NextPos a, NextPos b) {
	if (a.preferCnt == b.preferCnt) {
		if (a.emptyCnt == b.emptyCnt) {
			if (a.x == b.x) {
				return a.y < b.y;
			}
			return a.x < b.y;
		}
		return a.emptyCnt > b.emptyCnt;
	}
	return a.preferCnt > b.preferCnt;
}


void inser_studet(int dqIdx) {
	if (dqIdx == 0) {
		map[2][2] = dq[dqIdx].idx;
		dq[dqIdx].fX = 2, dq[dqIdx].fY = 2;
		return;
	}

	int sX, sY, nX, nY, tmpPrefer, tmpEmpty, studentIdx;
	int maxPrefer = -1, maxEmpty = -1 ,minX = 21, minY = 21;

	NextPos tmpPos;

	for (sX = 1; sX <= N; sX++) {
		for (sY = 1; sY <= N; sY++) {
			if (map[sX][sY] > 0) continue;
			tmpPrefer = 0, tmpEmpty = 0;
			for (int d = 0; d < 4; d++) {
				nX = sX + dx[d], nY = sY + dy[d];
				if (!inRange(nX, nY)) continue;

				if (map[nX][nY] == 0) tmpEmpty++;
				else {
					for (int pIdx = 0; pIdx < 4; pIdx++) {
						if (map[nX][nY] == dq[dqIdx].prefer[pIdx]) {
							tmpPrefer++;
							break;
						}
					}
				}
			}

			if (maxPrefer < tmpPrefer) {
				maxPrefer = tmpPrefer;
				maxEmpty = tmpEmpty;
				minX = sX;
				minY = sY;
			}
			else if (maxPrefer == tmpPrefer && maxEmpty <= tmpEmpty) {
				if (maxEmpty == tmpEmpty && minX >= sX) {
					if (minX == sX && minY > sY) {
						maxPrefer = tmpPrefer;
						maxEmpty = tmpEmpty;
						minX = sX;
						minY = sY;
					}
					else if(minX > sX) {
						maxPrefer = tmpPrefer;
						maxEmpty = tmpEmpty;
						minX = sX;
						minY = sY;
					}
				}
				else if(maxEmpty < tmpEmpty){
					maxPrefer = tmpPrefer;
					maxEmpty = tmpEmpty;
					minX = sX;
					minY = sY;
				}
			}
		}
	}

	studentIdx = dq[dqIdx].idx;
	nX = minX, nY = minY;
	map[nX][nY] = studentIdx;
	dq[dqIdx].fX = nX, dq[dqIdx].fY = nY;


}

void Solution() {
	for (int i = 0; i < dq.size(); i++) {
		inser_studet(i);
		//print_map();
	}
	find_answer();
}

void Input() {
	cin >> N;
	maxStudent = N * N;
	Student s;
	for (int i = 0; i < maxStudent; i++) {
		cin >> s.idx;
		for (int j = 0; j < 4; j++) {
			cin >> s.prefer[j];
		}
		s.fX = 0, s.fY = 0;
		dq.push_back(s);
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}