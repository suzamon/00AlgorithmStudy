#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int N;
int map[21][21];
int copy_map[21][21][2];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0,1} };
int Answer = 0;

int arr[5];

int find_max() {
	int returnFlag = 0;
	int max = 0;
	vector <int> v;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (copy_map[i][j][0] != 0) {
				if (max < copy_map[i][j][0]) max = copy_map[i][j][0];
				v.push_back(copy_map[i][j][0]);
			}
		}
	}

	if (Answer < max) Answer = max;
	if (v.size() == 1)returnFlag = 1;

	return returnFlag;

}

void sim(int curDir) {
	int startX, startY, nextX, nextY;


	switch (curDir) {
	case 0:
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (copy_map[i][j][0] != 0) {
					startX = i;
					startY = j;
					while (1) {
						nextX = startX - 1;
						nextY = startY;
						if (nextX == -1) {
							break;
						}
						else if (copy_map[nextX][nextY][0] == 0) {
							for (int i = 0; i < 2; i++) {
								copy_map[nextX][nextY][i] = copy_map[startX][startY][i];
								copy_map[startX][startY][i] = 0;
							}
							startX = nextX;
							startY = nextY;
						}
						else if (copy_map[nextX][nextY][0] == copy_map[startX][startY][0]) {
							if (copy_map[nextX][nextY][1] == 0) {
								copy_map[startX][startY][0] = 0;
								copy_map[startX][startY][1] = 0;
								copy_map[nextX][nextY][0] *= 2;
								copy_map[nextX][nextY][1] = 1;
							}
							else {
								nextX = startX;
								nextY = startY;
								break;
							}
						}
						else { //(copy_map[nextX][nextY][0] != copy_map[startX][startY][0])
							nextX = startX;
							nextY = startY;
							break;
						}
					}
				}
			}
		}
		break;
	case 1:
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < N; j++) {
				if (copy_map[i][j][0] != 0) {
					startX = i;
					startY = j;
					while (1) {
						nextX = startX + 1;
						nextY = startY;
						if (nextX == N) {
							break;
						}
						else if (copy_map[nextX][nextY][0] == 0) {
							for (int i = 0; i < 2; i++) {
								copy_map[nextX][nextY][i] = copy_map[startX][startY][i];
								copy_map[startX][startY][i] = 0;
							}
							startX = nextX;
							startY = nextY;
						}
						else if (copy_map[nextX][nextY][0] == copy_map[startX][startY][0]) {
							if (copy_map[nextX][nextY][1] == 0) {
								copy_map[startX][startY][0] = 0;
								copy_map[startX][startY][1] = 0;
								copy_map[nextX][nextY][0] *= 2;
								copy_map[nextX][nextY][1] = 1;
							}
							else {
								nextX = startX;
								nextY = startY;
								break;
							}
						}
						else { //(copy_map[nextX][nextY][0] != copy_map[startX][startY][0])
							nextX = startX;
							nextY = startY;
							break;
						}
					}
				}
			}
		}
		break;
	case 2:
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if (copy_map[i][j][0] != 0) {
					startX = i;
					startY = j;
					while (1) {
						nextX = startX;
						nextY = startY - 1;
						if (nextY == -1) {
							break;
						}
						else if (copy_map[nextX][nextY][0] == 0) {
							for (int i = 0; i < 2; i++) {
								copy_map[nextX][nextY][i] = copy_map[startX][startY][i];
								copy_map[startX][startY][i] = 0;
							}
							startX = nextX;
							startY = nextY;
						}
						else if (copy_map[nextX][nextY][0] == copy_map[startX][startY][0]) {
							if (copy_map[nextX][nextY][1] == 0) {
								copy_map[startX][startY][0] = 0;
								copy_map[startX][startY][1] = 0;
								copy_map[nextX][nextY][0] *= 2;
								copy_map[nextX][nextY][1] = 1;
							}
							else {
								nextX = startX;
								nextY = startY;
								break;
							}
						}
						else { //(copy_map[nextX][nextY][0] != copy_map[startX][startY][0])
							nextX = startX;
							nextY = startY;
							break;
						}
					}
				}
			}
		}
		break;
	case 3:
		for (int j = N - 1; j >= 0; j--) {
			for (int i = 0; i < N; i++) {
				if (copy_map[i][j][0] != 0) {
					startX = i;
					startY = j;
					while (1) {
						nextX = startX;
						nextY = startY + 1;
						if (nextY == N) {
							break;
						}
						else if (copy_map[nextX][nextY][0] == 0) {
							for (int i = 0; i < 2; i++) {
								copy_map[nextX][nextY][i] = copy_map[startX][startY][i];
								copy_map[startX][startY][i] = 0;
							}
							startX = nextX;
							startY = nextY;
						}
						else if (copy_map[nextX][nextY][0] == copy_map[startX][startY][0]) {
							if (copy_map[nextX][nextY][1] == 0) {
								copy_map[startX][startY][0] = 0;
								copy_map[startX][startY][1] = 0;
								copy_map[nextX][nextY][0] *= 2;
								copy_map[nextX][nextY][1] = 1;
							}
							else {
								nextX = startX;
								nextY = startY;
								break;
							}
						}
						else { //(copy_map[nextX][nextY][0] != copy_map[startX][startY][0])
							nextX = startX;
							nextY = startY;
							break;
						}
					}
				}
			}
		}
		break;

	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copy_map[i][j][1] = 0;
		}
	}

	/*
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copy_map[i][j][0] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/

}

void dfs(int start, int cnt) {
	if (cnt == 5) {
		/*
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
		*/
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				copy_map[i][j][0] = map[i][j];
				copy_map[i][j][1] = 0;
			}
		}

		for (int i = 0; i < 5; i++) {
			sim(arr[i]);
			if (find_max() == 1) {
				break;
			}
		}

		return;
	}

	for (int i = 0; i < 4; i++) {
		arr[cnt] = i;
		dfs(i, cnt + 1);

	}


}


int main(void) {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	/*
	cout << "½ÃÀÛ ¸Ê" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
			copy_map[i][j][0] = map[i][j];
			copy_map[i][j][1] = 0;
		}
		cout << endl;
	}
	cout << endl;
	*/

	for (int i = 0; i < 4; i++) {
		arr[0] = i;
		dfs(i, 1);
	}

	cout << Answer << endl;


	return 0;
}