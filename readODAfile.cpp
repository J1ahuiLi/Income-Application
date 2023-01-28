#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "defns.h"
#include "readODAfile.h"

using namespace std;


void readODAfile(SOC soc[], string odaFile) {
	ifstream inFile(odaFile, std::ios::in);
	string lineStr;
	stringstream ss(lineStr);
	string arrTemp[5];
	for (int i = 0; i < 1; i++) {
		getline(inFile, lineStr);
	}
	int earningLine = 0;
	int odaIndex = 0;
	while (getline(inFile, lineStr)) {
		while (lineStr.find('\\') < 1000) {
			lineStr.erase(lineStr.find('\\'), 1);
		}

		for (int i = 0; i < 5; i++) {
			int start = lineStr.find('"');
			int comma = lineStr.find(',');
			if (start == 0) {
				lineStr.erase(lineStr.find('"'), 1);
				int end = lineStr.find('"');
				lineStr.erase(lineStr.find('"'), 1);
				int wordSize = end - start;
				string temp = lineStr.substr(start, wordSize);
				while ((temp.find(',') < 1000) && (i != 0)) {
					temp.erase(temp.find(','), 1);
				}
				arrTemp[i] = temp;
				//strcpy(soc[odaIndex].occupation, occupation.c_str());
				lineStr.erase(start, wordSize + 1);
			}
			else if (start != 0) {
				comma = lineStr.find(',');
				string temp = lineStr.substr(0, comma);
				arrTemp[i] = temp;
				//strcpy(soc[odaIndex].SOC_code, socCodes.c_str());
				lineStr.erase(0, comma + 1);
			}
			else {
				string temp = lineStr.substr(0, comma);
				arrTemp[i] = temp;
				//strcpy(soc[odaIndex].occupation, occupation.c_str());
				lineStr.erase(0, comma + 1);
			}
		}

		strcpy(soc[earningLine].occupation, arrTemp[0].c_str());
		strcpy(soc[earningLine].SOC_code, arrTemp[1].c_str());
		soc[earningLine].total = stoi(arrTemp[2]);
		soc[earningLine].female = stoi(arrTemp[3]);
		soc[earningLine].male = stoi(arrTemp[4]);

		earningLine++;
	}
	return;
}
