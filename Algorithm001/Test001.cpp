#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

long N;
int Answer = 0;
int arr[10];

int Soltion(int num, int cnt) {
	int tmp = 0, tmpCnt = 0;

	while (1) {
		tmp = num % 10;
		if (arr[tmp] == 0) {
			arr[tmp] = 1;
			tmpCnt++;
		}
		num = num / 10;
		if (num == 0) break;
	}

	cnt = tmpCnt + cnt;

	return cnt;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		if (test_case != 1) {
			for (int i = 0; i < 10; i++) arr[i] = 0;
		}

		cin >> N;
		int num, cnt = 0, mul = 1;
		while (1) {
			num = mul * N;
			cnt = Soltion(num, cnt);
			if (cnt == 10) break;
			mul++;
		}
		cout << '#' << test_case << ' ' << num << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}