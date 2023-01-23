/*
K개의 글자 가르침 -> 어떤 K개를 가르쳐야 읽을 수 있는 단어의 갯수가 최대인지?
남극의 모든 단어 -> 'anta'로 시작 & 'tica'로 끝난다 -> 남극 단어는 N개 밖에 없다고 가정
읽을 수 있는 단어의 최댓값을 구하는 프로그램

N, K(N은 50보다 작거나 같은 자연수이고, K는 26보다 작거나 같은 자연수 또는 0이다.)
둘째 줄부터 N개의 줄에 남극 언어의 단어 -> 소문자로 구성 & 길이는 8보다 크거나 같고, 15보다 작거나 같다

=> anta tica -> a, n, t, i, c (a : 97 ~ z : 122) -> (a : 0 ~ z : 25)

1. K <= 5이면 알 수 있는 문자 0개
2. K >5 이면 탐색
	1) 각 문자별로 각각의 char 숫자를 샘 -> strArr[str.at(i)]++
	2) DFS로 탐색 (0 ~ N까지 탐색(해당 문자에 필요한 알파벳 수가 K개 이상이면 다음 순서), cnt == K 면 정답 구하고 최댓값을 Answer에 저장)

-> 실패 백트래킹으로 풀어야한다....	
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, Answer = 0;
int strArr[50][26];

int a[26] = { 0, };

void print() {

	cout << "현재 선택한 알파벳 : ";
	for (int j = 0; j < 26; j++) {
		if (a[j] == 0) continue;
		cout << (char)(j + 97) << ", ";
	}
	cout << endl;
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << i << "번째 문자" << endl;
		for (int j = 0; j < 26; j++) {
			if (strArr[i][j] == 0) continue;
			cout << (char)(j + 97) << "의 숫자: " << strArr[i][j] << endl;
		}
	}
}

void find_answer() {
	int flag, cnt = 0;
	for (int i = 0; i < N; i++) {
		flag = 0;
		for (int j = 0; j < 26; j++) {
			if (strArr[i][j] > 0 && a[j] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) cnt++;
	}

	Answer = max(Answer, cnt);
}

int reset_char(int idx, int cnt) {
	for (int j = 0; j < 26; j++) {
		if (strArr[idx][j] > 0 && a[j] > 0) {
			a[j]--;
			if (a[j] == 0) cnt--;
		}
	}
	return cnt;
}

int add_char(int idx, int cnt) {
	for (int j = 0; j < 26; j++) {
		if (strArr[idx][j] > 0) {
			a[j]++;
			if(a[j] == 1 && cnt < K) cnt++;
		}

		if (cnt == K) break;
	}
	return cnt;
}

int find_cnt(int idx) {
	int cnt = 0;

	for (int j = 0; j < 26; j++) {
		if (strArr[idx][j] > 0 && a[j] == 0) cnt++;
	}

	return cnt;
}

void DFS(int startIdx, int cnt) {
	if (startIdx == N || cnt >= K) {
		//print();
		find_answer();
		return;
	}
	int nextA[26] = { 0, };
	for (int i = startIdx; i < N; i++) {
		//cnt = add_char(i, cnt);
		for (int j = 0; j < 26; j++) {
			if (strArr[i][j] > 0 && a[j] == 0) {
				a[j]++;
				nextA[j]++;
				if (a[j] == 1 && cnt < K) cnt++;
			}

			if (cnt == K) break;
		}


		DFS(i + 1, cnt);
		//cnt = reset_char(i, cnt);
		for (int j = 0; j < 26; j++) {
			if (nextA[j] > 0) {
				a[j]--;
				nextA[j]--;
				if (a[j] == 0) cnt--;
			}
		}
	}


}

void Solution() {
	if (K < 5) {
		Answer = 0;
		return;
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt = find_cnt(i);
		if (cnt > K) continue;
		cnt = add_char(i, 0);

		DFS(i + 1, cnt);

		cnt = reset_char(i, cnt);
	}
}

void Input() {
	string strTmp;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> strTmp;
		for (int j = 0; j < strTmp.length(); j++) {
			strArr[i][(strTmp.at(j) - 97)]++;
		}
	}
}

int main(void) {

	Input();
	Solution();
	cout << Answer << endl;

	return 0;
}