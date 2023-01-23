/*
�������̳�� ũ�Ⱑ 1��1�� ���簢���� ���� �� �̾ ���� �����̸�, ������ ���� ������ �����ؾ� �Ѵ�.

���簢���� ���� ��ġ�� �� �ȴ�.
������ ��� ����Ǿ� �־�� �Ѵ�.
���簢���� ������ ����Ǿ� �־�� �Ѵ�. ��, �������� �������� �´�� ������ �� �ȴ�

ũ�Ⱑ N��M�� ���� ���� ��Ʈ�ι̳� �ϳ��� �������� �Ѵ�. ���̴� 1��1 ũ���� ĭ���� �������� ������, ������ ĭ���� ����

��Ʈ�ι̳� �ϳ��� ������ ���Ƽ� ��Ʈ�ι̳밡 ���� ĭ�� ���� �ִ� ������ ���� �ִ�� �ϴ� ���α׷��� �ۼ��Ͻÿ�.

��Ʈ�ι̳�� �ݵ�� �� ���簢���� ��Ȯ�� �ϳ��� ĭ�� �����ϵ��� ���ƾ� �ϸ�, ȸ���̳� ��Ī�� ���ѵ� �ȴ�.

ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (4 �� N, M �� 500)

��° �ٺ��� N���� �ٿ� ���̿� ���� �ִ� ���� �־�����.
i��° ���� j��° ���� ���������� i��° ĭ, ���ʿ������� j��° ĭ�� ���� �ִ� ���̴�.
�Է����� �־����� ���� 1,000�� ���� �ʴ� �ڿ����̴�.

A) ù° �ٿ� ��Ʈ�ι̳밡 ���� ĭ�� ���� ������ ���� �ִ��� ����Ѵ�.

1. Input
	N, M, map[N][M]
2. Solution
	1) 4�� 1x1 ���簢���� ���� �������̳� ����
		: �Ʒ�, ���� �̵��ϴ� �������̳븸 ����
		: ����� 4���� �������̳�� dq�� ����
	2) (0,0) ~ (N,M)���� Ž��


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, Answer = 0;
int map[501][501];
int arr[9][9] = { 0, };

int pointDx[4];
int pointDy[4];
deque <pair<int, int>> dq;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

void print_poly_map() {
	int cnt = 1;
	while (!dq.empty()) {
		int pmap[9][9] = { 0, };

		for (int i = 0; i < 4; i++) {
			pmap[4 + dq.front().first][ 4 + dq.front().second] = 1;
			dq.pop_front();
		}

		cout << cnt << "��° ����" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << pmap[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		cnt++;
	}
}

void find_answer() {
	int polyArr[4][2] = { 0, };
	int polyCnt = dq.size() / 4;
	int nextX, nextY, sum, exitFlag;

	for (int startX = 0; startX < N; startX++) {
		for (int startY = 0; startY < M; startY++) {
			for (int i = 0; i < polyCnt; i++) {
				sum = 0;
				exitFlag = 0;
				for (int j = 0; j < 4; j++) {
					polyArr[j][0] = dq[(i * 4) + j].first;
					polyArr[j][1] = dq[(i * 4) + j].second;
					nextX = startX + polyArr[j][0];
					nextY = startY + polyArr[j][1];
					if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) {
						exitFlag = 1;
						break;
					}
					sum += map[nextX][nextY];
				}
				if (sum > Answer && exitFlag == 0) {
					Answer = sum;
					/*
					cout << Answer << "�� ��" << endl;
					cout << "x: " << startX << ", y: " << startY << endl;
					cout << "ploy ��" << endl;
					for (int k = 0; k < 4; k++) {
						cout << '(' << polyArr[k][0] << ',' << polyArr[k][1] << "), ";
					}
					cout << endl;
					cout << endl;
					*/
				}
			}


		}
	}

}

void find_poly(int cnt) {
	if (cnt == 0) {
		pointDx[0] = 0;
		pointDy[0] = 0;
		arr[4][4] = 1;
		find_poly(1);
	}
	else if (cnt == 4) {
		for (int i = 0; i < 4; i++) dq.push_back(make_pair(pointDx[i], pointDy[i]));
		return;
	}

	int curX, curY, nextX, nextY;

	for (int i = 0; i < cnt; i++) {
		curX = pointDx[i];
		curY = pointDy[i];

		for (int d = 0; d < 4; d++) {
			nextX = curX + dx[d];
			nextY = curY + dy[d];
			if (arr[4 + nextX][4 + nextY] == 0) {
				pointDx[cnt] = nextX;
				pointDy[cnt] = nextY;
				arr[4 + nextX][4 + nextY] = 1;
				find_poly(cnt + 1);
				arr[4 + nextX][4 + nextY] = 0;
			}
		}
	}

}

void Solution() {
	find_poly(0);
	find_answer();
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	/*
	int T;

	cin >> T;
	for (int i = 0; i < T; i++) {
		Answer = 0;
		Input();
		Solution();
		cout << Answer << endl;
	}
	*/
	//find_poly(0);
	//print_poly_map();
	
	Input();
	Solution();
	cout << Answer << endl;
	
	return 0;
}