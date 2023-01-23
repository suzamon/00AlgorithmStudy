/*
오늘은 스타트링크에 다니는 사람들이 모여서 축구를 해보려고 한다.
축구는 평일 오후에 하고 의무 참석도 아니다.
축구를 하기 위해 모인 사람은 총 N명이고 신기하게도 N은 짝수이다.
이제 N/2명으로 이루어진 스타트 팀과 링크 팀으로 사람들을 나눠야 한다.

번호를 1부터 N까지로 배정했고, 아래와 같은 능력치를 조사했다.
능력치 Sij는 i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치이다.
팀의 능력치는 팀에 속한 모든 쌍의 능력치 Sij의 합이다.
 Sij는 Sji와 다를 수도 있으며, i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치는 Sij와 Sji이다.

N=4이고, S가 아래와 같은 경우를 살펴보자.

i\j	1	2	3	4
1	 	1	2	3
2	4	 	5	6
3	7	1	 	2
4	3	4	5
예를 들어, 1, 2번이 스타트 팀, 3, 4번이 링크 팀에 속한 경우에 두 팀의 능력치는 아래와 같다.
스타트 팀: S12 + S21 = 1 + 4 = 5
링크 팀: S34 + S43 = 2 + 5 = 7

1, 3번이 스타트 팀, 2, 4번이 링크 팀에 속하면, 두 팀의 능력치는 아래와 같다.
스타트 팀: S13 + S31 = 2 + 7 = 9
링크 팀: S24 + S42 = 6 + 4 = 10

축구를 재미있게 하기 위해서 스타트 팀의 능력치와 링크 팀의 능력치의 차이를 최소로 하려고 한다.
위의 예제와 같은 경우에는 1, 4번이 스타트 팀, 2, 3번 팀이 링크 팀에 속하면
스타트 팀의 능력치는 6, 링크 팀의 능력치는 6이 되어서 차이가 0이 되고 이 값이 최소이다.

첫째 줄에 N(4 ≤ N ≤ 20, N은 짝수)이 주어진다. 둘째 줄부터 N개의 줄에 S가 주어진다.
각 줄은 N개의 수로 이루어져 있고, i번 줄의 j번째 수는 Sij 이다. Sii는 항상 0이고,
나머지 Sij는 1보다 크거나 같고, 100보다 작거나 같은 정수이다.

첫째 줄에 스타트 팀과 링크 팀의 능력치의 차이의 최솟값을 출력한다.

int t1[10], t2[10], Answer = -1, pTeam[21],  N, arr[21][21];

1. Input()
	N, arr[N+1][N+1]

2. Solution()
	1) 사람별로 팀 구분 -> DFS로 구현 -> pCnt, t1Cnt, t2Cnt는 전달
		pCnt == N이면 끝
		탐색할 때, t1Cnt = N/2이면, 무조건 t2Cnt로
		DFS 인자 값으로 pCnt, t1Cnt, t2Cnt
		셋업은 속한 t1Cnt++, pCnt++, pTeam[pCnt] = team번호
	2) 셋업 다 되면 각각 속한 시너지 합을 팀별로 구해서 차이값 구함
		t1[10], t2[10]에 속한 인원들 index 넣기
		Answer = -1이면 무조건 Answer 값 변경
		Answer != -1이면 Answer 값이랑 비교해서 작으면 Answer 업데이트
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