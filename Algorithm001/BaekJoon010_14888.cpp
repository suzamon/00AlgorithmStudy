#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
long maxAnswer = -1000000000, minAnswer = 1000000000;

int number[12];
int arrOp[11];

vector <pair <int, int>> op;

void cal() {
	long num1, num2;

	num1 = number[0];

	for (int i = 0; i < N-1; i++) {
		num2 = number[i + 1];

		switch (arrOp[i]) {
		case 1:
			num1 = num1 + num2;
			break;
		case 2:
			num1 = num1 - num2;
			break;
		case 3:
			num1 = num1 * num2;
			break;
		case 4:
			num1 = num1 / num2;
			break;
		}
	}

	if (minAnswer > num1) minAnswer = num1;
	if (maxAnswer < num1) maxAnswer = num1;
}

void DFS(int cnt) {
	if (cnt == N - 1) {
		cal();
		return;
	}

	for (int i = 0; i < op.size(); i++) {
		if (op[i].second == 0) {
			op[i].second = 1;
			arrOp[cnt] = op[i].first;
			DFS(cnt + 1);
			op[i].second = 0;
		}
	}

}

void Solve() {
	for (int i = 0; i < op.size(); i++) {
		if (op[i].second == 0) {
			op[i].second = 1;
			arrOp[0] = op[i].first;
			DFS(1);
			op[i].second = 0;
		}
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> number[i];
	}
	int tmp;
	for (int i = 0; i < 4; i++) {
		cin >> tmp;

		for (int j = 0; j < tmp; j++) {
			op.push_back(make_pair(i + 1, 0));
		}

	}

}

int main(void) {
	Input();
	Solve();
	cout << maxAnswer << endl;
	cout << minAnswer << endl;

	return 0;
}