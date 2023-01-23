/*
왼쪽이나 오른쪽 2 이상 공간이 확보될 떄, 조망권이 확보됨 -> 조망권이 확보된 세대의 수 반환

가로 길이는 항상 1000 이하, 맨왼쪽과 맨 오른쪽 두칸은 지어지지 않는다!

빌딩의 높이는 최대 255

1. Input() : buildingHight[1000], buildingCnt

2.Solution() : 1 ~ buildingCnt 까지
	1). 왼쪽 2칸 ~ 오른쪽 2칸까지 가장 큰 건물 높이 찾기
	2-1) 1)에서 구한 값이 자기 빌딩 크기보다 높으면 다음 건물로 이동
	2-2) 1)에서 구한 값이 자기 빌딩 크기보다 낮으면 (자기 건물 높이 - 가장 큰 건물의 높이)를 Answer에 저장
	*find_max_height(int stdHeight, int col) : col -2 ~ col+2 (col 제외)까지 가장 큰 건물 탐색 후 반환

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

int buildingHeight[1001];
int buildingCnt = 0, Answer = 0;

void reset_map() {
	for (int i = 1; i <= buildingCnt; i++) {
		buildingHeight[i] = 0;
	}
}

int find_max_height(int curHeight, int col) {

	int maxHeight = 0, tmpH;

	for (int i = col - 2; i <= col + 2; i++) {
		if (i == col) continue;
		if (i <= 0 && i > buildingCnt) continue;

		if (maxHeight < buildingHeight[i]) maxHeight = buildingHeight[i];
	}

	return maxHeight;
}

void Solution() {
	Answer = 0;

	int curHeight, nextHeight;
	for (int i = 3; i <= buildingCnt - 2 ; i++) {
		curHeight = buildingHeight[i];
		nextHeight = find_max_height(curHeight, i);

		if (curHeight > nextHeight) {
			Answer += (curHeight - nextHeight);
		}

	}

	reset_map();
}

void Input() {
	cin >> buildingCnt;

	for (int i = 1; i <= buildingCnt; i++) {
		cin >> buildingHeight[i];
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	T= 10;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}