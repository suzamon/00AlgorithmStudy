#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<string> lines) {
	int answer = 0;

	string time;
	vector <int> day, hour, min, sec, during;

	vector <int> shour, smin, ssec;

	int tmpH, tmpM, tmpS, flag;

	int startH = -2, startM = 0;
	double startS = 0;
	int endH = -2, endM = 0;
	double endS = 0;

	if (lines.size() == 1) {
		answer = 1;
		return answer;
	}
	flag = 0;
	for (int i = 0; i < lines.size(); i++) {
		time = lines[i].substr(11);
		day.push_back(15);
		hour.push_back(stoi(time.substr(0, 2)));
		min.push_back(stoi(time.substr(3, 2)));
		sec.push_back(int(stod(time.substr(6, 6)) * 1000));
		during.push_back(int(stod(time.substr(13)) * 1000));
		//cout << hour << "시 " << min << "분 "<< sec <<"초 "<< endl;
		//cout << "소요 시간: " << during << endl;


		if (endH == -2) {
			endH = hour[i];
			endM = min[i];
			endS = sec[i];
		}
		else {
			if (endH < hour[i]) {
				endH = hour[i];
				endM = min[i];
				endS = sec[i];
			}
			else if (endH == hour[i]) {
				if (endM < min[i]) {
					endH = hour[i];
					endM = min[i];
					endS = sec[i];
				}
				else if (endM == min[i]) {
					if (endS < sec[i]) {
						endH = hour[i];
						endM = min[i];
						endS = sec[i];
					}
				}
			}
		}

		tmpH = hour[i];
		tmpM = min[i];
		tmpS = sec[i] - during[i] + 1;

		if (tmpS < 0) {
			tmpS += 60000;
			tmpM--;
			if (tmpM < 0) {
				tmpM += 60;
				tmpH--;
			}
		}

		shour.push_back(tmpH);
		smin.push_back(tmpM);
		ssec.push_back(tmpS);

		if (startH == -2) {
			startH = shour[i];
			startM = smin[i];
			startS = ssec[i];
		}
		else {
			if (startH > shour[i]) {
				startH = shour[i];
				startM = smin[i];
				startS = ssec[i];
			}
			else if (startH == shour[i]) {
				if (startM > smin[i]) {
					startH = shour[i];
					startM = smin[i];
					startS = ssec[i];
				}
				else if (startM == smin[i]) {
					if (startS > ssec[i]) {
						startH = shour[i];
						startM = smin[i];
						startS = ssec[i];
					}
				}
			}
		}

	}
	/*
	for (int i = 0; i < hour.size(); i++) {
		cout << "종료 시간" << endl;
		cout << hour[i] << "시 " << min[i] << "분 "<< sec[i] <<"초 "<< endl;
		cout << "소요 시간: " << during[i] << endl;
		cout << endl;
		cout << "시작 시간" << endl;
		cout << shour[i] << "시 " << smin[i] << "분 " << ssec[i] << "초 " << endl;
		cout << endl;
	}
	
	cout << "처음 시작 시간: " << startH << "시 " << startM << "분 " << startS << "초" << endl;
	cout << "가장 끝 시간: " << endH << "시 " << endM << "분 " << endS << "초" << endl;
	cout << endl;
	*/

	int x = startH, y = startM, z = startS, xx, yy ,zz;
	int tmpCnt = 0;
	int tmpH1, tmpM1, tmpS1, tmpDiff, tmp;

	while (1) {
		xx = x;
		yy = y;
		zz = z + 999;


		if (zz > 60000) {
			yy += 1;
			zz -= 60000;
			if (yy > 60) {
				yy -= 60;
				xx += 1;
			}
		}

		tmpCnt = 0;
		for (int i = 0; i < hour.size(); i++) {
			flag = 0;

			tmpH = shour[i];
			tmpM = smin[i];
			tmpS = ssec[i];

			tmpH1 = hour[i];
			tmpM1 = min[i];
			tmpS1 = sec[i];

			if (tmpH == x && tmpM == y && tmpS <= z) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 >= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 > yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 > xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH == x && tmpM < y) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 >= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 > yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 > xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH < x) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 >= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 > yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 > xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			if (flag == 1) continue;

			if (tmpH == x && tmpM == y && tmpS >= z) {
				if (tmpH == xx && tmpM == yy && tmpS <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH == xx && tmpM < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH == x && tmpM > y) {
				if (tmpH == xx && tmpM == yy && tmpS <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH == xx && tmpM < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH > x) {
				if (tmpH == xx && tmpM == yy && tmpS <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH == xx && tmpM < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			if (flag == 1) continue;

			if (tmpH1 == x && tmpM1 == y && tmpS1 >= z) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH1 == x && tmpM1 > y) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			else if (tmpH1 > x) {
				if (tmpH1 == xx && tmpM1 == yy && tmpS1 <= zz) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 == xx && tmpM1 < yy) {
					flag = 1;
					tmpCnt++;
				}
				else if (tmpH1 < xx) {
					flag = 1;
					tmpCnt++;
				}
			}
			if (flag == 1) continue;

		}

		if (tmpCnt > answer) {
			answer = tmpCnt;
		}

		if (xx > endH) break;
		else if (xx == endH) {
			if (yy > endM) break;
			else if (yy == endM) {
				if (zz >= endS) break;
			}
		}

		z += 1;
		if (z > 60000) {
			y += 1;
			z -= 60000;
			if (y > 60) {
				y -= 60;
				x += 1;
			}
		}

	}


	return answer;
}

int main(void) {
	vector<int> a;

	for

	return 0;
}