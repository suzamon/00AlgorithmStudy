#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <unordered_map>

using namespace std;

class MaleStudent {
public:
	int id;
	int score;

	MaleStudent(int id, int score) {
		this->id = id;
		this->score = score;
	}

	bool operator <(MaleStudent &student) {
		if (this->score == student.score) {
			return this->id > student.id;
		}
		return this->score > student.score;
	}

};

class FemaleStudent {
public:
	int id;
	int score;

	FemaleStudent(int id, int score) {
		this->id = id;
		this->score = score;
	}

	bool operator <(FemaleStudent &student) {
		if (this->score == student.score) {
			return this->id > student.id;
		}
		return this->score > student.score;
	}

};

deque <MaleStudent> MaleStudentDB[3];
deque <FemaleStudent> FemaleStudentDB[3];

unordered_map<int, int> um;

void init() {
	for (int i = 0; i < 3; i++) {
		while (!MaleStudentDB[i].empty()) MaleStudentDB[i].pop_back();
		while (!FemaleStudentDB[i].empty()) FemaleStudentDB[i].pop_back();
	}
	um.clear();
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	string g(mGender);
	int gen;

	if (g == "male") gen = 0;
	else gen = 1;
	um.insert(make_pair(mId, mGrade * 10 + gen));

	//dq.push_back({ mId, mGrade, gen });

	if (gen == 0) {
		if (MaleStudentDB[mGrade - 1].size() == 0) {
			//cout << mId << endl;
			MaleStudentDB[mGrade - 1].push_back({ mId, mScore });
			return mId;
		}
		for (int i = 0; i < MaleStudentDB[mGrade - 1].size(); i++) {
			if (mScore > MaleStudentDB[mGrade - 1][i].score) {
				MaleStudentDB[mGrade - 1].insert(MaleStudentDB[mGrade - 1].begin() + i, { mId, mScore });
				break;
			}
			else if (mScore == MaleStudentDB[mGrade - 1][i].score && mId > MaleStudentDB[mGrade - 1][i].score) {
				MaleStudentDB[mGrade - 1].insert(MaleStudentDB[mGrade - 1].begin() + i, { mId, mScore });
				break;
			}

			if (i == MaleStudentDB[mGrade - 1].size() - 1) {
				MaleStudentDB[mGrade - 1].push_back({ mId, mScore });
				break;
			}
		}
		//sort(MaleStudentDB[mGrade - 1].begin(), MaleStudentDB[mGrade - 1].end());
		//cout << MaleStudentDB[mGrade - 1].front().id << endl;
		return MaleStudentDB[mGrade - 1].front().id;
	}
	else {

		if (FemaleStudentDB[mGrade - 1].size() == 0) {
			FemaleStudentDB[mGrade - 1].push_back({ mId, mScore });
			//cout << mId << endl;
			return mId;
		}

		for (int i = 0; i < FemaleStudentDB[mGrade - 1].size(); i++) {
			if (mScore > FemaleStudentDB[mGrade - 1][i].score) {
				FemaleStudentDB[mGrade - 1].insert(FemaleStudentDB[mGrade - 1].begin() + i, { mId, mScore });
				break;
			}
			else if (mScore == FemaleStudentDB[mGrade - 1][i].score && mId > FemaleStudentDB[mGrade - 1][i].score) {
				FemaleStudentDB[mGrade - 1].insert(FemaleStudentDB[mGrade - 1].begin() + i, { mId, mScore });
				break;
			}

			if (i == FemaleStudentDB[mGrade - 1].size() - 1) {
				FemaleStudentDB[mGrade - 1].push_back({ mId, mScore });
				break;
			}
		}


		//sort(FemaleStudentDB[mGrade - 1].begin(), FemaleStudentDB[mGrade - 1].end());
		//cout << FemaleStudentDB[mGrade - 1].front().id << endl;
		return FemaleStudentDB[mGrade - 1].front().id;
	}

	return 0;
}

int remove(int mId) {
	int tmpId, tmpGrade, tmpGender, tmpScore, flag = 0;
	int findId = 0, findGrade, findGender, findScore;
	int dbSize;

	int tmp;

	if (um.find(mId) != um.end()) {
		tmp = um.find(mId)->second;
		findId = mId;
		findGrade = tmp / 10;
		findGender = tmp % 10;
		um.erase(mId);
	}
	else {
		return 0;
	}

	/*
	for (int i = 0; i < dbSize; i++) {
		tmpId = dq.front().id, tmpGrade = dq.front().grade, tmpGender = dq.front().gen;
		dq.pop_front();
		if (tmpId == mId) {
			findGender = tmpGender, findGrade = tmpGrade;
			findId = tmpId;
			break;
		}
		dq.push_back({ tmpId, tmpGrade, tmpGender });
	}
	if (findId == 0) return 0;
	*/
	if (findGender == 0) {
		dbSize = MaleStudentDB[findGrade - 1].size();
		for (int i = 0; i < dbSize; i++) {
			tmpId = MaleStudentDB[findGrade - 1].front().id, tmpScore = MaleStudentDB[findGrade - 1].front().score;
			MaleStudentDB[findGrade - 1].pop_front();
			if (tmpId == findId) {
				continue;
			}
			MaleStudentDB[findGrade - 1].push_back({ tmpId, tmpScore });
		}
		if (MaleStudentDB[findGrade - 1].size() == 0) return 0;

		//cout << MaleStudentDB[findGrade - 1].back().id << endl;

		return MaleStudentDB[findGrade - 1].back().id;
	}
	else {
		dbSize = FemaleStudentDB[findGrade - 1].size();

		for (int i = 0; i < dbSize; i++) {
			tmpId = FemaleStudentDB[findGrade - 1].front().id, tmpScore = FemaleStudentDB[findGrade - 1].front().score;
			FemaleStudentDB[findGrade - 1].pop_front();
			if (tmpId == findId) {
				continue;
			}
			FemaleStudentDB[findGrade - 1].push_back({ tmpId, tmpScore });
		}
		if (FemaleStudentDB[findGrade - 1].size() == 0) return 0;

		//cout << FemaleStudentDB[findGrade - 1].back().id << endl;

		return FemaleStudentDB[findGrade - 1].back().id;
	}


	return 0;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	int tmpId, tmpGrade, tmpGender, tmpScore, flag = 0, tmp;
	int findId = 0, findGrade, findGender, findScore = 0;
	int dbSize;

	for (int i = 0; i < mGradeCnt; i++) {
		if (mGenderCnt < 2) {
			findGrade = mGrade[i];
			string str(mGender[0]);
			if (str == "male") {
				dbSize = MaleStudentDB[findGrade - 1].size();
				for (int j = 0; j < dbSize; j++) {
					tmpId = MaleStudentDB[findGrade - 1].back().id, tmpScore = MaleStudentDB[findGrade - 1].back().score;
					MaleStudentDB[findGrade - 1].pop_back();
					MaleStudentDB[findGrade - 1].push_front({ tmpId, tmpScore });
					if (flag == 0 && mScore <= tmpScore) {
						flag = 1;
						findId = tmpId;
						findScore = tmpScore;
						continue;
					}
					else if (flag == 1 && mScore <= tmpScore && findScore >= tmpScore) {
						if (findScore == tmpScore && findId > tmpId) {
							findId = tmpId;
							continue;
						}
						else if (findScore > tmpScore) {
							findId = tmpId;
							findScore = tmpScore;
							continue;
						}
					}
				}
			}
			else {
				dbSize = FemaleStudentDB[findGrade - 1].size();
				for (int j = 0; j < dbSize; j++) {
					tmpId = FemaleStudentDB[findGrade - 1].back().id, tmpScore = FemaleStudentDB[findGrade - 1].back().score;
					FemaleStudentDB[findGrade - 1].pop_back();
					FemaleStudentDB[findGrade - 1].push_front({ tmpId, tmpScore });
					if (flag == 0 && mScore <= tmpScore) {
						flag = 1;
						findId = tmpId;
						findScore = tmpScore;
						continue;
					}
					else if (flag == 1 && mScore <= tmpScore && findScore >= tmpScore) {
						if (findScore == tmpScore && findId > tmpId) {
							findId = tmpId;
							continue;
						}
						else if (findScore > tmpScore) {
							findId = tmpId;
							findScore = tmpScore;
							continue;
						}
					}
				}
			}
		}
		else {
			findGrade = mGrade[i];
			dbSize = MaleStudentDB[findGrade - 1].size();
			for (int j = 0; j < dbSize; j++) {
				tmpId = MaleStudentDB[findGrade - 1].back().id, tmpScore = MaleStudentDB[findGrade - 1].back().score;
				MaleStudentDB[findGrade - 1].pop_back();
				MaleStudentDB[findGrade - 1].push_front({ tmpId, tmpScore });
				if (flag == 0 && mScore <= tmpScore) {
					flag = 1;
					findId = tmpId;
					findScore = tmpScore;
					continue;
				}
				else if (flag == 1 && mScore <= tmpScore && findScore >= tmpScore) {
					if (findScore == tmpScore && findId > tmpId) {
						findId = tmpId;
						continue;
					}
					else if (findScore > tmpScore) {
						findId = tmpId;
						findScore = tmpScore;
						continue;
					}
				}
			}
			dbSize = FemaleStudentDB[findGrade - 1].size();
			for (int j = 0; j < dbSize; j++) {
				tmpId = FemaleStudentDB[findGrade - 1].back().id, tmpScore = FemaleStudentDB[findGrade - 1].back().score;
				FemaleStudentDB[findGrade - 1].pop_back();
				FemaleStudentDB[findGrade - 1].push_front({ tmpId, tmpScore });
				if (flag == 0 && mScore <= tmpScore) {
					flag = 1;
					findId = tmpId;
					findScore = tmpScore;
					continue;
				}
				else if (flag == 1 && mScore <= tmpScore && findScore >= tmpScore) {
					if (findScore == tmpScore && findId > tmpId) {
						findId = tmpId;
						continue;
					}
					else if (findScore > tmpScore) {
						findId = tmpId;
						findScore = tmpScore;
						continue;
					}
				}
			}
		}
	}

	if (flag == 0) return 0;
	//cout << findId << endl;
	return findId;
}

