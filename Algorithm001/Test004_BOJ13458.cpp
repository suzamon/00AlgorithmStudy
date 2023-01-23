/*
N개의 시험장 -> i번 시험장에는 응시자 수 Ai
총감독관은 한 시험장에서 감시할 수 있는 응시자의 수가 B명이고,
부감독관은 한 시험장에서 감시할 수 있는 응시자의 수가 C명
각각의 시험장에 총감독관은 오직 1명만 있어야 하고, 부감독관은 여러 명 가능
각 시험장마다 응시생들을 모두 감시해야 한다. 이때, 필요한 감독관 수의 최솟값

첫째 줄에 시험장의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다.
둘째 줄에는 각 시험장에 있는 응시자의 수 Ai (1 ≤ Ai ≤ 1,000,000)가 주어진다.
셋째 줄에는 B와 C가 주어진다. (1 ≤ B, C ≤ 1,000,000)

1. Input()
	N, Student(deque), B, C

2.Solve()
	1) 1~N까지 각 시험장에서 B를 빼고 studentNum/C + 1을 Answer에 더함
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, B, C;
long Answer = 0;

deque <int> st;


void Solve() {
	int stNum;
	Answer = 0;
	for (int i = 0; i < N; i++) {
		stNum = st.front();
		st.pop_front();

		Answer += 1;
		stNum -= B;
		if (stNum > 0) {
			if (stNum%C == 0) Answer += stNum / C;
			else Answer += (stNum / C) + 1;
		}
	}
}

void Input() {
	int tmp;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		st.push_back(tmp);
	}
	cin >> B >> C;
	
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;
	return 0;
}