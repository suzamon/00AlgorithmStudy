/*
�Ʊ� �� ������ û�ҳ� �� �Ǿ���.

4��4ũ���� ������ �ְ�, ũ�Ⱑ 1��1�� ���簢�� ĭ���� �������� �ִ�. ������ �� ĭ�� (x, y)�� ���� ǥ���ϸ�,
x�� ���� ��ȣ, y�� ���� ��ȣ�̴�. �� ĭ���� ����Ⱑ �� ���� �����Ѵ�. �� ������ ��ȣ�� ������ ������ �ִ�.
��ȣ�� 1���� ũ�ų� ����, 16���� �۰ų� ���� �ڿ����̸�, �� ����Ⱑ ���� ��ȣ�� ���� ���� ����.
������ 8���� ����(�����¿�, �밢��) �� �ϳ��̴�.

������ û�ҳ� �� �� ������ �� ����⸦ �������� �Ѵ�. û�ҳ� ���� (0, 0)�� �ִ� ����⸦ �԰�,
(0, 0)�� ���� �ȴ�. ����� ������ (0, 0)�� �ִ� ������� ����� ����. ���� ����Ⱑ �̵��Ѵ�.

������ ��ȣ�� ���� �������� ������� �̵��Ѵ�. ������ �� ĭ�� �̵��� �� �ְ�,
�̵��� �� �ִ� ĭ�� �� ĭ�� �ٸ� ����Ⱑ �ִ� ĭ, �̵��� �� ���� ĭ�� �� �ְų�, ������ ��踦 �Ѵ� ĭ�̴�.
�� ������ ������ �̵��� �� �ִ� ĭ�� ���� ������ ������ 45�� �ݽð� ȸ����Ų��.
����, �̵��� �� �ִ� ĭ�� ������ �̵��� ���� �ʴ´�. �� ���� ��쿡�� �� ĭ���� �̵��� �Ѵ�.
����Ⱑ �ٸ� ����Ⱑ �ִ� ĭ���� �̵��� ���� ������ ��ġ�� �ٲٴ� ������� �̵��Ѵ�.

������� �̵��� ��� ������ �� �̵��Ѵ�. ���� ���⿡ �ִ� ĭ���� �̵��� �� �ִµ�,
�� ���� ���� ���� ĭ�� �̵��� �� �ִ�. �� ����Ⱑ �ִ� ĭ���� �̵��ߴٸ�, �� ĭ�� �ִ� ����⸦ �԰�,
�� ������� ������ ������ �ȴ�. �̵��ϴ� �߿� �������� ĭ�� �ִ� ������ ���� �ʴ´�.
����Ⱑ ���� ĭ���δ� �̵��� �� ����. �� �̵��� �� �ִ� ĭ�� ������ �������� ��� ������ ����.
�� �̵��� �Ŀ��� �ٽ� ����Ⱑ �̵��ϸ�, ���� �� ������ ����ؼ� �ݺ��ȴ�.

�� ���� �� �ִ� ����� ��ȣ�� ���� �ִ��� ���غ���.


�Է�
ù° �ٺ��� 4���� �ٿ� �� ĭ�� ����ִ� ������� ������ 1�� ����� ������� �־�����.
������� ������ �� ���� ai, bi�� �̷���� �ְ�, ai�� ������� ��ȣ, bi�� ������ �ǹ��Ѵ�.
���� bi�� 8���� �۰ų� ���� �ڿ����� �ǹ��ϰ�, 1���� ������� ��, ��, ��, ��, ��, ��, ��, �� �� �ǹ��Ѵ�.

���
�� ���� �� �ִ� ����� ��ȣ�� ���� �ִ��� ����Ѵ�.

Answer =0, shark[3], map[4][4], fish[17][4], -> ����, x, y, dir

1. Input()
	fish[4]�� ���� ������Ʈ(�ʱ� ����: 0, ������: 1), map�� ����� ��ȣ ������Ʈ
2. Solution()
	1) shark -> 0,0�� �ִ� ����� ���� & map[0][0]�� -1�� ǥ�� & Answer = Answer + map[0][0]
	2) move_fish() -> 1�� ���� 16�� ���� ����� �̵� �ùķ��̼�
		1) for(int idx=1; idx<17; idx++)
		2) fish[idx][0] == 1, continue;
		3) ���� ���� �ƴϸ� �̵� -> nX = x + dx[dir] & nY = y + dy[dir]
		4) �� ����ų� ��� ������ dir ���� => dir = change_dir(dir) -> 8�� �ݺ��ϸ� X
		5) if(map[nX][nY] == 0)�̸� �ٷ� fish�� ������Ʈ & map ������Ʈ
		6) else if(map[nX][nY] != 0)�̸�, �ش� ��ġ�� �ִ� ������ ��ġ ���� & map ������Ʈ
	3) move_shark(int sum)
		1) ������ position ���� -> posArr[4][2]�� ����
		2) �� posArr��ŭ DFS ����
		3) ���� �� �� �ִ� �� ������ return
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = 0;
int shark[3] = { 0, }, map[4][4] = { 0, }, fish[17][4] = { 0, };
int dx[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[9] = { 0, 0, -1, -1,-1, 0, 1 ,1, 1 };

void print_map() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int change_dir(int dir) {
	int nDir = dir + 1;
	if (nDir == 9) nDir = 1;
	return nDir;
}

void move_fish() {
	int idx, x, y, dir, nX, nY, nDir, idx2, cnt;
	
	for (idx = 1; idx < 17; idx++) {
		if (fish[idx][0] == 1) continue;
		x = fish[idx][1], y = fish[idx][2], dir = fish[idx][3];
		cnt = 0, nDir = dir;
		while (1) {
			if (cnt == 8) break;

			cnt++;
			nX = x + dx[nDir];
			nY = y + dy[nDir];
			if (nX < 0 || nX >= 4 || nY < 0 || nY >= 4 || map[nX][nY] == -1) {
				nDir = change_dir(nDir);
				continue;
			}

			if (map[nX][nY] == 0) {
				map[x][y] = 0;
				map[nX][nY] = idx;
				fish[idx][1] = nX, fish[idx][2] = nY, fish[idx][3] = nDir;
				break;
			}
			else {
				idx2 = map[nX][nY];

				map[x][y] = idx2;
				fish[idx2][1] = x, fish[idx2][2] = y;

				map[nX][nY] = idx;
				fish[idx][1] = nX, fish[idx][2] = nY, fish[idx][3] = nDir;
				break;
			}
		}
	}
}

void move_shark(int sum) {
	int x, y, dir, nX, nY, posCnt = 0;
	int pos[4][2] = { 0, };

	x = shark[0], y = shark[1], dir = shark[2];
	nX = x, nY = y;
	posCnt = 0;

	for (int i = 0; i < 4; i++) {
		nX = nX + dx[dir];
		nY = nY + dy[dir];

		if (nX < 0 || nX >= 4 || nY < 0 || nY >= 4) break;
		else if(map[nX][nY] == 0) continue;
		
		pos[posCnt][0] = nX;
		pos[posCnt][1] = nY;
		posCnt++;
	}

	if (posCnt == 0) {
		if (sum > Answer) Answer = sum;
		return;
	}

	int fishIdx = 0;
	if (posCnt == 1) {
		nX = pos[0][0];
		nY = pos[0][1];

		map[x][y] = 0;

		fishIdx = map[nX][nY];
		fish[fishIdx][0] = 1;

		map[nX][nY] = -1;
		shark[0] = nX;
		shark[1] = nY;
		shark[2] = fish[fishIdx][3];

		move_fish();

		move_shark(sum + fishIdx);
	}
	else {
		int copyMap[4][4], copyFish[17][4];

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				copyMap[i][j] = map[i][j];
			}
		}
		for (int i = 1; i < 17; i++) {
			for (int j = 0; j < 4; j++) {
				copyFish[i][j] = fish[i][j];
			}
		}

		for (int i = 0; i < posCnt; i++) {
			nX = pos[i][0];
			nY = pos[i][1];

			map[x][y] = 0;

			fishIdx = map[nX][nY];
			fish[fishIdx][0] = 1;

			map[nX][nY] = -1;
			shark[0] = nX;
			shark[1] = nY;
			shark[2] = fish[fishIdx][3];

			move_fish();
			move_shark(sum + fishIdx);
			
			
			map[x][y] = -1;
			fish[fishIdx][0] = 0;
			map[nX][nY] = fishIdx;
			shark[0] = x;
			shark[1] = y;
			shark[2] = dir;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					map[i][j] = copyMap[i][j];
				}
			}
			for (int i = 1; i < 17; i++) {
				for (int j = 0; j < 4; j++) {
					fish[i][j] = copyFish[i][j];
				}
			}
		}

	}
}

void Solution() {
	int idx = map[0][0];
	Answer = Answer + idx;
	shark[0] = 0, shark[1] = 0;
	shark[2] = fish[idx][3];
	fish[idx][0] = 1;
	map[0][0] = -1;

	move_fish();
	move_shark(Answer);
	cout << Answer << endl;
}

void Input() {
	int idx;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> idx;
			fish[idx][0] = 0;
			fish[idx][1] = i;
			fish[idx][2] = j;
			cin >> fish[idx][3];
			map[i][j] = idx;
		}
	}
}

int main(void) {
	Input();
	Solution();

	return 0;
}