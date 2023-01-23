/*
숫자 야구 게임은 2명이 하는 게임으로 다음과 같이 진행된다. 게임 참여자들을 Player 1과 Player 2로 나타낸다.

① Player 1은 중복되지 않는 숫자들로 구성된 4 자리의 수를 생각한다.
	(이 수를 생각하는 수라 하자. 생각하는 수는 0부터 시작할 수 있다.)
② Player 2는 중복되지 않는 숫자들로 구성된 4 자리의 수를 추측해서 물어본다.
	(이 수를 물어보는 수라 하자. 물어보는 수 또한 0부터 시작할 수 있다.)
③ Player 1은 생각하는 수와 물어보는 수를 비교해서 스트라이크와 볼의 개수를 알려준다.
④ 스트라이크의 개수는 생각하는 수와 물어보는 수가 같은 숫자를 가지고 있고 자리 위치까지 맞은 숫자의 개수이다.
⑤ 볼의 개수는 생각하는 수와 물어보는 수가 같은 숫자를 가지고 있지만 자리 위치는 서로 다른 숫자의 개수이다.
⑥ 만약 생각하는 수와 물어보는 수가 일치하면 게임이 끝난다.
⑦ 만약 생각하는 수와 물어보는 수가 일치하지 않으면 ②번으로 돌아가 과정들을 반복한다.

시뮬레이션에서는 Player 1이 컴퓨터가 되고 생각하는 수는 각 테스트 케이스로 주어진다.

query 함수를 이용하여 생각하는 수를 맞추도록 Player 2에 해당하는 doUserImplementation 함수 구현.

[입력]

입력 첫 줄에는 총 테스트 케이스 개수 T(1 ≤ T ≤ 50)가 주어진다.

그 다음 줄부터 테스트 케이스 T개가 온다. 각 테스트 케이스는 모두 1 줄로 구성되어 있다.

각 테스트 케이스의 첫 번째 줄에는 생각하는 수가 주어진다.

[제약 사항]
1. 생각하는 수는 4 자리의 수이다.
2. 생각하는 수는 0부터 9까지 중복되지 않는 숫자로 이루어진다.
3. 생각하는 수는 0부터 시작할 수 있다.
4. 각 테스트 케이스에서 query 함수의 호출한 횟수가 일정 수준 이하이고
생각하는 수와 guess 배열에 저장된 값이 일치하는 경우만 점수를 얻는다.
5. 동점자인 경우 query 함수를 호출한 총 횟수가 적을 수록 유리하다.

1. DFS(int cnt) :
	중복되지 않는 수 탐색, cnt==4면 return
2.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define N              4
#define MAX_QUERYCOUNT 1000000

static int digits[N];
static int digits_c[10];

static int T;

//extern void doUserImplementation(int guess[]);

//[0]~[3]:숫자,  [4]:스트라이크 개수,  [5]:볼 개수
int fail_data[10][6];
int dataCnt;
int* num;
int visited[10];

int isPossible() {
	int i, j;
	for (i = 0; i < dataCnt; i++) {
		int strike = 0, ball = 0;
		for (j = 0; j <= 3; j++) {
			// 자리와 숫자가 일치하는 경우
			if (fail_data[i][j] == num[j]) strike++;
			// 자리는 다르지만 숫자가 동일하게 존재하는 경우
			else if (visited[fail_data[i][j]]) ball++;
		}
		// strike 개수와 ball 개수가 완전히 일치하는지 확인
		// Query 호출하기전에 가지치기
		if ((fail_data[i][4] != strike) || (fail_data[i][5] != ball))
			return 0;
	}
	return 1;
}


int DFS(int cnt) {
	if (cnt == 4) {
		// query 함수 호출전에 검증된 데이터로 1차 필터
		if (!isPossible())
			return 0;

		Result ret = query(num);
		if (ret.strike == 4)
			return 1;

		// 검증된 실패 데이터 저장
		for (int i = 0; i <= 3; i++) 
			fail_data[dataCnt][i] = num[i];
		fail_data[dataCnt][4] = ret.strike;
		fail_data[dataCnt][5] = ret.ball;
		dataCnt++;

		return 0;
	}

	for (int i = 0; i <= 9; i++) {
		if (visited[i]) continue;

		visited[i] = 1;
		num[cnt] = i;
		if (DFS(cnt + 1)) {
			return 1;
		}
		visited[i] = 0;
	}
	return 0;
}

void doUserImplementation(int guess[]) {
	num = guess;
	dataCnt = 0;
	for (int i = 0; i <= 9; i++)
		visited[i] = 0;

	DFS(0);
}



static int querycount;

// the value of limit_query will be changed in evaluation
static const int limit_query = 2520;

typedef struct {
	int strike;
	int ball;
} Result;

static bool isValid(int guess[]) {
	int guess_c[10];

	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

// API : return a result for comparison with digits[] and guess[]
Result query(int guess[]) {
	Result result;

	if (querycount >= MAX_QUERYCOUNT) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	querycount++;

	if (!isValid(guess)) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	result.strike = 0;
	result.ball = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.strike++;
		else if (digits_c[guess[idx]] > 0)
			result.ball++;

	return result;
}

static void initialize() {
	for (int count = 0; count < 10; ++count) digits_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		char c;
		do scanf("%c", &c); while (c < '0' || c > '9');
		digits[idx] = c - '0';
		digits_c[digits[idx]]++;
	}

	querycount = 0;
}

static bool check(int guess[]) {
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx]) return false;
	return true;
}

int main() {
	int total_score = 0;
	int total_querycount = 0;;

	// freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; ++testcase) {
		initialize();

		int guess[N];
		doUserImplementation(guess);

		if (!check(guess)) querycount = MAX_QUERYCOUNT;
		if (querycount <= limit_query) total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
	}
	if (total_querycount > MAX_QUERYCOUNT) total_querycount = MAX_QUERYCOUNT;
	printf("total score = %d\ntotal query = %d\n", total_score * 100 / T, total_querycount);
	return 0;
}