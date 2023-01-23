#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int N, Answer = 0, Answer2 = 0;

int command[10001][3];

int green[6][4];
int blue[4][6];

void print_map() {
	cout << "초록맵" << endl;
	for (int row = 0; row < 6; row++) {
		for (int col = 0; col < 4; col++) {
			cout << green[row][col] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << "파란맵" << endl;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 6; col++) {
			cout << blue[row][col] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Find_block() {
	Answer2 = 0;

	for (int row = 2; row < 6; row++) {
		for (int col = 0; col < 4; col++) {
			if (green[row][col] == 1) Answer2++;
		}
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 2; col < 6; col++) {
			if (blue[row][col] == 1) Answer2++;
		}
	}
}

void Check_block() {
	int row, col, eraseCnt, startRow, startCol;
	queue <int> q;
	//1. 연한 초록색 칸에 있는지
	eraseCnt = 0;
	for (row = 0; row < 2; row++) {
		for (col = 0; col < 4; col++) {
			if (green[row][col] == 1) {
				eraseCnt++;
				break;
			}
		}
	}

	if (eraseCnt > 0) {
		for (col = 0; col < 4; col++) {
			for (row = 5 - eraseCnt; row >= (2- eraseCnt); row--) {
				q.push(green[row][col]);
				green[row][col] = 0;
			}
			row = 5;
			while (!q.empty()) {
				green[row][col] = q.front();
				row--;
				q.pop();
			}
		}
	}

	//1. 연한 파란색 칸에 있는지
	eraseCnt = 0;
	for (col = 0; col < 2; col++) {
		for (row = 0; row < 4; row++) {
			if (blue[row][col] == 1) {
				eraseCnt++;
				break;
			}
		}
	}

	if (eraseCnt > 0) {
		for (row = 0; row < 4; row++) {
			for (col = 5 - eraseCnt; col >= (2 - eraseCnt); col--) {
				q.push(blue[row][col]);
				blue[row][col] = 0;
			}
			col = 5;
			while (!q.empty()) {
				blue[row][col] = q.front();
				col--;
				q.pop();
			}
		}
	}
}

void Erase_block() {
	int row, col, blockCnt, startRow, startCol;
	//1-1 초록색 검사 && 지우기
	startRow = -1;
	for (row = 5; row > 1; row--) {
		blockCnt = 0;
		for (col = 0; col < 4; col++) {
			if (green[row][col] == 0) break;
			blockCnt++;
		}
		if (blockCnt == 4) {
			Answer++;
			for (col = 0; col < 4; col++) {
				green[row][col] = 0;
			}
			if (startRow == -1) startRow = row;
		}
	}
	//1-2 초록색 지운 행 있으면 블록 댕기기
	if (startRow != -1) {
		for (col = 0; col < 4; col++) {
			blockCnt = 0;
			for (row = startRow; row >= 0; row--) {
				if (green[row][col] == 1) {
					blockCnt++;
					green[row][col] = 0;
				}
			}
			if (blockCnt > 0) {
				for (row = startRow; row > (startRow - blockCnt); row--) {
					green[row][col] = 1;
				}
			}
		}
	}
	//2-1 파란색 검사 && 지우기
	startCol = - 1;
	for (col = 5; col > 1; col--) {
		blockCnt = 0;
		for (row = 0; row < 4; row++) {
			if (blue[row][col] == 0) break;
			blockCnt++;
		}
		if (blockCnt == 4) {
			Answer++;
			for (row = 0; row < 4; row++) {
				blue[row][col] = 0;
			}
			if (startCol == -1) startCol = col;
		}
	}
	//2-2 파란색 지운 열 있으면 블록 댕기기
	if (startCol != -1) {
		for (row = 0; row < 4; row++) {
			blockCnt = 0;	
			for (col = startCol; col >= 0; col--) {
				if (blue[row][col] == 1) {
					blockCnt++;
					blue[row][col] = 0;
				}
			}
			if (blockCnt > 0) {
				for (col = startCol; col > (startCol - blockCnt); col--) {
					blue[row][col] = 1;
				}
			}
		}
	}
}

void Add_block(int type, int startX, int startY) {
	int blockRow, blockCol;
	//1. 초록색 칸 블록 쌓기
	blockCol = startY;
	if (type == 1 || type == 3) {
		for (blockRow = 0; blockRow <= 6; blockRow++) {
			if (blockRow == 6) break;
			else if (green[blockRow][blockCol] == 1) break;
		}
		blockRow--;
		if (type == 1) green[blockRow][blockCol] = 1;
		else {
			green[blockRow - 1][blockCol] = 1;
			green[blockRow][blockCol] = 1;
		}
	}
	else if (type == 2) {
		for (blockRow = 0; blockRow <= 6; blockRow++) {
			if (blockRow == 6) break;
			else if (green[blockRow][blockCol] == 1 || green[blockRow][blockCol + 1] == 1) break;
		}
		blockRow--;
		green[blockRow][blockCol] = 1;
		green[blockRow][blockCol + 1] = 1;
	}
	//2. 파란색 칸 블록 쌓기
	blockRow = startX;
	if (type == 1 || type == 2) {
		for (blockCol = 0; blockCol <= 6; blockCol++) {
			if (blockCol == 6) break;
			else if (blue[blockRow][blockCol] == 1) break;
		}
		blockCol--;
		if (type == 1) blue[blockRow][blockCol] = 1;
		else {
			blue[blockRow][blockCol - 1] = 1;
			blue[blockRow][blockCol] = 1;
		}
	}
	else {
		for (blockCol = 0; blockCol <= 6; blockCol++) {
			if (blockCol == 6) break;
			else if (blue[blockRow][blockCol] == 1 || blue[blockRow + 1][blockCol] == 1) break;
		}
		blockCol--;
		blue[blockRow][blockCol] = 1;
		blue[blockRow + 1][blockCol] = 1;
	}
}

void Solve() {
	for (int i = 0; i < N; i++) {
		Add_block(command[i][0], command[i][1], command[i][2]);
		Erase_block();
		Check_block();
		//cout << i + 1 << "번째 턴" << endl;
		//print_map();
	}

	Find_block();
}

void Input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> command[i][0] >> command[i][1] >> command[i][2];
	}
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;
	cout << Answer2 << endl;
	return 0;
}