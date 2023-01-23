/*
개발한 혁셈블리어 사용 -> 문자로 이동
프로그램은 현재 위치에 있는 문자가 나타내는 명령 처리 & 이동 방향에 따라 문자 이동
가장 처음 위치는 제일 왼쪽 위에 있는 문자 & 이동 방향 : 오른쪽
이동방향 변경 가능 & 격자 바깥 반대편 위치


문자	수행 명령
<	이동 방향을 왼쪽으로 바꾼다.
>	이동 방향을 오른쪽으로 바꾼다.
^	이동 방향을 위쪽으로 바꾼다.
v	이동 방향을 아래쪽으로 바꾼다.
_	메모리에 0이 저장되어 있으면 이동 방향을 오른쪽으로 바꾸고, 아니면 왼쪽으로 바꾼다.
|	메모리에 0이 저장되어 있으면 이동 방향을 아래쪽으로 바꾸고, 아니면 위쪽으로 바꾼다.
?	이동 방향을 상하좌우 중 하나로 무작위로 바꾼다. 방향이 바뀔 확률은 네 방향 동일하다.
.	아무 것도 하지 않는다.
@	프로그램의 실행을 정지한다.
0~9	메모리에 문자가 나타내는 값을 저장한다.
+	메모리에 저장된 값에 1을 더한다. 만약 더하기 전 값이 15이라면 0으로 바꾼다.
-	메모리에 저장된 값에 1을 뺀다. 만약 빼기 전 값이 0이라면 15로 바꾼다.


1. Input() :
- programPos[4] (x,y,d,num) => 처음 0, 0, 0, 0
- visited[21][21][4] -> 방향 저장
- exitFlag = 0 -> 전역 변수 1로 설정되면 바로 Yes 출력
- dx[4], dy[4] : →, ←, ↓, ↑
- R, C (2 ≤ R, C ≤ 20)
- string strCom[21];

2. Solution():
1. check_exit() : commnad에 @ 있는지 확인 -> 없으면 바로 NO 출력 후 종료
2. simulation(int startX, int startY, int dir, int sum) -> 같은 위치, 같은 방향 있으면 탈출 -> NO 출력 후 종료
- DFS로 구현
- 해당 위치 명령어 반영 -> 이동 방향 혹은 num 변경 & visited 변수에 명령어 반영한 방향 변수 추가
- 이동 방향 고려해서 nextX, nextY 찾기 (범위 초과 시, 반영)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <string>

using namespace std;

//int visited[21][21][4][16] = { 0, };
deque <int> visit[21][21];
int R, C, exitFlag; //exitFlag = -1이면 NO, 1이면 YES
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

string strCom[21];

void reset_value() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			while (!visit[i][j].empty()) {
				visit[i][j].pop_front();
			}
			/*
			for (int k = 0; k < 4; k++) {
				for (int m = 0; m < 16; m++) {
					visited[i][j][k][m] = 0;
				}
			}
			*/
		}
	}

}

void simulation(int startX, int startY, int dir, int num) {
	//if (visited[21][21][dir][num] > 1) return;
	if (exitFlag == 1) return;

	//명령어 처리
	int nextX, nextY, nextDir, nextNum, tmpVisit;
	char command = strCom[startX].at(startY);
	switch (command) {
	case '<':
		nextDir = 1;
		nextNum = num;
		break;
	case '>':
		nextDir = 0;
		nextNum = num;
		break;
	case '^':
		nextDir = 3;
		nextNum = num;
		break;
	case 'v':
		nextDir = 2;
		nextNum = num;
		break;
	case '_':
		if (num == 0) nextDir = 0;
		else nextDir = 1;
		nextNum = num;
		break;
	case '|':
		if (num == 0) nextDir = 2;
		else nextDir = 3;
		nextNum = num;
		break;
	case '?':
		nextNum = num;
		for (int i = 0; i < 4; i++) {
			if (exitFlag == 1) break;
			nextDir = i;

			nextX = startX + dx[nextDir];
			nextY = startY + dy[nextDir];
			if (nextX < 0) nextX = R - 1;
			else if (nextX >= R) nextX = 0;
			if (nextY < 0) nextY = C - 1;
			else if (nextY >= C) nextY = 0;

			tmpVisit = nextNum * 10 + nextDir;

			if (visit[nextX][nextY].size() > 1) {
				int tmpFlag = 0;
				for (int i = 0; i < visit[startX][startY].size(); i++) {
					if (tmpVisit == visit[startX][startY][i]) {
						tmpFlag = 1;
						break;
					}
				}
				if (tmpFlag == 1) return;
			}

			visit[nextX][nextY].push_back(tmpVisit);
			//visited[nextX][nextY][nextDir][nextNum]++;
			simulation(nextX, nextY, nextDir, nextNum);
			//visited[nextX][nextY][nextDir][nextNum]--;
			visit[nextX][nextY].pop_back();
		}
		return;
		break;
	case '.':
		nextDir = dir;
		nextNum = num;
		break;
	case '@':
		exitFlag = 1;
		return;
		break;
	case '1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9': case'0':
		nextDir = dir;
		nextNum = num + (command - '0');
		break;
	case '+':
		nextDir = dir;
		nextNum = num + 1;
		if (nextNum > 15) nextNum = 0;
		break;
	case '-':
		nextDir = dir;
		nextNum = num - 1;
		if (nextNum < 0) nextNum = 15;
		break;
	}

	nextX = startX + dx[nextDir];
	nextY = startY + dy[nextDir];
	if (nextX < 0) nextX = R - 1;
	else if (nextX >= R) nextX = 0;
	if (nextY < 0) nextY = C - 1;
	else if (nextY >= C) nextY = 0;

	tmpVisit = nextNum * 10 + nextDir;

	if (visit[nextX][nextY].size() > 1) {
		int tmpFlag = 0;
		for (int i = 0; i < visit[startX][startY].size(); i++) {
			if (tmpVisit == visit[startX][startY][i]) {
				tmpFlag = 1;
				break;
			}
		}
		if (tmpFlag == 1) return;
	}
	visit[nextX][nextY].push_back(tmpVisit);
	//visited[nextX][nextY][nextDir][nextNum]++;
	simulation(nextX, nextY, nextDir, nextNum);
	//visited[nextX][nextY][nextDir][nextNum]--;
	visit[nextX][nextY].pop_back();
}

void check_exit() {
	int flag = 0;
	char command;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			command = strCom[i].at(j);
			if (command == '@') {
				flag++;
				break;
			}
		}
		if (flag > 0) break;
	}
	if (flag == 0) exitFlag = -1;
	return;
}

void Solution() {
	check_exit();
	if (exitFlag == -1) return;

	simulation(0, 0, 0, 0);
	if (exitFlag == 0) exitFlag = -1;

}

void Input() {
	exitFlag = 0;
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		cin >> strCom[i];
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ';
		if (exitFlag == 1) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		//reset_value();

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}