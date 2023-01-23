/*
0'49''50'''
������ ���� ���̾, ����̵�, ���̾��, ��������� ������ �� �� �ִ�. ���� ���� ��� ������ ��ٶ���̴�.
��ٶ�⸦ �����ϸ� �ϴÿ� �񱸸��� ���� �� �ִ�. ������ ��ٶ�⸦ ũ�Ⱑ N��N�� ���ڿ��� �����Ϸ��� �Ѵ�.
������ �� ĭ���� �ٱ��ϰ� �ϳ� �ְ�, �ٱ��ϴ� ĭ ��ü�� �����Ѵ�. �ٱ��Ͽ� ������ �� �ִ� ���� �翡�� ������ ����.
(r, c)�� ������ r�� c���� �ִ� �ٱ��ϸ� �ǹ��ϰ�, A[r][c]�� (r, c)�� �ִ� �ٱ��Ͽ� ����Ǿ� �ִ� ���� ���� �ǹ��Ѵ�.

������ ���� ���� �� ĭ�� (1, 1)�̰�, ���� ������ �Ʒ� ĭ�� (N, N)�̴�.
������ ���� ������ ���� 1�� ��� N�� ���� �����߰�, 1�� ���� N�� ���� �����ߴ�.
��, N�� ���� �Ʒ����� 1�� ����, 1�� ���� ������ N�� ���� �ְ�,
1�� ���� ���ʿ��� N�� ����, N�� ���� �����ʿ��� 1�� ���� �ִ�.

��ٶ�⸦ �����ϸ� (N, 1), (N, 2), (N-1, 1), (N-1, 2)�� �񱸸��� �����. ������ ĭ ��ü�� �����Ѵ�.
���� ������ �̵��� M�� ����Ϸ��� �Ѵ�. i��° �̵� ����� ���� di�� �Ÿ� si�� �̷���� �ִ�.
������ �� 8���� ������ ������, 8���� ������ ǥ���Ѵ�. 1���� ������� ��, ��, ��, ��, ��, ��, ��, �� �̴�.
�̵��� ����ϸ� ������ ������� ����ȴ�.

1. ��� ������ di �������� siĭ �̵��Ѵ�.
2. �� �������� �� ���� ������ �ִ� ĭ�� �ٱ��Ͽ� ����� ���� ���� 1 �����Ѵ�.
3. ������ ��� �������.
4. 2���� ���� ������ ĭ (r, c)�� ��������� ������ �����Ѵ�. ��������� ������ ����ϸ�,
   �밢�� �������� �Ÿ��� 1�� ĭ�� ���� �ִ� �ٱ����� ����ŭ (r, c)�� �ִ� �ٱ����� ���� ���� �����Ѵ�.
	- �̶��� �̵��� �ٸ��� ��踦 �Ѿ�� ĭ�� �밢�� �������� �Ÿ��� 1�� ĭ�� �ƴϴ�.
	- ���� ���, (N, 2)���� ������ �밢�� ĭ�� (N-1, 1), (N-1, 3)�̰�, (N, N)���� ������ �밢�� ĭ�� (N-1, N-1)���̴�.
5 �ٱ��Ͽ� ����� ���� ���� 2 �̻��� ��� ĭ�� ������ �����, ���� ���� 2 �پ���.
   �̶� ������ ����� ĭ�� 3���� ������ ����� ĭ�� �ƴϾ�� �Ѵ�.

M���� �̵��� ��� ���� �� �ٱ��Ͽ� ����ִ� ���� ���� ���� ���غ���.

�Է�
ù° �ٿ� N, M�� �־�����.
��° �ٺ��� N���� �ٿ��� N���� ������ �־�����. r��° ���� c��° ������ A[r][c]�� �ǹ��Ѵ�.
���� M���� �ٿ��� �̵��� ���� di, si�� ������� �� �ٿ� �ϳ��� �־�����.

���
ù° �ٿ� M���� �̵��� ��� ���� �� �ٱ��Ͽ� ����ִ� ���� ���� ���� ����Ѵ�.

����
2 �� N �� 50
1 �� M �� 100
0 �� A[r][c] �� 100
1 �� di �� 8
1 �� si �� 50

N, M, map[101][101], command[101][2]
struct Cloud{ int x, int y}
struct IncreaseCloud{ int x, int y, int cnt}
deque <Cloud> dc
deque <Cloud> removeDc;
int dx[9], dy[9] ( 1���� ������� ��, ��, ��, ��, ��, ��, ��, �� �̴�. )

1. Input()
	N, M, map[N][M], command[M][2]

2. Solution()
	1) (N, 1), (N, 2), (N-1, 1), (N-1, 2)�� �񱸸� �߰�
	2) for(time=1; time <M; time++)
	3) move_cloud(int d, int s) -> sX, sY, nX, nY
		1) for(int i=0; i<dc.size();i++)
		2) sX = dc[i].x, sY = dc[i].y;
		3) nX = sX + dx[d] * s, nY = sY + dx[d] * s;
		4) if(nX >N){ while(1) {nX = nX -N; if(nX <= N && nX >0) break;}}
		5) else if(nX < 1) { while(1) {nX = nX +N; if(nX <= N && nX >0) break;}}
		6) if(nY >N){ while(1) (nY = nY - N; if((nY <=N && (nY >0) break;}}
		7) else if(nY < 1){ while(1) (nY = nY + N; if((nY <=N && (nY >0) break;}}
		8) dc[i].x= nX, dc[i].y =nY;
	4) inc_water()
		1) int tmpSize = dc.size(), Cloud tmpC;
		2) for(int i=0; i<tmpSize;i++)
		3) tmpC = dc.front(); dc.pop_front();
		4) map[tmpC.x][tmpC.y]++;
		5) visited[tmpC.x][tmpC.y] = 1;
		6) removeDc.push_back(tmpC);
	5) magic_water() -> sX, sY, nX, nY, tmpCnt, deque <IncreaseCloud> dq;
		1) for(int i=0; i<removeDc.size();i++){
		2) tmpCnt = 0;
		2) sX = removeDc[i].x, sY = removeDc[i].y
		3) for(int d=2; d<=8; d+=2) {
		4)  nX = sX + dx[d], nY = sY + dx[d];
		5) if(!inRange(nX, nY)) continue;
		6) if(map[nX][nY] > 0) tmpCnt++;
		7) }
		8) dq.push_back({sX, sY, tmpCnt});
		9)}
		10) while(!dq.empty()) map[dq.front().x][dq.front().y] = map[dq.front().x][dq.front().y] + dq.front().cnt;
		11) dq.pop_front()
	6) make_cloud()
		1) for(int xx=1; xx<=N; xx++) for(int yy=1; yy<=N; yy++)
		2) if(map[xx][yy]>=2 && visited[xx][yy] ==0) dc.push_back({xx, yy}), visited[xx][yy] =1, map[xx][yy] -=2;
		3) while(!removeDc.empty()) visited[removeD.front().x][removeD.front().y] = 0 && removeD.pop_fronr()
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, Answer = 0;
int map[51][51], visited[51][51] = { 0, }, command[101][2];

struct Cloud {
	int x, y;
	Cloud(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct IncCloud {
	int x, y, cnt;
	IncCloud(int x, int y, int cnt) {
		this->x = x;
		this->y = y;
		this->cnt = cnt;
	}
};

deque <Cloud> dc;
deque <Cloud> removeDc;

int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

bool inRange(int xx, int yy) {
	if (xx<1 || xx>N || yy<1 || yy>N) return false;
	return true;
}

void print_info() {
	cout << "����ִ� ����" << endl;
	if (dc.size() > 0) {
		for (int i = 0; i < dc.size(); i++) {
			cout << '(' << dc[i].x << ", " << dc[i].y << ")�� ���� ����" << endl;
		}
	}
	else {
		cout << "����" << endl;
	}

	cout << "����� ����" << endl;
	if (removeDc.size() > 0) {
		for (int i = 0; i < removeDc.size(); i++) {
			cout << '(' << removeDc[i].x << ", " << removeDc[i].y << ")�� ����� ���� ����" << endl;
		}
	}
	else {
		cout << "����" << endl;
	}

	cout << "�� ����" << endl;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			cout << map[xx][yy] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	Answer = 0;
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] >= 1) Answer = Answer + map[xx][yy];
		}
	}
	cout << Answer << endl;
}

void make_cloud() {
	for (int xx = 1; xx <= N; xx++) {
		for (int yy = 1; yy <= N; yy++) {
			if (map[xx][yy] >= 2 && visited[xx][yy] == 0) {
				dc.push_back({ xx, yy });
				map[xx][yy] = map[xx][yy] - 2;
			}
		}
	}

	while (!removeDc.empty()) {
		visited[removeDc.front().x][removeDc.front().y] = 0;
		removeDc.pop_front();
	}
}

void magic_water() {
	int sX, sY, nX, nY, tmpCnt;

	deque <IncCloud> dq;
	for (int i = 0; i < removeDc.size(); i++) {
		tmpCnt = 0;
		sX = removeDc[i].x, sY = removeDc[i].y;
		for (int d = 2; d <= 8; d += 2) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY)) continue;

			if (map[nX][nY] > 0) tmpCnt++;
		}
		dq.push_back({ sX, sY, tmpCnt});
	}

	while (!dq.empty()) {
		map[dq.front().x][dq.front().y] = map[dq.front().x][dq.front().y] + dq.front().cnt;
		dq.pop_front();
	}
}

void inc_water() {
	int tmpSize = dc.size();
	Cloud tmpC = { 0, 0 };

	for (int i = 0; i < tmpSize; i++) {
		tmpC = dc.front(); 
		dc.pop_front();
		map[tmpC.x][tmpC.y]++;
		visited[tmpC.x][tmpC.y] = 1;
		removeDc.push_back(tmpC);
	}
}

void move_cloud(int d, int s) {
	int sX, sY, nX, nY;

	for (int i = 0; i < dc.size(); i++) {
		sX = dc[i].x, sY = dc[i].y;
		nX = sX + dx[d] * s, nY = sY + dy[d] * s;

		if (nX > N) { 
			while (1) { 
				nX = nX - N; 
				if (nX <= N && nX > 0) break; 
			} 
		}
		else if (nX < 1) {
			while (1) {
				nX = nX + N;
				if (nX <= N && nX > 0) break; 
			} 
		}

		if (nY > N) {
			while (1) {
				nY = nY - N;
				if (nY <= N && nY > 0) break;
			}
		}
		else if (nY < 1) {
			while (1) {
				nY = nY + N;
				if (nY <= N && nY > 0) break;
			}
		}

		dc[i].x = nX, dc[i].y = nY;
	}
}

void Solution() {
	int time;
	for (time = 0; time < M; time++) {
		move_cloud(command[time][0], command[time][1]);
		//print_info();
		inc_water();
		//print_info();
		magic_water();
		//print_info();
		make_cloud();
		//print_info();
	}

	find_answer();
}

void Input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> command[i][0] >> command[i][1];
	}

	dc.push_back({ N, 1 });
	dc.push_back({ N, 2 });
	dc.push_back({ N-1, 1 });
	dc.push_back({ N-1, 2 });
}

int main(void) {
	Input();
	Solution();
	return 0;
}