#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, Answer = 0;

int robot[3];

int map[51][51];
int visited[51][51];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void change_dir() {
	if (robot[2] == 0) robot[2] = 3;
	else robot[2] -= 1;
}

void print() {
	cout << "로봇 위치 : " << robot[0] << ", " << robot[1] << ", 방향: " << robot[2] << endl;

	cout << "visited map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

}

void Solve() {

	int startX, startY, nextX, nextY, dirFlag;
	visited[robot[0]][robot[1]] = 1;
	Answer++;
	while (1) {
		startX = robot[0];
		startY = robot[1];
		
		dirFlag = 0;

		for (int i = 0; i < 4; i++) {

			change_dir();

			nextX = startX + dx[robot[2]];
			nextY = startY + dy[robot[2]];
			if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < M && map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				robot[0] = nextX;
				robot[1] = nextY;
				Answer++;
				//cout << "청소" << endl;
				//print();
				break;
			}
			dirFlag++;
		}

		if (dirFlag == 4) {
			nextX = startX - dx[robot[2]];
			nextY = startY - dy[robot[2]];
			if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < M && map[nextX][nextY] == 0) {
				robot[0] = nextX;
				robot[1] = nextY;
				//cout << "후진" << endl;
				//print();
			}
			else {
				//cout << "끝" << endl;
				//print();
				break;
			}
		}
	}

}

void Input() {
	cin >> N >> M;

	for (int i = 0; i < 3; i++) {
		cin >> robot[i];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

}

int main(void) {

	Input();
	Solve();

	cout << Answer << endl;
	return 0;
}