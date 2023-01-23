#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

int N, M, Answer = 11;
int map[11][11];
int copyMap[11][11];
int copyR[2];
int copyB[2];
int r[2];
int b[2];
int h[2];
int nextR[2];
int nextB[2];

int dir[11];
int arr[11]; // n개 방향 선택 벡터의 startIndex
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

using namespace std;

void copy_map() {
	for (int i = 0; i < 2; i++) {
		copyB[i] = b[i];
		copyR[i] = r[i];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] =  map[i][j];
		}
	}
}

void print_copy_map() {
	cout << "Copy Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
}

int sim(int num) {
	copy_map();

	int curDir, nextX, nextY, curX, curY, returnFlag = 0;

	//cout << "시작" << endl;
	//print_copy_map();

	for (int i = 1; i <= num; i++) {
		curDir = dir[i];
		switch (curDir) {
		case 0:
			if (copyR[1] > copyB[1]) {
				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}

				if (returnFlag != -1) {
					curX = copyR[0];
					curY = copyR[1];
					while (1) {
						nextX = curX + dx[curDir];
						nextY = curY + dy[curDir];
						if (copyMap[nextX][nextY] == 0) {
							curX = nextX;
							curY = nextY;
						}
						else if (copyMap[nextX][nextY] == -1) {
							copyMap[copyR[0]][copyR[1]] = 0;
							returnFlag = 1;
							break;
						}
						else {
							copyMap[copyR[0]][copyR[1]] = 0;
							copyR[0] = curX;
							copyR[1] = curY;
							copyMap[copyR[0]][copyR[1]] = 2;
							break;

						}
					}
				}				
			}
			else {
				curX = copyR[0];
				curY = copyR[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyR[0]][copyR[1]] = 0;
						returnFlag = 1;
						break;
					}
					else {
						copyMap[copyR[0]][copyR[1]] = 0;
						copyR[0] = curX;
						copyR[1] = curY;
						copyMap[copyR[0]][copyR[1]] = 2;
						break;

					}
				}

				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}
			}
			break;
		case 1:
			if (copyR[1] > copyB[1]) {
				curX = copyR[0];
				curY = copyR[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyR[0]][copyR[1]] = 0;
						returnFlag = 1;
						break;
					}
					else {
						copyMap[copyR[0]][copyR[1]] = 0;
						copyR[0] = curX;
						copyR[1] = curY;
						copyMap[copyR[0]][copyR[1]] = 2;
						break;

					}
				}

				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}
			}
			else {
				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}

				if (returnFlag != -1) {
					curX = copyR[0];
					curY = copyR[1];
					while (1) {
						nextX = curX + dx[curDir];
						nextY = curY + dy[curDir];
						if (copyMap[nextX][nextY] == 0) {
							curX = nextX;
							curY = nextY;
						}
						else if (copyMap[nextX][nextY] == -1) {
							copyMap[copyR[0]][copyR[1]] = 0;
							returnFlag = 1;
							break;
						}
						else {
							copyMap[copyR[0]][copyR[1]] = 0;
							copyR[0] = curX;
							copyR[1] = curY;
							copyMap[copyR[0]][copyR[1]] = 2;
							break;

						}
					}
				}
			}
			break;
		case 2:
			if (copyR[0] > copyB[0]) {
				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}

				if (returnFlag != -1) {
					curX = copyR[0];
					curY = copyR[1];
					while (1) {
						nextX = curX + dx[curDir];
						nextY = curY + dy[curDir];
						if (copyMap[nextX][nextY] == 0) {
							curX = nextX;
							curY = nextY;
						}
						else if (copyMap[nextX][nextY] == -1) {
							copyMap[copyR[0]][copyR[1]] = 0;
							returnFlag = 1;
							break;
						}
						else {
							copyMap[copyR[0]][copyR[1]] = 0;
							copyR[0] = curX;
							copyR[1] = curY;
							copyMap[copyR[0]][copyR[1]] = 2;
							break;

						}
					}
				}
			}
			else {
				curX = copyR[0];
				curY = copyR[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyR[0]][copyR[1]] = 0;
						returnFlag = 1;
						break;
					}
					else {
						copyMap[copyR[0]][copyR[1]] = 0;
						copyR[0] = curX;
						copyR[1] = curY;
						copyMap[copyR[0]][copyR[1]] = 2;
						break;

					}
				}

				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}
			}
			break;
		case 3:
			if (copyR[0] > copyB[0]) {
				curX = copyR[0];
				curY = copyR[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyR[0]][copyR[1]] = 0;
						returnFlag = 1;
						break;
					}
					else {
						copyMap[copyR[0]][copyR[1]] = 0;
						copyR[0] = curX;
						copyR[1] = curY;
						copyMap[copyR[0]][copyR[1]] = 2;
						break;

					}
				}

				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}
			}
			else {
				curX = copyB[0];
				curY = copyB[1];
				while (1) {
					nextX = curX + dx[curDir];
					nextY = curY + dy[curDir];
					if (copyMap[nextX][nextY] == 0) {
						curX = nextX;
						curY = nextY;
					}
					else if (copyMap[nextX][nextY] == -1) {
						copyMap[copyB[0]][copyB[1]] = 0;
						returnFlag = -1;
						break;
					}
					else {
						copyMap[copyB[0]][copyB[1]] = 0;
						copyB[0] = curX;
						copyB[1] = curY;
						copyMap[copyB[0]][copyB[1]] = 3;
						break;

					}
				}

				if (returnFlag != -1) {
					curX = copyR[0];
					curY = copyR[1];
					while (1) {
						nextX = curX + dx[curDir];
						nextY = curY + dy[curDir];
						if (copyMap[nextX][nextY] == 0) {
							curX = nextX;
							curY = nextY;
						}
						else if (copyMap[nextX][nextY] == -1) {
							copyMap[copyR[0]][copyR[1]] = 0;
							returnFlag = 1;
							break;
						}
						else {
							copyMap[copyR[0]][copyR[1]] = 0;
							copyR[0] = curX;
							copyR[1] = curY;
							copyMap[copyR[0]][copyR[1]] = 2;
							break;

						}
					}
				}
			}
			break;
		}

		//cout << curDir << "방향 이동 후" << endl;
		//print_copy_map();


		if (returnFlag != 0) {
			return returnFlag;
		}
	}

	return 0;
}

void BFS(int sDir, int num) {
	vector <pair <int, pair< int, int>>> v;
	v.push_back(make_pair(sDir, make_pair(0, 1)));

	int curDir, pDir, nextDir, numDir, index = 0;
	int startNum = 2;
	arr[1] = index;

	while (1) {
		curDir = v[index].first;
		pDir = v[index].second.first;
		numDir = v[index].second.second;
		if (startNum == numDir) {
			arr[startNum] = index;
			startNum++;
		}
		if (numDir >= num) break;
		
		switch (curDir) {
		case 0: case 1:
			v.push_back(make_pair(2, make_pair(index, numDir + 1)));
			v.push_back(make_pair(3, make_pair(index, numDir + 1)));
			break;
		case 2: case 3:
			v.push_back(make_pair(0, make_pair(index, numDir + 1)));
			v.push_back(make_pair(1, make_pair(index, numDir + 1)));
			break;

		}
		index += 1;
	}

	/*
	cout << "벡터 정보: index, curDir, parent, number" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout <<i <<", "<< v[i].first << ", " << v[i].second.first << ", " << v[i].second.second << endl;
	}

	cout << "각 횟수별 startIndex" << endl;
	for (int i = 1; i <= num; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	*/
	int startIndex, endIndex, parentIndex, dirNum, simFlag = 0;
	for (int i = 1; i <= num; i++) {
		if (Answer < i) break;
		startIndex = arr[i];
		if (i < num) {
			endIndex = arr[i + 1];
		}
		else {
			endIndex = v.size();
		}

		for (int j = startIndex; j < endIndex; j++) {
			dirNum = i;
			dir[dirNum] = v[j].first;
			parentIndex = v[j].second.first;
			dirNum--;
			while (1) {
				if (dirNum == 0) {
					/*
					cout << i<< "개의 arr Dir" << endl;
					for (int k = 1; k <= i; k++) {
						cout << dir[k] << ' ';
					}
					cout << endl;
					*/
					simFlag = sim(i);
					if(simFlag == 1 && Answer > i) Answer = i;
					break;
				}
				dir[dirNum] = v[parentIndex].first;
				parentIndex = v[parentIndex].second.first;
				dirNum--;
			}
		}

		if (simFlag == 1) break;
	}
	

}

void Input() {
	string temp;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		for (int j = 0; j < M; j++) {
			switch (temp.at(j)) {
			case '.':
				map[i][j] = 0;
				break;
			case '#': 
				map[i][j] = 1;
				break;
			case 'O':
				map[i][j] = -1;
				h[0] = i;
				h[1] = j;
				break;
			case 'R':
				map[i][j] = 2;
				r[0] = i;
				r[1] = j;
				break;
			case 'B':
				map[i][j] = 3;
				b[0] = i;
				b[1] = j;
				break;
			}
		}
		
	}

}

void Solve() {

	for (int i = 0; i < 4; i++) {
		BFS(i, 11);
	}
	if (Answer == 11) Answer = -1;
	cout << Answer << endl;

}


int main(void) {
	Input();
	Solve();

	return 0;
}