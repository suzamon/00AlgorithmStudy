/* 1'42''14'''
��� �ʵ��б����� ������ �ϳ� �ְ�, ������ N��N ũ���� ���ڷ� ��Ÿ�� �� �ִ�. �б��� �ٴϴ� �л��� ���� N^2���̴�.
������ ��� �л��� �ڸ��� ���ϴ� ���̴�. �л��� 1������ N^2������ ��ȣ�� �Ű��� �ְ�, (r, c)�� r�� c���� �ǹ��Ѵ�.
������ ���� ���� �� ĭ�� (1, 1)�̰�, ���� ������ �Ʒ� ĭ�� (N, N)�̴�.

�������� �л��� ������ ���߰�, �� �л��� �����ϴ� �л� 4�� ��� �����ߴ�.
���� ������ ���� ��Ģ�� �̿��� ������ ������� �л��� �ڸ��� ���Ϸ��� �Ѵ�.
�� ĭ���� �л� �� ���� �ڸ��� ���� �� �ְ�, |r1 - r2| + |c1 - c2| = 1�� �����ϴ� �� ĭ�� (r1, c1)�� (r2, c2)�� �����ϴٰ� �Ѵ�.

1. ����ִ� ĭ �߿��� �����ϴ� �л��� ������ ĭ�� ���� ���� ĭ���� �ڸ��� ���Ѵ�.
2. 1�� �����ϴ� ĭ�� ���� ���̸�, ������ ĭ �߿��� ����ִ� ĭ�� ���� ���� ĭ���� �ڸ��� ���Ѵ�.
3. 2�� �����ϴ� ĭ�� ���� ���� ��쿡�� ���� ��ȣ�� ���� ���� ĭ����,
   �׷��� ĭ�� ���� ���̸� ���� ��ȣ�� ���� ���� ĭ���� �ڸ��� ���Ѵ�.

���� �л��� �������� ���ؾ� �Ѵ�. �л��� �������� �ڸ� ��ġ�� ��� ���� �Ŀ� ���� �� �ִ�.
�л��� �������� ���Ϸ��� �� �л��� ������ ĭ�� ���� �����ϴ� �л��� ���� ���ؾ� �Ѵ�.
�� ���� 0�̸� �л��� �������� 0, 1�̸� 1, 2�̸� 10, 3�̸� 100, 4�̸� 1000�̴�.
�л��� �������� �� ���� ���غ���.

�Է�
ù° �ٿ� N�� �־�����. ��° �ٺ��� N^2���� �ٿ� �л��� ��ȣ�� �� �л��� �����ϴ� �л� 4���� ��ȣ�� �� �ٿ� �ϳ���
�������� �ڸ��� ���� ������� �־�����.
�л��� ��ȣ�� �ߺ����� ������, � �л��� �����ϴ� �л� 4���� ��� �ٸ� �л����� �̷���� �ִ�.
�Է����� �־����� �л��� ��ȣ, �����ϴ� �л��� ��ȣ�� N2���� �۰ų� ���� �ڿ����̴�. � �л��� �ڱ� �ڽ��� �����ϴ� ���� ����.

���
ù° �ٿ� �л��� �������� �� ���� ����Ѵ�.

����
3 �� N �� 20

struct Student{ int idx, int prefer[4]}
struct NextPos{ int preferCnt, int emptyCnt, int x, int y}
int map[21][21], visited[21][21] ={0, };
N, dq <Student> dq;

1. Input()
	N, maxStudent, Student, dq�� �ֱ�
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
		13) [0]�� ��ġ�� map�� ǥ�� & goodbye

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
	cout << "�� ����" << endl;
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