/*
������ ��ŸƮ��ũ�� �ٴϴ� ������� �𿩼� �౸�� �غ����� �Ѵ�.
�౸�� ���� ���Ŀ� �ϰ� �ǹ� ������ �ƴϴ�.
�౸�� �ϱ� ���� ���� ����� �� N���̰� �ű��ϰԵ� N�� ¦���̴�.
���� N/2������ �̷���� ��ŸƮ ���� ��ũ ������ ������� ������ �Ѵ�.

��ȣ�� 1���� N������ �����߰�, �Ʒ��� ���� �ɷ�ġ�� �����ߴ�.
�ɷ�ġ Sij�� i�� ����� j�� ����� ���� ���� ������ ��, ���� �������� �ɷ�ġ�̴�.
���� �ɷ�ġ�� ���� ���� ��� ���� �ɷ�ġ Sij�� ���̴�.
 Sij�� Sji�� �ٸ� ���� ������, i�� ����� j�� ����� ���� ���� ������ ��, ���� �������� �ɷ�ġ�� Sij�� Sji�̴�.

N=4�̰�, S�� �Ʒ��� ���� ��츦 ���캸��.

i\j	1	2	3	4
1	 	1	2	3
2	4	 	5	6
3	7	1	 	2
4	3	4	5
���� ���, 1, 2���� ��ŸƮ ��, 3, 4���� ��ũ ���� ���� ��쿡 �� ���� �ɷ�ġ�� �Ʒ��� ����.
��ŸƮ ��: S12 + S21 = 1 + 4 = 5
��ũ ��: S34 + S43 = 2 + 5 = 7

1, 3���� ��ŸƮ ��, 2, 4���� ��ũ ���� ���ϸ�, �� ���� �ɷ�ġ�� �Ʒ��� ����.
��ŸƮ ��: S13 + S31 = 2 + 7 = 9
��ũ ��: S24 + S42 = 6 + 4 = 10

�౸�� ����ְ� �ϱ� ���ؼ� ��ŸƮ ���� �ɷ�ġ�� ��ũ ���� �ɷ�ġ�� ���̸� �ּҷ� �Ϸ��� �Ѵ�.
���� ������ ���� ��쿡�� 1, 4���� ��ŸƮ ��, 2, 3�� ���� ��ũ ���� ���ϸ�
��ŸƮ ���� �ɷ�ġ�� 6, ��ũ ���� �ɷ�ġ�� 6�� �Ǿ ���̰� 0�� �ǰ� �� ���� �ּ��̴�.

ù° �ٿ� N(4 �� N �� 20, N�� ¦��)�� �־�����. ��° �ٺ��� N���� �ٿ� S�� �־�����.
�� ���� N���� ���� �̷���� �ְ�, i�� ���� j��° ���� Sij �̴�. Sii�� �׻� 0�̰�,
������ Sij�� 1���� ũ�ų� ����, 100���� �۰ų� ���� �����̴�.

ù° �ٿ� ��ŸƮ ���� ��ũ ���� �ɷ�ġ�� ������ �ּڰ��� ����Ѵ�.

int t1[10], t2[10], Answer = -1, pTeam[21],  N, arr[21][21];

1. Input()
	N, arr[N+1][N+1]

2. Solution()
	1) ������� �� ���� -> DFS�� ���� -> pCnt, t1Cnt, t2Cnt�� ����
		pCnt == N�̸� ��
		Ž���� ��, t1Cnt = N/2�̸�, ������ t2Cnt��
		DFS ���� ������ pCnt, t1Cnt, t2Cnt
		�¾��� ���� t1Cnt++, pCnt++, pTeam[pCnt] = team��ȣ
	2) �¾� �� �Ǹ� ���� ���� �ó��� ���� ������ ���ؼ� ���̰� ����
		t1[10], t2[10]�� ���� �ο��� index �ֱ�
		Answer = -1�̸� ������ Answer �� ����
		Answer != -1�̸� Answer ���̶� ���ؼ� ������ Answer ������Ʈ
*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = -1;
int t1[10], t2[10], pTeam[21], arr[21][21];

void find_answer() {
	int t1Idx = 0, t2Idx = 0;

	for (int i = 1; i <= N; i++) {
		if (pTeam[i] == 1) {
			t1[t1Idx] = i;
			t1Idx++;
		}
		else if (pTeam[i] == 2) {
			t2[t2Idx] = i;
			t2Idx++;
		}
	}

	long sum1 = 0, sum2 = 0;
	int diff = 0;

	for (int i = 1; i <= N; i++) {
		if (pTeam[i] == 1) {
			for (int j = 0; j < t1Idx; j++) {
				sum1 += arr[i][t1[j]];
			}
		}
		else {
			for (int j = 0; j < t2Idx; j++) {
				sum2 += arr[i][t2[j]];
			}
		}
	}

	diff = (int)(abs(sum1 - sum2));

	if (Answer == -1) Answer = diff;
	else if (Answer > diff) Answer = diff;

}

void DFS(int pCnt, int t1Cnt, int t2Cnt) {
	if (pCnt == N + 1) {
		find_answer();
		return;
	}

	if (t1Cnt < N / 2) {
		pTeam[pCnt] = 1;
		DFS(pCnt + 1, t1Cnt + 1, t2Cnt);
	}

	if (t2Cnt < N / 2) {
		pTeam[pCnt] = 2;
		DFS(pCnt + 1, t1Cnt, t2Cnt + 1);
	}

}

void Solution() {
	pTeam[1] = 1;
	DFS(2, 1, 0);
	pTeam[1] = 2;
	DFS(2, 0, 1);
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}