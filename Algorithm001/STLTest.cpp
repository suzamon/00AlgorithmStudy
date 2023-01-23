#include <iostream>
#include <string>

#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>


using namespace std;


bool fncomp(std::string a, std::string b) {
	return a > b;
}

bool fncomp_2(std::string a, std::string b) {
	return a < b;
}

int main() {

	/***************************************
				hash
	 *************************************/


	std::unordered_map<std::string, int> um;

	if (um.empty()) {
		std::cout << "unordered_map is empty" << std::endl;
	}
	std::cout << endl;

	//insert
	um.insert(std::pair<std::string, int>("key9", 9));
	um.insert(std::make_pair("key1", 1));
	um["key2"] = 2;


	cout << "[size] undoreder_map size is " << um.size() << std::endl;

	for (auto& i : um) {
		std::cout << "[visit] key : " << i.first << " , value : " << i.second << std::endl;
	}
	std::cout << endl;

	std::unordered_map<std::string, int>::iterator iter_um = um.find("key2");
	if (iter_um != um.end()) {
		std::cout << "[find] key : " << iter_um->first << " , value : " << iter_um->second << std::endl;
		um.erase("key2");
	}
	else {
		std::cout << "[find] no such key" << std::endl;
	}
	std::cout << endl;

	cout << "[size] undoreder_map size is " << um.size() << std::endl;

	for (auto& i : um) {
		std::cout << "[visit] key : " << i.first << " , value : " << i.second << std::endl;
	}
	std::cout << endl;

	/***************************************
				binary tree
	 *************************************/

	std::map<std::string, int> m;

	m["kate"] = 300;
	m.insert(std::make_pair("Alice", 100));
	m.insert(std::pair<std::string, int>("bob", 200));

	for (auto iter_m = m.begin(); iter_m != m.end(); iter_m++) {
		cout << "[map][visit] key : " << iter_m->first << " , value : " << iter_m->second << std::endl;
	}
	std::cout << endl;

	std::map<std::string, int>::iterator iter_m = m.find("Alice");
	if (iter_m != m.end()) {
		std::cout << "[map][find] key : " << iter_m->first << " , value : " << iter_m->second << std::endl;
		m.erase("Alice");
	}
	else {
		std::cout << "[map][find] no such key" << std::endl;
	}
	std::cout << endl;

	for (auto iter : m) {
		cout << iter.first << ", " << iter.second << std::endl;
	}
	std::cout << endl;

	//Decending order
	//std::map<std::string, int, greater<string> > m_g; // 내림차순
	std::map<std::string, int > m_g; //오름차순
	m_g["c"] = 3;
	m_g["b"] = 2;
	m_g["a"] = 1;
	

	for (auto i : m_g) {
		std::cout << "[map_g][visit] key : " << i.first << " , value : " << i.second << std::endl;
	}
	std::cout << endl;

	//functor
	bool(*fn_pt) (std::string, std::string) = fncomp;
	std::map<std::string, int, bool(*)(std::string, std::string)> m_f(fn_pt);

	m_f["321"] = 1;
	m_f["2323"] = 2;

	for (auto i : m_f) {
		std::cout << "[map_f][visit] key : " << i.first << " , value : " << i.second << std::endl;
	}


	/***************************************
			Doubly linked  list
	 *************************************/

	std::list<int> l;

	std::list<int>::iterator iter_list = l.begin();

	for (int i = 0; i < 5; i++) {
		l.push_back(i);
	}

	for (iter_list = l.begin(); iter_list != l.end(); iter_list++) {
		std::cout << *iter_list << " , ";
	}
	std::cout << std::endl;

	for (int i = 5; i < 10; i++) {
		l.push_front(i);
	}

	for (iter_list = l.begin(); iter_list != l.end(); iter_list++) {
		std::cout << *iter_list << " , ";
	}
	std::cout << std::endl;

	l.pop_back();
	l.pop_front();

	for (iter_list = l.begin(); iter_list != l.end(); iter_list++) {
		std::cout << *iter_list << " , ";
	}
	std::cout << std::endl;

	/***************************************
			vector
	 *************************************/

	std::string myStrings[] = { "Hi", "I'm", "Jisoo", "Nice to meet you" };
	std::vector<std::string> v(myStrings, myStrings + sizeof(myStrings) / sizeof(std::string));

	std::cout << "vector size is " << v.size() << std::endl;
	std::cout << "vector capacity is " << v.capacity() << std::endl;

	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << std::endl;
	}

	v.push_back("We are gonna be a rich");
	std::cout << "vector size is " << v.size() << std::endl;
	std::cout << "vector capacity is " << v.capacity() << std::endl;

	v.shrink_to_fit();
	std::cout << "vector size is " << v.size() << std::endl;
	std::cout << "vector capacity is " << v.capacity() << std::endl;

	std::vector<std::string>::iterator it_v = v.begin() + 2;
	v.insert(it_v, "Sex master is here.");
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << std::endl;
	}

	v.erase(v.begin() + 2);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::vector<int> temp(88);
	std::cout << "ttttttttttttttttttt " << temp.capacity() << std::endl;

	/***************************************
			sort (algorithm)
	 *************************************/

	std::sort(v.begin(), v.end(), fncomp_2);

	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << std::endl;
	}

	/***************************************
			stack
	 *************************************/

	stack<std::string> s;

	s.push("stack test");
	s.push("this will be a top");
	s.push("no i'm a top");

	s.pop();

	while (!s.empty()) {
		std::cout << "[stack] " << s.top() << std::endl;
		s.pop();
	}

	return 0;


}
