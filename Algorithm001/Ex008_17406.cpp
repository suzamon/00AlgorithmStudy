/*
크기가 N×M 크기인 배열 A가 있을때, 배열 A의 값은 각 행에 있는 모든 수의 합 중 최솟값을 의미한다.
배열은 회전 연산을 수행할 수 있다.
회전 연산은 세 정수 (r, c, s)로 이루어져 있고,
가장 왼쪽 윗 칸이 (r-s, c-s), 가장 오른쪽 아랫 칸이 (r+s, c+s)인 정사각형을
시계 방향으로 한 칸씩 돌린다는 의미

배열 A와 사용 가능한 회전 연산이 주어졌을 때, 배열 A의 값의 최솟값을 구해보자.
회전 연산은 모두 한 번씩 사용 & 순서는 임의로 정해도 된다.

첫째 줄에 배열 A의 크기 N, M, 회전 연산의 개수 K가 주어진다.
둘째 줄부터 N개의 줄에 배열 A에 들어있는 수 A[i][j]가 주어지고,
다음 K개의 줄에 회전 연산의 정보 r, c, s가 주어진다.

3 ≤ N, M ≤ 50
1 ≤ K ≤ 6
1 ≤ A[i][j] ≤ 100
1 ≤ s
1 ≤ r-s < r < r+s ≤ N
1 ≤ c-s < c < c+s ≤ M

1. Input() : N, M, K, map[N][M], command[6][3]

2. Solution():
	1. 회전 명령어 순서 정하기 -> DFS(int start, int cnt)
	2. rotate() -> 아래 참조
	3. find_min() : 행별 최소값 탐색


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, M, K, Answer = 5001;

int map[51][51];
int copyMap[51][51];
int command[6][3]{ 0, };
int visited[6] = { 0, };

int arr[6];

void find_min() {
	int minSum = 5001, sum = 0;

	for (int r = 1; r <= N; r++) {
		sum = 0;
		for (int c = 1; c <= M; c++) {
			sum += copyMap[r][c];
		}
		minSum = min(minSum, sum);
	}

	Answer = min(Answer, minSum);
}

void rot_map(int row, int col, int size) {
	queue <pair <int, int>> q;
	queue <int> q1;
	int r, c;

	
	for (int s = 1; s <= size; s++) {
		r = row - s + 1;
		c = col - s;
		q1.push(copyMap[r][c]);
		r = row - s;
		for (c = col - s; c <= col + s; c++) {
			//q.push(make_pair(r, c));
			q1.push(copyMap[r][c]);
		}
		c--;
		for (r = row - s + 1; r <= row + s; r++) {
			//q.push(make_pair(r, c));
			q1.push(copyMap[r][c]);
		}
		r--;
		for (c = col + s - 1; c >= col - s; c--) {
			//q.push(make_pair(r, c));
			q1.push(copyMap[r][c]);
		}
		c++;
		for (r = row + s - 1; r > row - s + 1; r--) {
			//q.push(make_pair(r, c));
			q1.push(copyMap[r][c]);
		}

		r = row - s;
		for (c = col - s; c <= col + s; c++) {
			//cout << r << ", " << c << ": ";
			//cout << q.front().first << ", " << q.front().second << endl;
			//q.pop();
			copyMap[r][c] = q1.front();
			q1.pop();
		}
		c--;
		for (r = row - s + 1; r <= row + s; r++) {
			//cout << r << ", " << c << ": ";
			//cout << q.front().first << ", " << q.front().second << endl;
			//q.pop();
			copyMap[r][c] = q1.front();
			q1.pop();
		}
		r--;
		for (c = col + s - 1; c >= col - s; c--) {
			//cout << r << ", " << c << ": ";
			//cout << q.front().first << ", " << q.front().second << endl;
			//q.pop();
			copyMap[r][c] = q1.front();
			q1.pop();
		}
		c++;
		for (r = row + s - 1; r > row - s; r--) {
			//cout << r << ", " << c << ": ";
			//cout << q.front().first << ", " << q.front().second << endl;
			//q.pop();
			copyMap[r][c] = q1.front();
			q1.pop();
		}
		//cout << "queue size: " << q.size() << endl;
		//cout << "rotate end" << endl;
	}
}

void copy_map() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			copyMap[r][c] = map[r][c];
		}
	}
}

void find_com(int cnt) {
	if (cnt == K) {
		/*
		cout << "명령어 셋트: ";
		for (int i = 0; i < cnt; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
		*/
		int idx;
		copy_map();
		for (int i = 0; i < cnt; i++) {
			idx = arr[i];
			rot_map(command[idx][0], command[idx][1], command[idx][2]);
		}
		find_min();

		return;
	}

	for (int i = 0; i < K; i++) {
		if (visited[i] == 0) {
			visited[i] = 1;
			arr[cnt] = i;
			find_com(cnt + 1);
			visited[i] = 0;
		}
	}
}

void Solution() {
	/*
	copy_map();
	cout << "Before Rotate" << endl;;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	rot_map(4, 2, 1);
	rot_map(3, 4, 2);
	cout << "Rotate" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
	
	for (int i = 0; i < K; i++) {
		arr[0] = i;
		visited[i] = 1;
		find_com(1);
		visited[i] = 0;
	}
	
}

void Input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> command[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}