#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include "defns.h"
//#include "bst.h"
#include "hashtable.h"

using namespace std;

string addComma(int num) {
	stringstream tempInt;
	tempInt << num;
	string finalInt = tempInt.str();
	size_t len = finalInt.length();
	for (int index = (int)len - 3; index > 0; index -= 3) {
		finalInt.insert(index, ",");
	}

	return finalInt;
}

string trans(bst* pre) {
	string socC;
	int indexSOC = 0;
	while (pre->soc.SOC_code[indexSOC] != '\0') {
		if (isdigit(pre->soc.SOC_code[indexSOC])) {
			socC += pre->soc.SOC_code[indexSOC];
		}
		else if (pre->soc.SOC_code[indexSOC] == ' ') {
			socC += ",";
		}
		indexSOC++;
	}
	return socC;
}

void insertBST(bst* root, SOC soc[], int index, HashTable* HashTable) {
	bst* tmp = new bst;
	tmp->soc = soc[index];
	tmp->left = nullptr;
	tmp->right = nullptr;

	if (root == NULL) {
		root = tmp;
		return;
	}

	bst* pre = root;
	while (true) {
		if (strcmp(pre->soc.occupation, soc[index].occupation) >= 0) {
			if (pre->left == NULL) {
				pre->left = tmp;
				if (trans(pre->left).find(",") == -1) {
					insertHash(HashTable, pre->left, stoi(trans(pre->left)));
				}
				else {
					stringstream ss(trans(pre->left));
					string str;
					while (getline(ss, str, ',')) {
						if (str != "") {
							insertHash(HashTable, pre->left, stoi(str));
						}
					}
				}
				return;
			}
			pre = pre->left;
		}
		else {
			if (pre->right == NULL) {
				pre->right = tmp;
				if (trans(pre->right).find(",") == -1) {
					insertHash(HashTable, pre->right, stoi(trans(pre->right)));
				}
				else {
					stringstream ss(trans(pre->right));
					string str;
					while (getline(ss, str, ',')) {
						if (str != "") {
							insertHash(HashTable, pre->right, stoi(str));
						}	
					}
				}
				return;
			}
			pre = pre->right;
		}
	}
}

void inordertree(bst* root, char start[], char end[]) {
	if (root) {
		inordertree(root->left, start, end);
		if ((strcmp(start, root->soc.occupation) <= 0) && (strcmp(end, root->soc.occupation) > 0)) {
			cout << '\t' << root->soc.occupation << ": YRFT: " << addComma(root->soc.total) << ", Female: " << addComma(root->soc.female) << ", Male: " << addComma(root->soc.male) << endl;
		}
		inordertree(root->right, start, end);
	}
}