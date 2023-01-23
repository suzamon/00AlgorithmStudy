/*
����
ũ�Ⱑ N��M�� ������ �����Ѵ�. ������ �������� ����, ������ �����̴�.
�� ������ ���� �ֻ����� �ϳ� ������ ������, �ֻ����� �������� �Ʒ��� ����.
 ������ ��ǥ�� (r, c)�� ��Ÿ����, r�� �������κ��� ������ ĭ�� ����, c�� �������κ��� ������ ĭ�� �����̴�.

�ֻ����� ���� ���� �� ���� 1�̰�, ������ �ٶ󺸴� ������ 3�� ���·� ������ ������,
������ �ִ� ���� ��ǥ�� (x, y) �̴�. ���� ó���� �ֻ������� ��� �鿡 0�� ������ �ִ�.

������ �� ĭ���� ������ �ϳ��� ������ �ִ�.
�ֻ����� ������ ��, �̵��� ĭ�� ���� �ִ� ���� 0�̸�, �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����ȴ�.
0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�, ĭ�� ���� �ִ� ���� 0�� �ȴ�.

�ֻ����� ���� ���� ��ǥ�� �̵���Ű�� ����� �־����� ��,
�ֻ����� �̵����� �� ���� ��ܿ� ���� �ִ� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�ֻ����� ������ �ٱ����� �̵���ų �� ����.
���� �ٱ����� �̵���Ű���� �ϴ� ��쿡�� �ش� ����� �����ؾ� �ϸ�, ��µ� �ϸ� �� �ȴ�.

�Է�
ù° �ٿ� ������ ���� ũ�� N, ���� ũ�� M (1 �� N, M �� 20),
�ֻ����� ���� ���� ��ǥ x, y(0 �� x �� N-1, 0 �� y �� M-1), �׸��� ����� ���� K (1 �� K �� 1,000)�� �־�����.

��° �ٺ��� N���� �ٿ� ������ ���� �ִ� ���� ���ʺ��� ��������, �� ���� ���ʺ��� ���� ������� �־�����.
�ֻ����� ���� ĭ�� ���� �ִ� ���� �׻� 0�̴�. ������ �� ĭ�� ���� �ִ� ���� 10 �̸��� �ڿ��� �Ǵ� 0�̴�.

������ �ٿ��� �̵��ϴ� ����� ������� �־�����. ������ 1, ������ 2, ������ 3, ������ 4�� �־�����.

���
�̵��� ������ �ֻ����� �� �鿡 ���� �ִ� ���� ����Ѵ�.
���� �ٱ����� �̵���Ű���� �ϴ� ��쿡�� �ش� ����� �����ؾ� �ϸ�, ��µ� �ϸ� �� �ȴ�.


N, M, K,
map[21][21], dicePos[2];
int diceMap[4][3];
deque <int> com;

int dx[5], dy[5] -> ������ 1, ������ 2, ������ 3, ������ 4

1. Input()
	N, M, dicePos[2], K, map[N][M], com

2. Solution()
	int dir;
	while(!com.empty()){
	dir = com.front(), com.pop_front();
	move_dice(dir)
	print_dice_up()
	}

* void move_dice(dir)
	int nX, nY;
	nX = dicePos[0] + dx[dir];
	nY = dicePos[1] + dy[dir];
	if(!inRange(nX, nY)) return;
	change_diceMap(dir);
	int tmp;
	if(map[nX][nY] == 	0) {
	map[nX][nY] = diceMap[1][1];
	return;
	}
	diceMap[1][1] = map[nX][nY];
	map[nX][nY] = 0;
	return;

*void change_diceMap(int dir)
	deque <int> tmp;
	switch(dir){
	case 1:
		for(int i=1; i<=2; i++) tmp.push_back(diceMap[1][i])
		tmp.push_back(diceMap[3][1])
		tmp.push_back(diceMap[1][0]);
		for(int i=0; i<=2; i++) {
		diceMap[1][i] = tmp.front();
		tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 2:
		tmp.push_back(diceMap[3][1])
		for(int i=0; i<=2; i++) tmp.push_back(diceMap[1][i])
		for(int i=0; i<=2; i++) {
		diceMap[1][i] = tmp.front();
		tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 3:
		tmp.push_back(diceMap[3][1]);
		for(int i=0; i<=2; i++) tmp.push_back(diceMap[i][1]);
		for(int i=0; i<=3; i++){
		diceMap[i][1] = tmp.front();
		tmp.pop_front();
		}
		break;
	case 4:
		for(int i=1; i<=3; i++) tmp.push_back(diceMap[i][1]);
		tmp.push_back(diceMap[0][1]);
		for(int i=0; i<=3; i++){
		diceMap[i][1] = tmp.front();
		tmp.pop_front();
		}
		break;
	}
	return;
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, K, Answer = 0;
int map[21][21], dicePos[2];
int diceMap[4][3] = { 0, };

deque <int> com;

int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };

void change_diceMap(int dir){
	deque <int> tmp;
	switch (dir) {
	case 1:
		for (int i = 1; i <= 2; i++) tmp.push_back(diceMap[1][i]);
		tmp.push_back(diceMap[3][1]);
		tmp.push_back(diceMap[1][0]);
		for (int i = 0; i <= 2; i++) {
			diceMap[1][i] = tmp.front();
			tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 2:
		tmp.push_back(diceMap[3][1]);
		for (int i = 0; i <= 2; i++) tmp.push_back(diceMap[1][i]);
		for (int i = 0; i <= 2; i++) {
			diceMap[1][i] = tmp.front();
			tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 3:
		tmp.push_back(diceMap[3][1]);
		for (int i = 0; i <= 2; i++) tmp.push_back(diceMap[i][1]);
		for (int i = 0; i <= 3; i++) {
			diceMap[i][1] = tmp.front();
			tmp.pop_front();
		}
		break;
	case 4:
		for (int i = 1; i <= 3; i++) tmp.push_back(diceMap[i][1]);
		tmp.push_back(diceMap[0][1]);
		for (int i = 0; i <= 3; i++) {
			diceMap[i][1] = tmp.front();
			tmp.pop_front();
		}
		break;
	}
	return;

}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy < M) return true;
	return false;
}

int move_dice(int dir) {
	int nX, nY;
	nX = dicePos[0] + dx[dir];
	nY = dicePos[1] + dy[dir];
	if (!inRange(nX, nY)) return 1;
	dicePos[0] = nX, dicePos[1] = nY;
	change_diceMap(dir);
	int tmp;
	if (map[nX][nY] == 0) {
		map[nX][nY] = diceMap[1][1];
	}
	else {
		diceMap[1][1] = map[nX][nY];
		map[nX][nY] = 0;
	}
	return 0;

}

void print_dice_up() {
	cout << diceMap[3][1] << endl;
}

void Solution() {
	int dir, flag = 0;
	while (!com.empty()) {
		dir = com.front(), com.pop_front();
		flag = move_dice(dir);
		if (flag == 0) print_dice_up();
	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < 2; i++) {
		cin >> dicePos[i];
	}
	cin >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int tmp;
	for (int i = 0; i < K; i++) {
		cin >> tmp;
		com.push_back(tmp);
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}