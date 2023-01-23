#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

long N, B, C;
long Answer = 0;
vector <long> student;

void Solve() {
	int numStudent;

	for (int i = 0; i < student.size(); i++) {
		numStudent = student[i];

		if (numStudent < B) Answer++;
		else {
			Answer++;
			numStudent -= B;
			if (numStudent % C == 0) {
				Answer += numStudent / C;
			}
			else {
				Answer += numStudent / C;
				Answer++;
			}
		}
	}
}


void Input() {
	int tmpStudent;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmpStudent;
		student.push_back(tmpStudent);
	}
	cin >> B >> C;
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;
	return 0;
}