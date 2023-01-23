#include <iostream>

#define N_MAX 100005

typedef long long ll;
using namespace std;

ll Answer, Biggest_Time;
int N, M;
ll Counter[N_MAX];

void init() {
	Answer = 0;
	Biggest_Time = 0;
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> Counter[i];
		if (Counter[i] > Biggest_Time) Biggest_Time = Counter[i];
	}
}

void Solution() {
	ll Left = 0;
	ll Right = (ll)(Biggest_Time * M);

	ll Mid, Sum;
	Answer = Right;

	while(Left <= Right) {
		Sum = 0;
		Mid = (Left + Right) / 2;

		for (int i = 0; i < N; i++) Sum = Sum + (Mid / Counter[i]);

		if (Sum < M) Left = Mid + 1;
		else {
			Answer = Mid;
			Right = Mid - 1;
		}
	}

}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		Input();
		Solution();

		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}


/*
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

#define MAX_N 100001

using namespace std;

int N, M, maxTmpArrSize, Answer = 0;
int arr[MAX_N] = { 0, };
int tmpArr[MAX_N] = { 0, };

void print_info() {
	cout << "Array" << endl;
	for (int i = 0; i < N; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

bool compare(int a, int b) {
	return a < b;
}

void precondi() {
	sort(arr, arr + N, compare);
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		arr[i] = 0;
		tmpArr[i] = 0;
	}
}

void simulation(int peopleCnt) {
	if (peopleCnt == 1) {
		tmpArr[0] = 1;
		Answer = arr[0];
		maxTmpArrSize = 1;
		return;
	}

	int tmpTime, tmpIdx, addIdx = 0, beforeTime= Answer;
	Answer = max(Answer, arr[addIdx] * (tmpArr[addIdx] + 1));

	for (tmpIdx = 1; tmpIdx <= maxTmpArrSize; tmpIdx++) {
		if (tmpArr[tmpIdx - 1] <= tmpArr[tmpIdx]) continue;
		
		tmpTime = beforeTime;
		tmpTime = max(tmpTime, arr[tmpIdx] * (tmpArr[tmpIdx] + 1));

		if (Answer > tmpTime) {
			addIdx = tmpIdx;
			Answer = tmpTime;
		}
	}

	if (addIdx == maxTmpArrSize && addIdx < (N - 1)) {
		maxTmpArrSize++;
	}
	tmpArr[addIdx]++;
}

void Solution() {
	precondi();
	//print_info();

	for (int i = 1; i <= M; i++) {
		simulation(i);
		//cout << i << ": " << Answer << endl;
	}

}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Init();
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
*/
