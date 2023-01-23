/*
�ܿ� ������ �¾� N���� �����ϸ鼭 �ھ� ã���
�ִ��� ���� ������ ����� -> ���� ���� ������ ����⸦ Ÿ�� ��� �������� ������ �� �ֵ��� ��������.
�������� �ٸ� ������ �̵��� �� �ٸ� ������ ���� ����(������ �̹� �湮�� ������) �ȴ�.

ù ��° �ٿ��� �׽�Ʈ ���̽��� �� T(T �� 100)
�� �׽�Ʈ ���̽����� ������ ���� ����
ù ��° �ٿ��� ������ �� N(2 �� N �� 1 000)�� ������� ���� M(1 �� M �� 10 000)
���� M���� �ٿ� a�� b �ֵ��� �Էµȴ�. a�� b�� �պ��ϴ� ����Ⱑ �ִٴ� ���� �ǹ�
�־����� ���� �������� �׻� ���� �׷���

1. Input() : N, M, deque q[N] <int>

2. Solve() :
 -> MST : �ּҽ���Ʈ�� N���� ��Ʈ Ž���ҷ��� N-1�� Ž���ϸ� ��!
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int T, N, M, Answer = 9999;

deque <int> q[1001];
int visited[1001];

void DFS(int startC, int numC, int cnt) {
	if (numC == N) {
		if (Answer > cnt) Answer = cnt;
		return;
	}
	if (cnt > Answer) return;

	int nextC, nextNumC;
	for (int i = 0; i < q[startC].size(); i++) {
		if (q[startC][i] == 0) continue;
		
		nextC = q[startC][i];
		q[startC][i] = 0;
		if (visited[nextC] == 0) {
			visited[nextC] = 1;
			nextNumC = numC + 1;
		}
		else {
			nextNumC = numC;
		}
		DFS(nextC, nextNumC, cnt + 1);
		
		q[startC][i] = 1;
		if (nextNumC != numC) visited[nextC] = 0;


	}
}

void Solution() {
	for (int i = 0; i < N; i++) {
		visited[i] = 1;
		DFS(i, 1, 0);
		visited[i] = 0;
	}
}

void Reset() {
	int tmpSize;
	for (int i = 0; i < N; i++) {
		tmpSize = q[i].size();
		for (int j = 0; j < tmpSize; j++) {
			q[i].pop_back();
		}
	}
	Answer = 9999;

}

void Input() {
	cin >> N >> M;
	int startC, endC;
	
	for (int i = 0; i < M; i++) {
		cin >> startC >> endC;
		//q[startC].push_back(endC);
		//q[endC].push_back(startC);
	}
	
}

int main(void) {
	cin >> T;
	for (int i = 0; i < T; i++) {
		Input();
		//Solution();
		cout << N-1 << endl;
		//Reset();
	}

	return 0;
}