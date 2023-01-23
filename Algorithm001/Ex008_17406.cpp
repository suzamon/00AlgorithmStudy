/*
ũ�Ⱑ N��M ũ���� �迭 A�� ������, �迭 A�� ���� �� �࿡ �ִ� ��� ���� �� �� �ּڰ��� �ǹ��Ѵ�.
�迭�� ȸ�� ������ ������ �� �ִ�.
ȸ�� ������ �� ���� (r, c, s)�� �̷���� �ְ�,
���� ���� �� ĭ�� (r-s, c-s), ���� ������ �Ʒ� ĭ�� (r+s, c+s)�� ���簢����
�ð� �������� �� ĭ�� �����ٴ� �ǹ�

�迭 A�� ��� ������ ȸ�� ������ �־����� ��, �迭 A�� ���� �ּڰ��� ���غ���.
ȸ�� ������ ��� �� ���� ��� & ������ ���Ƿ� ���ص� �ȴ�.

ù° �ٿ� �迭 A�� ũ�� N, M, ȸ�� ������ ���� K�� �־�����.
��° �ٺ��� N���� �ٿ� �迭 A�� ����ִ� �� A[i][j]�� �־�����,
���� K���� �ٿ� ȸ�� ������ ���� r, c, s�� �־�����.

3 �� N, M �� 50
1 �� K �� 6
1 �� A[i][j] �� 100
1 �� s
1 �� r-s < r < r+s �� N
1 �� c-s < c < c+s �� M

1. Input() : N, M, K, map[N][M], command[6][3]

2. Solution():
	1. ȸ�� ��ɾ� ���� ���ϱ� -> DFS(int start, int cnt)
	2. rotate() -> �Ʒ� ����
	3. find_min() : �ະ �ּҰ� Ž��


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
		cout << "��ɾ� ��Ʈ: ";
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