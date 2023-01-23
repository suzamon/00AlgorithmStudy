/*
����
�������� ���ϰ� �ִ� �����̴� ��縦 �Ϸ��� �Ѵ�.

���ú��� N+1��° �Ǵ� �� ��縦 �ϱ� ���ؼ�, ���� N�� ���� �ִ��� ���� ����� �Ϸ��� �Ѵ�.

�����̴� �񼭿��� �ִ��� ���� ����� ������� ��Ź�� �߰�, �񼭴� �Ϸ翡 �ϳ��� ���� �ٸ� ����� ����� ��Ƴ��Ҵ�.

������ ����� ����� �Ϸ��ϴµ� �ɸ��� �Ⱓ Ti�� ����� ���� �� ���� �� �ִ� �ݾ� Pi�� �̷���� �ִ�.

N = 7�� ��쿡 ������ ���� ��� ����ǥ�� ����.

	1��	2��	3��	4��	5��	6��	7��
Ti	3	5	1	1	2	4	2
Pi	10	20	10	20	15	40	200

1�Ͽ� �����ִ� ����� �� 3���� �ɸ���, ������� �� ���� �� �ִ� �ݾ��� 10�̴�.
5�Ͽ� �����ִ� ����� �� 2���� �ɸ���, ���� �� �ִ� �ݾ��� 15�̴�.

����� �ϴµ� �ʿ��� �Ⱓ�� 1�Ϻ��� Ŭ �� �ֱ� ������, ��� ����� �� ���� ����.
���� �� 1�Ͽ� ����� �ϰ� �Ǹ�, 2��, 3�Ͽ� �ִ� ����� �� �� ���� �ȴ�.
2�Ͽ� �ִ� ����� �ϰ� �Ǹ�, 3, 4, 5, 6�Ͽ� �����ִ� ����� �� �� ����.

����, N+1��°���� ȸ�翡 ���� ������, 6, 7�Ͽ� �ִ� ����� �� �� ����.

��� ���� �� �� �ִ� ����� �ִ� ������ 1��, 4��, 5�Ͽ� �ִ� ����� �ϴ� ���̸�, �̶��� ������ 10+20+15=45�̴�.

����� ������ ���� ��, �����̰� ���� �� �ִ� �ִ� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N (1 �� N �� 15)�� �־�����.

��° �ٺ��� N���� �ٿ� Ti�� Pi�� �������� ���еǾ �־�����, 1�Ϻ��� N�ϱ��� ������� �־�����. (1 �� Ti �� 5, 1 �� Pi �� 1,000)

���
ù° �ٿ� �����̰� ���� �� �ִ� �ִ� ������ ����Ѵ�.


N, day[16], fee[16]

1. Input()
	N, day[N], fee[N]

2. Solution()
	int nD = 0, nS = 0;
	for(int d=1; d<=N; d++)
	nD = d + (day[d] - 1);
	if(nD > N) continue;
	nS = fee[d];
	DFS(nD, nS)

*DFS(int sD, int sS)
	if(sD > N){
	if(Answer < nS) Answer = nS;
	return;
	}
	else if(sD==N){
	if(day[sD] == 1) {
	int nS = sS + fee[sD];
	if(Answer < nS) Answer = nS;
	}
	else{
	if(Answer < nS) Answer = nS;
	}
	return;
	}

	int nD;
	for(int d = sD; d <=N; d++){
	nD = sD + day[d];
	if(nD <= N){
	DFS(nD, sS + fee[d]);
	}
	else{
	DFS(nD, sS);
	}
	}

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, Answer = 0;
int day[16] = { 0, }, fee[16] = { 0, };

void DFS(int sD, int sS) {
	if (sD >= N) {
		if (Answer < sS) Answer = sS;
		return;
	}

	int nD;
	for (int d = sD + 1; d <= N; d++) {
		if (d == N) {
			if (day[d] == 1) {
				DFS(N + 1, sS + fee[d]);
			}
			else {
				DFS(N + 1, sS);
			}
		}
		else {
			nD = d + day[d] - 1;
			if (nD <= N) {
				DFS(nD, sS + fee[d]);
			}
			else {
				DFS(nD, sS);
			}
		}
	}
}

void Solution() {
	int nD = 0, nS = 0;
	for (int d = 1; d <= N; d++) {
		nD = d + (day[d]) - 1;
		if (nD > N) continue;
		nS = fee[d];
		DFS(nD, nS);
	}
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> day[i] >> fee[i];
	}
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}