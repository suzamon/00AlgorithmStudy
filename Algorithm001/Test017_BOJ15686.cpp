/*
ũ�Ⱑ N��N�� ���ð� �ִ�. ���ô� 1��1ũ���� ĭ���� �������� �ִ�. ������ �� ĭ�� �� ĭ, ġŲ��, �� �� �ϳ��̴�.
������ ĭ�� (r, c)�� ���� ���·� ��Ÿ����, r�� c�� �Ǵ� ���������� r��° ĭ, ���ʿ������� c��° ĭ�� �ǹ��Ѵ�.
r�� c�� 1���� �����Ѵ�.

�� ���ÿ� ��� ������� ġŲ�� �ſ� �����Ѵ�. ����, ������� "ġŲ �Ÿ�"��� ���� �ַ� ����Ѵ�.
ġŲ �Ÿ��� ���� ���� ����� ġŲ�� ������ �Ÿ��̴�.
��, ġŲ �Ÿ��� ���� �������� ��������, ������ ���� ġŲ �Ÿ��� ������ �ִ�.
������ ġŲ �Ÿ��� ��� ���� ġŲ �Ÿ��� ���̴�.

������ �� ĭ (r1, c1)�� (r2, c2) ������ �Ÿ��� |r1-r2| + |c1-c2|�� ���Ѵ�.

�� ���ÿ� �ִ� ġŲ���� ��� ���� �����������̴�. ���������� ���翡���� ������ ������Ű�� ���� �Ϻ� ġŲ���� ���
���� ���� ���� �� ���ÿ��� ���� ������ ���� �� �� �ִ�  ġŲ���� ������ �ִ� M����� ����� �˾Ƴ�����.

���ÿ� �ִ� ġŲ�� �߿��� �ִ� M���� ����, ������ ġŲ���� ��� ������Ѿ� �Ѵ�.
��� ����, ������ ġŲ �Ÿ��� ���� �۰� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N(2 �� N �� 50)�� M(1 �� M �� 13)�� �־�����.
��° �ٺ��� N���� �ٿ��� ������ ������ �־�����.
������ ������ 0, 1, 2�� �̷���� �ְ�, 0�� �� ĭ, 1�� ��, 2�� ġŲ���� �ǹ��Ѵ�. ���� ������ 2N���� ���� ������,
��� 1���� �����Ѵ�. ġŲ���� ������ M���� ũ�ų� ����, 13���� �۰ų� ����.

���
ù° �ٿ� �����Ű�� ���� ġŲ���� �ִ� M���� ����� ��, ������ ġŲ �Ÿ��� �ּڰ��� ����Ѵ�.

deque <int, int> chicken, int [101][2] house
deque <int> chickenDis[101] -> �� ������ �� ġŲ���� �Ÿ� ����

N, M, map[N][N]

1. Input()
	N, M, map[N][N] -> 1�̸�, house�� 2��, chicken�� ����
2. Solution()
	1) find_all_distance(startX, startY) : �� ������ �� ġŲ�������� �Ÿ� ����
	3) find_chicken(int cnt) : M���� ġŲ ����
		3-1) cnt == M�̸�, �� �� �� ġŲ �Ÿ� ���ϱ�
		3-2) totalDistance�� ���ؼ� Answer�̶� ��
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, houseCnt = 0, Answer = 0;
int house[101][2];
int arr[14];
deque <pair <int, int>> chicken;
deque <int> chickenDis[101];

void find_all_distance(int houseIdx) {
	int startX = house[houseIdx][0];
	int startY = house[houseIdx][1];

	int nextX, nextY, distance;

	for (int chickenIdx = 0; chickenIdx < chicken.size(); chickenIdx++) {
		nextX = chicken[chickenIdx].first;
		nextY = chicken[chickenIdx].second;

		distance = abs(nextX - startX) + abs(nextY - startY);
		chickenDis[houseIdx].push_back(distance);
	}
}

void find_chicken(int start, int cnt) {
	if (cnt == M) {
		int totalDistance = 0, tmpDistance = 200;

		for (int i = 0; i < houseCnt; i++) {
			tmpDistance = 200;
			for (int j = 0; j < cnt; j++) {
				if (tmpDistance > chickenDis[i][arr[j]]) tmpDistance = chickenDis[i][arr[j]];
			}
			totalDistance = totalDistance + tmpDistance;
		}

		if (Answer == 0) Answer = totalDistance;
		else if(Answer > totalDistance) Answer = totalDistance;

		return;
	}

	for (int i = start; i < chicken.size(); i++) {
		arr[cnt] = i;
		find_chicken(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < houseCnt; i++) {
		find_all_distance(i);
	}

	for (int i = 0; i <= chicken.size() - M; i++) {
		find_chicken(0, 0);
	}

}

void Input() {
	int tmp;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			if (tmp == 1) {
				house[houseCnt][0] = i;
				house[houseCnt][1] = j;
				houseCnt++;
			}
			else if (tmp == 2) {
				chicken.push_back(make_pair(i, j));
			}
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}