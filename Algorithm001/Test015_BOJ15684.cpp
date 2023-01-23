/*
��ٸ� ������ N���� ���μ��� M���� ���μ����� �̷���� �ִ�. ������ ���μ� ���̿��� ���μ��� ���� �� �ִµ�,
������ ���μ����� ���μ��� ���� �� �ִ� ��ġ�� ������ H�̰�,
��� ���μ��� ���� ��ġ�� ���´�. �Ʒ� �׸��� N = 5, H = 6 �� ����� �׸��̰�, ���μ��� ����.

�ʷϼ��� ���μ��� ��Ÿ����, �ʷϼ��� ������ �����ϴ� ���� ���μ��� ���� �� �ִ� ���̴�.
���μ��� ������ �� ���μ��� �����ؾ� �Ѵ�. ��, �� ���μ��� �����ϰų� ���� ���ϸ� �� �ȴ�.
��, ���μ��� ���� ���� �־�� �Ѵ�.

���� �׸����� ���μ��� �� 5�� �ִ�. ���μ��� ���� �׸��� ���� ������ �� ���μ��� �����ؾ� �ϰ�,
���μ��� ���� �� �ִ� ��ġ�� �����ؾ� �Ѵ�.

��ٸ� ������ ������ ���μ����� ������ �����ϰ�, ���μ��� ���� ���������� �Ʒ� �������� �������� �Ѵ�.
�̶�, ���μ��� ������ ���μ��� �̿��� �� ���μ����� �̵��� ����, �̵��� ���μ����� �Ʒ� �������� �̵��ؾ� �Ѵ�.

��ٸ��� ���μ��� �߰��ؼ�, ��ٸ� ������ ����� �����Ϸ��� �Ѵ�. �̶�, i�� ���μ��� ����� i���� ���;� �Ѵ�.
�׷��� �ϱ� ���ؼ� �߰��ؾ� �ϴ� ���μ� ������ �ּڰ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� ���μ��� ���� N, ���μ��� ���� M, ���μ����� ���μ��� ���� �� �ִ� ��ġ�� ���� H�� �־�����.
(2 �� N �� 10, 1 �� H �� 30, 0 �� M �� (N-1)��H)
��° �ٺ��� M���� �ٿ��� ���μ��� ������ �� �ٿ� �ϳ��� �־�����.
���μ��� ������ �� ���� a�� b�� ��Ÿ����. (1 �� a �� H, 1 �� b �� N-1)
b�� ���μ��� b+1�� ���μ��� a�� ���� ��ġ���� �����ߴٴ� �ǹ��̴�.
���� ���� �ִ� ������ ��ȣ�� 1���̰�, �Ʒ��� ������ ������ 1�� �����Ѵ�.
���μ��� ���� ���ʿ� �ִ� ���� ��ȣ�� 1���̰�, ���������� �� ������ 1�� �����Ѵ�.
�Է����� �־����� ���μ��� ���� �����ϴ� ���� ����.

���
i�� ���μ��� ����� i���� �������� ��ٸ� ������ �����Ϸ���, �߰��ؾ� �ϴ� ���μ� ������ �ּڰ��� ����Ѵ�.
����, ������ 3���� ū ���̸� -1�� ����Ѵ�. ��, �Ұ����� ��쿡�� -1�� ����Ѵ�.


N, H, M, map[H][N],

1. Input()
	N, H, map�� ǥ��
2. Solution()
	1) int Simulation(int cnt)
		1-1) cnt==0 �̸�, ���� copy_map() ȣ��
		1-2) for(int startCol; startCol < N; startCol++)
		1-3) for(int startRow; startRow <H; startRow++)
		1-4) nextCol = startCol;
		1-5) map[startRow][nextCol] = 1�̸� nextCol ++
		1-6) map[startRow][nextCol-1] = 1�̸� nextCol--;
		1-7) ���� nextCol==startCol�̸� ��� �� ����, �ƴϸ� return -1;
		1-8) ��� ���� ���� �����ϸ� return 1;

	2) for(int goal=1; goal>3; goal++)
	3) add_labber(int startRow, int startCol, int cnt, int goal)
		3-1) cnt==goal�̸� Simulation(cnt)
		3-2) cnt != goal�̸�, startRow & startCol���� �߰� ������ ��ġ�� labber �߰��ؼ� DFS


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