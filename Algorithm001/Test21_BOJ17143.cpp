/*
낚시왕이 상어 낚시를 하는 곳은 크기가 R×C인 격자판으로 나타낼 수 있다.
격자판의 각 칸은 (r, c)로 나타낼 수 있다. r은 행, c는 열이고, (R, C)는 아래 그림에서 가장 오른쪽 아래에 있는 칸이다.
칸에는 상어가 최대 한 마리 들어있을 수 있다. 상어는 크기와 속도를 가지고 있다.

낚시왕은 처음에 1번 열의 한 칸 왼쪽에 있다. 다음은 1초 동안 일어나는 일이며, 아래 적힌 순서대로 일어난다.
낚시왕은 가장 오른쪽 열의 오른쪽 칸에 이동하면 이동을 멈춘다.

1. 낚시왕이 오른쪽으로 한 칸 이동한다.
2. 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
3. 상어가 이동한다.

상어는 입력으로 주어진 속도로 이동하고, 속도의 단위는 칸/초이다.
상어가 이동하려고 하는 칸이 격자판의 경계를 넘는 경우에는 방향을 반대로 바꿔서 속력을 유지한채로 이동한다.

왼쪽 그림의 상태에서 1초가 지나면 오른쪽 상태가 된다.
상어가 보고 있는 방향이 속도의 방향, 왼쪽 아래에 적힌 정수는 속력이다.
왼쪽 위에 상어를 구분하기 위해 문자를 적었다.

상어가 이동을 마친 후에 한 칸에 상어가 두 마리 이상 있을 수 있다.
이때는 크기가 가장 큰 상어가 나머지 상어를 모두 잡아먹는다.

낚시왕이 상어 낚시를 하는 격자판의 상태가 주어졌을 때, 낚시왕이 잡은 상어 크기의 합을 구해보자.


입력
첫째 줄에 격자판의 크기 R, C와 상어의 수 M이 주어진다. (2 ≤ R, C ≤ 100, 0 ≤ M ≤ R×C)

둘째 줄부터 M개의 줄에 상어의 정보가 주어진다.
상어의 정보는 다섯 정수 r, c, s, d, z (1 ≤ r ≤ R, 1 ≤ c ≤ C, 0 ≤ s ≤ 1000, 1 ≤ d ≤ 4, 1 ≤ z ≤ 10000) 로 이루어져 있다.
(r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기이다.
d가 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽을 의미한다.

두 상어가 같은 크기를 갖는 경우는 없고, 하나의 칸에 둘 이상의 상어가 있는 경우는 없다.

출력
낚시왕이 잡은 상어 크기의 합을 출력한다.

int R, C, M, Answer;
int personCol;

deque <int> shark[5] (r, c, s, d, z) (r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};


1. Input()
	R, C, M, shark[0]~shark[4]에 저장

2. Solution()
	1) find_shark(int col) -> for(col=1; col<=C; col++) 반복
		1-1) int map[101][101] = {0, };
		1-2) shark 돌면서 map에 (idx + 1) 표기 (size[4] = -1인 경우에는 다음 상어
		1-2-1) map에 표기하면서 '0'이 아닌 경우에는 기입된 idx 상어 크기와 기입할 idx 상어 크기 비교해서
				작은 크기 상어 사이즈[4]을 -1로 셋팅
		1-2-2) map에 '0'으로 표기되어 있으면 그냥 기입
		1-3) map에 표기가 끝난 경우에는 해당 col에서 row 값이 가장 작은 상어 잡힘 -> Answer에 크기 추가
		1-4) 잡힙 상어 사이즈는 -1로 셋팅
	2) move_shark()
		2-1) shark 탐색 시작 -> shark[0].size 저장해서 반복!
		2-2) r, c, s, d, z 값 저장 -> z = -1이면 그냥 pop만 진행
		2-3) 상어 방향에 맞게끔 위치 갱신
		2-4) 갱신된 값 shark에 저장(push_back)
	3) 반복이 끝나면 Answer 값 출력

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int R, C, M, Answer = 0;
int personCol;

deque <int> shark[5]; //(r, c, s, d, z) (r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기

int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, 1, -1 };


void find_shark(int col) {
	int map[101][101] = { 0, };
	int arr[5];
	int tmpIdx, tmpSize;

	for (int idx = 0; idx < shark[0].size(); idx++) {
		arr[4] = shark[4][idx];
		if (arr[4] == -1) continue;

		for (int i = 0; i < 4; i++) {
			arr[i] = shark[i][idx];
		}

		if (map[arr[0]][arr[1]] == 0) {
			map[arr[0]][arr[1]] = idx + 1;
		}
		else {
			tmpIdx = map[arr[0]][arr[1]] - 1;
			tmpSize = shark[4][tmpIdx];
			if (arr[4] < tmpSize) {
				shark[4][idx] = -1;
			}
			else {
				shark[4][tmpIdx] = -1;
				map[arr[0]][arr[1]] = idx + 1;
			}
		}
	}

	for (int row = 1; row <= R; row++) {

		if (map[row][col] > 0) {
			tmpIdx = map[row][col] - 1;
			Answer = Answer + shark[4][tmpIdx];
			shark[4][tmpIdx] = -1;
			//cout << col << "열에서 ";
			//printf("%c", 'A' + tmpIdx);
			//cout << "번째 상어 잡힘" << endl;
			map[row][col] = 0;
			break;
		}

	}
	/*
	cout << "맵" << endl;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
}

void move_shark() {
	int r, c, s, d, z, nR, nC, nS, nD, tmp;
	int tmpSize = shark[0].size();
	for (int idx = 0; idx < tmpSize; idx++) {
		z = shark[4].front();
		shark[4].pop_front();
		if (z == -1) {
			for (int i = 0; i < 4; i++) {
				tmp = shark[i].front();
				shark[i].pop_front();
				shark[i].push_back(tmp);
			}
			shark[4].push_back(-1);
			continue;
		}
		r = shark[0].front();
		c = shark[1].front();
		s = shark[2].front();
		nS = s;
		d = shark[3].front();
		for (int i = 0; i < 4; i++) {
			shark[i].pop_front();
		}

		switch (d) {
		case 1:
			if (r - s >= 1) {
				nR = r - s;
				nD = 1;
			}
			else {
				s = s - (r - 1);
				while (1) {
					if ((1 + s) >= 1 && (1 + s) <= R) {
						nR = 1 + s;
						nD = 2;
						break;
					}
					s = s - (R - 1);
					if ((R - s) >= 1 && (R - s) <= R) {
						nR = R - s;
						nD = 1;
						break;
					}
					s = s - (R - 1);
				}
			}
			shark[0].push_back(nR);
			shark[1].push_back(c);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 2:
			if (r + s <= R) {
				nR = r + s;
				nD = 2;
			}
			else {
				s = s - (R - r);
				while (1) {
					if ((R - s) >= 1 && (R - s) <= R) {
						nR = R - s;
						nD = 1;
						break;
					}
					s = s - (R - 1);
					if ((1 + s) >= 1 && (1 + s) <= R) {
						nR = 1 + s;
						nD = 2;
						break;
					}
					s = s - (R - 1);
				}
			}
			shark[0].push_back(nR);
			shark[1].push_back(c);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 3:
			if (c + s <= C) {
				nC = c + s;
				nD = 3;
			}
			else {
				s = s - (C - c);
				while (1) {
					if ((C - s) >= 1 && (C - s) <= C) {
						nC = C - s;
						nD = 4;
						break;
					}
					s = s - (C - 1);
					if ((1 + s) >= 1 && (1 + s) <= C) {
						nC = 1 + s;
						nD = 3;
						break;
					}
					s = s - (C - 1);
				}
			}
			shark[0].push_back(r);
			shark[1].push_back(nC);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 4:
			if (c - s >= 1) {
				nC = c - s;
				nD = 4;
			}
			else {
				s = s - (c - 1);
				while (1) {
					if ((1 + s) >= 1 && (1 + s) <= C) {
						nC = 1 + s;
						nD = 3;
						break;
					}
					s = s - (C - 1);
					if ((C - s) >= 1 && (C - s) <= C) {
						nC = C - s;
						nD = 4;
						break;
					}
					s = s - (C - 1);
				}
			}
			shark[0].push_back(r);
			shark[1].push_back(nC);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		}
	}
}

void Solution() {
	for (int col = 1; col <= C; col++) {
		find_shark(col);
		move_shark();
	}
	cout << Answer << endl;
}

void Input() {
	int tmp;
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> tmp;
			shark[j].push_back(tmp);
		}
	}
}

int main(void) {

	Input();
	Solution();


	return 0;
}