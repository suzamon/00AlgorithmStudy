/* 
0'28''22'''
���̰� N�� �����̾� ��Ʈ�� �ְ�, ���̰� 2N�� ��Ʈ�� �� �����̾� ��Ʈ�� ���Ʒ��� ���θ� ���� �ִ�.
��Ʈ�� ���� 1 �������� 2N���� ĭ���� �������� ������, �� ĭ���� �Ʒ� �׸��� ���� 1���� 2N������ ��ȣ�� �Ű��� �ִ�.

��Ʈ�� �� ĭ ȸ���ϸ� 1������ 2N-1�������� ĭ�� ���� ��ȣ�� ĭ�� �ִ� ��ġ�� �̵��ϰ�,
2N�� ĭ�� 1�� ĭ�� ��ġ�� �̵��Ѵ�. i�� ĭ�� �������� Ai�̴�.
���� �׸����� 1�� ĭ�� �ִ� ��ġ�� "�ø��� ��ġ", N�� ĭ�� �ִ� ��ġ�� "������ ��ġ"��� �Ѵ�.

�����̾� ��Ʈ�� �ڽ� ��� �κ��� �ϳ��� �ø����� �Ѵ�. �κ��� �ø��� ��ġ���� �ø� �� �ִ�.
�������� �κ��� ������ ��ġ�� �����ϸ� �� ��� ������. �κ��� �����̾� ��Ʈ ������ ������ �̵��� �� �ִ�.
�κ��� �ø��� ��ġ�� �ø��ų� �κ��� � ĭ���� �̵��ϸ� �� ĭ�� �������� ��� 1��ŭ �����Ѵ�.

�����̾� ��Ʈ�� �̿��� �κ����� �ǳ������� �ű���� �Ѵ�. �κ��� �ű�� ���������� �Ʒ��� ���� ���� ������� �Ͼ��.

1. ��Ʈ�� �� ĭ ���� �ִ� �κ��� �Բ� �� ĭ ȸ���Ѵ�.
2. ���� ���� ��Ʈ�� �ö� �κ�����, ��Ʈ�� ȸ���ϴ� �������� �� ĭ �̵��� �� �ִٸ� �̵��Ѵ�.
   ���� �̵��� �� ���ٸ� ������ �ִ´�.
	1. �κ��� �̵��ϱ� ���ؼ��� �̵��Ϸ��� ĭ�� �κ��� ������, �� ĭ�� �������� 1 �̻� ���� �־�� �Ѵ�.
3. �ø��� ��ġ�� �ִ� ĭ�� �������� 0�� �ƴϸ� �ø��� ��ġ�� �κ��� �ø���.
4. �������� 0�� ĭ�� ������ K�� �̻��̶�� ������ �����Ѵ�. �׷��� �ʴٸ� 1������ ���ư���.

����Ǿ��� �� �� ��° �ܰ谡 ���� ���̾����� ���غ���. ���� ó�� ����Ǵ� �ܰ�� 1��° �ܰ��̴�.

�Է�
ù° �ٿ� N, K�� �־�����. ��° �ٿ��� A1, A2, ..., A2N�� �־�����.

���
�� ��° �ܰ谡 ���� ���϶� ����Ǿ����� ����Ѵ�.

����
2 �� N �� 100
1 �� K �� 2N
1 �� Ai �� 1,000

N, K, exitFlag, Answer;

struct State { int state, int robot}
deque <int> belt

1. Input()
	N, K, belt�� ������ ����

2. Solution()
	1) while(1)
	2) time++;
	3) move_belt() -> pop_back() & push_front()
	4) move_robot()
		1) Ư�� case  i= N-1�� �κ� ������ �ƿ�
		2) i = N-2 ~ 0���� �ش� idx�� �κ� �ְ�, ���� ĭ�� ������ >= 1 �̸�  �κ� �ű��
		3) Ư�� case -> i = N-2 �κ��� �̵��ϸ� �ٷ� belt[N-1].state = 0;
	5) start_robot()
		1) i = 0�� �κ� ������, �κ� �ø���
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, Answer = 0;

struct BeltInfo {
	int state;
	int robot;
};

deque <BeltInfo> dq;


int move_robot(int exitFlag) {
	if (dq[N - 1].robot == 1) dq[N - 1].robot = 0;

	for (int i = N - 2; i >= 1; i--) {
		if (dq[i].robot == 1 && dq[i+1].robot == 0 && dq[i + 1].state >= 1) {
			dq[i].robot = 0;
			dq[i + 1].state--;
			dq[i + 1].robot = 1;
			if (dq[i + 1].state == 0) exitFlag++;

			if (i == N - 2) dq[i + 1].robot = 0;
		}
	}

	if (dq[0].state > 0) {
		dq[0].robot = 1;
		dq[0].state--;
		if (dq[0].state == 0) exitFlag++;
	}
	return exitFlag;
}

void move_belt() {
	BeltInfo tmp;

	tmp = dq.back();
	dq.pop_back();

	dq.push_front(tmp);
}

void Solution() {
	int time = 0, exitFlag = 0;
	
	while (1) {
		time++;
		move_belt();
		exitFlag = move_robot(exitFlag);

		if (exitFlag >= K) break;
	}
	Answer = time;
	cout << Answer << endl;

}

void Input() {
	int tmp;
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++)	{
		cin >> tmp;
		dq.push_back({ tmp, 0 });
	} 
}

int main(void) {
	Input();
	Solution();
	return 0;
}