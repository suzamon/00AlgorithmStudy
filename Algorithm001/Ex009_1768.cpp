/*
���� �߱� ������ 2���� �ϴ� �������� ������ ���� ����ȴ�. ���� �����ڵ��� Player 1�� Player 2�� ��Ÿ����.

�� Player 1�� �ߺ����� �ʴ� ���ڵ�� ������ 4 �ڸ��� ���� �����Ѵ�.
	(�� ���� �����ϴ� ���� ����. �����ϴ� ���� 0���� ������ �� �ִ�.)
�� Player 2�� �ߺ����� �ʴ� ���ڵ�� ������ 4 �ڸ��� ���� �����ؼ� �����.
	(�� ���� ����� ���� ����. ����� �� ���� 0���� ������ �� �ִ�.)
�� Player 1�� �����ϴ� ���� ����� ���� ���ؼ� ��Ʈ����ũ�� ���� ������ �˷��ش�.
�� ��Ʈ����ũ�� ������ �����ϴ� ���� ����� ���� ���� ���ڸ� ������ �ְ� �ڸ� ��ġ���� ���� ������ �����̴�.
�� ���� ������ �����ϴ� ���� ����� ���� ���� ���ڸ� ������ ������ �ڸ� ��ġ�� ���� �ٸ� ������ �����̴�.
�� ���� �����ϴ� ���� ����� ���� ��ġ�ϸ� ������ ������.
�� ���� �����ϴ� ���� ����� ���� ��ġ���� ������ ������� ���ư� �������� �ݺ��Ѵ�.

�ùķ��̼ǿ����� Player 1�� ��ǻ�Ͱ� �ǰ� �����ϴ� ���� �� �׽�Ʈ ���̽��� �־�����.

query �Լ��� �̿��Ͽ� �����ϴ� ���� ���ߵ��� Player 2�� �ش��ϴ� doUserImplementation �Լ� ����.

[�Է�]

�Է� ù �ٿ��� �� �׽�Ʈ ���̽� ���� T(1 �� T �� 50)�� �־�����.

�� ���� �ٺ��� �׽�Ʈ ���̽� T���� �´�. �� �׽�Ʈ ���̽��� ��� 1 �ٷ� �����Ǿ� �ִ�.

�� �׽�Ʈ ���̽��� ù ��° �ٿ��� �����ϴ� ���� �־�����.

[���� ����]
1. �����ϴ� ���� 4 �ڸ��� ���̴�.
2. �����ϴ� ���� 0���� 9���� �ߺ����� �ʴ� ���ڷ� �̷������.
3. �����ϴ� ���� 0���� ������ �� �ִ�.
4. �� �׽�Ʈ ���̽����� query �Լ��� ȣ���� Ƚ���� ���� ���� �����̰�
�����ϴ� ���� guess �迭�� ����� ���� ��ġ�ϴ� ��츸 ������ ��´�.
5. �������� ��� query �Լ��� ȣ���� �� Ƚ���� ���� ���� �����ϴ�.

1. DFS(int cnt) :
	�ߺ����� �ʴ� �� Ž��, cnt==4�� return
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

//[0]~[3]:����,  [4]:��Ʈ����ũ ����,  [5]:�� ����
int fail_data[10][6];
int dataCnt;
int* num;
int visited[10];

int isPossible() {
	int i, j;
	for (i = 0; i < dataCnt; i++) {
		int strike = 0, ball = 0;
		for (j = 0; j <= 3; j++) {
			// �ڸ��� ���ڰ� ��ġ�ϴ� ���
			if (fail_data[i][j] == num[j]) strike++;
			// �ڸ��� �ٸ����� ���ڰ� �����ϰ� �����ϴ� ���
			else if (visited[fail_data[i][j]]) ball++;
		}
		// strike ������ ball ������ ������ ��ġ�ϴ��� Ȯ��
		// Query ȣ���ϱ����� ����ġ��
		if ((fail_data[i][4] != strike) || (fail_data[i][5] != ball))
			return 0;
	}
	return 1;
}


int DFS(int cnt) {
	if (cnt == 4) {
		// query �Լ� ȣ������ ������ �����ͷ� 1�� ����
		if (!isPossible())
			return 0;

		Result ret = query(num);
		if (ret.strike == 4)
			return 1;

		// ������ ���� ������ ����
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