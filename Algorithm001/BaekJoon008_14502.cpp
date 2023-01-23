#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, Answer = 0;

int map[9][9];
int copyMap[9][9];
int wall[3][2];

vector <pair <int, int>> virus;
vector <pair <int, int>> emptyP;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

void find_empty_place() {
	int cntEmpty = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (copyMap[i][j] == 0) cntEmpty++;
		}
	}
	if (cntEmpty > Answer) Answer = cntEmpty;
}

void simulation() {

	queue <pair <int, int>>  simVirus;

	for (int i = 0; i < virus.size(); i++) {
		simVirus.push(make_pair(virus[i].first, virus[i].second));
	}

	int startX, startY, nextX, nextY;

	while (!simVirus.empty()) {
		startX = simVirus.front().first;
		startY = simVirus.front().second;
		simVirus.pop();

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < M) {
				if (copyMap[nextX][nextY] == 0) {
					copyMap[nextX][nextY] = 2;
					simVirus.push(make_pair(nextX, nextY));
				}
			}

		}
	}


}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < 3; i++) {
		copyMap[wall[i][0]][wall[i][1]] = 1;
	}

}

void findWall(int start, int cnt) {
	if (cnt == 3) {
		/*
		cout << "Find Wall" << endl;
		for (int i = 0; i < 3; i++) {
			cout << wall[i][0] << ", " << wall[i][1]<<endl;
		}
		cout << endl;
		*/
		copy_map();
		simulation();
		find_empty_place();
		return;
	}

	for (int i = start; i < emptyP.size(); i++) {
		wall[cnt][0] = emptyP[i].first;
		wall[cnt][1] = emptyP[i].second;
		findWall(i + 1, cnt + 1);
	}
}

void Solve() {
	for (int i = 0; i < emptyP.size() - 2; i++) {
		wall[0][0] = emptyP[i].first;
		wall[0][1] = emptyP[i].second;
		findWall(i + 1, 1);
	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));
			}
			else if (map[i][j] == 0) {
				emptyP.push_back(make_pair(i, j));
			}
		}
	}
}

int main(void) {
	Input();
	Solve();

	cout << Answer << endl;
	return 0;
}