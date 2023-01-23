/*
3'00''10'''
마법사 상어는 그동안 배운 마법을 이용해 어항을 정리하려고 한다. 어항은 정육면체 모양이고,
한 변의 길이는 모두 1이다. 상어가 가지고 있는 어항은 N개이고, 가장 처음에 어항은 일렬로 바닥 위에 놓여져 있다.
어항에는 물고기가 한 마리 이상 들어있다.
<그림 1>은 어항 8개가 바닥 위에 놓여있는 상태이며, 칸에 적힌 값은 그 어항에 들어있는 물고기의 수이다.
편의상 어항은 정사각형으로 표현했다.


어항을 한 번 정리하는 과정은 다음과 같이 이루어져 있다.
먼저, 물고기의 수가 가장 적은 어항에 물고기를 한 마리 넣는다.
만약, 그러한 어항이 여러개라면 물고기의 수가 최소인 어항 모두에 한 마리씩 넣는다.
위의 예시의 경우 물고기의 수가 가장 적은 어항에는 물고기가 2마리 있고, 그러한 어항은 2개가 있다.
따라서, 2개의 어항에 물고기를 한 마리씩 넣어 <그림 2>와 같아진다.

이제 어항을 쌓는다. 먼저, 가장 왼쪽에 있는 어항을 그 어항의 오른쪽에 있는 어항의 위에 올려 놓아 <그림 3>이 된다.

이제, 2개 이상 쌓여있는 어항을 모두 공중 부양시킨 다음, 전체를 시계방향으로 90도 회전시킨다.
이후 공중 부양시킨 어항을 바닥에 있는 어항의 위에 올려놓는다.
바닥의 가장 왼쪽에 있는 어항 위에 공중 부양시킨 어항 중 가장 왼쪽에 있는 어항이 있어야 한다.
이 작업은 공중 부양시킨 어항 중 가장 오른쪽에 있는 어항의 아래에 바닥에 있는 어항이 있을때까지 반복한다.

먼저, <그림 4>와 같이 어항이 놓인 상태가 변하고, 한 번 더 변해서 <그림 5>가 된다.

<그림 5>에서 한 번 더 어항을 공중 부양시키는 것은 불가능하다.
그 이유는 <그림 6>과 같이 공중 부양시킨 어항 중 가장 오른쪽에 있는 어항의 아래에 바닥에 있는 어항이 없기 때문이다.

공중 부양 작업이 모두 끝나면, 어항에 있는 물고기의 수를 조절한다.

모든 인접한 두 어항에 대해서, 물고기 수의 차이를 구한다. 이 차이를 5로 나눈 몫을 d라고 하자.
d가 0보다 크면, 두 어항 중 물고기의 수가 많은 곳에 있는 물고기 d 마리를 적은 곳에 있는 곳으로 보낸다.
이 과정은 모든 인접한 칸에 대해서 동시에 발생한다. 이 과정이 완료되면 <그림 7>이 된다.

이제 다시 어항을 바닥에 일렬로 놓아야 한다. 가장 왼쪽에 있는 어항부터, 그
리고 아래에 있는 어항부터 가장 위에 있는 어항까지 순서대로 바닥에 놓아야 한다.
<그림 8>이 바닥에 다시 일렬로 놓은 상태이다.

다시 공중 부양 작업을 해야 한다.
이번에는 가운데를 중심으로 왼쪽 N/2개를 공중 부양시켜 전체를 시계 방향으로 180도 회전 시킨 다음,
오른쪽 N/2개의 위에 놓아야 한다. 이 작업은 두 번 반복해야한다. 두 번 반복하면 바닥에 있는 어항의 수는 N/4개가 된다.
<그림 9>는 이 작업을 1번 했을 때, <그림 10>은 다시 한 번 더 했을 때이다.

여기서 다시 위에서 한 물고기 조절 작업을 수행하고, 바닥에 일렬로 놓는 작업을 수행한다.
<그림 10>에서 조절 작업을 마친 결과는 <그림 11>이 되고, 여기서 다시 바닥에 일렬로 놓는 작업을 수행하면
<그림 12>가 된다.


어항의 수 N, 각 어항에 들어있는 물고기의 수가 주어진다.
물고기가 가장 많이 들어있는 어항과 가장 적게 들어있는
어항의 물고기 수 차이가 K 이하가 되려면 어항을 몇 번 정리해야하는지 구해보자.

입력
첫째 줄에 N, K가 주어진다. 둘째에는 어항에 들어있는 물고기의 수가 가장 왼쪽에 있는 어항부터 순서대로 주어진다.

출력
 물고기가 가장 많이 들어있는 어항과 가장 적게 들어있는 어항의 물고기 수 차이가 K 이하가 되려면 어
항을 몇 번 정리해야하는지 출력한다.

제한
4 ≤ N ≤ 100
N은 4의 배수
0 ≤ K ≤ 10
1 ≤ 각 어항에 들어있는 물고기의 수 ≤ 10,000

N, K
deque <int> fishball[100];
int dx[4], dy[4] = 상, 하, 좌, 우

1. Input()
	N, K, fishball[0].push_back()
2. Solution()
	1. int time;
	2. while(1)
	3) time++;
	4) pour_fish()
		1) deque <pair <int, int>> dq;
		2) deque <int> tmp;
		3) for(idx=0; idx <fishball[0].size(); idx++) tmp.push(fishball[i][idx]);
		4) sort(tmp.begin(), tmp.end(), compare);
		2) int min = tmp[0];
		3) for(idx=0; idx <fishball[0].size(); idx++)
		4) if(fishball[0][i] == min) fishball[0][i]++;
		5) while(1) tmp.pop_front();
	5) fishball[1].push_back(fishball[0].front());
	6) fishball[0].pop_front();
	7) int upside_fishball(int rowSize, int cnt)
		1) int topRow, bottomRow, row, col
		2) if(cnt == 0) topRow = rowSize;
		3) else if(cnt ==1) topRow = rowSize +1;
		3) bottomRow = fishball[0].size() - fishball[1].size();
		4) if(topRow > botomRow) return 1;
		5) deque <int> dq;
		6) int colSize = fishball[rowSize - 1].size();
		6) for(col =0; col < colSize; col++)
		6) for(row =0; row <rowSize; row++)
		7) dq.push(fishball[row].front()), fishball[row].pop_front();
		9) for(row = topRow; row>=0 ; row--)
		10) for(col=0; col <fishball[0].size(); col++)
		11) fishball[row].pop_back(dq.front()) dq.pop_front();
	8) int sim(int topRow)
		1) int sR, sC, rowSize, colSize
		2)

* find_diff(){

}

12 7
5 2 3 14 9 2 11 8 9 10 11 12
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, K, Answer = 0;
deque <int> fishball[100];

int dx[2] = { 0, 1};
int dy[2] = { 1, 0 };

void print_info(int maxRow) {
	cout << "어항 정보" << endl;
	for (int i = maxRow - 1; i >= 0; i--) {
		cout << i << "번째 Row : ";
		for (int j = 0; j < fishball[i].size(); j++) {
			cout << fishball[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool compare(pair <int, int> a, pair<int, int> b) {
	return a.first < b.first;
}

int find_diff() {
	int idx;
	deque <pair <int, int>> tmp;
	for (idx = 0; idx < fishball[0].size(); idx++) {
		tmp.push_back(make_pair(fishball[0][idx], idx));
	}
	sort(tmp.begin(), tmp.end(), compare);

	int min = tmp[0].first;
	int max = tmp[tmp.size() - 1].first;

	int diff = max - min;
	return diff;
}

void pour_fish() {
	int idx;
	deque <pair <int, int>> tmp;
	for (idx = 0; idx < fishball[0].size(); idx++) {
		tmp.push_back(make_pair(fishball[0][idx], idx));
	}
	sort(tmp.begin(), tmp.end(), compare);
	int min = tmp[0].first, tmpVal;

	while (!tmp.empty()) {
		tmpVal = tmp.front().first;
		idx = tmp.front().second;
		tmp.pop_front();
		if (tmpVal != min) continue;
		fishball[0][idx]++;
	}

}

int upside_fishball(int rowSize, int cnt) {
	int topRow, bottomRow, row, col, colSize;
	topRow = rowSize;
	bottomRow = fishball[0].size() - fishball[rowSize - 1].size();
	if (topRow > bottomRow) return -1;
	deque <int> dq;
	colSize = fishball[rowSize - 1].size();
	for (col = 0; col < colSize; col++) {
		for (row = 0; row < rowSize; row++) {
			dq.push_back(fishball[row].front());
			fishball[row].pop_front();
		}
	}

	if (cnt == 0) colSize++;
	else if(cnt == 1) topRow++;

	for (row = topRow - 1; row > 0; row--) {
		for (col = 0; col < colSize; col++) {
			fishball[row].push_back(dq.front());
			dq.pop_front();
		}
	}
	return topRow;
}

struct SimPos {
	int x, y, cnt;
	SimPos(int x, int y, int cnt) {
		this->x = x;
		this->y = y;
		this->cnt = cnt;
	}
};

bool inRange(int x, int y, int xSize, int ySize) {
	if (x < 0 || x >= xSize || y < 0 || y >= ySize) return false;
	return true;
}

void sim(int topRow) {
	int sR, sC, sF, nR, nC, nF, diff, rowSize, colSize;

	deque <SimPos> dq;

	rowSize = topRow;
	colSize = fishball[0].size();

	for (int row = 0; row < rowSize; row++) {
		colSize = fishball[row].size();
		for (int col = 0; col < colSize; col++) {

			sR = row, sC = col, sF = fishball[sR][sC];
			for (int d = 0; d < 2; d++) {
				nR = sR + dx[d];
				nC = sC + dy[d];
				if (!inRange(nR, nC, rowSize, colSize)) continue;
				if (nC >= fishball[nR].size()) continue;
				nF = fishball[nR][nC], diff = 0;
				diff = (int) abs(sF - nF) / 5;
				if (diff == 0) continue;

				if (nF > sF) {
					dq.push_back({ nR, nC, -diff });
					dq.push_back({ sR, sC, diff });
				}
				else {
					dq.push_back({ nR, nC, diff });
					dq.push_back({ sR, sC, -diff });
				}

			}
		}
	}
	

	while (!dq.empty()) {
		sR = dq.front().x, sC = dq.front().y, diff = dq.front().cnt;
		dq.pop_front();
		fishball[sR][sC] = fishball[sR][sC] + diff;
	}
}

void resize_map(int topRow) {
	int row, col, rowSize, colSize;

	colSize = fishball[0].size();
	rowSize = topRow;

	deque <int> dq;

	for (col = 0; col < colSize; col++) {
		for (row = 0; row < rowSize; row++) {
			if (fishball[row].size() == 0) break;
			dq.push_back(fishball[row].front());
			fishball[row].pop_front();
		}
	}

	while (!dq.empty()) {
		fishball[0].push_back(dq.front());
		dq.pop_front();
	}

}

void sim2() {
	deque <int> dq;

	int row, col;

	int sC = (fishball[0].size() / 2) -1;

	for (col = sC; col >= 0; col--) {
		dq.push_back(fishball[0][col]);
	}
	for (int col = 0; col <= sC; col++) {
		fishball[0].pop_front();
		fishball[1].push_back(dq.front());
		dq.pop_front();
	}
	sC = (fishball[0].size() / 2) - 1;
	for (row = 1; row >= 0; row--) {
		for (col = sC; col >= 0; col--) {
			dq.push_back(fishball[row][col]);
		}
	}

	for (int row = 2; row <= 3; row++) {
		for (col = 0; col <= sC; col++) {
			if(row==2) fishball[1].pop_front();
			else if(row==3) fishball[0].pop_front();
			fishball[row].push_back(dq.front());
			dq.pop_front();
		}
	}

}

void Solution() {
	int time =0, diff;
	Answer = 0;
	diff = find_diff();
	if (diff <= K) return;

	int rSize, topRow, flag;
	while (1) {
		time++;
		pour_fish();
		
		//1번 쌓아올림
		fishball[1].push_back(fishball[0].front());
		fishball[0].pop_front();
		rSize = 2;
		while (1) {
			for (int i = 0; i < 2; i++) {
				flag = upside_fishball(rSize, i);
				if (flag ==  - 1) break;
				else topRow = flag;
			}
			if (flag == -1) break;
			rSize++;
		}
		//print_info(topRow);
		sim(topRow);
		//print_info(topRow);
		resize_map(topRow);
		//print_info(1);
		sim2();
		topRow = 4;
		//print_info(topRow);
		sim(topRow);
		//print_info(topRow);
		resize_map(topRow);
		diff = find_diff();
		//print_info(topRow);
		diff = find_diff();
		if (diff <= K) {
			Answer = time;
			break;
		}
	}
	cout << Answer << endl;
}

void Input() {
	int tmp;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		fishball[0].push_back(tmp);
	}
}

int main(void) {
	Input();
	Solution();
	return 0;
}