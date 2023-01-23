#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>


#define MAX_NODE 1000000

using namespace std;

struct Node {
	int data;
	Node* next;

};

Node node[MAX_NODE];
int nodeCnt;
Node head;
Node tail;

int N;

void init()
{
	head.next = nullptr;
	tail.next = nullptr;
	nodeCnt = 0;
}

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void addNode2Head(int data){
	Node* newNode = getNode(data);

	if (tail.next == nullptr) tail.next = newNode;

	newNode->next = head.next;
	head.next = newNode;
}

void addNode2Tail(int data){
	Node* newNode = getNode(data);

	if (head.next == nullptr) head.next = newNode;

	newNode->next = nullptr;
	if (tail.next == nullptr) {
		tail.next = newNode;
		return;
	}
	tail.next->next = newNode;
	tail.next = newNode;
}

void removeNode(int num, int cnt){
	if (head.next == nullptr) return;

	Node* prev_ptr = &head;

	int idx = 0;

	while (prev_ptr->next != nullptr && idx != num){ 
		idx++;
		prev_ptr = prev_ptr->next;
	}

	Node* last_ptr;
	if (prev_ptr->next != nullptr) {
		last_ptr = prev_ptr->next;
		for (int i = 1; i <= cnt; i++) {
			last_ptr = last_ptr->next;
			if (last_ptr == nullptr) break;
		}
		prev_ptr->next = last_ptr;

		if (last_ptr == nullptr) tail.next = prev_ptr;
	}
}

void insertNode(int num, int cnt) {
	if (head.next == nullptr) return;

	Node* prev_ptr = &head;

	int idx = 0, tmp_data;

	while (prev_ptr->next != nullptr && idx != num) {
		idx++;
		prev_ptr = prev_ptr->next;
	}

	if (prev_ptr->next == nullptr) {
		for (int i = 0; i < cnt; i++) {
			cin >> tmp_data;
			addNode2Tail(tmp_data);
		}
	}
	else {
		Node* tmp_ptr = prev_ptr->next;
		Node* newNode;

		for (int i = 0; i < cnt; i++) {
			cin >> tmp_data;
			newNode = getNode(tmp_data);
			prev_ptr->next = newNode;
			prev_ptr = newNode;
		}

		prev_ptr->next = tmp_ptr;
	}

}

void print_list() {
	Node* ptr = &head;
	
	int num = 0;
	ptr = ptr->next;
	while (num < 10) {
		cout << ptr->data << ' ';
		ptr = ptr->next;
		num++;
	}
	cout << endl;
}

void Input() {
	init();
	cin >> N;
	int tmp_data;
	for (int i = 0; i < N; i++) {
		cin >> tmp_data;
		addNode2Tail(tmp_data);
	}
}

void Solution() {
	char cmd;

	int cmdCnt, x, y, s;;
	cin >> cmdCnt;
	for (int i = 0; i < cmdCnt; i++) {
		cin >> cmd;
		switch (cmd) {
		case 'I':
			//cout << "TEST" << endl;
			cin >> x >> y;
			insertNode(x, y);
			break;
		case 'D':
			cin >> x >> y;
			removeNode(x, y);
			break;
		case 'A':
			cin >> y;

			for (int i = 0; i < y; i++) {
				cin >> s;
				addNode2Tail(s);
			}
			break;
		}
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T = 10;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	//freopen("input.txt", "r", stdin);
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		Input();
		Solution();
		cout << '#' << test_case << ' ';
		print_list();

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}