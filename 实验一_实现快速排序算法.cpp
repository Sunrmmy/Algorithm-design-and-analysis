#include <iostream>
#include <vector>
using namespace std;

// ��������Ԫ�صĸ�������
template<typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ������
template<typename T>
class Sorter {
public:
    // ð�������㷨
    void bubbleSort(vector<T>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {  // ���ǰһ��Ⱥ�һ���ͽ�������λ��
                    Swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // ���������㷨
    void quickSort(vector<T>& arr, int left, int right) {
        if (left < right) {
            T pivot = arr[left];  // ѡ����߽�Ԫ����Ϊ��׼ֵ
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
            quickSort(arr, left, L - 1);  // �ݹ�������벿��
            quickSort(arr, L + 1, right);  // �ݹ������Ұ벿��
        }
    }

    // ѡ�������㷨
    void selectSort(vector<T>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
					minIndex = j;       // �ҵ���СԪ�ص��±긳��minIndex
                }
            }
            if (minIndex != i) {
                Swap(arr[i], arr[minIndex]);
            }
        }
    }

	// ���������㷨
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

	// ϣ�������㷨
    void shellSort(vector<T>& arr) {
		int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {

        }
    }
};

// �������ݺ���
template<typename T>
void inputData(vector<T>& arr, int n) {
    cout << "������" << n << "������" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// ������ݺ���
template<typename T>
void outputData(vector<T>& arr) {
    cout << "����������: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // �������������һ����
    cout << "�����������������Ԫ�ظ�����" << endl;
    int n;
    cin >> n;

    cout << "�������������ͣ�0-������1-����������" << endl;
    int type;
    cin >> type;

    if (type == 0) {
        vector<int> arr(n);
        inputData(arr, n);

		Sorter<int> sorter;  //����ģ������Ϊint�Ķ���

        // ����ð�������㷨
        // sorter.bubbleSort(arr);

        // ���ÿ��������㷨
        // sorter.quickSort(arr, 0, n - 1);

        // ����ѡ�������㷨
        // sorter.selectSort(arr);

		// ���ò��������㷨
		// sorter.insertSort(arr);

        // �������������
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
        cout << "�������" << endl;
    }

    return 0;
}
