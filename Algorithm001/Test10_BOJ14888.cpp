/*
����
N���� ���� �̷���� ���� A1, A2, ..., AN�� �־�����. ��, ���� �� ���̿� �������� �� �ִ� N-1���� �����ڰ� �־�����.
�����ڴ� ����(+), ����(-), ����(��), ������(��)���θ� �̷���� �ִ�.

�츮�� ���� �� ���̿� �����ڸ� �ϳ��� �־, ������ �ϳ� ���� �� �ִ�. �̶�, �־��� ���� ������ �ٲٸ� �� �ȴ�.

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

�Է�
ù° �ٿ� ���� ���� N(2 �� N �� 11)�� �־�����. ��° �ٿ��� A1, A2, ..., AN�� �־�����.
(1 �� Ai �� 100) ��° �ٿ��� ���� N-1�� 4���� ������ �־����µ�,
���ʴ�� ����(+)�� ����, ����(-)�� ����, ����(��)�� ����, ������(��)�� �����̴�.

���
ù° �ٿ� ���� �� �ִ� ���� ����� �ִ���, ��° �ٿ��� �ּڰ��� ����Ѵ�.
�����ڸ� ��� �����־ �׻� -10�ﺸ�� ũ�ų� ����, 10�ﺸ�� �۰ų� ���� ����� ������ �Է¸� �־�����.
����, �տ������� ������� ��, �߰��� ���Ǵ� ���� ����� �׻� -10�ﺸ�� ũ�ų� ����, 10�ﺸ�� �۰ų� ����.


int N, opCnt = 0,  Answer = 0;
int num[12];
deque <int, int> op;
int finalOp[11];

Input()
	N, num[N], op[4];

Solution()
	for(int i=0; i<op.size(); i++){
	finalOp[0] = op[i].first;
	op[i].second = 1;
	DFS(1);
	op[i].second = 0;
	}

void DFS(int cnt){
	if(cnt == N-1){
	calcu();
	return;
	}
	for(int i=0; i<op.size(); i++){
	if(op[i].second == 0) {
	finalOp[cnt] = op[i].first;
	op[i].second = 1;
	DFS(cnt + 1);
	op[i].second = 0;
	}
	}
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N;
long minAns = 1000000000, maxAns = -1000000000;
int num[12];
deque <pair <int, int>> op;
int finalOp[11];

void cal() {
	long tmp = 0;
	tmp = num[0];

	for (int i = 0; i < N - 1; i++) {
		switch (finalOp[i]) {
		case 1:
			tmp = tmp + num[i + 1];
			break;
		case 2:
			tmp = tmp - num[i + 1];
			break;
		case 3:
			tmp = (long) tmp * num[i + 1];
			break;
		case 4:
			tmp = (long) tmp / num[i + 1];
			break;
		}
	}

	if (maxAns < tmp) maxAns = tmp;
	if (minAns > tmp) minAns = tmp;
}

void DFS(int cnt) {
	if (cnt == N - 1) {
		cal();
		return;
	}
	for (int i = 0; i < op.size(); i++) {
		if (op[i].second == 0) {
			finalOp[cnt] = op[i].first;
			op[i].second = 1;
			DFS(cnt + 1);
			op[i].second = 0;
		}
	}
}

void Solution() {
	for (int i = 0; i < op.size(); i++) {
		finalOp[0] = op[i].first;
		op[i].second = 1;
		DFS(1);
		op[i].second = 0;
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> num[i];
	int tmp;

	for (int i = 1; i <= 4; i++) {
		cin >> tmp;
		for (int j = 0; j < tmp; j++) {
			op.push_back(make_pair(i, 0));
		}
	}
}


int main(void) {
	Input();
	Solution();
	cout << maxAns << endl;
	cout << minAns << endl;
	return 0;
}