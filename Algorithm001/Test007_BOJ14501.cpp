/*
�������� ���ϰ� �ִ� �����̴� ��縦 �Ϸ��� �Ѵ�.

���ú��� N+1��° �Ǵ� �� ��縦 �ϱ� ���ؼ�, ���� N�� ���� �ִ��� ���� ���
�����̴� �񼭿��� �ִ��� ���� ����� ������� ��Ź�� �߰�, �񼭴� �Ϸ翡 �ϳ��� ���� �ٸ� ����� ����� ��Ƴ��Ҵ�.
������ ����� ����� �Ϸ��ϴµ� �ɸ��� �Ⱓ Ti�� ����� ���� �� ���� �� �ִ� �ݾ� Pi

����� �ϴµ� �ʿ��� �Ⱓ�� 1�Ϻ��� Ŭ �� �ֱ� ������, ��� ����� �� ���� ����.
���� �� 1�Ͽ� ����� �ϰ� �Ǹ�, 2��, 3�Ͽ� �ִ� ����� �� �� ���� �ȴ�.
2�Ͽ� �ִ� ����� �ϰ� �Ǹ�, 3, 4, 5, 6�Ͽ� �����ִ� ����� �� �� ����.
����, N+1��°���� ȸ�翡 ���� ������, 6, 7�Ͽ� �ִ� ����� �� �� ����.
��� ���� �� �� �ִ� ����� �ִ� ������ 1��, 4��, 5�Ͽ� �ִ� ����� �ϴ� ���̸�, �̶��� ������ 10+20+15=45�̴�.

����� ������ ���� ��, �����̰� ���� �� �ִ� �ִ� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

ù° �ٿ� N (1 �� N �� 15)�� �־�����.
��° �ٺ��� N���� �ٿ� Ti�� Pi�� �������� ���еǾ �־�����,
1�Ϻ��� N�ϱ��� ������� �־�����. (1 �� Ti �� 5, 1 �� Pi �� 1,000)

ù° �ٿ� �����̰� ���� �� �ִ� �ִ� ������ ���

1. Input()
	N, Days[N], Fee[N], Answer = 0

2. Solve()
	1) DFS(start, sum) : 1~N���� Ž�� -> ���Ŀ� Answer�̶� ���ؼ� ������

*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, days[16], fee[16], Answer = 0;

void DFS(int start, int sum) {
	if (start == N) {
		if (Answer < sum) Answer = sum;
		return;
	}

	int nextD;

	for (int i = start; i < N; i++) {
		nextD = i + days[i];
		
		if (nextD <= N) DFS(nextD, sum + fee[i]);
	}
	if (Answer < sum) Answer = sum;
	return;
}

void Solution() {
	int startD;
	for (int i = 0; i < N; i++) {
		startD = i + days[i];
		if (startD < N) {
			DFS(startD, fee[i]);
		}
		else if (startD == N && Answer < fee[i]) {
			Answer = fee[i];
		}
	}
}

void Input() {
	Answer = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> days[i] >> fee[i];
	}	
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;
	return 0;
}