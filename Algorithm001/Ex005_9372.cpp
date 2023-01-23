/*
겨울 방학을 맞아 N개국 여행하면서 자아 찾기로
최대한 적은 종류의 비행기 -> 가장 적은 종류의 비행기를 타고 모든 국가들을 여행할 수 있도록 도와주자.
국가에서 다른 국가로 이동할 때 다른 국가를 거쳐 가도(심지어 이미 방문한 국가라도) 된다.

첫 번째 줄에는 테스트 케이스의 수 T(T ≤ 100)
각 테스트 케이스마다 다음과 같은 정보
첫 번째 줄에는 국가의 수 N(2 ≤ N ≤ 1 000)과 비행기의 종류 M(1 ≤ M ≤ 10 000)
이후 M개의 줄에 a와 b 쌍들이 입력된다. a와 b를 왕복하는 비행기가 있다는 것을 의미
주어지는 비행 스케줄은 항상 연결 그래프

1. Input() : N, M, deque q[N] <int>

2. Solve() :
 -> MST : 최소신장트리 N개의 노트 탐색할려면 N-1번 탐색하면 됨!
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