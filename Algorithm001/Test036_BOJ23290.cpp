/*
2'50''25'''

������ ���� ���̾, ����̵�, ���̾��, ���������, ��ٶ��, ���ڵ� ������ �� �� �ִ�.
������ ������ ��� ��������� ������ ���� ������ ������ �����, 4 �� 4 ũ���� ���ڿ��� �����Ϸ��� �Ѵ�.
(r, c)�� ������ r�� c���� �ǹ��Ѵ�. ������ ���� ���� �� ĭ�� (1, 1)�̰�, ���� ������ �Ʒ� ĭ�� (4, 4)�̴�.

���ڿ��� ����� M������ �ִ�. �� ������ ������ ĭ �ϳ��� �� ������, �̵� ������ ������ �ִ�.
�̵� ������ 8���� ����(�����¿�, �밢��) �� �ϳ��̴�. ������ �� ������ ���� ���ڿ� ���ִ�.
�� ������ �� ĭ�� ���ִ�. �� �̻��� ����Ⱑ ���� ĭ�� ���� ���� ������,
������ ���� ����Ⱑ ���� ĭ�� ���� ���� �ִ�.

����� ���� ���� �� ���� ������ ���� �۾��� ���������� �̷������.

1. �� ��� ����⿡�� ���� ������ �����Ѵ�. ���� ������ �ð��� ���� �ɸ��� ������,
   �Ʒ� 5������ ����Ⱑ �����Ǿ� ĭ�� ��Ÿ����.
2. ��� ����Ⱑ �� ĭ �̵��Ѵ�. �� �ִ� ĭ, ������� ������ �ִ� ĭ, ������ ������ ����� ĭ���δ� �̵��� �� ����.
   �� ������ �ڽ��� ������ �ִ� �̵� ������ �̵��� �� �ִ� ĭ�� ���� ������ ������ 45�� �ݽð� ȸ����Ų��.
   ����, �̵��� �� �ִ� ĭ�� ������ �̵��� ���� �ʴ´�. �� ���� ��쿡�� �� ĭ���� �̵��� �Ѵ�.
   ������� ������ �Ʒ� 3���� �����Ѵ�.
3. �� �����ؼ� 3ĭ �̵��Ѵ�. ���� ���� ĭ���� �����¿�� ������ ĭ���� �̵��� �� �ִ�.
   �����ؼ� �̵��ϴ� ĭ �߿� ������ ������ ����� ĭ�� ������, �� ����� �Ұ����� �̵� ����̴�.
   �����ؼ� �̵��ϴ� �߿� �� ����Ⱑ �ִ� ���� ĭ���� �̵��ϰ� �ȴٸ�, �� ĭ�� �ִ� ��� ������ ���ڿ��� ���ܵǸ�,
   ���ܵǴ� ��� ������ ����� ������ �����.
   ������ �̵� ��� �߿��� ���ܵǴ� ������� ���� ���� ���� ������� �̵��ϸ�,
   �׷��� ����� ���������� ��� ���� ������ ���� �ռ��� ����� �̿��Ѵ�. ���� ���� ���� ������ �ϴ� ��Ʈ�� �ִ�.
4. �� �� �� �������� ���� ������� ������ ���ڿ��� �������.
5. 1���� ����� ���� ������ �Ϸ�ȴ�. ��� ������ ������ 1������ ��ġ�� ������ �״�� ���� �ȴ�.

���ڿ� �ִ� ������� ��ġ, ���� ������ ����� ��ġ, �׸��� ���� Ƚ�� S�� �־�����.
S�� ������ ��� ��������, ���ڿ� �ִ� ������� ���� ���غ���.

�Է�
ù° �ٿ� ������� �� M, �� ������ ������ Ƚ�� S�� �־�����.
��° �ٺ��� M���� �ٿ��� ������� ���� fx, fy, d�� �־�����. (fx, fy)�� ������� ��ġ�� �ǹ��ϰ�, d�� ������ �ǹ��Ѵ�.
������ 8 ������ �ڿ����� ǥ���ϰ�, 1���� ������� ��, ��, ��, ��, ��, ��, ��, �� �̴�.
������ �ٿ��� sx, sy�� �־�����, �� (sx, sy)�� ������ �ǹ��Ѵ�.
���� ���� �ִ� ������� ���� �׻� 1,000,000 ������ �Է¸� �־�����.

���
S���� ������ ��ģ �� ���ڿ� �ִ� ������� ���� ����Ѵ�.

����
1 �� M �� 10
1 �� S �� 100
1 �� fx, fy, sx, sy �� 4
1 �� d �� 8
�� ����� �Ǵ� ������ �� ���� ĭ�� ���� ���� �ִ�.

M, S,
struct Fish{int x,y,dir, state}
deque <Fish> fish;
deque <Fish> addFish;
deque <int> map[5][5]

struct Nextpos{
	int dirArr[3], fishCnt;
}


int shark[2], scent[5][5];
int dx[9], dy[9] = ��, ��, ��, ��, ��, ��, ��, ��
int sharkDx[5], sharkDy[5] = ��, ��, ��, ��
int sharkDir[3];

1. Input()
	M, S, fish.push_back(), shark[0~1], NextPos sharkNextPos = {0, 0, 0, 0};
2. Solution()
	1) int time;
	2) for(time=1; time<=S; time++)
	3) void magic_fish()
		1) for(int i=0; i<fish.size(); i++) addFish.push_back(fish[i]) & map[fish[i].x][fish[i].y].pop_front();
	4) move_fish()
		1) int sX, sY, state, sD, nX, nY, nD, fishSize, cnt;
		2) fishSize = fish.size();
		3) for(int i=0; i<fishSize; i++){
		4) state = fish.front().state;
		5) if(state==1) fish.pop_front() & continue;
		6) sX = fish.front().x, sY = fish.front().y, sD = fish.front().dir, nD = sD;
		7) fish.pop_front(), cnt = 0;
		8) while(1) {
		9) cnt++;
		10) if(cnt==9) break;
		11) nX = sX + dx[nD], nY = sY + dy[nD];
		12) if(inRange(nX, nY) && scent[nX][nY] == 0 && (nX!= shark[0] && nY != shark[1])) break;
		13) nD = change_dir(nD);
		15) }
		16) if(cnt==9) fish.push_back({sX, sY, sD, state), map[sX][sY].push_back(i)continue;
		17) fish.push_back({nX, nY, nD, state), map[nX][nY].push_back(i);
		18 }
	5) sharkNextPos '1', '1', '1', '0'���� �¾�
	5) move_shark(int cnt)
		1) if(cnt==3)
		2) int sX, sY, nX, nY, fishCnt = 0;
		3) sX = shark[0], sY= shark[1];
		4) for(int i=0; i<3; i++) {
		5) nX = sX + sharkDx[sharkDir[i]], nY = sY + sharkDy[sharkDir[i]];
		6) if(!inRange(nX, nY)) return;
		7) if(map[nX][nY].size() >0) fishCnt = fishCnt + map[nX][nY].size();
		8) }
		10) if(sharkNextPos.fishCnt == 0) sharkNextPos ��ü
		11) else if(sharkNextPos.fishCnt < fishCnt) -> sharkNextPos ��ü
		12) return;
		13) for(int d=1; d<=4; d++){
		14) sharkDir[cnt] = d;
		15) move_shark(cnt+1);
		16) }
	6) nextPos��� ��� �̵� & ���� �濡 ����� ������ scent[nX][nY] = 3���� �¾�
	6) dec_scent()
		1) for(int x=1; x<=4; x++)
		2) for(int y=1; y<=4; y++)
		3) if(scent[x][y] > 0) scent[x][y]--;
	7) void add_fish()
		1) int addSize = addFish.size();
		2) for(int i=0; i<addSize; i++)
		3) fish.push_back(addFish.front());
		4) addFish.pop_front();

* int change_dir(int dir)
	1) int nDir;
	2) if(dir > 1) nDir = dir -1;
	3) else nDir = 8;
	4) return nDir;
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int M, S;
long Answer = 0;

struct Fish {
	int x, y, dir, state, s;
	Fish(int x, int y, int dir, int state, int s) {
		this->x = x;
		this->y = y;
		this->dir = dir;
		this->state = state;
		this->s = s;
	}
};

struct NextPos {
	int dirArr[3], fishCnt;
	NextPos(int a, int b, int c, int d) {
		this->dirArr[0] = a;
		this->dirArr[1] = b;
		this->dirArr[2] = c;
		this->fishCnt = d;
	}
};

deque <Fish> fish;
deque <Fish> addFish;
deque <pair<int, int>> map[5][5][9];

int shark[2], sharkDir[3], scent[5][5] = { 0, };
NextPos sharkNextPos = { 0, 0, 0, 0 };

int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int sharkDx[5] = { 0, -1, 0, 1, 0 };
int sharkDy[5] = { 0, 0, -1, 0, 1 };

void print_info() {
	cout << "���� ���" << endl;
	cout << "��� ��ġ: (" << shark[0] << ", " << shark[1] << ')'<<endl;
	for (int i = 0; i < fish.size(); i++) {
		cout << '(' << fish[i].x << ", " << fish[i].y << ") ��ġ�� "<< i<<"�� ����� ����: " << fish[i].dir << ", ����: " << fish[i].state << endl;
	}

	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 0) {
					for (int idx = 0; idx < map[x][y][d].size(); idx++) {
						cout << '(' << x << ", " << y << ") ��ġ�� " << d<<"������ ���� "<< map[x][y][d][idx].first << "�� " << map[x][y][d][idx].second << " ������ ����� ����" << endl;
					}
				}
			}

		}
	}
}

bool inRange(int x, int y) {
	if (x < 1 || x>4 || y < 1 || y>4) return false;
	return true;
}

int change_dir(int dir) {
	int nDir;
	if (dir > 1) nDir = dir - 1;
	else nDir = 8;
	return nDir;
}

void dec_scent() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			if(scent[x][y] > 0) scent[x][y]--;
		}
	}
}

void remove_fish() {
	int fishSize = fish.size();
	Fish f = { 0, 0,0,0, 0 };
	for (int i = 0; i < fishSize; i++) {
		f = fish.front();	
		fish.pop_front();
		if (f.state == 1) {
			continue;
		}
		fish.push_back(f);
	}
}

void reset_map() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 0) {
					while (!map[x][y][d].empty()) map[x][y][d].pop_front();
				}
			}
		}
	}
	int x, y, d, s;
	for (int i = 0; i < fish.size(); i++) {
		x = fish[i].x, y = fish[i].y, d = fish[i].dir, s = fish[i].s;
		map[x][y][d].push_back(make_pair(i, s));
	}
}

void add_fish() {
	int addSize = addFish.size();
	for (int i = 0; i < addSize; i++) {
		fish.push_back(addFish.front());
		//map[addFish.front().x][addFish.front().y][addFish.front().dir].push_back(make_pair(idx, addFish.front().s));
		addFish.pop_front();
	}

	reset_map();
}

void union_fish() {
	int fishIdx, fishSize,mapSize, unionIdx, tmpSize, flag = 0;
	for (int x = 1; x <=4; x++) {
		for (int y = 1; y <= 4; y++) {
			for (int d = 1; d <= 8; d++) {
				if (map[x][y][d].size() > 1) {
					if (flag == 0) flag = 1;
					mapSize = map[x][y][d].size();
					for (int i = 0; i < mapSize; i++) {
						if (i == 0) {
							unionIdx = map[x][y][d].front().first;
							fishSize = map[x][y][d].front().second;
							map[x][y][d].pop_front();
							continue;
						}
						tmpSize = map[x][y][d].front().second;
						fishIdx = map[x][y][d].front().first;
						map[x][y][d].pop_front();
						fish[fishIdx].state = 1;
						fishSize = fishSize + tmpSize;
					}
					fish[unionIdx].s = fishSize;
					map[x][y][d].push_back(make_pair(unionIdx, fishSize));
				}
			}
		}
	}
	if(flag == 1) remove_fish();
	return;
}

void magic_fish() {
	for (int i = 0; i < fish.size(); i++) {
		addFish.push_back(fish[i]);
	}
}

void move_shark(int cnt) {
	if (cnt == 3) {
		int sX, sY, nX, nY, fishCnt = 0;
		int visited[5][5] = { 0, };
		nX = shark[0], nY = shark[1];
		for (int i = 0; i < 3; i++) {
			nX = nX + sharkDx[sharkDir[i]], nY = nY + sharkDy[sharkDir[i]];
			if (!inRange(nX, nY)) return;

			if (visited[nX][nY] == 0) {
				for (int d = 1; d <= 8; d++) {
					if (map[nX][nY][d].size() == 0) continue;
					for (int tmpIdx = 0; tmpIdx < map[nX][nY][d].size(); tmpIdx++) {
						fishCnt = fishCnt + map[nX][nY][d][tmpIdx].second;
					}
				}
				visited[nX][nY] = 1;
			}
			visited[nX][nY] = 1;
		}
		if (sharkNextPos.fishCnt == -1) {
			for (int i = 0; i < 3; i++) {
				sharkNextPos.dirArr[i] = sharkDir[i];
			}
			sharkNextPos.fishCnt = fishCnt;
		}
		else if (sharkNextPos.fishCnt < fishCnt) {
			for (int i = 0; i < 3; i++) {
				sharkNextPos.dirArr[i] = sharkDir[i];
			}
			sharkNextPos.fishCnt = fishCnt;
		}
		return;
	}

	for (int d = 1; d <= 4; d++) {
		sharkDir[cnt] = d;
		move_shark(cnt + 1);
	}
}


void sim_shark() {
	int sX, sY, nX, nY, tmpIdx, tmpSize;
	nX = shark[0], nY = shark[1];
	for (int i = 0; i < 3; i++) {
		nX = nX + sharkDx[sharkNextPos.dirArr[i]];
		nY = nY + sharkDy[sharkNextPos.dirArr[i]];
		for (int d = 1; d <= 8; d++) {
			if (map[nX][nY][d].size() > 0) {
				scent[nX][nY] = 3;
				tmpSize = map[nX][nY][d].size();
				for (int j = 0; j < tmpSize; j++) {
					tmpIdx = map[nX][nY][d].front().first;
					map[nX][nY][d].pop_front();
					fish[tmpIdx].state = 1;
				}
			}
		}
	}
	shark[0] = nX, shark[1] = nY;
}

void move_fish() {
	int sX, sY, state, sD, nX, nY, nD, fishSize, cnt, s;
	fishSize = fish.size();
	for (int i = 0; i < fishSize; i++) {
		state = fish.front().state;
		if (state == 1) {
			fish.pop_front();
			continue;
		}
		sX = fish.front().x, sY = fish.front().y, sD = fish.front().dir, nD = sD, s = fish.front().s;
		fish.pop_front();
		map[sX][sY][sD].pop_front();
		cnt = 0;

		while (1) {
			cnt++;
			if (cnt == 9) break;
			nX = sX + dx[nD], nY = sY + dy[nD];
			if (inRange(nX, nY) && scent[nX][nY] == 0 && (nX != shark[0] || nY != shark[1])) break;
			nD = change_dir(nD);
		}

		if (cnt == 9) {
			fish.push_back({ sX, sY, sD, state, s });
			map[sX][sY][sD].push_back(make_pair(i, s));
			continue;
		}
		fish.push_back({ nX, nY, nD, state, s });
		map[nX][nY][nD].push_back(make_pair(i, s));
	}
}

void find_answer() {
	Answer = 0;
	for (int i = 0; i < fish.size(); i++) {
		Answer = Answer + fish[i].s;
	}
}

void Solution() {
	int time;
	for (time = 1; time <= S; time++) {
		//cout << time << "�� ��" << endl;
		union_fish();
		//print_info();
		magic_fish();
		move_fish();
		//cout << "����� �̵� ��" << endl;
		//print_info();
		sharkNextPos = { 0, 0, 0, -1 };
		move_shark(0);
		sim_shark();
		//cout << "��� �̵� ��" << endl;
		//print_info();
		dec_scent();
		remove_fish();
		add_fish();
		//cout << "����� ���� ��" << endl;
		//print_info();
	}

	find_answer();
	cout << Answer << endl;
}

void Input() {
	cin >> M >> S;
	int x, y, dir, state, idx;
	idx = 0;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> dir;
		state = 0;
		fish.push_back({ x, y, dir, state, 1 });
		map[x][y][dir].push_back(make_pair(idx, 1));
		idx++;
	}

	cin >> shark[0] >> shark[1];
}

int main(void) {
	Input();
	//print_info();
	Solution();
	return 0;
}