/*
NxM ����̱� -> ����, ������, ����, �Ʒ���
�������� ���� ���� -> ����, �Ķ��� ���� ���� -> ����
������ �� �����϶����� ����̱�
�ּ� ��� ����?

N, M (3 �� N, M �� 10)
�� ���ڿ��� '.', '#', 'O', 'R', 'B' �� �̷���� �ִ�.
'.'�� �� ĭ�� �ǹ��ϰ�, '#'�� ���� �̵��� �� ���� ��ֹ� �Ǵ� ���� �ǹ��ϸ�,
'O'�� ������ ��ġ, 'R'�� ���� ������ ��ġ, 'B'�� �Ķ� ������ ��ġ

�ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ����Ѵ�.
����, 10�� ���Ϸ� �������� ���� ������ ������ ���� ���� �� ������ -1�� ����Ѵ�.
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, Answer = 11;
char map[11][11], copyMap[11][11];

int arr[11];//0 ��, 1 ��, 2 ��, 3 ��
int startRx, startRy, startBx, startBy;

void print() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

int sim() {
	int retFlag = 0;

	int Rx = startRx, Ry = startRy, Bx = startBx, By = startBy;
	int nextRx, nextRy, nextBx, nextBy, nextDir;
	copy_map();
	for (int i = 0; i < 10; i++) {
		nextDir = arr[i];
		nextRx = Rx, nextRy = Ry, nextBx = Bx, nextBy = By;

		if (Answer < i + 1) return retFlag;

		switch (nextDir) {
		case 0:
			if (nextRx > nextBx) {
				while (1) {
					if (copyMap[nextBx - 1][nextBy] == '.') {
						nextBx--;
					}
					else if (copyMap[nextBx - 1][nextBy] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (retFlag == -1) break;

				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}

				while (1) {
					if (copyMap[nextRx - 1][nextRy] == '.') {
						nextRx--;
					}
					else if (copyMap[nextRx - 1][nextRy] == 'O') {
						retFlag = 1;
						if (Answer > i + 1) Answer = i + 1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					copyMap[Rx][Ry] = '.';
					copyMap[nextRx][nextRy] = 'R';
				}
			}
			else {
				while (1) {
					if (copyMap[nextRx - 1][nextRy] == '.') {
						nextRx--;
					}
					else if (copyMap[nextRx - 1][nextRy] == 'O') {
						nextRy--;
						retFlag = 1;
						break;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					if (map[nextRx][nextRy] == 'O') {
						copyMap[Rx][Ry] = '.';
					}
					else {
						copyMap[Rx][Ry] = '.';
						copyMap[nextRx][nextRy] = 'R';
					}
				}
				while (1) {
					if (copyMap[nextBx - 1][nextBy] == '.') {
						nextBx--;
					}
					else if (copyMap[nextBx - 1][nextBy] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}
				if (retFlag == 1) {
					if (Answer > i + 1) Answer = i + 1;
					return retFlag;
				}
			}
			
			if (Rx == nextRx && Ry == nextRy && Bx == nextBx && By == nextBy) {
				retFlag = -1;
				return retFlag;
			}
			else {
				Rx = nextRx, Ry = nextRy;
				Bx = nextBx, By = nextBy;
			}
			break;
		case 1:
			if (nextRx < nextBx) {
				while (1) {
					if (copyMap[nextBx + 1][nextBy] == '.') {
						nextBx++;
					}
					else if (copyMap[nextBx + 1][nextBy] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (retFlag == -1) break;

				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}

				while (1) {
					if (copyMap[nextRx + 1][nextRy] == '.') {
						nextRx++;
					}
					else if (copyMap[nextRx + 1][nextRy] == 'O') {
						retFlag = 1;
						if (Answer > i + 1) Answer = i + 1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					copyMap[Rx][Ry] = '.';
					copyMap[nextRx][nextRy] = 'R';
				}
			}
			else {
				while (1) {
					if (copyMap[nextRx + 1][nextRy] == '.') {
						nextRx++;
					}
					else if (copyMap[nextRx + 1][nextRy] == 'O') {
						nextRy--;
						retFlag = 1;
						break;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					if (map[nextRx][nextRy] == 'O') {
						copyMap[Rx][Ry] = '.';
					}
					else {
						copyMap[Rx][Ry] = '.';
						copyMap[nextRx][nextRy] = 'R';
					}
				}
				while (1) {
					if (copyMap[nextBx + 1][nextBy] == '.') {
						nextBx++;
					}
					else if (copyMap[nextBx + 1][nextBy] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}
				if (retFlag == 1) {
					if (Answer > i + 1) Answer = i + 1;
					return retFlag;
				}
			}

			if (Rx == nextRx && Ry == nextRy && Bx == nextBx && By == nextBy) {
				retFlag = -1;
				return retFlag;
			}
			else {
				Rx = nextRx, Ry = nextRy;
				Bx = nextBx, By = nextBy;
			}
			break;
		case 2:
			if (nextRy > nextBy) {
				while (1) {
					if (copyMap[nextBx][nextBy - 1] == '.') {
						nextBy--;
					}
					else if (copyMap[nextBx][nextBy - 1] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (retFlag == -1) break;

				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}

				while (1) {
					if (copyMap[nextRx][nextRy - 1] == '.') {
						nextRy--;
					}
					else if (copyMap[nextRx][nextRy - 1] == 'O') {
						retFlag = 1;
						if (Answer > i + 1) Answer = i + 1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					copyMap[Rx][Ry] = '.';
					copyMap[nextRx][nextRy] = 'R';
				}
			}
			else {
				while (1) {
					if (copyMap[nextRx][nextRy - 1] == '.') {
						nextRy--;
					}
					else if (copyMap[nextRx][nextRy - 1] == 'O') {
						nextRy--;
						retFlag = 1;
						break;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					if (map[nextRx][nextRy] == 'O') {
						copyMap[Rx][Ry] = '.';
					}
					else {
						copyMap[Rx][Ry] = '.';
						copyMap[nextRx][nextRy] = 'R';
					}
				}
				while (1) {
					if (copyMap[nextBx][nextBy - 1] == '.') {
						nextBy--;
					}
					else if (copyMap[nextBx][nextBy - 1] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}
				if (retFlag == 1) {
					if (Answer > i + 1) Answer = i + 1;
					return retFlag;
				}
			}

			if (Rx == nextRx && Ry == nextRy && Bx == nextBx && By == nextBy) {
				retFlag = -1;
				return retFlag;
			}
			else {
				Rx = nextRx, Ry = nextRy;
				Bx = nextBx, By = nextBy;
			}
			break;
		case 3:
			if (nextRy < nextBy) {
				while (1) {
					if (copyMap[nextBx][nextBy + 1] == '.') {
						nextBy++;
					}
					else if (copyMap[nextBx][nextBy + 1] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (retFlag == -1) break;

				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}

				while (1) {
					if (copyMap[nextRx][nextRy + 1] == '.') {
						nextRy++;
					}
					else if (copyMap[nextRx][nextRy + 1] == 'O') {
						retFlag = 1;
						if (Answer > i + 1) Answer = i + 1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					copyMap[Rx][Ry] = '.';
					copyMap[nextRx][nextRy] = 'R';
				}
			}
			else {
				while (1) {
					if (copyMap[nextRx][nextRy + 1] == '.') {
						nextRy++;
					}
					else if (copyMap[nextRx][nextRy + 1] == 'O') {
						nextRy--;
						retFlag = 1;
						break;
					}
					else {
						break;
					}
				}
				if (Rx != nextRx || Ry != nextRy) {
					if (map[nextRx][nextRy] == 'O') {
						copyMap[Rx][Ry] = '.';
					}
					else {
						copyMap[Rx][Ry] = '.';
						copyMap[nextRx][nextRy] = 'R';
					}
				}
				while (1) {
					if (copyMap[nextBx][nextBy + 1] == '.') {
						nextBy++;
					}
					else if (copyMap[nextBx][nextBy + 1] == 'O') {
						retFlag = -1;
						return retFlag;
					}
					else {
						break;
					}
				}
				if (Bx != nextBx || By != nextBy) {
					copyMap[Bx][By] = '.';
					copyMap[nextBx][nextBy] = 'B';
				}
				if (retFlag == 1) {
					if (Answer > i + 1) Answer = i + 1;
					return retFlag;
				}
			}

			if (Rx == nextRx && Ry == nextRy && Bx == nextBx && By == nextBy) {
				retFlag = -1;
				return retFlag;
			}
			else {
				Rx = nextRx, Ry = nextRy;
				Bx = nextBx, By = nextBy;
			}
			break;
		}

		//print();
	}

	return retFlag;
}

void DFS(int cnt) {
	if (cnt == 10) {
		/*
		if (arr[0] == 2 && arr[1] == 1 && arr[2] == 3 && arr[3] == 1 && arr[4] == 2) {
			cout << "#!@#" << endl;
		}
		*/
		int flag = sim();
		//print();
		/*
		for (int i = 0; i < 10; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
		*/
		return;
	}

	for (int d = 0; d < 4; d++) {
		if (arr[cnt - 1] == 0 && (d == 1 || d == 0)) {
			continue;
		}
		else if (arr[cnt - 1] == 1 && (d == 1 || d == 0)) {
			continue;
		}
		else if (arr[cnt - 1] == 2 && (d == 2 || d == 3)) {
			continue;
		}
		else if (arr[cnt - 1] == 3 && (d == 2 || d == 3)) {
			continue;
		}

		arr[cnt] = d;
		DFS(cnt + 1);
	}

}

void Solve() {
	for (int d = 0; d < 4; d++) {
		arr[0] = d;
		DFS(1);
	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {		
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'B') {
				startBx = i;
				startBy = j;
			}
			else if (map[i][j] == 'R') {
				startRx = i;
				startRy = j;
			}
		}
	}

}


int main(void) {
	Input();
	//print();
	Solve();
	if (Answer == 11) {
		Answer = -1;
	}

	cout << Answer << endl;
	return 0;
}