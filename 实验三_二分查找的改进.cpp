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

// ���ֲ��ң��Ż�����һ����> ��ֵ����
/*
	���������
	ԭ����mid���㷽ʽ�� (left + right) / 2 = left + (right - left) / 2
	���������ϳ�������ʱ����Ҫ���ҵ����ڷǳ������������˵��������Ч�ʾͻ�ϵ�

	�Ż�˼·��
	�������ǿ��Ը�����Ҫ���ҵ�keyֵ��̬����midֵʹ�ü����mid�����׽ӽ�key����Ч��߲���Ч�ʡ�
	ͨ��keyֵ����Сֵ�ġ����롱���������������Сֵ�����롱��ֵȥ����mid�Ļ��ֱ�ֵ������ڹ̶���1/2���ָ�����Ч��
	
	�ܽ᣺
	���ڴ���������ֲ����㷨��һ�µģ�����ʱ�临�Ӷ���Ȼ��O(logn)�����������ݷֲ���Ϊ���ȵ������Ч�ʻ���ߡ�
	ȱ�㣺���������ݷֲ������ȵ�����¿���Ч�ʷ����ϵ�
*/
int insertValueSearch(vector<int>& arr, int key, int n) {
	int left = 0, right = n - 1;
	if (key < arr[left] || key > arr[right])
		return -1;

	while (left <= right) {
		int mid = left + (key - arr[left]) / (arr[right] - arr[left]) * (right - left);	//�ؼ�������mid
		if (key == arr[mid])
			return mid;
		else if (key < arr[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}


// ���ֲ��ң��Ż�����������> 쳲���������
/*
	�Ż�˼·��
	����쳲��������еĲ����㷨������쳲��������е��������������顣
	
	�� mid = left + F(k-1) - 1 ����⣺
	F(k) = F(k-1) + F(k-2)����΢����һ�£�(F(k)-1) = (F(k-1)-1) + (F(k-2)-1) + 1	���ɽ�F(k)-1��Ԫ�ػ���ΪF(k-1)-1��F(k-2)-1���� + mid��
	
	�ܽ᣺
	ʱ�临�Ӷ���Ȼ��O(logn)����ƽ��������˵�ȶ��ֲ��Ҹ��á�
	ȱ�㣺��Ҫ��ʵ��쳲��������У�ʵ�ֽ�Ϊ����
*/

// 쳲���������
int* fibonacci(int n) {
	int* fib = new int[n + 1];
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib;
}
// 쳲���������
int fibonacciSearch(vector<int>& arr, int key, int n) {
	int* fib = fibonacci(20);
	int left = 0, right = n - 1;
	int k = 0;
	while (n > fib[k] - 1) {
		k++;
	}
	//������ʱ����ʹ�����鳤�ȴﵽfib[k]-1
	vector<int> temp(fib[k] - 1);		//���fib[k]-1 > n������arr�����һ��Ԫ����䵽fib[k]-1
	for (int i = 0; i < n; i++) {
		temp[i] = arr[i];
	}
	for (int i = n; i < fib[k] - 1; i++) {
		temp[i] = arr[n - 1];
	}

	//��ʼ����
	while (left <= right) {
		int mid = left + fib[k - 1] - 1;//�ؼ�������mid = left + F(k-1) - 1

		if (temp[mid] == key) {
			delete[] fib;				//�ͷ�쳲���������
			return (mid < n) ? mid : n - 1;
		}
		else if (temp[mid] < key) {
			left = mid + 1;
			k -= 2;						//�Ұ벿�֣�F(k) = F(k-1) + F(k-2)
		}
		else {
			right = mid - 1;
			k -= 1;						//��벿�֣�F(k) = F(k-1) + F(k-2)
		}
	}
	delete[] fib;
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
	//int res = binarySearch(arr, key, n);
	//int res = insertValueSearch(arr, key, n);
	int res = fibonacciSearch(arr, key, n);

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