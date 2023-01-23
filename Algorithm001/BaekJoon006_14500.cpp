#include <iostream>

using namespace std;

int N, M;
int map[501][501];
int visited[501][501];
int answer;
int point[4][2];
int dir[4][2] = { {0,1}, {0, -1}, {-1, 0}, {1,0} };


void find_answer(int cnt) {
	if (cnt == 4) {
		int temp_sum = 0;
		for (int i = 0; i < cnt; i++) {
			temp_sum += map[point[i][0]][point[i][1]];
		}
		if (answer < temp_sum) {
			answer = temp_sum;
			/*
			cout << "Answer : "<< answer << endl;
			for (int i = 0; i < cnt; i++) {
				cout << point[i][0] << ", " << point[i][1] <<endl;
			}
			cout << endl;
			*/
		}

		return;
	}

	int startX, startY, nextX, nextY;

	for (int i = 0; i < cnt; i++) {
		startX = point[i][0];
		startY = point[i][1];

		for (int j = 0; j < 4; j++) {
			nextX = startX + dir[j][0];
			nextY = startY + dir[j][1];

			if (visited[nextX][nextY] == 0 && nextX >= 0 && nextX < N && nextY >= 0 && nextY < M) {
				point[cnt][0] = nextX;
				point[cnt][1] = nextY;
				visited[nextX][nextY] = 1;
				find_answer(cnt + 1);
				visited[nextX][nextY] = 0;
			}
		}
	}


}

int main(void) {
	cin >> N;
	cin >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			point[0][0] = i;
			point[0][1] = j;
			visited[i][j] = 1;
			find_answer(1);
			visited[i][j] = 0;
		}
	}

	cout << answer << endl;



	return 0;
}