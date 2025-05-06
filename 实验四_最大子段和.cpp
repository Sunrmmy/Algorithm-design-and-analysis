#include<iostream>

/*
ʵ���ģ�����Ӷκ�
��������Description: ������n������(����Ϊ������)��ɵ�����a1 ,a2, ..., an,��������������Ӷκ͵����ֵ�� ������Ӷε�����Ԫ�غ��Ǹ�����ʱ����������Ӷκ�Ϊ0��
Input: ��һ����һ��������n(n<1000)�������n������,����ֵ��С��10000��ֱ���ļ�������
Output: �����������Ӷκ͡�
Sample Input
6 -2 11 -4 13 -5 -2
Sample Output
24
����������кܶ෽��������ͨ�����������Ρ���̬�滮����ʵ�����÷��κͶ�̬�滮�ķ������������Ŀ��
*/

// �Ҷ���Ŀ����⣺�����Input��һ�е�һ��������nӦ�ò����������еģ���������Ϊn+1��Ԫ�ء����nΪ���г��ȣ�������������Ӷκ͵ļ��㣬�������Input�õ���OutputӦ��Ϊ20��
//                 ����Ҫ��nҲ����������ֻ���main��ʼ�����벿�������޸ļ��ɡ���д����n���������е�����Ӷκ͡�

using namespace std;


//���η�
int MaxSubSum1(int arr[], int left, int right) {
    if (left == right) {
        // ֻ��һ��Ԫ��ʱ�����ظ�Ԫ�ػ�0������Ǹ�����
        return arr[left] > 0 ? arr[left] : 0;
    }

    int center = (left + right) / 2;

    // �ݹ������������ֵ�����Ӷκ�
    int leftsum = MaxSubSum1(arr, left, center);
    int rightsum = MaxSubSum1(arr, center + 1, right);

    // �ֱ�����Խ�м�����������ֵ�����Ӷκ�
    int leftmidsum = 0, leftmaxsum = 0;
    for (int i = center, sum = 0; i >= left; i--) {
        sum += arr[i];
		if (sum > leftmaxsum) { // ����ǰ�ʹ������ͣ����������
            leftmaxsum = sum;
        }
    }

    int rightmidsum = 0, rightmaxsum = 0;
    for (int i = center + 1, sum = 0; i <= right; i++) {
        sum += arr[i];
        if (sum > rightmaxsum) {
            rightmaxsum = sum;
        }
    }
    // ��Խ�м������Ӷκ�
    int crosssum = leftmaxsum + rightmaxsum;

    return max(max(leftsum, rightsum), crosssum);
}


//��̬�滮��
int MaxSubSumDP(int arr[], int n) {
	int maxsum = 0, thissum = 0;
	for (int i = 1; i <= n; i++) {
		thissum += arr[i];
		if (thissum > maxsum) {
			maxsum = thissum;
		}
		if (thissum < 0) {
			thissum = 0;
		}
	}
	return maxsum;
}



int main() {
	int* arr = new int[1001];
	int n = 0;
	cin >> n;
	arr[0] = n; // arr[0]�洢���г���n��arr[1]~arr[n]�洢����Ԫ��
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	int left = 1, right = n;
	int maxSubSum1 = MaxSubSum1(arr, left, right);
	int maxSubSumDP = MaxSubSumDP(arr, n);
	printf("�����η�������������ֶκ�Ϊ��%d\n", maxSubSum1);
	printf("����̬�滮��������������ֶκ�Ϊ��%d\n", maxSubSumDP);

	return 0;
}