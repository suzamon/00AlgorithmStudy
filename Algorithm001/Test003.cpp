#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

int N, Answer = 0;
deque <int> dq;

int arr[4];


void Input() {
	string str;
	char tmp;
	cin >> str;
	for (int i = 0; i < str.length(); i++) {
		tmp = str.at(i);
		dq.push_back((int)tmp - 'A' + 1);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}