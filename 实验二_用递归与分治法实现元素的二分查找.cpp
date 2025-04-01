#include<iostream>
#include<vector>
using namespace std;

// 二分查找
int binarySearch(vector<int>& arr, int key, int n) {
	int left = 0, right = n - 1;
	if (key < arr[left] || key > arr[right]) 
		return -1;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (key == arr[mid]) 
			return mid;
		else if (key < arr[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

bool isIncreasingOrder(vector<int>& arr, int n) {
	for (int i = 0; i < n - 2; i++) {
		if (arr[i] > arr[i + 1]) {
			cout << "你输入的数组不是有序的，请重新输入" << endl;
			return false;
		}
	}
	return true;
}


int main() {
	// 输入数组长度和数组元素
	int n = 0;
	int key = 0;
	cout << "数组长度：" << endl;
	cin >> n;
	vector<int> arr(n);
	cout << "请输入有序递增的" << n << "个数：";
	
	bool isOrder = false;
	while (!isOrder) {
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		isOrder = isIncreasingOrder(arr, n);
	}

	cout << "请输入你要查找的数：";
	cin >> key;

	// 进行二分查找
	int res = binarySearch(arr, key, n);

	// 输出查找结果
	cout << "查找结果：";
	if (res == -1) {
		cout << "未找到" << endl;
	}
	else {
		cout << "下标为：" << res << endl;
	}

	return 0;
}