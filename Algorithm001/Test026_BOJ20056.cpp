/*
1'09''27'''
어른 상어가 마법사가 되었고, 파이어볼을 배웠다.

마법사 상어가 크기가 N×N인 격자에 파이어볼 M개를 발사했다.
가장 처음에 파이어볼은 각자 위치에서 이동을 대기하고 있다.
i번 파이어볼의 위치는 (ri, ci), 질량은 mi이고, 방향은 di, 속력은 si이다. 위치 (r, c)는 r행 c열을 의미한다.
격자의 행과 열은 1번부터 N번까지 번호가 매겨져 있고, 1번 행은 N번과 연결되어 있고, 1번 열은 N번 열과 연결되어 있다.
파이어볼의 방향은 어떤 칸과 인접한 8개의 칸의 방향을 의미하며, 정수로는 다음과 같다.

7	0	1
6	 	2
5	4	3

마법사 상어가 모든 파이어볼에게 이동을 명령하면 다음이 일들이 일어난다.

1. 모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
	이동하는 중에는 같은 칸에 여러 개의 파이어볼이 있을 수도 있다.
2. 이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 다음과 같은 일이 일어난다.
	1. 같은 칸에 있는 파이어볼은 모두 하나로 합쳐진다.
	2. 파이어볼은 4개의 파이어볼로 나누어진다.
	3. 나누어진 파이어볼의 질량, 속력, 방향은 다음과 같다.
		1. 질량은 ⌊(합쳐진 파이어볼 질량의 합)/5⌋이다.
		2. 속력은 ⌊(합쳐진 파이어볼 속력의 합)/(합쳐진 파이어볼의 개수)⌋이다.
		3. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고,
		   그렇지 않으면 1, 3, 5, 7이 된다.
	4. 질량이 0인 파이어볼은 소멸되어 없어진다.

마법사 상어가 이동을 K번 명령한 후, 남아있는 파이어볼 질량의 합을 구해보자.

입력
첫째 줄에 N, M, K가 주어진다.
둘째 줄부터 M개의 줄에 파이어볼의 정보가 한 줄에 하나씩 주어진다. 파이어볼의 정보는 다섯 정수 ri, ci, mi, si, di로 이루어져 있다.
서로 다른 두 파이어볼의 위치가 같은 경우는 입력으로 주어지지 않는다.

출력
마법사 상어가 이동을 K번 명령한 후, 남아있는 파이어볼 질량의 합을 출력한다.

제한
4 ≤ N ≤ 50
0 ≤ M ≤ N2
1 ≤ K ≤ 1,000
1 ≤ ri, ci ≤ N
1 ≤ mi ≤ 1,000
1 ≤ si ≤ 1,000
0 ≤ di ≤ 7

N, M, K, Answer =0;

deque <int> map[51][51];
deque <Fireball> fires;


1. Input()
	N, M, K, M만큼 fires에 기입(idx 통일을 위해 쓰레기값 1개 넣기)
2. Solution()
	1) move_fireBall()
		1) idx : 1~fireBall.Size() 까지반복
		2) nX = x + dx[d] * s, nY = y + dy[d] * s
		3) if(nX <= 0) {while(1){ nX = nX + N; if(nX > 0 && nX <= N) break;}}
		4) else if(nX > N)  {while(1){ nX = nX - N; if(nX > 0 && nX <= N) break;}}
		5) y값도 동일하게 셋업
		6) map[nX][nY].push_back(idx);
		8) fires[idx] 정보 갱신

	2) union_fireball()
		0) int firesSize, sumM, sumS, cnt, dFlag, tmpSize, firesIdx;
		0) int x, y, tmpX, tmpY, tmpM, tmpS, tmpD;
		1) firesSize = fires.size()
		2) for(int i= 1; i< firesSize; i++)만큼 반복 (3~ )
		3) if(fires[i].m ==0) continue;
		4) x = fires[i].x, y= fires[i].y;
		5) if(map[x][y] == 1) map[x][y].pop_front() & continue;

		6) tmpSize = map[x][y].size(), sumM = 0, sumS =0, cnt=0, dFlag =0;

		7) for(int j=0; j< tmpSize; j++)만큼 반복 (8~11)
		8) fireIdx = map[x][y].front() & map[x][y].pop_front()
		9) sumM += fires[fireIdx].m & sumS += fires[fireIdx].s & cnt++ & fires[fireIdx].m = 0
		10) if(j==0) dFlag = fires[fireIdx].d % 2;
		11) else if( fires[fireIdx].d % 2 != dFlag) dFlag =2;

		10) tmpM = sumM/5 -> if(tmpM == 0) 이면 continue;
		12) tmpX = x, tmpY = y, tmpS = sumS/cnt;
		14) if(dFlag < 2) 방향은 0, 2, 4, 6인 fireball push_back
		15) 아니면 방향1, 3, 5, 7인 fireball push_back

	3) update_fireball()
		1) firesSize = fires.size()
		2) for(int i= 0; i< firesSize; i++)만큼 반복
		3) front() 해서 m=0 이면 삭제
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, K, Answer = 0;

struct Fireball {
	int x, y, m, s, d;
};

deque <Fireball> fires;
deque <int> map[51][51];

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void find_answer() {
	int firesSize = fires.size();
	Answer = 0;
	for (int i = 1; i < firesSize; i++) {
		Answer = Answer + fires[i].m;
	}
}

void update_fireballs() {
	int firesSize = fires.size();

	Fireball f;

	for (int i = 0; i < firesSize; i++) {
		f = fires.front();
		fires.pop_front();
		if (f.m > 0) {
			fires.push_back(f);
		}
	}
}

void union_frieballs() {
	int firesSize, sumM, sumS, cnt, dFlag, tmpSize, fireIdx;
	int x, y, tmpX, tmpY, tmpM, tmpS, tmpD;

	firesSize = fires.size();

	for (int i = 1; i < firesSize; i++) {
		if (fires[i].m == 0) continue;

		x = fires[i].x, y = fires[i].y;
		if (map[x][y].size() == 1) {
			map[x][y].pop_front();
			continue;
		}

		tmpSize = map[x][y].size(), sumM = 0, sumS = 0, cnt = 0, dFlag = 0;

		for (int j = 0; j < tmpSize; j++) {
			fireIdx = map[x][y].front();
			map[x][y].pop_front();
			sumM = sumM + fires[fireIdx].m;
			sumS = sumS + fires[fireIdx].s;
			cnt++;
			fires[fireIdx].m = 0;
			if(j == 0) dFlag = fires[fireIdx].d % 2;
			else if ((fires[fireIdx].d % 2) != dFlag) dFlag = 2;
		}

		tmpM = (int) sumM / 5;
		if (tmpM == 0) continue;
		tmpX = x, tmpY = y, tmpS = (int) sumS / cnt;
		if (dFlag < 2) {
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 0 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 2 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 4 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 6 });
		}
		else {
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 1 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 3 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 5 });
			fires.push_back({ tmpX, tmpY, tmpM, tmpS, 7 });
		}
	}

}

void move_fireballs() {
	int sX, sY, sD, sS, nX, nY;
	for (int idx = 1; idx < fires.size(); idx++) {
		sX = fires[idx].x, sY = fires[idx].y, sD = fires[idx].d, sS = fires[idx].s;
		nX = sX + (dx[sD] * sS);
		nY = sY + (dy[sD] * sS);
		if (nX < 1) {
			while (1) {
				nX = nX + N;
				if (nX > 0 && nX <= N) break;
			}
		}
		else if (nX > N) {
			while (1) {
				nX = nX - N;
				if (nX > 0 && nX <= N) break;
			}
		}

		if (nY < 1) {
			while (1) {
				nY = nY + N;
				if (nY > 0 && nY <= N) break;
			}
		}
		else if (nY > N) {
			while (1) {
				nY = nY - N;
				if (nY > 0 && nY <= N) break;
			}
		}

		map[nX][nY].push_back(idx);
		fires[idx].x = nX, fires[idx].y = nY;
	}
}

void Solution() {
	int time;
	for (time = 1; time <= K; time++) {
		move_fireballs();
		union_frieballs();
		update_fireballs();
	}
	find_answer();
	cout << Answer << endl;
}

void Input() {
	fires.push_back({ 0,0,3,0,0 });

	cin >> N >> M >> K;

	int x, y, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> m >> s >> d;
		fires.push_back({ x,y,m,s,d });
	}
}

int main(void) {
	Input();
	Solution();
	return 0;
}