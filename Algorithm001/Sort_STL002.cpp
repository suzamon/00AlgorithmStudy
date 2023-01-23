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
	v.push_back(pair<int, string>(90, "이태일"));
	v.push_back(pair<int, string>(90, "박한울"));
	v.push_back(pair<int, string>(82, "나동빈"));
	v.push_back(pair<int, string>(98, "강종구"));
	v.push_back(pair<int, string>(79, "이상욱"));

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		cout << v[i].second << ", " << v[i].first << endl;
	}

	cout << endl;

	vector <pair<string, pair<int, int> > > v2;

	v2.push_back(pair<string, pair<int, int>>("나동빈", make_pair(90, 19961222)));
	v2.push_back(pair<string, pair<int, int>>("이태일", make_pair(97, 19930518)));
	v2.push_back(pair<string, pair<int, int>>("박한울", make_pair(95, 19930203)));
	v2.push_back(pair<string, pair<int, int>>("강종구", make_pair(88, 19921207)));
	v2.push_back(pair<string, pair<int, int>>("이상욱", make_pair(90, 19900302)));

	sort(v2.begin(), v2.end(), compare);
	for (int i = 0; i < v.size(); i++) {
		cout << v2[i].first << ", " << v2[i].second.first << ", " << v2[i].second.second << endl;
	}

	cout << endl;

	return 0;
}
