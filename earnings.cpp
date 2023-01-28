#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "defns.h"
#include "readODAfile.h"
#include "readEarning.h"
#include "maxheap.h"
#include "hashtable.h"
#include "bst.h"
#include "prime.h"

using namespace std;

typedef long long LL;

int csvLine(int csvLine, string fileName) {
	ifstream infile(fileName);
	string line;
	while (getline(infile, line)) {
		csvLine++;
	}
	return csvLine;
}

double round(double number, unsigned int bits) {
	LL integerPart = number;
	number -= integerPart;
	for (unsigned int i = 0; i < bits; ++i){
		number *= 10;
	}
	number = (LL)(number);
	for (unsigned int i = 0; i < bits; ++i){
		number /= 10;
	}

	return integerPart + number;
}

int main(string argc, char* argv[]) {
	int odaLine = 0;
	int earningLine = 0;
	string fileYear = argv[1];
	string odaFile = "Occupation-Dist-All-" + fileYear + ".csv";
	string earningFile = "Earnings-1960-2019.csv";
	int odaSize = csvLine(odaLine, odaFile) - 1;
	int earningSize = csvLine(earningLine, earningFile) - 8;

	SOC* soc = new SOC[odaSize];
	//Initialization
	for (int i = 0; i < odaSize; i++) {
		for (int n = 0; n < OCC_LEN; n++) {
			soc[i].occupation[n] = '\0';
		}
		for (int n = 0; n < CODE_LEN; n++) {
			soc[i].SOC_code[n] = '\0';
		}
		soc[i].total = 0;
		soc[i].male = 0;
		soc[i].female = 0;
	}

	earnings* earn = new earnings[earningSize];
	//Initialization
	for (int i = 0; i < earningSize; i++) {
		earn[i].year = 0;
		earn[i].male_total = 0;
		earn[i].male_with_earnings = 0;
		earn[i].male_earnings = 0;
		earn[i].male_earnings_moe = 0;
		earn[i].female_total = 0;
		earn[i].female_with_earnings = 0;
		earn[i].female_earnings = 0;
		earn[i].female_earnings_moe = 0;
	}

	readODAfile(soc, odaFile);
	readEarning(earn, earningFile);

	bst* root = new bst;
	root->soc = soc[0];
	root->left = nullptr;
	root->right = nullptr;

	int m = 3 * odaSize;
	while(TestForPrime(m) == 0) {
		m++;
	}
	HashTable* HashTable = NULL;
	HashTable = initHash(m);

	for (int i = 1; i < odaSize; i++) {
		insertBST(root, soc, i, HashTable);
	}

	string query[4];
	string str;
	char ch;
	cin.ignore(10, '\n');
	while (getline(cin, str)) {
		istringstream input(str);
		string output;
		int indexQuery = 0;
		int task = 0;
		while (input >> output) {
			query[indexQuery] = output;
			indexQuery++;
		}
		if (query[1] == "max") {
			task = 1;
		}
		else if (query[1] == "ratio") {
			task = 2;
		}
		else if (query[1] == "occupation" && indexQuery == 3) {
			task = 3;
		}
		else if (query[1] == "occupation" && indexQuery == 4) {
			task = 4;
		}
		else {
			cout << "ERROR!" << endl;
		}

		switch (task) {
		case 1: {
			string type = query[2];
			int maxTimes = stoi(query[3]);
			cout << "Query: find max " << type << " " << maxTimes << '\n' << endl;
			if (type == "total") {
				BuildMaxHeap(soc, odaSize, type);
				cout << "Top " << maxTimes << " occupations in " << fileYear << " for total workers:" << endl;
				for (int a = 0; a < maxTimes; a++) {
					cout << '\t' << soc[0].occupation << ": " << addComma(soc[0].total) << endl;
					MaxHeapDelete(soc, odaSize, type);
					odaSize = odaSize - 1;
				}
			}
			else if (type == "male") {
				BuildMaxHeap(soc, odaSize, type);
				cout << "Top " << maxTimes << " occupations in " << fileYear << " for male workers:" << endl;
				for (int a = 0; a < maxTimes; a++) {
					cout << '\t' << soc[0].occupation << ": " << addComma(soc[0].male) << endl;
					MaxHeapDelete(soc, odaSize, type);
					odaSize = odaSize - 1;
				}
			}
			else if (type == "female") {
				BuildMaxHeap(soc, odaSize, type);
				cout << "Top " << maxTimes << " occupations in " << fileYear << " for female workers:" << endl;
				for (int a = 0; a < maxTimes; a++) {
					cout << '\t' << soc[0].occupation << ": " << addComma(soc[0].female) << endl;
					MaxHeapDelete(soc, odaSize, type);
					odaSize = odaSize - 1;
				}
			}
			break;
		}

		case 2: {
			int startYear = stoi(query[2]);
			int endYear = stoi(query[3]);
			cout << "Query: find ratio " << startYear << " " << endYear << '\n' << endl;
			cout << "The female-to-male earnings ratio for " << startYear << "-" << endYear << ":" << endl;
			for (int i = 2012 - startYear; i >= 2012 - endYear; i--) {
				double ratio = ((double)earn[i].female_earnings / (double)earn[i].male_earnings) * (double)100;
				stringstream tempRatio;
				tempRatio << round(ratio, 1);
				string finalRatio = tempRatio.str();
				if(finalRatio.find(".") != -1) {
					cout << '\t' << earn[i].year << ": " << round(ratio, 1) << "%" << endl;
				}
				else {
					cout << '\t' << earn[i].year << ": " << round(ratio, 1) << ".0%" << endl;
				}			
			}
			break;
		}
		case 3: {
			cout << "Query: find occupation " << query[2] << '\n' << endl;
			cout << "The occupation with SOC code " << query[2] << ":" << endl;
			string socKey = query[2].substr(0, 2) + query[2].substr(3, 4);
			cout << '\t' << findHash(HashTable, stoi(socKey), m)->node->soc.occupation << ": YRFT: " << addComma(findHash(HashTable, stoi(socKey), m)->node->soc.total) << ", Female: " << addComma(findHash(HashTable, stoi(socKey), m)->node->soc.female) << ", Male: " << addComma(findHash(HashTable, stoi(socKey), m)->node->soc.male) << endl;
			break;
		}
		case 4: {
			cout << "Query: range occupation " << query[2] << " " << query[3] << '\n' << endl;
			cout << "The occupations in the range " << query[2] << " to " << query[3] << ":" << endl;
			char* start = new char[query[2].size() - 2];
			char* end = new char[query[3].size() - 2];
			strcpy(start, query[2].substr(1, query[2].size() - 2).c_str());
			strcpy(end, query[3].substr(1, query[3].size() - 2).c_str());
			inordertree(root, start, end);
			break;
		}
		default:
			cout << "Error: unrecognized query " << task << "\n";
			break;
		}
	}
	return 0;
}
