/*
����
�� N���� �������� �ְ�, ������ �����帶�� �����ڵ��� �ִ�. i�� �����忡 �ִ� �������� ���� Ai���̴�.

�������� �Ѱ������� �ΰ��������� �� ������ �ִ�.
�Ѱ������� �� �����忡�� ������ �� �ִ� �������� ���� B���̰�,
�ΰ������� �� �����忡�� ������ �� �ִ� �������� ���� C���̴�.

������ �����忡 �Ѱ������� ���� 1�� �־�� �ϰ�, �ΰ������� ���� �� �־ �ȴ�.

�� �����帶�� ���û����� ��� �����ؾ� �Ѵ�. �̶�, �ʿ��� ������ ���� �ּڰ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� �������� ���� N(1 �� N �� 1,000,000)�� �־�����.

��° �ٿ��� �� �����忡 �ִ� �������� �� Ai (1 �� Ai �� 1,000,000)�� �־�����.

��° �ٿ��� B�� C�� �־�����. (1 �� B, C �� 1,000,000)

���
�� �����帶�� ���û��� ��� �����ϱ� ���� �ʿ��� �������� �ּ� ���� ����Ѵ�.

N, deque <int> dq, B, C
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, B, C;
long long Answer = 0;
deque <int> dq;

void Solution() {
	Answer = 0;
	
	int stdNum = 0, dqSize;
	dqSize = dq.size();
	for (int i = 0; i < dqSize; i++) {
		stdNum = dq.front();
		dq.pop_front();

		if (stdNum <= B) {
			Answer++;
			continue;
		}
		else {
			stdNum = stdNum - B;
			Answer++;
			if (stdNum % C == 0) {
				Answer = Answer + (stdNum / C);
			}
			else {
				Answer = Answer + (stdNum / C);
				Answer++;
			}
		}
	}
}

void Input() {
	int tmp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		dq.push_back(tmp);
	}
	cin >> B >> C;
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}