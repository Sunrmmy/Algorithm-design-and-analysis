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

// 二分查找（优化方案一）—> 插值查找
/*
	问题分析：
	原本的mid计算方式是 (left + right) / 2 = left + (right - left) / 2
	这样当给较长定数组时，所要查找的数在非常靠近数组两端的情况查找效率就会较低

	优化思路：
	所以我们可以根据所要查找的key值动态计算mid值使得计算的mid更容易接近key，有效提高查找效率。
	通过key值到最小值的“距离”与数组中最大与最小值“距离”比值去计算mid的划分比值，相较于固定的1/2划分更灵活高效。
	
	总结：
	由于大体框架与二分查找算法是一致的，所以时间复杂度仍然是O(logn)，但是在数据分布较为均匀的情况下效率会更高。
	缺点：再数组数据分布不均匀的情况下可能效率反而较低
*/
int insertValueSearch(vector<int>& arr, int key, int n) {
	int left = 0, right = n - 1;
	if (key < arr[left] || key > arr[right])
		return -1;

	while (left <= right) {
		int mid = left + (key - arr[left]) / (arr[right] - arr[left]) * (right - left);	//关键：划分mid
		if (key == arr[mid])
			return mid;
		else if (key < arr[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}


// 二分查找（优化方案二）—> 斐波那契查找
/*
	优化思路：
	基于斐波那契数列的查找算法，利用斐波那契数列的性质来划分数组。
	
	对 mid = left + F(k-1) - 1 的理解：
	F(k) = F(k-1) + F(k-2)，稍微变形一下：(F(k)-1) = (F(k-1)-1) + (F(k-2)-1) + 1	即可将F(k)-1个元素划分为F(k-1)-1和F(k-2)-1两段 + mid。
	
	总结：
	时间复杂度仍然是O(logn)，就平均性能来说比二分查找更好。
	缺点：需要先实现斐波那契数列，实现较为复杂
*/

// 斐波那契数列
int* fibonacci(int n) {
	int* fib = new int[n + 1];
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib;
}
// 斐波那契查找
int fibonacciSearch(vector<int>& arr, int key, int n) {
	int* fib = fibonacci(20);
	int left = 0, right = n - 1;
	int k = 0;
	while (n > fib[k] - 1) {
		k++;
	}
	//创建临时数组使得数组长度达到fib[k]-1
	vector<int> temp(fib[k] - 1);		//如果fib[k]-1 > n，则用arr的最后一个元素填充到fib[k]-1
	for (int i = 0; i < n; i++) {
		temp[i] = arr[i];
	}
	for (int i = n; i < fib[k] - 1; i++) {
		temp[i] = arr[n - 1];
	}

	//开始查找
	while (left <= right) {
		int mid = left + fib[k - 1] - 1;//关键：划分mid = left + F(k-1) - 1

		if (temp[mid] == key) {
			delete[] fib;				//释放斐波那契数组
			return (mid < n) ? mid : n - 1;
		}
		else if (temp[mid] < key) {
			left = mid + 1;
			k -= 2;						//右半部分，F(k) = F(k-1) + F(k-2)
		}
		else {
			right = mid - 1;
			k -= 1;						//左半部分，F(k) = F(k-1) + F(k-2)
		}
	}
	delete[] fib;
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
	//int res = binarySearch(arr, key, n);
	//int res = insertValueSearch(arr, key, n);
	int res = fibonacciSearch(arr, key, n);

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