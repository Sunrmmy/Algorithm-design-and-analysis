#include <iostream>
#include <vector>
using namespace std;

// 交换两个元素的辅助函数
template<typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 排序类
template<typename T>
class Sorter {
public:
    // 冒泡排序算法
    void bubbleSort(vector<T>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {  // 如果前一项比后一项大就交换两数位置
                    Swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // 快速排序算法
    void quickSort(vector<T>& arr, int left, int right) {
        if (left < right) {
            T pivot = arr[left];  // 选择左边界元素作为基准值
            int L = left, R = right;
            while (L < R) {
                while (L < R && arr[R] >= pivot) {
                    R--;
                }
                arr[L] = arr[R];
                while (L < R && arr[L] <= pivot) {
                    L++;
                }
                arr[R] = arr[L];
            }
            arr[L] = pivot;
            quickSort(arr, left, L - 1);  // 递归排序左半部分
            quickSort(arr, L + 1, right);  // 递归排序右半部分
        }
    }

    // 选择排序算法
    void selectSort(vector<T>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
					minIndex = j;       // 找到最小元素的下标赋给minIndex
                }
            }
            if (minIndex != i) {
                Swap(arr[i], arr[minIndex]);
            }
        }
    }

	// 插入排序算法
    void insertSort(vector<T>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[i] < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

	// 希尔排序算法
    void shellSort(vector<T>& arr) {
		int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {

        }
    }
};

// 输入数据函数
template<typename T>
void inputData(vector<T>& arr, int n) {
    cout << "请输入" << n << "个数：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// 输出数据函数
template<typename T>
void outputData(vector<T>& arr) {
    cout << "排序后的数组: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 定义所需排序的一组数
    cout << "请输入需排序的数组元素个数：" << endl;
    int n;
    cin >> n;

    cout << "请输入数据类型（0-整数，1-浮点数）：" << endl;
    int type;
    cin >> type;

    if (type == 0) {
        vector<int> arr(n);
        inputData(arr, n);

		Sorter<int> sorter;  //创建模板类型为int的对象、

        // 调用冒泡排序算法
        // sorter.bubbleSort(arr);

        // 调用快速排序算法
        // sorter.quickSort(arr, 0, n - 1);

        // 调用选择排序算法
        // sorter.selectSort(arr);

		// 调用插入排序算法
		// sorter.insertSort(arr);

        // 输出排序后的数组
        outputData(arr);
    }
    else if (type == 1) {
        vector<double> arr(n);
        inputData(arr, n);
		Sorter<double> sorter;

        // sorter.bubbleSort(arr);
        // sorter.quickSort(arr, 0, n - 1);
        // sorter.selectSort(arr);
        // sorter.insertSort(arr);

        outputData(arr);
    }
    else {
        cout << "输入错误！" << endl;
    }

    return 0;
}
