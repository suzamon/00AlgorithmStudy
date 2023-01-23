/*
����
�������̳�� ũ�Ⱑ 1��1�� ���簢���� ���� �� �̾ ���� �����̸�, ������ ���� ������ �����ؾ� �Ѵ�.

���簢���� ���� ��ġ�� �� �ȴ�.
������ ��� ����Ǿ� �־�� �Ѵ�.
���簢���� ������ ����Ǿ� �־�� �Ѵ�. ��, �������� �������� �´�� ������ �� �ȴ�.
���簢�� 4���� �̾� ���� �������̳�� ��Ʈ�ι̳��� �ϸ�, ������ ���� 5������ �ִ�.

�Ƹ��̴� ũ�Ⱑ N��M�� ���� ���� ��Ʈ�ι̳� �ϳ��� �������� �Ѵ�.
���̴� 1��1 ũ���� ĭ���� �������� ������, ������ ĭ���� ������ �ϳ� ���� �ִ�.

��Ʈ�ι̳� �ϳ��� ������ ���Ƽ� ��Ʈ�ι̳밡 ���� ĭ�� ���� �ִ� ������ ���� �ִ�� �ϴ� ���α׷��� �ۼ��Ͻÿ�.
��Ʈ�ι̳�� �ݵ�� �� ���簢���� ��Ȯ�� �ϳ��� ĭ�� �����ϵ��� ���ƾ� �ϸ�, ȸ���̳� ��Ī�� ���ѵ� �ȴ�.

�Է�
ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (4 �� N, M �� 500)
��° �ٺ��� N���� �ٿ� ���̿� ���� �ִ� ���� �־�����.
i��° ���� j��° ���� ���������� i��° ĭ, ���ʿ������� j��° ĭ�� ���� �ִ� ���̴�.
�Է����� �־����� ���� 1,000�� ���� �ʴ� �ڿ����̴�.

���
ù° �ٿ� ��Ʈ�ι̳밡 ���� ĭ�� ���� ������ ���� �ִ��� ����Ѵ�.

N, M, map[N][M]

deque <pair <int, int>> bolckPos[13];


2. Input()
	N, M, map[N][M], 19�� ��� x+a, y+b �߰�
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

���� �밡�ٷ� Ǯ���� �̤�

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