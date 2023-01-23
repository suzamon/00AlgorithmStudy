#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head;
Node tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	head.next = nullptr;
	tail.next = nullptr;
	nodeCnt = 0;
}

void addNode2Head(int data)
{
	Node* newNode = getNode(data);

	if (head.next == nullptr) tail.next = newNode;

	newNode->next = head.next;
	head.next = newNode;
}

void addNode2Tail(int data)
{
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

void addNode2Num(int data, int num)
{
	Node* prev_ptr = &head;

	int cnt = 1;

	if (num == 1) {
		addNode2Head(data);
		return;
	}

	while (cnt < num) {
		prev_ptr = prev_ptr->next;
		if (prev_ptr == nullptr) break;
		cnt++;
	}

	if (prev_ptr == nullptr) {
		addNode2Tail(data);
		return;
	}

	Node* newNode = getNode(data);

	newNode->next = prev_ptr->next;
	prev_ptr->next = newNode;
}

void removeNode(int data)
{
	Node* prev_ptr = &head;

	while (prev_ptr->next != nullptr && prev_ptr->next->data != data) {
		prev_ptr = prev_ptr->next;
	}

	if (prev_ptr->next != nullptr) {
		prev_ptr->next = prev_ptr->next->next;
	}
}

int getList(int output[MAX_NODE])
{
	int cnt = 0;

	Node* ptr = head.next;
	
	while (ptr != nullptr) {

		output[cnt] = ptr->data;
		cnt++;
		ptr = ptr->next;
	}

	return cnt;
}