#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool compare(pair<string, pair<int, int>> a, pair<string, pair<int, int>> b) {
	if (a.second.first == b.second.first) {
		return a.second.second > b.second.second;
	}
	else {
		return a.second.first > b.second.first;
	}

}

int main(void) {
	vector <pair <int, string>> v;
	v.push_back(pair<int, string>(90, "������"));
	v.push_back(pair<int, string>(90, "���ѿ�"));
	v.push_back(pair<int, string>(82, "������"));
	v.push_back(pair<int, string>(98, "������"));
	v.push_back(pair<int, string>(79, "�̻��"));

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		cout << v[i].second << ", " << v[i].first << endl;
	}

	cout << endl;

	vector <pair<string, pair<int, int> > > v2;

	v2.push_back(pair<string, pair<int, int>>("������", make_pair(90, 19961222)));
	v2.push_back(pair<string, pair<int, int>>("������", make_pair(97, 19930518)));
	v2.push_back(pair<string, pair<int, int>>("���ѿ�", make_pair(95, 19930203)));
	v2.push_back(pair<string, pair<int, int>>("������", make_pair(88, 19921207)));
	v2.push_back(pair<string, pair<int, int>>("�̻��", make_pair(90, 19900302)));

	sort(v2.begin(), v2.end(), compare);
	for (int i = 0; i < v.size(); i++) {
		cout << v2[i].first << ", " << v2[i].second.first << ", " << v2[i].second.second << endl;
	}

	cout << endl;

	return 0;
}
