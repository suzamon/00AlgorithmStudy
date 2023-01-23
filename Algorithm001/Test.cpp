#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <map>

using namespace std;

int N, M, Answer = 0;

class Student {
public:
	int score;

	Student(string name, int score) {
		this->name = name;
		this->score = score;
	}

	bool operator <(Student &student) {
		return this->score < student.score;
	}
};

struct compare {
	bool operator()(const Student& m1, const Student& m2) {
		return m1.score < m2.score;
	}
};


int main(void) {
	map <Student> m;

	int pqSize = pq.size();


	for (int i = 0; i < pqSize; i++) {
		cout << pq.top().name <<", "<< pq.top().score << endl;
		pq.pop();
	}

	return 0;
}