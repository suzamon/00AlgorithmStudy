/*
����
������ ��ŸƮ��ũ�� �ٴϴ� ������� �𿩼� �౸�� �غ����� �Ѵ�. �౸�� ���� ���Ŀ� �ϰ� �ǹ� ������ �ƴϴ�.
�౸�� �ϱ� ���� ���� ����� �� N���̰� �ű��ϰԵ� N�� ¦���̴�.
���� N/2������ �̷���� ��ŸƮ ���� ��ũ ������ ������� ������ �Ѵ�.

BOJ�� ��ϴ� ȸ�� ��� ������� ��ȣ�� 1���� N������ �����߰�, �Ʒ��� ���� �ɷ�ġ�� �����ߴ�.
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
���� ������ ���� ��쿡�� 1, 4���� ��ŸƮ ��, 2, 3�� ���� ��ũ ���� ���ϸ� ��ŸƮ ���� �ɷ�ġ�� 6,
��ũ ���� �ɷ�ġ�� 6�� �Ǿ ���̰� 0�� �ǰ� �� ���� �ּ��̴�.

�Է�
ù° �ٿ� N(4 �� N �� 20, N�� ¦��)�� �־�����. ��° �ٺ��� N���� �ٿ� S�� �־�����.
�� ���� N���� ���� �̷���� �ְ�, i�� ���� j��° ���� Sij �̴�. Sii�� �׻� 0�̰�, ������ Sij�� 1���� ũ�ų� ����,
100���� �۰ų� ���� �����̴�.

���
ù° �ٿ� ��ŸƮ ���� ��ũ ���� �ɷ�ġ�� ������ �ּڰ��� ����Ѵ�.


int N, cntA, cntB;
long Answer = 100000000;
int arr[21][21];
int teamA[21], teamB[21];

Input()
	N, arr[21][21];
Solution()
	cntA = 0, cntB = 0;
	findTeam(1);



void findTeam(int cnt){
	if(cnt == N + 1){
	findDiff();
	return;
	}
	for(int i=1; i<=2; i++){
	if( i== 1 && cntA < N/2){
	teamA[cntA] = cnt;
	cntA++;
	findTeam(cnt+1);
	cntA--;
	}
	else if( i== 2 && cntB < N/2){
	cntB++;
	teamB[cntA] = cnt;
	findTeam(cnt+1);
	cntB--;
	}

	}
}

void findDiff(){
	int sumA = 0, sumB = 0;
	int sIdx, nIdx;
	for(int i=0; i<N/2; i++){
	sIdx = teamA[i];
	for(int j=0; j<N/2; j++){
	nIdx = teamA[j];
	if(sIdx==nIdx) continue;
	sumA = sumA + arr[sIdx][nIdx];
	}
	}

	for(int i=0; i<N/2; i++){
	sIdx = teamB[i];
	for(int j=0; j<N/2; j++){
	nIdx = teamB[j];
	if(sIdx==nIdx) continue;
	sumB = sumB + arr[sIdx][nIdx];
	}
	}

	long finalDiff = abs(sumA - sumB);
	if(Answer > finalDiff) Answer = finalDiff;r
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

int N, cntA, cntB;
long Answer = 100000000;
int arr[21][21];
int teamA[21], teamB[21];

void findDiff() {
	int sumA = 0, sumB = 0;
	int sIdx, nIdx;
	for (int i = 0; i < N / 2; i++) {
		sIdx = teamA[i];
		for (int j = 0; j < N / 2; j++) {
			nIdx = teamA[j];
			if (sIdx == nIdx) continue;
			sumA = sumA + arr[sIdx][nIdx];
		}
	}

	for (int i = 0; i < N / 2; i++) {
		sIdx = teamB[i];
		for (int j = 0; j < N / 2; j++) {
			nIdx = teamB[j];
			if (sIdx == nIdx) continue;
			sumB = sumB + arr[sIdx][nIdx];
		}
	}

	long finalDiff = abs(sumA - sumB);
	if (Answer > finalDiff) Answer = finalDiff;
}

void findTeam(int cnt) {
	if (cnt == N + 1) {
		findDiff();
		return;
	}
	for (int i = 1; i <= 2; i++) {
		if (i == 1 && cntA < N / 2) {
			teamA[cntA] = cnt;
			cntA++;
			findTeam(cnt + 1);
			cntA--;
		}
		if (i == 2 && cntB < N / 2) {
			teamB[cntB] = cnt;
			cntB++;
			findTeam(cnt + 1);
			cntB--;
		}

	}
}

void Solution() {
	cntA = 0, cntB = 0;
	findTeam(1);
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