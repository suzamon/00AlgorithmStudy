/*
N���� ���� �̷���� ���� A1, A2, ..., AN�� �־�����. ��, ���� �� ���̿� �������� �� �ִ� N-1���� �����ڰ� �־�����.
�����ڴ� ����(+), ����(-), ����(��), ������(��)���θ� �̷���� �ִ�.

���� ���, 6���� ���� �̷���� ������ 1, 2, 3, 4, 5, 6�̰�,
�־��� �����ڰ� ����(+) 2��, ����(-) 1��, ����(��) 1��, ������(��) 1���� ��쿡�� �� 60������ ���� ���� �� �ִ�.
���� ���, �Ʒ��� ���� ���� ���� �� �ִ�.
1+2+3-4��5��6
1��2+3+4-5��6
1+2��3��4-5+6
1��2��3-4+5+6
���� ����� ������ �켱 ������ �����ϰ� �տ������� �����ؾ� �Ѵ�. ��, �������� ���� ���������� �� ���Ѵ�.
������ ����� ���� ���� C++14�� ������ ������. ��, ����� �ٲ� �� ���� ���ϰ�, �� ���� ������ �ٲ� �Ͱ� ����.
�̿� ����, ���� �� 4���� ����� ����غ��� �Ʒ��� ����.
1+2+3-4��5��6 = 1
1��2+3+4-5��6 = 12
1+2��3��4-5+6 = 5
1��2��3-4+5+6 = 7
N���� ���� N-1���� �����ڰ� �־����� ��, ���� �� �ִ� ���� ����� �ִ��� �Ͱ� �ּ��� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

ù° �ٿ� ���� ���� N(2 �� N �� 11)�� �־�����.
��° �ٿ��� A1, A2, ..., AN�� �־�����. (1 �� Ai �� 100)
��° �ٿ��� ���� N-1�� 4���� ������ �־����µ�,
���ʴ�� ����(+)�� ����, ����(-)�� ����, ����(��)�� ����, ������(��)�� �����̴�.

ù° �ٿ� ���� �� �ִ� ���� ����� �ִ���, ��° �ٿ��� �ּڰ��� ����Ѵ�.
�����ڸ� ��� �����־ �׻� -10�ﺸ�� ũ�ų� ����, 10�ﺸ�� �۰ų� ���� ����� ������ �Է¸� �־�����.
����, �տ������� ������� ��, �߰��� ���Ǵ� ���� ����� �׻� -10�ﺸ�� ũ�ų� ����, 10�ﺸ�� �۰ų� ����.

-> ��Ž���� DFS ��� Ǯ��

long Answer, max, min
int N, num[12], op[4], totalOpCnt;
1. Input()
	N, num, max, min, op[4], totalOpCnt;

2. Solution()
	: DFS�� ���� for(int i=0; i<4; i++) op[i]��ŭ ����
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, num[12], op[4], totalOpCnt;
int fOp[12];
long maxAnswer = -1000000000, minAnswer = 1000000000;

void findAnswer() {
	long tmpAnswer = num[0];

	for (int i = 0; i < N - 1; i++) {
		switch (fOp[i]) {
		case 0:
			tmpAnswer = tmpAnswer + num[i + 1];
			break;
		case 1:
			tmpAnswer = tmpAnswer - num[i + 1];
			break;
		case 2:
			tmpAnswer = tmpAnswer * num[i + 1];
			break;
		case 3:
			tmpAnswer = tmpAnswer / num[i + 1];
			break;
		}
	}

	if (maxAnswer < tmpAnswer) maxAnswer = tmpAnswer;
	if (minAnswer > tmpAnswer) minAnswer = tmpAnswer;
}

void DFS(int cnt) {
	if (cnt == totalOpCnt) {
		findAnswer();
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (op[i] > 0) {
			op[i]--;
			fOp[cnt] = i;
			DFS(cnt + 1);
			op[i]++;
		}
	}

}

void Solution() {
	for (int i = 0; i < 4; i++) {
		if (op[i] > 0) {
			op[i]--;
			fOp[0] = i;
			DFS(1);
			op[i]++;
		}
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	totalOpCnt = N - 1;
	for (int i = 0; i < 4; i++) {
		cin >> op[i];
	}
}


int main(void) {
	Input();
	Solution();
	cout << maxAnswer << endl;
	cout << minAnswer << endl;
	return 0;
}