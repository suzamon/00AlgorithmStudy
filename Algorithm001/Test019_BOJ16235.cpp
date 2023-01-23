#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>

using namespace std;

int N, M, K;
int A[11][11];
int map[11][11];

deque <pair <pair<int, int>, pair<int, int>>> tree_deque;
deque <pair <pair<int, int>, pair<int, int>>> died_tree_deque;

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < tree_deque.size(); i++) {
		cout << tree_deque[i].first.first << "년산 나무 상태:" << tree_deque[i].first.second << ", 위치 : (" << tree_deque[i].second.first << ", " << tree_deque[i].second.second << ") " << endl;
	}
	cout << endl;
}

void Solve() {
	int time = 0;
	int x, y, age, size;
	while (1) {
		time++;

		//Spring
		size = tree_deque.size();
		for (int i = 0; i < size; i++) {
			x = tree_deque.front().second.first;
			y = tree_deque.front().second.second;
			age = tree_deque.front().first.first;
			tree_deque.pop_front();
			if (map[x][y] >= age) {
				map[x][y] -= age;
				tree_deque.push_back(make_pair(make_pair(age + 1, 0), make_pair(x, y)));
			}
			else {
				died_tree_deque.push_back(make_pair(make_pair(age, -1), make_pair(x, y)));
			}
		}

		//cout << time << "년 후 봄" << endl;
		//print();

		//Summer
		size = died_tree_deque.size();
		for (int i = 0; i < size; i++) {
			x = died_tree_deque.front().second.first;
			y = died_tree_deque.front().second.second;
			age = died_tree_deque.front().first.first;
			map[x][y] += (age / 2);
			died_tree_deque.pop_front();
		}

		//cout << time << "년 후 여름" << endl;
		//print();

		//Fall
		for (int i = tree_deque.size() - 1; i >= 0; i--) {
			if (tree_deque[i].first.first < 5) break;

			if (tree_deque[i].first.first % 5 == 0) {
				x = tree_deque[i].second.first;
				y = tree_deque[i].second.second;
				for (int j = -1; j <= 1; j++) {
					for (int k = -1; k <= 1; k++) {
						if (j == 0 && k == 0) continue;

						if (x + j >= 0 && x + j < N && y + k >= 0 && y + k < N) {
							tree_deque.push_front(make_pair(make_pair(1, 0), make_pair(x + j, y + k)));
							i++;
						}
					}
				}
			}
		}
		//cout << time << "년 후 가을" << endl;
		//print();
		//Winter
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] += A[i][j];
			}
		}

		//cout << time << "년 후 겨울" << endl;
		//print();
		if (time == K || tree_deque.size() == 0) break;
	}
}

void print_tree() {
	for (int i = 0; i < tree_deque.size(); i++) {
		cout << tree_deque[i].first.first << "년산 나무 상태:" << tree_deque[i].first.second << ", 위치 : (" << tree_deque[i].second.first << ", " << tree_deque[i].second.second << ") " << endl;
	}
}

void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			map[i][j] = 5;
		}
	}
	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x;
		cin >> y;
		cin >> z;
		tree_deque.push_back(make_pair(make_pair(z, 0), make_pair(x - 1, y - 1)));
		//tree_deque.push_back(make_pair(make_pair(z, 0), make_pair(x - 1, y - 1)));
	}

	sort(tree_deque.begin(), tree_deque.end());
	//print_tree();

}

int main(void) {
	Input();
	Solve();

	cout << tree_deque.size() << endl;

	return 0;
}