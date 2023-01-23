/*
�� 8���� ��ϸ� ������ �ִ� ��Ϲ��� 4���� �Ʒ� �׸��� ���� �Ϸķ� ������ �ִ�.
��, ��ϴ� N�� �Ǵ� S�� �� �ϳ��� ��Ÿ���� �ִ�.
��Ϲ������� ��ȣ�� �Ű��� �ִµ�, ���� ���� ��Ϲ����� 1��, �� �������� 2��, �� �������� 3��, ���� ������ ��Ϲ����� 4��
�̶�, ��Ϲ����� �� K�� ȸ����Ű���� �Ѵ�. ��Ϲ����� ȸ���� �� ĭ�� �������� �Ѵ�.
ȸ���� �ð� ����� �ݽð� ������ �ְ�, �Ʒ� �׸��� ���� ȸ���Ѵ�.

��Ϲ����� ȸ����Ű����, ȸ����ų ��Ϲ����� ȸ����ų ������ �����ؾ� �Ѵ�.
��Ϲ����� ȸ���� ��, ���� �´��� �ؿ� ���� ���� �ִ� ��Ϲ����� ȸ����ų ���� �ְ�, ȸ����Ű�� ���� ���� �ִ�.
��Ϲ��� A�� ȸ���� ��, �� ���� �ִ� ��Ϲ��� B�� ���� �´��� ����� ���� �ٸ��ٸ�,
B�� A�� ȸ���� ����� �ݴ�������� ȸ���ϰ� �ȴ�.

�� ��Ϲ����� �´��� �κ��� �ʷϻ� �������� �����ִ� �κ��̴�.
���⼭, 3�� ��Ϲ����� �ݽð� �������� ȸ���ߴٸ�, 4�� ��Ϲ����� �ð� �������� ȸ���ϰ� �ȴ�.
2�� ��Ϲ����� �´��� �κ��� S������ ���� ���� ������, ȸ������ �ʰ� �ǰ�,
1�� ��Ϲ����� 2���� ȸ������ �ʾұ� ������, ȸ������ �ʰ� �ȴ�.


ù° �ٿ� 1�� ��Ϲ����� ����, ��° �ٿ� 2�� ��Ϲ����� ����, ��° �ٿ� 3�� ��Ϲ����� ����, ��° �ٿ� 4�� ��Ϲ����� ����
���´� 8���� ������ �̷���� �ְ�, 12�ù������ �ð���� ������� �־�����. N���� 0, S���� 1�� ��Ÿ���ִ�.

�ټ�° �ٿ��� ȸ�� Ƚ�� K(1 �� K �� 100)�� �־�����.
���� K�� �ٿ��� ȸ����Ų ����� ������� �־�����.
�� ����� �� ���� ������ �̷���� �ְ�, ù ��° ������ ȸ����Ų ��Ϲ����� ��ȣ, �� ��° ������ �����̴�.
������ 1�� ���� �ð� �����̰�, -1�� ���� �ݽð� �����̴�.

K�� ȸ����Ų ���Ŀ� �� ��Ϲ����� ������ ���� ����Ѵ�. ������ ������ ���� ����Ѵ�.

1�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 1��
2�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 2��
3�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 4��
4�� ��Ϲ����� 12�ù����� N���̸� 0��, S���̸� 8��

wheel[4][8], K, rot[K][2]

1. Input()
	wheel, K, rot[K][2]
2. Solution()
	1) K�� �ݺ�
	2) ù ȸ�� ��Ű�� �������� �����ؼ� ȸ���� ������ ȸ�� ���� Ž�� -> dq�� ����
		-> ���� [2]�� [6]�� ��
	3) dq�� ����� �������� �ð� or �ݽð� ȸ��
	4) K�� �ݺ� �� ���� ���� -> �� ������ [0] �迭 Ž��
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, Answer = 0;
int wheel[4][8], rot[101][2] = { 0, };
deque <pair <int, int>> r;

void find_answer() {
	int score = 1;
	for (int i = 0; i < 4; i++) {
		if(i > 0) score = score * 2;
		if(wheel[i][0] == 1) Answer = Answer + score;
	}
}

void rotate_wheel(int rotIdx, int rotDir) {
	int tmp;
	if (rotDir == 1) {
		tmp = wheel[rotIdx][7];
		for (int i = 7; i > 0; i--) {
			wheel[rotIdx][i] = wheel[rotIdx][i - 1];
		}
		wheel[rotIdx][0] = tmp;
	}
	else {
		tmp = wheel[rotIdx][0];
		for (int i = 0; i < 7; i++) {
			wheel[rotIdx][i] = wheel[rotIdx][i + 1];
		}
		wheel[rotIdx][7] = tmp;
	}
}

void find_rot(int idx) {
	int startIdx = rot[idx][0] - 1, startDir = rot[idx][1];

	r.push_back(make_pair(startIdx, startDir));

	switch (startIdx) {
	case 0:
		if (wheel[0][2] != wheel[1][6]) {
			startDir = -startDir;
			r.push_back(make_pair(1, startDir));
			if (wheel[1][2] != wheel[2][6]) {
				startDir = -startDir;
				r.push_back(make_pair(2, startDir));
				if (wheel[2][2] != wheel[3][6]) {
					startDir = -startDir;
					r.push_back(make_pair(3, startDir));
				}
			}
		}
		break;
	case 1:
		if (wheel[1][6] != wheel[0][2]) {
			r.push_back(make_pair(0, -startDir));
		}
		if (wheel[1][2] != wheel[2][6]) {
			startDir = -startDir;
			r.push_back(make_pair(2, startDir));
			if (wheel[2][2] != wheel[3][6]) {
				startDir = -startDir;
				r.push_back(make_pair(3, startDir));
			}
		}
		break;
	case 2:
		if (wheel[2][2] != wheel[3][6]) {
			r.push_back(make_pair(3, -startDir));
		}
		if (wheel[2][6] != wheel[1][2]) {
			startDir = -startDir;
			r.push_back(make_pair(1, startDir));
			if (wheel[1][6] != wheel[0][2]) {
				startDir = -startDir;
				r.push_back(make_pair(0, startDir));
			}
		}
		break;
	case 3:
		if (wheel[3][6] != wheel[2][2]) {
			startDir = -startDir;
			r.push_back(make_pair(2, startDir));
			if (wheel[2][6] != wheel[1][2]) {
				startDir = -startDir;
				r.push_back(make_pair(1, startDir));
				if (wheel[1][6] != wheel[0][2]) {
					startDir = -startDir;
					r.push_back(make_pair(0, startDir));
				}
			}
		}
	}

	while (!r.empty()) {
		rotate_wheel(r.front().first, r.front().second);
		r.pop_front();
	}

}

void Solution() {
	for (int i = 0; i < K; i++) {
		find_rot(i);
	}
	find_answer();
}

void Input() {
	int tmp;
	for (int i = 0; i < 4; i++) {
		cin >> tmp;
		for (int j = 7; j >= 0; j--) {
			wheel[i][j] = tmp % 10;
			tmp = tmp / 10;
		}
	}

	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> rot[i][0] >> rot[i][1];
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}