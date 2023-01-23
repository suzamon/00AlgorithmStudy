/*
캐슬 디펜스는 성을 향해 몰려오는 적을 잡는 턴 방식의 게임 -> NxM 격자판으로 나타냄
격자판은 1x1 크기의 칸으로 나누어져 있고, 각 칸에 포함된 적의 수는 최대 하나
격자판의 N번 행 바로 아래에는 모든 칸에 성이 있다
성을 지키기 위해 궁수 3명 배치, 궁수는 성이 있는 칸 배치 & 하나의 칸에는 최대 1명의 궁수
각각의 턴마다 궁수는 D 거리 이하의 적 중에 가장 가까운 적 &  많을 경우 가장 왼쪽의 적을 공격 & 같은 적을 여러 궁수가 공격할 수도
공격받은 적은 게임 제외 -> 공격 끝나면 적은 아래로 한칸 이동, 성이 있는 칸으로 이동한 경우 게임에서 제외
모든 적이 제외되면 게임 끝 & 공격으로 제거할 수 있는 적의 최대 수를 계산

거리 : (r1, c1), (r2, c2)의 거리는 |r1-r2| + |c1-c2|

N, M, D (3 ≤ N, M ≤ 15, 1 ≤ D ≤ 10)

1. Input() : N, M, D, map[N+1][M], arrow[3][2]

2. Solution() :
	1) void find_arrow(int startRow, int cnt) : DFS를 통해 궁수 위치 3곳 정하기 이후 cnt==3이면 simulation()
	2) int simulation() 1)에서 궁수 위치가 정해지면 실행 -> 궁수가 잡을 수 있는 적 탐색
		2-1) kill_enermy[3][2]에 각각 위치 조건에 따른 적 선택
		2-2) 2-1)에서 찾은 적 제거
		2-3) 한칸씩 내리기
		2-4) 칸에 적이 한명도 없으면 종료
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

int N, M, D, enermyNum, Answer = 0;
int map[16][15];
int simMap[16][15];
int arrow[3][2] = { 0, };

using namespace std;

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			simMap[i][j] = map[i][j];
		}
	}
}

int simulation() {
	int exitNum, killNum = 0;
	int arrowX, arrowY, curD, nextD;
	int kill[3][2];
	int tmpArr[15];

	exitNum = enermyNum;

	while (1) {
		//제거할 적 찾기
		for (int arrowIdx = 0; arrowIdx < 3; arrowIdx++) {
			arrowX = arrow[arrowIdx][0];
			arrowY = arrow[arrowIdx][1];
			curD = 0;
			nextD = 0;
			kill[arrowIdx][0] = -1;
			kill[arrowIdx][1] = -1;
			for (int i = N - 1; i >= 0; i--) {
				if (abs(arrowX - i) > D) break;
				for (int j = 0; j < M; j++) {
					if (simMap[i][j] != 0) {
						if (curD == 0) {
							curD = abs(arrowX - i) + abs(arrowY - j);
							if (curD > D) {
								curD = 0;
								continue;
							}
							kill[arrowIdx][0] = i;
							kill[arrowIdx][1] = j;
						}
						else {
							nextD = abs(arrowX - i) + abs(arrowY - j);
							if (nextD < curD) {
								kill[arrowIdx][0] = i;
								kill[arrowIdx][1] = j;
								curD = nextD;
							}
							else if (nextD == curD && kill[arrowIdx][1] > j) {
								kill[arrowIdx][0] = i;
								kill[arrowIdx][1] = j;
								curD = nextD;
							}
						}
					}
				}
				
			}

		}

		//적 제거
		for (int i = 0; i < 3; i++) {
			arrowX = kill[i][0];
			arrowY = kill[i][1];
			if (arrowX == -1 && arrowY == -1) continue;
			if (simMap[arrowX][arrowY] == 1) {
				exitNum--;
				simMap[arrowX][arrowY] = 0;
				killNum++;
			}
		}

		//한칸씩 내리기
		for (int i = N - 1; i > 0; i--) {
			for (int j = 0; j < M; j++) {
				if (i == N - 1 && simMap[i][j] == 1) {
					exitNum--;
				}
				simMap[i][j] = simMap[i - 1][j];
			}
		}
		for (int j = 0; j < M; j++) {
			simMap[0][j] = 0;
		}

		if (exitNum <= 0) break;
	}
	
	return killNum;
	
}

void find_arrow(int startCol, int cnt) {
	if (cnt == 3) {
		/*
		cout << "궁수 위치" << endl;
		for (int i = 0; i < 3; i++) {
			cout << arrow[i][0] << ", " << arrow[i][1] << endl;
		}
		cout << endl;
		*/
		int tmp_answer;

		copy_map();

		tmp_answer = simulation();
		if (tmp_answer > Answer) Answer = tmp_answer;

	}

	for (int i = startCol; i < M; i++) {
		arrow[cnt][1] = i;
		find_arrow(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < 3; i++) {
		arrow[i][0] = N;
	}

	for (int i = 0; i <= M - 3; i++) {
		arrow[0][1] = i;
		find_arrow(i + 1, 1);
	}
}

void Input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) enermyNum++;
		}
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;

	return 0;
}