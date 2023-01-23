/*
문제
폴리오미노란 크기가 1×1인 정사각형을 여러 개 이어서 붙인 도형이며, 다음과 같은 조건을 만족해야 한다.

정사각형은 서로 겹치면 안 된다.
도형은 모두 연결되어 있어야 한다.
정사각형의 변끼리 연결되어 있어야 한다. 즉, 꼭짓점과 꼭짓점만 맞닿아 있으면 안 된다.
정사각형 4개를 이어 붙인 폴리오미노는 테트로미노라고 하며, 다음과 같은 5가지가 있다.

아름이는 크기가 N×M인 종이 위에 테트로미노 하나를 놓으려고 한다.
종이는 1×1 크기의 칸으로 나누어져 있으며, 각각의 칸에는 정수가 하나 쓰여 있다.

테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성하시오.
테트로미노는 반드시 한 정사각형이 정확히 하나의 칸을 포함하도록 놓아야 하며, 회전이나 대칭을 시켜도 된다.

입력
첫째 줄에 종이의 세로 크기 N과 가로 크기 M이 주어진다. (4 ≤ N, M ≤ 500)
둘째 줄부터 N개의 줄에 종이에 쓰여 있는 수가 주어진다.
i번째 줄의 j번째 수는 위에서부터 i번째 칸, 왼쪽에서부터 j번째 칸에 쓰여 있는 수이다.
입력으로 주어지는 수는 1,000을 넘지 않는 자연수이다.

출력
첫째 줄에 테트로미노가 놓인 칸에 쓰인 수들의 합의 최댓값을 출력한다.

N, M, map[N][M]

deque <pair <int, int>> bolckPos[13];


2. Input()
	N, M, map[N][M], 19개 블록 x+a, y+b 추가
3. Solution()
	int sX, sY;
	for(sX =0; sX <N; sX++){
	for(sY=0; sY <M; sY++){
	simualtion(sX, sY);
	}
	cout <<Answer<<endl;


* void simulation(int sX, int sY){
	int nX, nY, tmpSum, flag =0;
	for(int i=0; i<13; i++) {
	tmpSum = 0, flag = 0;
	for(int j=0; j<blockPos[i].size(); j++){
	nX= sX+blockPos[i][j].first, nY= sY + blockPos[i][j].second;
	if(!inRange(nX, nY)){
	flag =1;
	break;
	}
	tmpSum = tmpSum + map[nX][nY];
	}
	if(flag==0 && Answer < tmpSum) Answer = tmpSum;
	}
	}

완전 노가다로 풀었네 ㅜㅜ

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
int map[501][501];

deque <pair <int, int>> blockPos[19];

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy <= M) return true;
	return false;
}

void simulation(int sX, int sY) {
	int nX, nY, tmpSum, flag = 0;
	for (int i = 0; i < 19; i++) {
		tmpSum = map[sX][sY], flag = 0;
		for (int j = 0; j < blockPos[i].size(); j++) {
			nX = sX + blockPos[i][j].first, nY = sY + blockPos[i][j].second;
			if (!inRange(nX, nY)) {
				flag = 1;
				break;
			}
			tmpSum = tmpSum + map[nX][nY];
		}
		if (flag == 0 && Answer < tmpSum) Answer = tmpSum;
	}
}

void Solution() {
	int sX, sY;
	for (sX = 0; sX < N; sX++) {
		for (sY = 0; sY < M; sY++) {
			simulation(sX, sY);
		}
	}
	cout << Answer << endl;
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= 3; i++) {
		blockPos[0].push_back(make_pair(0, i));
	}
	for (int i = 1; i <= 3; i++) {
		blockPos[1].push_back(make_pair(i, 0));
	}

	blockPos[2].push_back(make_pair(0, 1));
	blockPos[2].push_back(make_pair(1, 0));
	blockPos[2].push_back(make_pair(1, 1));

	blockPos[3].push_back(make_pair(1, 0));
	blockPos[3].push_back(make_pair(2, 0));
	blockPos[3].push_back(make_pair(2, 1));

	blockPos[4].push_back(make_pair(1, 0));
	blockPos[4].push_back(make_pair(0, 1));
	blockPos[4].push_back(make_pair(0, 2));

	blockPos[5].push_back(make_pair(0, 1));
	blockPos[5].push_back(make_pair(1, 1));
	blockPos[5].push_back(make_pair(2, 1));

	blockPos[6].push_back(make_pair(0, 1));
	blockPos[6].push_back(make_pair(0, 2));
	blockPos[6].push_back(make_pair(-1, 2));

	blockPos[7].push_back(make_pair(1, 0));
	blockPos[7].push_back(make_pair(1, 1));
	blockPos[7].push_back(make_pair(2, 1));

	blockPos[8].push_back(make_pair(0, 1));
	blockPos[8].push_back(make_pair(-1, 1));
	blockPos[8].push_back(make_pair(-1, 2));

	blockPos[9].push_back(make_pair(0, 1));
	blockPos[9].push_back(make_pair(1, 1));
	blockPos[9].push_back(make_pair(0, 2));

	blockPos[10].push_back(make_pair(1, 0));
	blockPos[10].push_back(make_pair(1, 1));
	blockPos[10].push_back(make_pair(2, 0));

	blockPos[11].push_back(make_pair(0, 1));
	blockPos[11].push_back(make_pair(-1, 1));
	blockPos[11].push_back(make_pair(0, 2));

	blockPos[12].push_back(make_pair(0, 1));
	blockPos[12].push_back(make_pair(-1, 1));
	blockPos[12].push_back(make_pair(1, 1));

	blockPos[13].push_back(make_pair(0, 1));
	blockPos[13].push_back(make_pair(-1, 1));
	blockPos[13].push_back(make_pair(-2, 1));

	blockPos[14].push_back(make_pair(1, 0));
	blockPos[14].push_back(make_pair(1, 1));
	blockPos[14].push_back(make_pair(1, 2));

	blockPos[15].push_back(make_pair(0, 1));
	blockPos[15].push_back(make_pair(1, 0));
	blockPos[15].push_back(make_pair(2, 0));

	blockPos[16].push_back(make_pair(0, 1));
	blockPos[16].push_back(make_pair(0, 2));
	blockPos[16].push_back(make_pair(1, 2));

	blockPos[17].push_back(make_pair(1, 0));
	blockPos[17].push_back(make_pair(0, 1));
	blockPos[17].push_back(make_pair(-1, 1));

	blockPos[18].push_back(make_pair(0, 1));
	blockPos[18].push_back(make_pair(1, 1));
	blockPos[18].push_back(make_pair(1, 2));
}


int main(void) {
	Input();
	Solution();
	return 0;
}