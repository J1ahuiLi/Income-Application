#include <iostream>
#include <string>
#include <cstring>
#include "hashtable.h"
#include "defns.h"


using namespace std;

int hashF(int k, int m) {
	return (k % m);
}

HashTable* initHash(int m) {
	int i = 0;
	HashTable *hTable = NULL;

	hTable = (HashTable*)malloc(sizeof(HashTable));
	if (NULL == hTable) {
		cout << "HashTable malloc error. \n";
	}

	//Allocate memory space for an array of pointers
	hTable->m = m;
	hTable->theChain = (List*)malloc(sizeof(List) * m);
	if (NULL == hTable->theChain) {
		cout << "HashTable malloc error. \n";
		free(hTable);
		return NULL;
	}

	//Initialize a linked list node for an array of pointers
	for (i = 0; i < m; i++) {
		hTable->theChain[i] = (hash_table_entry *)malloc(sizeof(hash_table_entry));
		if (NULL == hTable->theChain[i]) {
			cout << "HashTable malloc error. \n";
			free(hTable->theChain);
			free(hTable);
			return NULL;
		}
		else {
			memset(hTable->theChain[i], 0, sizeof(hash_table_entry));
		}
	}
	return hTable;
}

Element findHash(HashTable *HashTable, int key, int m) {
	int i = 0;
	hash_table_entry* L = NULL;
	hash_table_entry* e = NULL;
	i = hashF(key, m);
	L = HashTable->theChain[i];
	e = L->next;

	string socC;
	int indexSOC = 0;
	while (e != NULL && e->SOC_code[indexSOC] != '\0') {
		if (isdigit(e->SOC_code[indexSOC])) {
			socC += e->SOC_code[indexSOC];
		}
		else if (e->SOC_code[indexSOC] == ' ') {
			socC += ",";
		}
		indexSOC++;
	}

	while (e != NULL && socC.find(to_string(key)) == -1) {
		e = e->next;
	}
	return e;
}

void insertHash(HashTable* HashTable, bst* pre, int key) {
	Element e = NULL;
	Element tmp = NULL;
	List L = NULL;
	//e = findHash();

	if (NULL == e) {
		tmp = (Element)malloc(sizeof(hash_table_entry));
		if (NULL == tmp) {
			cout << "malloc error\n";
			return;
		}
		L = HashTable->theChain[hashF(key, HashTable->m)];
		tmp->node = pre;
		for (int i = 0; i < CODE_LEN; i++) {
			tmp->SOC_code[i] = pre->soc.SOC_code[i];
		}
		L->next = tmp;
	}
	else {
		cout << "exist\n";
	}
}
