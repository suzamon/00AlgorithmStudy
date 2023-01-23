/*
사다리 게임은 N개의 세로선과 M개의 가로선으로 이루어져 있다. 인접한 세로선 사이에는 가로선을 놓을 수 있는데,
각각의 세로선마다 가로선을 놓을 수 있는 위치의 개수는 H이고,
모든 세로선이 같은 위치를 갖는다. 아래 그림은 N = 5, H = 6 인 경우의 그림이고, 가로선은 없다.

초록선은 세로선을 나타내고, 초록선과 점선이 교차하는 점은 가로선을 놓을 수 있는 점이다.
가로선은 인접한 두 세로선을 연결해야 한다. 단, 두 가로선이 연속하거나 서로 접하면 안 된다.
또, 가로선은 점선 위에 있어야 한다.

위의 그림에는 가로선이 총 5개 있다. 가로선은 위의 그림과 같이 인접한 두 세로선을 연결해야 하고,
가로선을 놓을 수 있는 위치를 연결해야 한다.

사다리 게임은 각각의 세로선마다 게임을 진행하고, 세로선의 가장 위에서부터 아래 방향으로 내려가야 한다.
이때, 가로선을 만나면 가로선을 이용해 옆 세로선으로 이동한 다음, 이동한 세로선에서 아래 방향으로 이동해야 한다.

사다리에 가로선을 추가해서, 사다리 게임의 결과를 조작하려고 한다. 이때, i번 세로선의 결과가 i번이 나와야 한다.
그렇게 하기 위해서 추가해야 하는 가로선 개수의 최솟값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 세로선의 개수 N, 가로선의 개수 M, 세로선마다 가로선을 놓을 수 있는 위치의 개수 H가 주어진다.
(2 ≤ N ≤ 10, 1 ≤ H ≤ 30, 0 ≤ M ≤ (N-1)×H)
둘째 줄부터 M개의 줄에는 가로선의 정보가 한 줄에 하나씩 주어진다.
가로선의 정보는 두 정수 a과 b로 나타낸다. (1 ≤ a ≤ H, 1 ≤ b ≤ N-1)
b번 세로선과 b+1번 세로선을 a번 점선 위치에서 연결했다는 의미이다.
가장 위에 있는 점선의 번호는 1번이고, 아래로 내려갈 때마다 1이 증가한다.
세로선은 가장 왼쪽에 있는 것의 번호가 1번이고, 오른쪽으로 갈 때마다 1이 증가한다.
입력으로 주어지는 가로선이 서로 연속하는 경우는 없다.

출력
i번 세로선의 결과가 i번이 나오도록 사다리 게임을 조작하려면, 추가해야 하는 가로선 개수의 최솟값을 출력한다.
만약, 정답이 3보다 큰 값이면 -1을 출력한다. 또, 불가능한 경우에도 -1을 출력한다.


N, H, M, map[H][N],

1. Input()
	N, H, map에 표기
2. Solution()
	1) int Simulation(int cnt)
		1-1) cnt==0 이면, 먼저 copy_map() 호출
		1-2) for(int startCol; startCol < N; startCol++)
		1-3) for(int startRow; startRow <H; startRow++)
		1-4) nextCol = startCol;
		1-5) map[startRow][nextCol] = 1이면 nextCol ++
		1-6) map[startRow][nextCol-1] = 1이면 nextCol--;
		1-7) 이후 nextCol==startCol이면 모든 열 진행, 아니면 return -1;
		1-8) 모든 열이 조건 만족하면 return 1;

	2) for(int goal=1; goal>3; goal++)
	3) add_labber(int startRow, int startCol, int cnt, int goal)
		3-1) cnt==goal이면 Simulation(cnt)
		3-2) cnt != goal이면, startRow & startCol부터 추가 가능한 위치에 labber 추가해서 DFS


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, H, M, Answer = 0;
int map[31][11] = { 0, };

int Simulation() {
	int startRow, startCol, nextCol;

	for (startCol = 1; startCol <= N; startCol++) {
		nextCol = startCol;
		for (startRow = 1; startRow <= H; startRow++) {
			if (nextCol == 1) {
				if (map[startRow][nextCol] == 1) nextCol++;
			}
			else if (nextCol == N) {
				if (map[startRow][nextCol - 1] == 1) nextCol--;
			}
			else {
				if (map[startRow][nextCol] == 1) nextCol++;
				else if (map[startRow][nextCol - 1] == 1) nextCol--;
			}
		}
		//cout << startCol << ": " << nextCol << endl;
		if (nextCol != startCol) return -1;
	}

	return 1;
}

void add_labber(int startRow, int startCol, int cnt, int goal) {
	if (cnt == goal) {
		int retFlag = Simulation();
		if (retFlag == 1) {
			if (Answer == 0) Answer = goal;
			else if (Answer > goal) Answer = goal;
		}
		return;
	}

	if (startCol < N + 1) {
		for (; startCol <= N; startCol++) {
			if (Answer != 0) return;

			if (map[startRow][startCol] == 0) {
				if (startCol == 1) {
					if (map[startRow][startCol + 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else if (startCol == N) {
					if (map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else {
					if (map[startRow][startCol + 1] == 0 && map[startRow][startCol -1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
			}
		}
	}

	startRow = startRow + 1;
	for (; startRow <= H; startRow++) {
		if (Answer != 0) return;

		for (startCol = 1; startCol <= N; startCol++) {
			if (map[startRow][startCol] == 0) {
				if (startCol == 1) {
					if (map[startRow][startCol + 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else if (startCol == N) {
					if (map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else {
					if (map[startRow][startCol + 1] == 0 && map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
			}
		}
	}

}

void Solution() {
	int flag = 0, goal;
	flag = Simulation();
	if (flag == 1) return;

	for (goal = 1; goal <= 3; goal++) {
		add_labber(1, 1, 0, goal);
		if (Answer != 0) break;
	}

	if (Answer == 0 && goal == 4) Answer = -1;
}

void Input() {
	cin >> N >> M >> H;

	int xx, yy;
	for (int i = 0; i < M; i++) {
		cin >> xx >> yy;

		map[xx][yy] = 1;
	}

}


int main(void) {
	Input();
	//cout << Simulation() << endl;
	Solution();

	cout << Answer << endl;
	return 0;
}