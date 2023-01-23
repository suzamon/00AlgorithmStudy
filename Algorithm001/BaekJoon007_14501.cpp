#include <iostream>

using namespace std;

int N, Answer = 0;
int work[15][2];
int sum;

void DFS(int start, int sum) {
	if (start == N) {
		if (sum > Answer) Answer = sum;
		return;
	}

	int nextStart, nextSum;

	for (int i = start; i < N; i++) {
		nextStart = i + work[i][0];
		if (nextStart <= N) {
			nextSum = sum + work[i][1];
			DFS(nextStart, nextSum);
		}
		else {
			if (sum > Answer) Answer = sum;
		}

	}

}

void Solve() {
	int tmp_start = 0;
	for (int i = 0; i < N; i++) {
		sum = 0;
		tmp_start = i + work[i][0];
		sum += work[i][1];
		if (tmp_start < N) {
			DFS(tmp_start, sum);
		}
		else if (tmp_start == N && sum > Answer) {
			Answer = sum;
		}
	}

}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> work[i][0] >> work[i][1];
	}
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;

	return 0;
}