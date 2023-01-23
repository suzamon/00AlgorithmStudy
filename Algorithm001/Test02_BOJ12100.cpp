/*
문제
2048 게임은 4×4 크기의 보드에서 혼자 즐기는 재미있는 게임이다. 이 링크를 누르면 게임을 해볼 수 있다.

이 게임에서 한 번의 이동은 보드 위에 있는 전체 블록을 상하좌우 네 방향 중 하나로 이동시키는 것이다.
이때, 같은 값을 갖는 두 블록이 충돌하면 두 블록은 하나로 합쳐지게 된다.
한 번의 이동에서 이미 합쳐진 블록은 또 다른 블록과 다시 합쳐질 수 없다.
(실제 게임에서는 이동을 한 번 할 때마다 블록이 추가되지만, 이 문제에서 블록이 추가되는 경우는 없다)

<그림 1>의 경우에서 위로 블록을 이동시키면 <그림 2>의 상태가 된다.
여기서, 왼쪽으로 블록을 이동시키면 <그림 3>의 상태가 된다.

마지막으로, 똑같은 수가 세 개가 있는 경우에는 이동하려고 하는 쪽의 칸이 먼저 합쳐진다.
예를 들어, 위로 이동시키는 경우에는 위쪽에 있는 블록이 먼저 합쳐지게 된다.
<그림 14>의 경우에 위로 이동하면 <그림 15>를 만든다.

이 문제에서 다루는 2048 게임은 보드의 크기가 N×N 이다.
보드의 크기와 보드판의 블록 상태가 주어졌을 때,
최대 5번 이동해서 만들 수 있는 가장 큰 블록의 값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 보드의 크기 N (1 ≤ N ≤ 20)이 주어진다. 둘째 줄부터 N개의 줄에는 게임판의 초기 상태가 주어진다.
 0은 빈 칸을 나타내며, 이외의 값은 모두 블록을 나타낸다.
블록에 쓰여 있는 수는 2보다 크거나 같고, 1024보다 작거나 같은 2의 제곱꼴이다. 블록은 적어도 하나 주어진다.

출력
최대 5번 이동시켜서 얻을 수 있는 가장 큰 블록을 출력한다.

int N, Answer;
int map[21][21], copyMap[21][21];
int arr[6];
deque <pair <int, int>> dq;

Input()
	N, map[21][21];
Solution()
	1) for(int i=1; i<=4; i) arr[0] = i, DFS(1);


	1) DFS(int cnt) -> 1: 상, 2: 하, 3: 좌, 4: 우
		if(cnt==5)
		copy_map()

		break;
		for(int i=1; i<=4; i++)
			arr[cnt] = i;
			DFS(cnt+1)

	2) simulation(int d)
		int tmp;
		switch(d)
			case 1:
				for(int yy=0; yy<N; yy++){
				for(int xx=0; xx<N; xx++){
					if(copyMap[xx][yy] == 0) continue;
					if(dq.size() ==0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
					}
					tmp = dq.size() -1;
					if(dq[tmp].second==0 && dq[tmp].first == copyMap[xx][yy]) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
					}
					else{
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
					}
				}
				for(int xx=0; xx<N; xx++){
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if(dq.size() ==0) break;
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

int N, M, Answer = 0;
int map[21][21], copyMap[21][21];
int dir[6];

deque <pair<int, int>> dq;

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void find_answer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Answer < copyMap[i][j]) Answer = copyMap[i][j];
		}
	}
}

int simulation(int time) {
	int d, tmp, cnt, change;
	d = dir[time];
	cnt = 0, change = 0;
	switch (d) {
	case 1: //상
		for (int yy = 0; yy < N; yy++) {
			for (int xx = 0; xx < N; xx++) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int xx = 0; xx < N; xx++) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 2: //하
		for (int yy = 0; yy < N; yy++) {
			for (int xx = N-1; xx >= 0 ; xx--) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int xx = N - 1; xx >= 0; xx--) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 3: //좌
		for (int xx = 0; xx < N; xx++) {
			for (int yy = 0; yy < N; yy++) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int yy = 0; yy < N; yy++) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 4: //우
		for (int xx = 0; xx < N; xx++) {
			for (int yy = N - 1; yy >= 0; yy--) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int yy = N - 1; yy >= 0; yy--) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	}

	return change;
}

void DFS(int cnt) {
	if (cnt == 5) {
		int retFlag = 0;
		copy_map();
		for (int i = 0; i < cnt; i++) {
			retFlag = 0;
			retFlag += simulation(i);
			//if(retFlag == 0) break;
			//print_map();
		}
		find_answer();

		return;
	}

	for (int i = 1; i <= 4; i++) {
		dir[cnt] = i;
		DFS(cnt + 1);
	}
}

void Solution() {
	for (int i = 1; i <= 4; i++) {
		dir[0] = i;
		DFS(1);
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}