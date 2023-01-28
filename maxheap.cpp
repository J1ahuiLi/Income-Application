#include <iostream>
#include <stdlib.h>
#include "defns.h"
#include "maxheap.h"

using namespace std;

void Swap(SOC arr[], int i, int j){
	SOC temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void AdjustHeap(SOC arr[], int size, int i, string type ) {
	int left_child = 2 * i + 1;
	int right_child = 2 * i + 2;
	int max = i;
	if (type == "total") {
		if (left_child < size && arr[left_child].total > arr[max].total) {
			max = left_child;
		}
		if (right_child < size && arr[right_child].total > arr[max].total) {
			max = right_child;
		}
		if (max != i) {
			Swap(arr, i, max);
			AdjustHeap(arr, size, max, type);
		}
	}
	else if (type == "male") {
		if (left_child < size && arr[left_child].male > arr[max].male) {
			max = left_child;
		}
		if (right_child < size && arr[right_child].male > arr[max].male) {
			max = right_child;
		}
		if (max != i) {
			Swap(arr, i, max);
			AdjustHeap(arr, size, max, type);
		}
	}
	else if (type == "female") {
		if (left_child < size && arr[left_child].female > arr[max].female) {
			max = left_child;
		}
		if (right_child < size && arr[right_child].female > arr[max].female) {
			max = right_child;
		}
		if (max != i) {
			Swap(arr, i, max);
			AdjustHeap(arr, size, max, type);
		}
	}
	
}

int BuildMaxHeap(SOC arr[], int size, string type) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		AdjustHeap(arr, size, i, type);
	}
	return size;
}

int MaxHeapDelete(SOC arr[], int size, string type) {
	if (size <= 0)return -1;
	Swap(arr, 0, size - 1);
	AdjustHeap(arr, size - 1, 0, type);
	return size - 1;
}