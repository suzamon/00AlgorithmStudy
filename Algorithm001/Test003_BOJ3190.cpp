/*
게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다. 보드의 상하좌우 끝에 벽이 있다.
게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다. 뱀은 처음에 오른쪽을 향한다.
뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.

뱀은 매 초마다 이동
1. 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
2. 만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
3. 만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉, 몸길이는 변하지 않는다.

사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초에 끝나는지 계산

첫째 줄에 보드의 크기 N이 주어진다. (2 ≤ N ≤ 100) 다음 줄에 사과의 개수 K가 주어진다. (0 ≤ K ≤ 100)

다음 K개의 줄에는 사과의 위치가 주어지는데, 첫 번째 정수는 행, 두 번째 정수는 열 위치를 의미한다. 사과의 위치는 모두 다르며, 맨 위 맨 좌측 (1행 1열) 에는 사과가 없다.

다음 줄에는 뱀의 방향 변환 횟수 L 이 주어진다. (1 ≤ L ≤ 100)

다음 L개의 줄에는 뱀의 방향 변환 정보가 주어지는데,  정수 X와 문자 C로 이루어져 있으며.
게임 시작 시간으로부터 X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻이다.
X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.


tail[4] -> x, y, 지금 방향, 다음방향idx
head[4] -> x, y, 다음 방향, 다음방향idx

1. Input()
	N, K
	사과 위치
	L
	방향 정보(시간, D)
	changeHeadDir[L][2] -> 뱀머리 방향 이동 [1] = 0이면 L, [1]=1이면 R
	changeTailDir[L][2] -> 뱀꼬리 방향 이동 [1] = 0이면 L, [1]=1이면 R

2. Simualtion()
	1-1) (idx = L이면 생략)머리 방향 이동 시간이면 머리 방향 셋팅, 머리 다음 방향 idx++
	1-2) (idx = L이면 생략) 꼬리 방향 이동 시간이면 꼬리 방향 셋팅, 꼬리 다음 방향 idx++
	2) 머리 이동 -> 몸통 있거나 혹은 벽을 벗어나면 게임 종료
	3-1) 사과 없으면 꼬리 현재 방향으로 이동
	3-2) 사과 있으면 꼬리 그대로 & 다음 방향 idx ~ L 까지 방향 변경 시간 + 1 증가


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

int dx[4] = { 0, 1, 0, -1 }; // 우, 하, 좌, 상
int dy[4] = { 1, 0, -1, 0 };

int head[4], tail[4];

void print_map(int t) {
	cout << t << "초 후" << endl;
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
	map[1][1] = 2;//뱀은 2

	for (int i = 0; i < K; i++) {
		cin >> r >> c;
		map[r][c] = 1;//사과는 1
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