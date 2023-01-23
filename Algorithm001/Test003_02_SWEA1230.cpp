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
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	//freopen("input.txt", "r", stdin);
	//freopen("input.txt", "r", stdin);
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		Input();
		Solution();
		cout << '#' << test_case << ' ';
		print_list();

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}