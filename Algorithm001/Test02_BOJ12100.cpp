/*
����
2048 ������ 4��4 ũ���� ���忡�� ȥ�� ���� ����ִ� �����̴�. �� ��ũ�� ������ ������ �غ� �� �ִ�.

�� ���ӿ��� �� ���� �̵��� ���� ���� �ִ� ��ü ����� �����¿� �� ���� �� �ϳ��� �̵���Ű�� ���̴�.
�̶�, ���� ���� ���� �� ����� �浹�ϸ� �� ����� �ϳ��� �������� �ȴ�.
�� ���� �̵����� �̹� ������ ����� �� �ٸ� ��ϰ� �ٽ� ������ �� ����.
(���� ���ӿ����� �̵��� �� �� �� ������ ����� �߰�������, �� �������� ����� �߰��Ǵ� ���� ����)

<�׸� 1>�� ��쿡�� ���� ����� �̵���Ű�� <�׸� 2>�� ���°� �ȴ�.
���⼭, �������� ����� �̵���Ű�� <�׸� 3>�� ���°� �ȴ�.

����������, �Ȱ��� ���� �� ���� �ִ� ��쿡�� �̵��Ϸ��� �ϴ� ���� ĭ�� ���� ��������.
���� ���, ���� �̵���Ű�� ��쿡�� ���ʿ� �ִ� ����� ���� �������� �ȴ�.
<�׸� 14>�� ��쿡 ���� �̵��ϸ� <�׸� 15>�� �����.

�� �������� �ٷ�� 2048 ������ ������ ũ�Ⱑ N��N �̴�.
������ ũ��� �������� ��� ���°� �־����� ��,
�ִ� 5�� �̵��ؼ� ���� �� �ִ� ���� ū ����� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� ������ ũ�� N (1 �� N �� 20)�� �־�����. ��° �ٺ��� N���� �ٿ��� �������� �ʱ� ���°� �־�����.
 0�� �� ĭ�� ��Ÿ����, �̿��� ���� ��� ����� ��Ÿ����.
��Ͽ� ���� �ִ� ���� 2���� ũ�ų� ����, 1024���� �۰ų� ���� 2�� �������̴�. ����� ��� �ϳ� �־�����.

���
�ִ� 5�� �̵����Ѽ� ���� �� �ִ� ���� ū ����� ����Ѵ�.

int N, Answer;
int map[21][21], copyMap[21][21];
int arr[6];
deque <pair <int, int>> dq;

Input()
	N, map[21][21];
Solution()
	1) for(int i=1; i<=4; i) arr[0] = i, DFS(1);


	1) DFS(int cnt) -> 1: ��, 2: ��, 3: ��, 4: ��
		if(cnt==5)
		copy_map()

		break;
		for(int i=1; i<=4; i++)
			arr[cnt] = i;
			DFS(cnt+1)

	2) simulation(int d)
		int tmp;
		switch(d)
			case 1:
				for(int yy=0; yy<N; yy++){
				for(int xx=0; xx<N; xx++){
					if(copyMap[xx][yy] == 0) continue;
					if(dq.size() ==0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
					}
					tmp = dq.size() -1;
					if(dq[tmp].second==0 && dq[tmp].first == copyMap[xx][yy]) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
					}
					else{
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
					}
				}
				for(int xx=0; xx<N; xx++){
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if(dq.size() ==0) break;
				}
				}
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
int map[21][21], copyMap[21][21];
int dir[6];

deque <pair<int, int>> dq;

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void find_answer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Answer < copyMap[i][j]) Answer = copyMap[i][j];
		}
	}
}

int simulation(int time) {
	int d, tmp, cnt, change;
	d = dir[time];
	cnt = 0, change = 0;
	switch (d) {
	case 1: //��
		for (int yy = 0; yy < N; yy++) {
			for (int xx = 0; xx < N; xx++) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int xx = 0; xx < N; xx++) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 2: //��
		for (int yy = 0; yy < N; yy++) {
			for (int xx = N-1; xx >= 0 ; xx--) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int xx = N - 1; xx >= 0; xx--) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 3: //��
		for (int xx = 0; xx < N; xx++) {
			for (int yy = 0; yy < N; yy++) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int yy = 0; yy < N; yy++) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	case 4: //��
		for (int xx = 0; xx < N; xx++) {
			for (int yy = N - 1; yy >= 0; yy--) {
				if (copyMap[xx][yy] == 0) continue;
				cnt++;
				if (dq.size() == 0) {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
					continue;
				}
				tmp = dq.size() - 1;
				if (dq[tmp].first == copyMap[xx][yy] && dq[tmp].second == 0) {
					dq[tmp].first = dq[tmp].first + copyMap[xx][yy];
					dq[tmp].second = 1;
					copyMap[xx][yy] = 0;
				}
				else {
					dq.push_back(make_pair(copyMap[xx][yy], 0));
					copyMap[xx][yy] = 0;
				}
			}
			change = cnt - dq.size();
			if (dq.size() == 0) continue;
			for (int yy = N - 1; yy >= 0; yy--) {
				copyMap[xx][yy] = dq.front().first;
				dq.pop_front();
				if (dq.size() == 0) break;
			}
		}
		break;
	}

	return change;
}

void DFS(int cnt) {
	if (cnt == 5) {
		int retFlag = 0;
		copy_map();
		for (int i = 0; i < cnt; i++) {
			retFlag = 0;
			retFlag += simulation(i);
			//if(retFlag == 0) break;
			//print_map();
		}
		find_answer();

		return;
	}

	for (int i = 1; i <= 4; i++) {
		dir[cnt] = i;
		DFS(cnt + 1);
	}
}

void Solution() {
	for (int i = 1; i <= 4; i++) {
		dir[0] = i;
		DFS(1);
	}
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}