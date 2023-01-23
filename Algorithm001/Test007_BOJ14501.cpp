/*
상담원으로 일하고 있는 백준이는 퇴사를 하려고 한다.

오늘부터 N+1일째 되는 날 퇴사를 하기 위해서, 남은 N일 동안 최대한 많은 상담
백준이는 비서에게 최대한 많은 상담을 잡으라고 부탁을 했고, 비서는 하루에 하나씩 서로 다른 사람의 상담을 잡아놓았다.
각각의 상담은 상담을 완료하는데 걸리는 기간 Ti와 상담을 했을 때 받을 수 있는 금액 Pi

상담을 하는데 필요한 기간은 1일보다 클 수 있기 때문에, 모든 상담을 할 수는 없다.
예를 들어서 1일에 상담을 하게 되면, 2일, 3일에 있는 상담은 할 수 없게 된다.
2일에 있는 상담을 하게 되면, 3, 4, 5, 6일에 잡혀있는 상담은 할 수 없다.
또한, N+1일째에는 회사에 없기 때문에, 6, 7일에 있는 상담을 할 수 없다.
퇴사 전에 할 수 있는 상담의 최대 이익은 1일, 4일, 5일에 있는 상담을 하는 것이며, 이때의 이익은 10+20+15=45이다.

상담을 적절히 했을 때, 백준이가 얻을 수 있는 최대 수익을 구하는 프로그램을 작성하시오.

첫째 줄에 N (1 ≤ N ≤ 15)이 주어진다.
둘째 줄부터 N개의 줄에 Ti와 Pi가 공백으로 구분되어서 주어지며,
1일부터 N일까지 순서대로 주어진다. (1 ≤ Ti ≤ 5, 1 ≤ Pi ≤ 1,000)

첫째 줄에 백준이가 얻을 수 있는 최대 이익을 출력

1. Input()
	N, Days[N], Fee[N], Answer = 0

2. Solve()
	1) DFS(start, sum) : 1~N까지 탐색 -> 이후에 Answer이랑 비교해서 업데이

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