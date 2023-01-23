/*
K���� ���� ����ħ -> � K���� �����ľ� ���� �� �ִ� �ܾ��� ������ �ִ�����?
������ ��� �ܾ� -> 'anta'�� ���� & 'tica'�� ������ -> ���� �ܾ�� N�� �ۿ� ���ٰ� ����
���� �� �ִ� �ܾ��� �ִ��� ���ϴ� ���α׷�

N, K(N�� 50���� �۰ų� ���� �ڿ����̰�, K�� 26���� �۰ų� ���� �ڿ��� �Ǵ� 0�̴�.)
��° �ٺ��� N���� �ٿ� ���� ����� �ܾ� -> �ҹ��ڷ� ���� & ���̴� 8���� ũ�ų� ����, 15���� �۰ų� ����

=> anta tica -> a, n, t, i, c (a : 97 ~ z : 122) -> (a : 0 ~ z : 25)

1. K <= 5�̸� �� �� �ִ� ���� 0��
2. K >5 �̸� Ž��
	1) �� ���ں��� ������ char ���ڸ� �� -> strArr[str.at(i)]++
	2) DFS�� Ž�� (0 ~ N���� Ž��(�ش� ���ڿ� �ʿ��� ���ĺ� ���� K�� �̻��̸� ���� ����), cnt == K �� ���� ���ϰ� �ִ��� Answer�� ����)

-> ���� ��Ʈ��ŷ���� Ǯ����Ѵ�....	
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

	cout << "���� ������ ���ĺ� : ";
	for (int j = 0; j < 26; j++) {
		if (a[j] == 0) continue;
		cout << (char)(j + 97) << ", ";
	}
	cout << endl;
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << i << "��° ����" << endl;
		for (int j = 0; j < 26; j++) {
			if (strArr[i][j] == 0) continue;
			cout << (char)(j + 97) << "�� ����: " << strArr[i][j] << endl;
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