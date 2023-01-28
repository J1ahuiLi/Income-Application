#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "defns.h"
#include "readEarning.h"

using namespace std;

void readEarning(earnings earn[], string earningFile) {
	

	ifstream inFile(earningFile, std::ios::in);
	string lineStr;
	int arrTemp[8];
	for (int i = 0; i < 8; i++) {
		getline(inFile, lineStr);
	}
	int earningLine = 0;
	while (getline(inFile, lineStr)) {
		while (lineStr.find("\\") < 1000) {
			lineStr.erase(lineStr.find("\\"), 1);
		}
		stringstream ss(lineStr);
		string year;
		getline(ss, year, ',');
		earn[earningLine].year = stoi(year);
		lineStr.erase(0, 5);
		
		while (lineStr.find("N") != -1) {
			lineStr.replace(lineStr.find("N"), 1, "-1");
		}

		for (int i = 0; i < 8; i++) {
			int start = lineStr.find('"');
			int comma = lineStr.find(',');
			if (start == 0) {
				lineStr.erase(lineStr.find('"'), 1);
				int end = lineStr.find('"');
				lineStr.erase(lineStr.find('"'), 1);
				int wordSize = end - start;
				string temp = lineStr.substr(start, wordSize);
				while (temp.find(',') < 1000) {
					temp.erase(temp.find(','), 1);
				}
				int result = stoi(temp);
				arrTemp[i] = result;
				lineStr.erase(start, wordSize + 1);
			}
			else if ((start != 0)&&(comma == 3)) {
				arrTemp[i] = stoi(lineStr.substr(0, comma));
				lineStr.erase(0, comma + 1);
			}
			else if ((start != 0) && (comma == 1)) {
				lineStr.erase(lineStr.find(','), 1);
				comma = lineStr.find(',');
				arrTemp[i] = stoi(lineStr.substr(0, comma));
				lineStr.erase(0, comma + 1);
			}
			else {
				arrTemp[i] = stoi(lineStr);
				lineStr.erase(0, comma + 1);
			}
			
		}

		earn[earningLine].male_total = arrTemp[0];
		earn[earningLine].male_with_earnings = arrTemp[1];
		earn[earningLine].male_earnings = arrTemp[2];
		earn[earningLine].male_earnings_moe = arrTemp[3];
		earn[earningLine].female_total = arrTemp[4];
		earn[earningLine].female_with_earnings = arrTemp[5];
		earn[earningLine].female_earnings = arrTemp[6];
		earn[earningLine].female_earnings_moe = arrTemp[7];

		earningLine++;
	}
	return;
}