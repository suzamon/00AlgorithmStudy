#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <cmath>

using namespace std;

int N, Answer = 0;
long M;

int Solution() {
	int min_num = pow(2, N -1 );
	if (M < min_num) return 0;

	if ((1 & M) != 1) return 0;
	for (int i = 1; i < N; i++) {
		if (((1 << i) & M) != (1 << i)) return 0;
	}
	return 1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int flag = 1;
		cin >> N >> M;
		flag = Solution();
		if (flag == 0) cout << '#' << test_case << ' ' << "OFF" << endl;
		else cout << '#' << test_case << ' ' << "ON" << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}