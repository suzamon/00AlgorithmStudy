/*
������ NxN ���簢 ���������� ����ǰ�, ��� ĭ���� ����� ������ �ִ�. ������ �����¿� ���� ���� �ִ�.
������ �����Ҷ� ���� ���� �������� ��ġ�ϰ� ���� ���̴� 1 �̴�. ���� ó���� �������� ���Ѵ�.
���� �̸����� ���ٴϴٰ� �� �Ǵ� �ڱ��ڽ��� ���� �ε����� ������ ������.

���� �� �ʸ��� �̵�
1. ���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
2. ���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
3. ���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�. ��, �����̴� ������ �ʴ´�.

����� ��ġ�� ���� �̵���ΰ� �־��� �� �� ������ �� �ʿ� �������� ���

ù° �ٿ� ������ ũ�� N�� �־�����. (2 �� N �� 100) ���� �ٿ� ����� ���� K�� �־�����. (0 �� K �� 100)

���� K���� �ٿ��� ����� ��ġ�� �־����µ�, ù ��° ������ ��, �� ��° ������ �� ��ġ�� �ǹ��Ѵ�. ����� ��ġ�� ��� �ٸ���, �� �� �� ���� (1�� 1��) ���� ����� ����.

���� �ٿ��� ���� ���� ��ȯ Ƚ�� L �� �־�����. (1 �� L �� 100)

���� L���� �ٿ��� ���� ���� ��ȯ ������ �־����µ�,  ���� X�� ���� C�� �̷���� ������.
���� ���� �ð����κ��� X�ʰ� ���� �ڿ� ����(C�� 'L') �Ǵ� ������(C�� 'D')�� 90�� ������ ȸ����Ų�ٴ� ���̴�.
X�� 10,000 ������ ���� �����̸�, ���� ��ȯ ������ X�� �����ϴ� ������ �־�����.


tail[4] -> x, y, ���� ����, ��������idx
head[4] -> x, y, ���� ����, ��������idx

1. Input()
	N, K
	��� ��ġ
	L
	���� ����(�ð�, D)
	changeHeadDir[L][2] -> ��Ӹ� ���� �̵� [1] = 0�̸� L, [1]=1�̸� R
	changeTailDir[L][2] -> �첿�� ���� �̵� [1] = 0�̸� L, [1]=1�̸� R

2. Simualtion()
	1-1) (idx = L�̸� ����)�Ӹ� ���� �̵� �ð��̸� �Ӹ� ���� ����, �Ӹ� ���� ���� idx++
	1-2) (idx = L�̸� ����) ���� ���� �̵� �ð��̸� ���� ���� ����, ���� ���� ���� idx++
	2) �Ӹ� �̵� -> ���� �ְų� Ȥ�� ���� ����� ���� ����
	3-1) ��� ������ ���� ���� �������� �̵�
	3-2) ��� ������ ���� �״�� & ���� ���� idx ~ L ���� ���� ���� �ð� + 1 ����


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, L, Answer = 0;
int map[101][101];
int changeHeadDir[101][2];
int changeTailDir[101][2];

int dx[4] = { 0, 1, 0, -1 }; // ��, ��, ��, ��
int dy[4] = { 1, 0, -1, 0 };

int head[4], tail[4];

void print_map(int t) {
	cout << t << "�� ��" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int change_dir(int curDir, int rot) {
	int nextDir;
	if (rot == 0) {
		nextDir = curDir - 1;
		if (nextDir < 0) nextDir = 3;
	}
	else {
		nextDir = curDir + 1;
		if (nextDir > 3) nextDir = 0;
	}
	return nextDir;
}

void Simulation() {
	int t;
	head[0] = 1;
	head[1] = 1;
	head[2] = 0;
	head[3] = 0;

	tail[0] = 1;
	tail[1] = 1;
	tail[2] = 0;
	tail[3] = 0;

	t = 1;

	while (1) {
		
		if (head[3] != L && t == changeHeadDir[head[3]][0]) {
			head[2] = change_dir(head[2], changeHeadDir[head[3]][1]);
			head[3]++;
		}
		if (tail[3] != L && t == changeTailDir[tail[3]][0]) {
			tail[2] = change_dir(tail[2], changeTailDir[tail[3]][1]);
			tail[3]++;
		}

		head[0] = head[0] + dx[head[2]];
		head[1] = head[1] + dy[head[2]];

		if (head[0] == 0 || head[0] == N+1 || head[1] == 0 || head[1] == N+1 || map[head[0]][head[1]] == 2) {
			Answer = t;
			break;
		}

		if (map[head[0]][head[1]] == 1) {
			map[head[0]][head[1]] = 2;
			for (int i = tail[3]; i < L; i++) {
				changeTailDir[i][0]++;
			}
		}
		else {
			map[head[0]][head[1]] = 2;
			map[tail[0]][tail[1]] = 0;
			tail[0] = tail[0] + dx[tail[2]];
			tail[1] = tail[1] + dy[tail[2]];
		}

		//print_map(t);

		t++;
	}
}

void Input() {
	int r, c, t;
	char dir;
	cin >> N >> K;
	map[1][1] = 2;//���� 2

	for (int i = 0; i < K; i++) {
		cin >> r >> c;
		map[r][c] = 1;//����� 1
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> t >> dir;
		changeHeadDir[i][0] = t + 1;
		changeTailDir[i][0] = t + 1;
		if (dir == 'L') {
			changeHeadDir[i][1] = 0;
			changeTailDir[i][1] = 0;
		}
		else {
			changeHeadDir[i][1] = 1;
			changeTailDir[i][1] = 1;
		}
	}
}

int main(void) {
	Input();
	Simulation();

	cout << Answer << endl;
	return 0;
}