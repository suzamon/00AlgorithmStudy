/*
1'04''13'''
어떤 국가에서는 자국 내 방송국에서 스파이가 활동하는 사실을 알아냈다.
스파이는 영상물에 암호 코드를 삽입하여 송출하고 있었다.
암호 코드는 국가 내 중요 시설을 의미하는 숫자임을 알아냈다. 암호 코드의 규칙은 아래와 같다.

1. 총 8개의 숫자로 이루어져 있다.

2. 앞 7자리는 상품 고유의 번호를 나타내며, 마지막 자리는 검증 코드를 나타낸다.

	- 검증코드는 아래와 같은 방법으로 계산한다.

	“(홀수 자리의 합 x 3) + 짝수 자리의 합 + 검증 코드” 가 10의 배수가 되어야 한다.

	상품 고유의 번호가 8801234일 경우,

	“( ( 8 + 0 + 2 + 4 ) x 3 ) + ( 8 + 1 + 3 ) + 검증 코드”

	= “42 + 12 + 검증 코드”

	= “54 + 검증 코드” 가 10 의 배수가 되어야 하므로, 검증코드는 6이 되어야 한다.

	즉, 88012346 이 정상적인 암호코드고, 그 외의 검증코드가 포함된 경우 비정상적인 암호코드다.


A 업체에서는 이 암호코드들을 빠르고 정확하게 인식할 수 있는 스캐너를 개발하려고 한다.
스캐너의 성능은 아래와 같은 방법으로 측정된다.

1. 세로 50. 가로 100 이하의 크기를 가진 직사각형 배열에 암호코드 정보가 포함되어 전달된다.
이 때, 하나의 배열에는 1개의 암호코드가 존재한다.
(단, 모든 암호코드가 정상적인 암호코드임을 보장할 수 없다. 비정상적인 암호코드가 포함될 수 있다.)
2. 배열은 1, 0으로 이루어져 있으며 그 안에 포함되어 있는 암호코드 정보를 확인한다.
3. 포함된 암호코드들의 검증코드를 확인하여 정상적인 암호코드인지 확인한다.
4. 정상적인 암호코드들을 판별한 뒤 이 암호코드들에 적혀있는 숫자들의 합을 출력한다.
5. 이때, 총 소요시간이 적을수록 성능이 좋은 것으로 간주된다.


배열에 포함되어 있는 암호코드의 세부 규칙은 아래와 같다.

1. 암호코드 하나는 숫자 8개로 구성되며 시작 구분선, 종료 구분선은 별도로 존재하지 않는다.
2. 암호코드가 일부만 표시된 경우는 없다. 모든 암호코드는 8개의 숫자로 구성되어 있다.
3. 암호코드의 세로 길이는 5 ~ 50 칸이다.
4. 암호코드의 가로 길이는 총 길이는 56칸이다. 암호코드에 구성하는 숫자 하나가 차지하는 길이는 7칸이다.
  각 숫자들을 그림으로 표시하는 방법은 다음과 같다.


암호코드 정보가 포함된 2차원 배열을 입력으로 받아 정상적인 암호코드를 판별하는 프로그램을 작성하라.

[입력]

가장 첫줄은 전체 테스트 케이스의 수이다.
각 테스트 케이스의 첫 줄에 두 자연수가 주어지는데 각각 배열의 세로 크기 N, 배열의 가로크기 M이다 (1≤N<50, 1≤M<100).
그 다음 N개의 줄에는 M개의 배열의 값이 주어진다.

[출력]

각 테스트 케이스의 답을 순서대로 표준출력으로 출력하며, 각 케이스마다 줄의 시작에 “#C”를 출력하여야 한다.
이때 C는 케이스의 번호이다. 같은 줄에 빈칸을 하나 두고,
입력에 주어진 배열에서 정상적인 암호코드들에 포함된 숫자들의 합을 출력한다.



0111011 0110001 0111011 0110001 0110001 0001101 0010011 0111011

N, M, arr[8][8], string s, sX, sY;



*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

int N, M, tmpIdx, sY, lY, Answer = 0;

string str;

char arr[9][8] = { 0, };

char ch[10][7] = { {'0', '0', '0', '1', '1', '0', '1'}, {'0', '0', '1', '1','0','0','1'},{'0','0','1','0','0','1','1'}, {'0','1','1','1','1','0','1'}, {'0','1', '0', '0', '0', '1', '1'}, {'0', '1', '1', '0', '0', '0', '1'}, {'0', '1', '0', '1','1','1','1'}, {'0', '1','1','1','0','1','1'}, {'0','1','1','0','1','1','1'}, {'0', '0', '0', '1', '0', '1', '1'} };

void print_info() {
	cout << "정보 송출" << endl;
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << "번째 문자: ";
		for (int j = 0; j < 7; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}


int find_num(int idx) {
	int tmpIdx, cnt = 0, retFlag = 0;
	for (tmpIdx = 0; tmpIdx < 10; tmpIdx++) {
		cnt = 0;
		for (int j = 0; j < 7; j++) {
			if (arr[idx][j] == ch[tmpIdx][j]) {
				cnt++;
			}
			else break;
		}
		if (cnt == 7) break;
		if (tmpIdx == 9 && cnt != 7) {
			retFlag = 1;
			break;
		}
	}

	if (retFlag == 1) return -1;
	return tmpIdx;
}

int check_str() {
	int sR = 0, sC = 0, cnt = 0, retFlag = 0;
	
	for (int i = tmpIdx; i < tmpIdx + 56; i++) {
		cnt++;
		arr[sR][sC] = str.at(i);
		sC++;
		if (cnt == 7) {
			sC = 0;
			sR++;
			cnt = 0;
		}
		if (sR == 8) {
			break;
		}
	}

	int num[8] = { 0, };
	for (int i = 0; i < 8; i++) {
		num[i] = find_num(i);
		if (num[i] == -1) {
			retFlag = 1;
			break;
		}
	}
	if (retFlag == 1) return retFlag;

	/*
	cout << "Num" << endl;
	for (int i = 0; i < 8; i++) {
		cout << num[i] << ' ';
	}
	cout << endl;
	*/
	int a = 0, b = 0, c = 0;
	c = num[7];
	for (int i = 1; i < 8; i++) {
		if (i % 2 == 1) {
			a += num[i-1];
		}
		else {
			b += num[i-1];
		}
	}

	if ((a * 3 + b + c) % 10 == 0) {
		Answer = a + b + c;
	}
	else retFlag = 1;


	return retFlag;
}

void Solution() {

	tmpIdx = sY - 3;
	Answer = 0;
	if (tmpIdx + 56 <= lY) {
		while (1) {
			tmpIdx = tmpIdx++;
			if (tmpIdx + 56 > lY) break;
		}
	}
	int exitFlag = 0;
	while (1) {
		exitFlag = check_str();
		if (exitFlag == 0) break;
		tmpIdx++;
		if (tmpIdx > sY) break;
	}

	
}

void Input() {
	int flag = 0;
	string tmpStr;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> tmpStr;
		if (flag == 1) continue;
		for (int j = 0; j < M; j++) {
			if (tmpStr.at(j) == '1' && flag ==0) {
				sY = j;
				str = tmpStr;
				flag = 1;
			}
			else if (tmpStr.at(j) == '1' && flag == 1) {
				lY = j;
			}
		}
	}
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

		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}