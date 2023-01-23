/*
N���� ������ -> i�� �����忡�� ������ �� Ai
�Ѱ������� �� �����忡�� ������ �� �ִ� �������� ���� B���̰�,
�ΰ������� �� �����忡�� ������ �� �ִ� �������� ���� C��
������ �����忡 �Ѱ������� ���� 1�� �־�� �ϰ�, �ΰ������� ���� �� ����
�� �����帶�� ���û����� ��� �����ؾ� �Ѵ�. �̶�, �ʿ��� ������ ���� �ּڰ�

ù° �ٿ� �������� ���� N(1 �� N �� 1,000,000)�� �־�����.
��° �ٿ��� �� �����忡 �ִ� �������� �� Ai (1 �� Ai �� 1,000,000)�� �־�����.
��° �ٿ��� B�� C�� �־�����. (1 �� B, C �� 1,000,000)

1. Input()
	N, Student(deque), B, C

2.Solve()
	1) 1~N���� �� �����忡�� B�� ���� studentNum/C + 1�� Answer�� ����
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