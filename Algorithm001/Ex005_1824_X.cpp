/*
������ �������� ��� -> ���ڷ� �̵�
���α׷��� ���� ��ġ�� �ִ� ���ڰ� ��Ÿ���� ��� ó�� & �̵� ���⿡ ���� ���� �̵�
���� ó�� ��ġ�� ���� ���� ���� �ִ� ���� & �̵� ���� : ������
�̵����� ���� ���� & ���� �ٱ� �ݴ��� ��ġ


����	���� ���
<	�̵� ������ �������� �ٲ۴�.
>	�̵� ������ ���������� �ٲ۴�.
^	�̵� ������ �������� �ٲ۴�.
v	�̵� ������ �Ʒ������� �ٲ۴�.
_	�޸𸮿� 0�� ����Ǿ� ������ �̵� ������ ���������� �ٲٰ�, �ƴϸ� �������� �ٲ۴�.
|	�޸𸮿� 0�� ����Ǿ� ������ �̵� ������ �Ʒ������� �ٲٰ�, �ƴϸ� �������� �ٲ۴�.
?	�̵� ������ �����¿� �� �ϳ��� �������� �ٲ۴�. ������ �ٲ� Ȯ���� �� ���� �����ϴ�.
.	�ƹ� �͵� ���� �ʴ´�.
@	���α׷��� ������ �����Ѵ�.
0~9	�޸𸮿� ���ڰ� ��Ÿ���� ���� �����Ѵ�.
+	�޸𸮿� ����� ���� 1�� ���Ѵ�. ���� ���ϱ� �� ���� 15�̶�� 0���� �ٲ۴�.
-	�޸𸮿� ����� ���� 1�� ����. ���� ���� �� ���� 0�̶�� 15�� �ٲ۴�.


1. Input() :
- programPos[4] (x,y,d,num) => ó�� 0, 0, 0, 0
- visited[21][21][4] -> ���� ����
- exitFlag = 0 -> ���� ���� 1�� �����Ǹ� �ٷ� Yes ���
- dx[4], dy[4] : ��, ��, ��, ��
- R, C (2 �� R, C �� 20)
- string strCom[21];

2. Solution():
1. check_exit() : commnad�� @ �ִ��� Ȯ�� -> ������ �ٷ� NO ��� �� ����
2. simulation(int startX, int startY, int dir, int sum) -> ���� ��ġ, ���� ���� ������ Ż�� -> NO ��� �� ����
- DFS�� ����
- �ش� ��ġ ��ɾ� �ݿ� -> �̵� ���� Ȥ�� num ���� & visited ������ ��ɾ� �ݿ��� ���� ���� �߰�
- �̵� ���� ����ؼ� nextX, nextY ã�� (���� �ʰ� ��, �ݿ�)
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
int R, C, exitFlag; //exitFlag = -1�̸� NO, 1�̸� YES
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

	//��ɾ� ó��
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
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}