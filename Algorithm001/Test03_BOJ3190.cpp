/*
문제
 'Dummy' 라는 도스게임이 있다. 이 게임에는 뱀이 나와서 기어다니는데, 사과를 먹으면 뱀 길이가 늘어난다.
뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.

게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다.
보드의 상하좌우 끝에 벽이 있다. 게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다.
뱀은 처음에 오른쪽을 향한다.

뱀은 매 초마다 이동을 하는데 다음과 같은 규칙을 따른다.

먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉, 몸길이는 변하지 않는다.
사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초에 끝나는지 계산하라.

입력
첫째 줄에 보드의 크기 N이 주어진다. (2 ≤ N ≤ 100) 다음 줄에 사과의 개수 K가 주어진다. (0 ≤ K ≤ 100)

다음 K개의 줄에는 사과의 위치가 주어지는데, 첫 번째 정수는 행, 두 번째 정수는 열 위치를 의미한다.
사과의 위치는 모두 다르며, 맨 위 맨 좌측 (1행 1열) 에는 사과가 없다.

다음 줄에는 뱀의 방향 변환 횟수 L 이 주어진다. (1 ≤ L ≤ 100)

다음 L개의 줄에는 뱀의 방향 변환 정보가 주어지는데,  정수 X와 문자 C로 이루어져 있으며.
게임 시작 시간으로부터 X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻이다.
 X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.

출력
첫째 줄에 게임이 몇 초에 끝나는지 출력한다.

int N, K, Answer = 0;
int map[101][101]; -> 1: 뱀 자리, 2: 사과
int head[2], tail[2], headDir;
int dx[5], dy[5] -> 1: 우/ 2: 하/ 3: 좌/ 4: 상
deque <pair <int, int>> chDir; -> 초, 방향 전환(1: 오른쪽 90도, 2: 왼쪽 90도)
deque <int> tailDir -> 뱀 머리 이동 방향(사과 만나면 그대로 & 사과 없으면 pop())


Input()
	N, K, map[1][1] = 1, headDir = 1, map에 사과, chDir push
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
	cout << time << "초 후 맵 정보" << endl;
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