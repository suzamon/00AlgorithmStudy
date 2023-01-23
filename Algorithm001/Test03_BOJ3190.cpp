/*
����
 'Dummy' ��� ���������� �ִ�. �� ���ӿ��� ���� ���ͼ� ���ٴϴµ�, ����� ������ �� ���̰� �þ��.
���� �̸����� ���ٴϴٰ� �� �Ǵ� �ڱ��ڽ��� ���� �ε����� ������ ������.

������ NxN ���簢 ���������� ����ǰ�, ��� ĭ���� ����� ������ �ִ�.
������ �����¿� ���� ���� �ִ�. ������ �����Ҷ� ���� ���� �������� ��ġ�ϰ� ���� ���̴� 1 �̴�.
���� ó���� �������� ���Ѵ�.

���� �� �ʸ��� �̵��� �ϴµ� ������ ���� ��Ģ�� ������.

���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�. ��, �����̴� ������ �ʴ´�.
����� ��ġ�� ���� �̵���ΰ� �־��� �� �� ������ �� �ʿ� �������� ����϶�.

�Է�
ù° �ٿ� ������ ũ�� N�� �־�����. (2 �� N �� 100) ���� �ٿ� ����� ���� K�� �־�����. (0 �� K �� 100)

���� K���� �ٿ��� ����� ��ġ�� �־����µ�, ù ��° ������ ��, �� ��° ������ �� ��ġ�� �ǹ��Ѵ�.
����� ��ġ�� ��� �ٸ���, �� �� �� ���� (1�� 1��) ���� ����� ����.

���� �ٿ��� ���� ���� ��ȯ Ƚ�� L �� �־�����. (1 �� L �� 100)

���� L���� �ٿ��� ���� ���� ��ȯ ������ �־����µ�,  ���� X�� ���� C�� �̷���� ������.
���� ���� �ð����κ��� X�ʰ� ���� �ڿ� ����(C�� 'L') �Ǵ� ������(C�� 'D')�� 90�� ������ ȸ����Ų�ٴ� ���̴�.
 X�� 10,000 ������ ���� �����̸�, ���� ��ȯ ������ X�� �����ϴ� ������ �־�����.

���
ù° �ٿ� ������ �� �ʿ� �������� ����Ѵ�.

int N, K, Answer = 0;
int map[101][101]; -> 1: �� �ڸ�, 2: ���
int head[2], tail[2], headDir;
int dx[5], dy[5] -> 1: ��/ 2: ��/ 3: ��/ 4: ��
deque <pair <int, int>> chDir; -> ��, ���� ��ȯ(1: ������ 90��, 2: ���� 90��)
deque <int> tailDir -> �� �Ӹ� �̵� ����(��� ������ �״�� & ��� ������ pop())


Input()
	N, K, map[1][1] = 1, headDir = 1, map�� ���, chDir push
Solution()
	int time =0, exitFlag = 0, rotDir = 0;
	while(1){
	time++;
	exitFlag = move_snake();
	if(exitFlag ==1) {
		Answer = time;
		break;
	}
	if(chDir.size() == 0) continue;
	if(time == chDir.front().first){
	rotDir = chDir.front().second;
	chDir.pop_front();
	change_dir(rotDir);
	}
	}


*int move_snake()
	int sX, sY, nX, nY, dir;
	sX = head[0], sY = head[1];
	nX = sX + dx[headDir], nY = sY + dy[headDir];
	if(!inRange(nX, nY)) return 1;
	else if(map[nX][nY] == 1) return 1;

	head[0] = nX, head[1] = nY;
	tailDir.push_back(headDir);

	if(map[nX][nY]==2) {
		map[nX][nY] = 1;
		continue;
	}
	map[nX][nY] = 1;

	sX = tail[0], sY = tail[1];
	map[sX][sY] = 0;
	dir = tailDir.front();
	tailDir.pop_front();
	tail[0] = sX + dx[dir], tail[1] = sY + dy[dir];

*void change_dir(int rotDir)
	int sDir = headDir;
	if(rotDir ==1){
	headDir = headDir + 1;
	if(headDir ==5) headDir = 1;
	}
	else if(rotDir ==2){
	headDir = headDir - 1;
	if(headDir ==0) headDir = 4;
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

int N, K, L, Answer = 0;
int map[101][101] = { 0, };
int head[2], tail[2], headDir;
int dx[5] = { 0, 0, 1, 0, -1 };
int dy[5] = { 0, 1, 0, -1, 0 };
deque <pair <int, int>> chDir;
deque <int> tailDir;

void print_map(int time) {
	cout << time << "�� �� �� ����" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j<= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int yy) {
	if (xx > 0 && xx <= N && yy > 0 && yy <= N) return true;
	else return false;
}

void change_dir(int rotDir) {
	int sDir = headDir;
	if (rotDir == 1) {
		headDir = headDir + 1;
		if (headDir == 5) headDir = 1;
	}
	else if (rotDir == 2) {
		headDir = headDir - 1;
		if (headDir == 0) headDir = 4;
	}
}

int move_snake() {
	int sX, sY, nX, nY, dir;
	sX = head[0], sY = head[1];
	nX = sX + dx[headDir], nY = sY + dy[headDir];
	if (!inRange(nX, nY)) return 1;
	else if (map[nX][nY] == 1) return 1;

	head[0] = nX, head[1] = nY;
	tailDir.push_back(headDir);

	if (map[nX][nY] == 2) {
		map[nX][nY] = 1;
		return 0;
	}

	map[nX][nY] = 1;
	sX = tail[0], sY = tail[1];
	map[sX][sY] = 0;
	dir = tailDir.front();
	tailDir.pop_front();
	tail[0] = sX + dx[dir], tail[1] = sY + dy[dir];
	return 0;
}

void Solution() {
	int time = 0, exitFlag = 0, rotDir = 0;

	while (1) {
		time++;
		exitFlag = 0;
		exitFlag = move_snake();
		if (exitFlag == 1) {
			Answer = time;
			break;
		}
		if (chDir.size() == 0) continue;

		if (chDir.front().first == time) {
			rotDir = chDir.front().second;
			chDir.pop_front();
			change_dir(rotDir);
		}
		//print_map(time);
	}

}

void Input() {
	int tmpX, tmpY;
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> tmpX >> tmpY;
		map[tmpX][tmpY] = 2;
	}

	head[0] = 1, head[1] = 1, headDir = 1;
	tail[0] = 1, tail[1] = 1;
	map[1][1] = 1;

	int time;
	char d;
	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> time;
		cin >> d;
		if (d == 'D') {
			chDir.push_back(make_pair(time, 1));
		}
		else if (d == 'L') {
			chDir.push_back(make_pair(time, 2));
		}
	}
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}