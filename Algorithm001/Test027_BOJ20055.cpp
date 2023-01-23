/* 
0'28''22'''
길이가 N인 컨베이어 벨트가 있고, 길이가 2N인 벨트가 이 컨베이어 벨트를 위아래로 감싸며 돌고 있다.
벨트는 길이 1 간격으로 2N개의 칸으로 나뉘어져 있으며, 각 칸에는 아래 그림과 같이 1부터 2N까지의 번호가 매겨져 있다.

벨트가 한 칸 회전하면 1번부터 2N-1번까지의 칸은 다음 번호의 칸이 있는 위치로 이동하고,
2N번 칸은 1번 칸의 위치로 이동한다. i번 칸의 내구도는 Ai이다.
위의 그림에서 1번 칸이 있는 위치를 "올리는 위치", N번 칸이 있는 위치를 "내리는 위치"라고 한다.

컨베이어 벨트에 박스 모양 로봇을 하나씩 올리려고 한다. 로봇은 올리는 위치에만 올릴 수 있다.
언제든지 로봇이 내리는 위치에 도달하면 그 즉시 내린다. 로봇은 컨베이어 벨트 위에서 스스로 이동할 수 있다.
로봇을 올리는 위치에 올리거나 로봇이 어떤 칸으로 이동하면 그 칸의 내구도는 즉시 1만큼 감소한다.

컨베이어 벨트를 이용해 로봇들을 건너편으로 옮기려고 한다. 로봇을 옮기는 과정에서는 아래와 같은 일이 순서대로 일어난다.

1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.
   만약 이동할 수 없다면 가만히 있는다.
	1. 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.

종료되었을 때 몇 번째 단계가 진행 중이었는지 구해보자. 가장 처음 수행되는 단계는 1번째 단계이다.

입력
첫째 줄에 N, K가 주어진다. 둘째 줄에는 A1, A2, ..., A2N이 주어진다.

출력
몇 번째 단계가 진행 중일때 종료되었는지 출력한다.

제한
2 ≤ N ≤ 100
1 ≤ K ≤ 2N
1 ≤ Ai ≤ 1,000

N, K, exitFlag, Answer;

struct State { int state, int robot}
deque <int> belt

1. Input()
	N, K, belt에 내구도 삽입

2. Solution()
	1) while(1)
	2) time++;
	3) move_belt() -> pop_back() & push_front()
	4) move_robot()
		1) 특수 case  i= N-1에 로봇 있으면 아웃
		2) i = N-2 ~ 0까지 해당 idx에 로봇 있고, 다음 칸에 내구도 >= 1 이면  로봇 옮기기
		3) 특수 case -> i = N-2 로봇이 이동하면 바로 belt[N-1].state = 0;
	5) start_robot()
		1) i = 0에 로봇 없으면, 로봇 올리기
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, K, Answer = 0;

struct BeltInfo {
	int state;
	int robot;
};

deque <BeltInfo> dq;


int move_robot(int exitFlag) {
	if (dq[N - 1].robot == 1) dq[N - 1].robot = 0;

	for (int i = N - 2; i >= 1; i--) {
		if (dq[i].robot == 1 && dq[i+1].robot == 0 && dq[i + 1].state >= 1) {
			dq[i].robot = 0;
			dq[i + 1].state--;
			dq[i + 1].robot = 1;
			if (dq[i + 1].state == 0) exitFlag++;

			if (i == N - 2) dq[i + 1].robot = 0;
		}
	}

	if (dq[0].state > 0) {
		dq[0].robot = 1;
		dq[0].state--;
		if (dq[0].state == 0) exitFlag++;
	}
	return exitFlag;
}

void move_belt() {
	BeltInfo tmp;

	tmp = dq.back();
	dq.pop_back();

	dq.push_front(tmp);
}

void Solution() {
	int time = 0, exitFlag = 0;
	
	while (1) {
		time++;
		move_belt();
		exitFlag = move_robot(exitFlag);

		if (exitFlag >= K) break;
	}
	Answer = time;
	cout << Answer << endl;

}

void Input() {
	int tmp;
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++)	{
		cin >> tmp;
		dq.push_back({ tmp, 0 });
	} 
}

int main(void) {
	Input();
	Solution();
	return 0;
}