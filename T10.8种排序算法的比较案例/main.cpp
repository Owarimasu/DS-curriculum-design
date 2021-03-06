#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <regex>
#include "MaxHeap.h"
using namespace std;

// A is always the original array
vector<int> A;
// B is the copy of A, will participate in sort function

bool isPositiveInterger(string s)
{
	//compile a Regex pattern to match the positive intergers
	regex pattern("^(\\+)?(\\d+)$");
	if (regex_match(s, pattern)) {
		return true;
	}
	else
		return false;
}


// BubbleSort
void BubbleSort(vector<int>& B, int n, long long& compare_times) {
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			compare_times++;
			if (B[j] > B[j + 1]) {
				temp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = temp;
			}
		}
	}
}

// SelectionSort
void SelectionSort(vector<int>& B, int n, long long& swap_times) {
	for (int i = 0; i < n; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			swap_times++;
			if (B[j] < B[min]) {
				min = j;
			}
		}
		swap(B[i], B[min]);
	}
}

void InsertionSort(vector<int>& B, int n, long long& swap_times) {
	int temp;
	for (int i = 1; i < n; i++) {
		temp = B[i];
		for (int j = i - 1; j >= 0; j--) {
			
			// j==0 means the element is the smallest
			if (j == 0) {
				B[j] = temp;
			}
			// move the element to its next position
			if (temp < B[j]) {
				B[j+1] = B[j];
				swap_times++;
			}
			else {
				B[j + 1] = temp;
				break;
			}
		}
	}
}


void ShellSort(vector<int>& B, int n, long long& swap_times) {
	int gap = (int)(n / 2);
	while (gap) {	
		for (int i = gap; i < n; i++) {
			for (int j = i; j >= gap && B[j] < B[j - gap]; j -= gap) {
				swap(B[j], B[j - gap]);
				swap_times++;
			}
		}
		gap = gap == 2 ? 1 : (int)(gap / 2.2);
	}
}


void QuickSort(vector<int>& B, const int left, const int right, long long& swap_times) {

	if (left < right) {
		int pivotPos = left;
		int pivot = B[left];
		for (int i = left + 1; i <= right; i++) {
			swap_times++;
			if (B[i] < pivot) {
				pivotPos++;
				if (pivotPos != i) {
					swap(B[pivotPos], B[i]);
					
				}
			}
		}
		B[left] = B[pivotPos];
		B[pivotPos] = pivot;
		QuickSort(B, left, pivotPos - 1, swap_times);
		QuickSort(B, pivotPos + 1, right, swap_times);
	}
}


void HeapSort(vector<int>& B, int size, long long& swap_times) {
	Heap maxHeap = Heap(B, size, swap_times);
	for (int i = size - 1; i > 0; i--) {
		maxHeap.swap(0, i);
		swap_times++;
		maxHeap.siftDown(0, i - 1, swap_times);
	}
}

void merge(vector<int>& L1, vector<int>& L2, const int left, const int mid, const int right, long long& compare_times) {
	// L1[left:mid] and L1[mid+1:right]
	for (int i = left; i <= right; i++) {
		L2[i] = L1[i];
	}
	int s1 = left;
	int s2 = mid + 1;
	int t = left;
	while (s1 <= mid && s2 <= right) {
		compare_times++;
		if (L2[s1] <= L2[s2]) {
			L1[t++] = L2[s1++];
		}
		else {
			L1[t++] = L2[s2++];
		}
	}
	while (s1 <= mid) {
		compare_times++;
		L1[t++] = L2[s1++];
	}
	while (s2 <= right) {
		compare_times++;
		L1[t++] = L2[s2++];
	}
}


void MergeSort(vector<int>& L1, vector<int>& L2, int left, int right, long long& compare_times) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(L1, L2, left, mid, compare_times);
		MergeSort(L1, L2, mid + 1, right, compare_times);
		merge(L1, L2, left, mid, right, compare_times);
	}
}


// get the highest order of the largest figure
int MaxBit(vector<int> B, int n) {
	int max = B[0];
	for (int i = 1; i < n; i++ ) {
		if (max < B[i]) {
			max = B[i];
		}
	}
	int d = 1;
	int p = 10;
	while (max >= p) {
		max = max / 10;
		d++;
	}
	return d;
}


void RadixSort( vector<int>& B, int size, long long& swap_times) {
	int d = MaxBit(B, size);
	int* temp = new int[size];
	int count[10];
	// the radix which will be sorted by this
	int radix = 1;
	// make d times sorts
	for (int i = 1; i <= d; i++) {
		//empty the counter before each sorting
		for (int j = 0; j < 10; j++) {
			count[j] = 0;
		}
		for (int j = 0; j < size; j++) {
			int k = (B[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++) {
			count[j] = count[j - 1] + count[j];
		}
		// using temp[] to store the elements
		for (int j = size - 1; j >= 0; j--) {
			int k = (B[j] / radix) % 10;
			temp[count[k] - 1] = B[j];
			count[k]--;
		}
		for (int j = 0; j < size; j++) {
			B[j] = temp[j];
		}
		radix *= 10;
	}
}




vector<int> copyVector(int n) {
	vector<int> B;
	for (int i = 0; i < n; i++) {
		B.push_back(A[i]);
	}
	return B;
}


int checkInput(string input, int& num) {
	if (!isPositiveInterger(input)) {
		cout << "请输入正整数";
		return 0;
	}
	num = stoi(input);
	if (num > 100000 || num == 0) {
		cout << "个数请介于1-100000之间";
		return 0;
	}
	return 1;
}

int main()
{
	cout << "**" << setw(10) << ' ' << "排序算法比较" << setw(10) << ' ' << "**" << endl;
	cout << "====================================" << endl;
	cout << "**" << setw(9) << ' ' << "1 --- 冒泡排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "2 --- 选择排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "3 --- 直接插入排序" << setw(5) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "4 --- 希尔排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "5 --- 快速排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "6 --- 堆排序" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "7 --- 归并排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "8 --- 基数排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "9 --- 退出程序" << setw(9) << ' ' << "**" << endl;
	cout << "====================================" << endl;
	string input;
	int num;
	int loop = 1;
	while (loop) {
		cout << "请输入要产生随机数的个数: ";
		cin >> input;
		// input number is not proper
		if (!checkInput(input, num)) {
			cout << endl << endl;
		}
		else {
			loop = 0;
		}
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) {
		int item = rand();
		A.push_back(item);
	}
	/*
	for (int i = 0; i < num; i++) {
		cout << A[i] << ' ';
	}
	*/
	loop = 1;
	vector<int> B, C;
	long long swap_times, compare_times;
	while (loop) {
		cout << endl << "请选择排序算法：";
		int id;
		cin >> id;
		DWORD time_start, time_end;
		switch (id) {
		case 1:
			B = copyVector(num);
			swap_times = 0;
			time_start = GetTickCount();
			BubbleSort(B, num, swap_times);
			time_end = GetTickCount();
			cout << "冒泡排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "冒泡排序交换次数：" << swap_times << endl;
			break;
		case 2:
			B = copyVector(num);
			swap_times = 0;
			time_start = GetTickCount();
			SelectionSort(B, num, swap_times);
			time_end = GetTickCount();
			cout << "选择排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "选择排序交换次数：" << swap_times << endl;
			break;
		case 3:
			B = copyVector(num);
			swap_times = 0;
			time_start = GetTickCount();
			InsertionSort(B, num, swap_times);
			time_end = GetTickCount();
			cout << "直接插入排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "直接插入排序交换次数：" << swap_times << endl;
			break;
		case 4:
			B = copyVector(num);
			swap_times = 0;
			time_start = GetTickCount();
			ShellSort(B, num, swap_times);
			time_end = GetTickCount();
			cout << "希尔排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "希尔排序交换次数：" << swap_times << endl;
			break;
		case 5:
			B = copyVector(num);
			//DWORD time_start, time_end;
			swap_times = 0;
			time_start = GetTickCount();
			QuickSort(B, 0, num-1, swap_times);
			time_end = GetTickCount();
			cout << "快速排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "快速排序交换次数：" << swap_times << endl;
			break;
		case 6:
			B = copyVector(num);
			//DWORD time_start, time_end;
			swap_times = 0;
			time_start = GetTickCount();
			HeapSort(B, num, swap_times);
			time_end = GetTickCount();
			cout << "堆排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "堆排序交换次数：" << swap_times << endl;
			break;
		case 7:
			B = copyVector(num);
			C = copyVector(num);
			//DWORD time_start, time_end;
			compare_times = 0;
			time_start = GetTickCount();
			MergeSort(B, C, 0, num-1, compare_times);
			time_end = GetTickCount();
			cout << "归并排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "归并排序比较次数：" << compare_times << endl;
			break;
		case 8:
			B = copyVector(num);
			//DWORD time_start, time_end;
			swap_times = 0;
			time_start = GetTickCount();
			RadixSort(B, num, compare_times);
			time_end = GetTickCount();
			cout << "基数排序所用时间：" << (time_end - time_start) << "ms" << endl;
			cout << "基数排序交换次数：" << swap_times << endl;
			break;
		case 9:
			loop = 0;
			break;
		}
	}
	system("pause");
}