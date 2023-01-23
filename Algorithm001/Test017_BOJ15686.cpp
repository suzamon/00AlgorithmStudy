/*
크기가 N×N인 도시가 있다. 도시는 1×1크기의 칸으로 나누어져 있다. 도시의 각 칸은 빈 칸, 치킨집, 집 중 하나이다.
도시의 칸은 (r, c)와 같은 형태로 나타내고, r행 c열 또는 위에서부터 r번째 칸, 왼쪽에서부터 c번째 칸을 의미한다.
r과 c는 1부터 시작한다.

이 도시에 사는 사람들은 치킨을 매우 좋아한다. 따라서, 사람들은 "치킨 거리"라는 말을 주로 사용한다.
치킨 거리는 집과 가장 가까운 치킨집 사이의 거리이다.
즉, 치킨 거리는 집을 기준으로 정해지며, 각각의 집은 치킨 거리를 가지고 있다.
도시의 치킨 거리는 모든 집의 치킨 거리의 합이다.

임의의 두 칸 (r1, c1)과 (r2, c2) 사이의 거리는 |r1-r2| + |c1-c2|로 구한다.

이 도시에 있는 치킨집은 모두 같은 프랜차이즈이다. 프렌차이즈 본사에서는 수익을 증가시키기 위해 일부 치킨집을 폐업
오랜 연구 끝에 이 도시에서 가장 수익을 많이 낼 수 있는  치킨집의 개수는 최대 M개라는 사실을 알아내었다.

도시에 있는 치킨집 중에서 최대 M개를 고르고, 나머지 치킨집은 모두 폐업시켜야 한다.
어떻게 고르면, 도시의 치킨 거리가 가장 작게 될지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N(2 ≤ N ≤ 50)과 M(1 ≤ M ≤ 13)이 주어진다.
둘째 줄부터 N개의 줄에는 도시의 정보가 주어진다.
도시의 정보는 0, 1, 2로 이루어져 있고, 0은 빈 칸, 1은 집, 2는 치킨집을 의미한다. 집의 개수는 2N개를 넘지 않으며,
적어도 1개는 존재한다. 치킨집의 개수는 M보다 크거나 같고, 13보다 작거나 같다.

출력
첫째 줄에 폐업시키지 않을 치킨집을 최대 M개를 골랐을 때, 도시의 치킨 거리의 최솟값을 출력한다.

deque <int, int> chicken, int [101][2] house
deque <int> chickenDis[101] -> 각 집에서 각 치킨집의 거리 저장

N, M, map[N][N]

1. Input()
	N, M, map[N][N] -> 1이면, house에 2면, chicken에 저장
2. Solution()
	1) find_all_distance(startX, startY) : 각 집에서 각 치킨집까지의 거리 저장
	3) find_chicken(int cnt) : M개의 치킨 선택
		3-1) cnt == M이면, 각 집 별 치킨 거리 구하기
		3-2) totalDistance에 더해서 Answer이랑 비교
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, houseCnt = 0, Answer = 0;
int house[101][2];
int arr[14];
deque <pair <int, int>> chicken;
deque <int> chickenDis[101];

void find_all_distance(int houseIdx) {
	int startX = house[houseIdx][0];
	int startY = house[houseIdx][1];

	int nextX, nextY, distance;

	for (int chickenIdx = 0; chickenIdx < chicken.size(); chickenIdx++) {
		nextX = chicken[chickenIdx].first;
		nextY = chicken[chickenIdx].second;

		distance = abs(nextX - startX) + abs(nextY - startY);
		chickenDis[houseIdx].push_back(distance);
	}
}

void find_chicken(int start, int cnt) {
	if (cnt == M) {
		int totalDistance = 0, tmpDistance = 200;

		for (int i = 0; i < houseCnt; i++) {
			tmpDistance = 200;
			for (int j = 0; j < cnt; j++) {
				if (tmpDistance > chickenDis[i][arr[j]]) tmpDistance = chickenDis[i][arr[j]];
			}
			totalDistance = totalDistance + tmpDistance;
		}

		if (Answer == 0) Answer = totalDistance;
		else if(Answer > totalDistance) Answer = totalDistance;

		return;
	}

	for (int i = start; i < chicken.size(); i++) {
		arr[cnt] = i;
		find_chicken(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < houseCnt; i++) {
		find_all_distance(i);
	}

	for (int i = 0; i <= chicken.size() - M; i++) {
		find_chicken(0, 0);
	}

}

void Input() {
	int tmp;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			if (tmp == 1) {
				house[houseCnt][0] = i;
				house[houseCnt][1] = j;
				houseCnt++;
			}
			else if (tmp == 2) {
				chicken.push_back(make_pair(i, j));
			}
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}