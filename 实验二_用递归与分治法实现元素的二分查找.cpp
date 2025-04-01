#include<iostream>
#include<vector>
using namespace std;

// ���ֲ���
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
			cout << "����������鲻������ģ�����������" << endl;
			return false;
		}
	}
	return true;
}


int main() {
	// �������鳤�Ⱥ�����Ԫ��
	int n = 0;
	int key = 0;
	cout << "���鳤�ȣ�" << endl;
	cin >> n;
	vector<int> arr(n);
	cout << "���������������" << n << "������";
	
	bool isOrder = false;
	while (!isOrder) {
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		isOrder = isIncreasingOrder(arr, n);
	}

	cout << "��������Ҫ���ҵ�����";
	cin >> key;

	// ���ж��ֲ���
	int res = binarySearch(arr, key, n);

	// ������ҽ��
	cout << "���ҽ����";
	if (res == -1) {
		cout << "δ�ҵ�" << endl;
	}
	else {
		cout << "�±�Ϊ��" << res << endl;
	}

	return 0;
}