#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

int N, M, numCnt;
int arr[7];
deque <pair <int, int>> d;

void print_arr() {
	for (int i = numCnt - 1; i >= 0; i--) {
		cout << arr[i];
	}
	cout << endl;
}

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	return a.first < b.first;
}

int find_repeat_num() {
	int beforeValue = -1;
	for (int i = numCnt - 1; i >= 0; i--) {
		if (beforeValue == d[i].first) {
			return 1;
		}
		else {
			beforeValue = d[i].first;
		}
	}
	return 0;
}

int change_num(int state) {
	if (state == 3) return 3;
	else if (state == 2) {
		int tmp = arr[0];
		arr[0] = arr[1];
		arr[1] = tmp;
		return 1;
	}

	int orignalIdx, changeIdx, tmpCnt, changeNum1, changeNum2;

	tmpCnt = 0;
	for (int i = numCnt - 1; i >= 0; i--) {
		orignalIdx = d[i].second;
		if (orignalIdx == i) {
			tmpCnt++;
			continue;
		}

		changeIdx = i;
		changeNum1 = d[i].first;
		break;
	}

	if (tmpCnt == numCnt) {
		int beforeValue = -1;

		if (state == 1) return 3;

		int tmp = arr[0];
		arr[0] = arr[1];
		arr[1] = tmp;
		return 2;

	}
	else {
		
		if (state == 1) {
			int changeNumCnt = 0, changeIdx2;
			for (int i = numCnt - 1; i >= 0; i--) {
				if (d[i].first == changeNum1) {
					changeNumCnt++;
					if (changeNumCnt > 2) break;
				}
			}

			if (changeNumCnt > 1) {
				for (int i = 0; i < numCnt; i++) {
					if (d[i].second == changeIdx) {
						d[i].first = changeNum2;
						changeIdx2 = d[i].second;
						break;
					}
				}

				arr[changeIdx2] == changeNum1;


				for (int i = 0; i < numCnt; i++) {
					if (d[i].first == changeNum2) {
						changeNum2 = d[i].first;
						break;
					}
				}
			}
			else {
				for (int i = 0; i < numCnt; i++) {
					if (d[i].second == changeIdx) {
						d[i].second = orignalIdx;
						arr[orignalIdx] = d[i].first;
						break;
					}
				}
				d[changeIdx].second = changeIdx;
				arr[changeIdx] = d[changeIdx].first;
			}


		}

		for (int i = 0; i < numCnt; i++) {
			if (d[i].second == changeIdx) {
				d[i].second = orignalIdx;
				arr[orignalIdx] = d[i].first;
				break;
			}
		}
		d[changeIdx].second = changeIdx;
		arr[changeIdx] = d[changeIdx].first;

		return state;
	}

}

void Solution() {
	int state = find_repeat_num();

	for (int i = 0; i < M; i++) {
		state = change_num(state);
		cout << i + 1 << "번 교체" << endl;
		print_arr();
		
	}
}

void Input() {
	cin >> N;
	cin >> M;

	int tmp;
	numCnt = 0;
	while (1) {
		if (N / 10 == 0) {
			d.push_back(make_pair(N % 10, numCnt));
			arr[numCnt] = N % 10;
			numCnt++;
			break;
		}

		d.push_back(make_pair(N % 10, numCnt));
		arr[numCnt] = N % 10;
		N = N / 10;
		numCnt++;
	}

	sort(d.begin(), d.end(), compare);
	
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

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}