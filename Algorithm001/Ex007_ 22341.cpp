#include <iostream>
#include <stdlib.h>

#define MAX 30000

using namespace std;

//extern int makeBlock(int module[][4][4]);

int check_block(int idx1, int idx2, int module[][4][4], int avgH) {
	//체크 ->
	int flag = 0, rotCnt = 0;
	int originalMap[4][4] = { 0, };
	int copyMap[4][4] = { 0, };

	for (int cnt = 0; cnt < 4; cnt++) {
		flag = 0;

		if (cnt > 0) {
			/*
			if (cnt == 1) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						originalMap[i][j] = module[idx2][i][j];
					}
				}
			}
			*/

			//3번 회전 실행
			rotCnt++;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					copyMap[i][j] = module[idx2][i][j];
				}
			}
			for (int c = 0; c < 4; c++) {
				for (int r = 0; r < 4; r++) {
					module[idx2][r][c] = copyMap[3 - c][r];
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if ((module[idx1][i][j] + module[idx2][i][3 - j]) != avgH) {
					flag = -1;
					break;
				}
			}
			if (flag == -1) break;
		}

		if (flag == 0) { //합체 성공
			break;
		}
	}

	if (flag == 0) return 1;
	return flag;
}

int find_height(int idx, int module[][4][4]) {
	int sum = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sum += module[idx][i][j];
		}
	}

	return sum;

}

int makeBlock(int module[][4][4]) {
	int Answer = 0;
	int firstH, nextH, totalH, avgH, checkFlag;
	int visited[30001] = { 0, };
	int sumH[30001] = { 0, };

	for (int i = 0; i < 30000; i++) {
		sumH[i] = find_height(i, module);
	}


	for (int i = 0; i < 30000 - 1; i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;

		firstH = sumH[i];

		for (int j = i + 1; j < 30000; j++) {
			if (visited[j] == 1) continue;

			nextH = sumH[j];
			totalH = firstH + nextH;
			if (totalH % 16 != 0) continue;

			avgH = totalH / 16;

			checkFlag = check_block(i, j, module, avgH);
			if (checkFlag == -1) continue;

			visited[j] = 1;
			Answer += avgH;
		}
	}

	return Answer;
}

int main(void)
{
	static int module[MAX][4][4];

	srand(3); // 3 will be changed

	for (int tc = 1; tc <= 10; tc++)
	{
		for (int c = 0; c < MAX; c++)
		{
			int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					module[c][y][x] = base + (rand() % 3);
				}
			}
		}
		cout << "#" << tc << " " << makeBlock(module) << endl;
	}

	return 0;
}
