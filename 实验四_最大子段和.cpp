#include<iostream>

/*
实验四：最大子段和
问题描述Description: 给定有n个整数(可能为负整数)组成的序列a1 ,a2, ..., an,求该序列连续的子段和的最大值。 如果该子段的所有元素和是负整数时定义其最大子段和为0。
Input: 第一行有一个正整数n(n<1000)，后面跟n个整数,绝对值都小于10000。直到文件结束。
Output: 输出它的最大子段和。
Sample Input
6 -2 11 -4 13 -5 -2
Sample Output
24
解决该问题有很多方法，可以通过暴力、分治、动态规划。本实验运用分治和动态规划的方法来解决该题目。
*/

// 我对题目的理解：这里的Input第一行的一个正整数n应该不算在序列中的，否则序列为n+1个元素。这个n为序列长度，并不参与最大子段和的计算，因此所给Input得到的Output应该为20。
//                 若需要连n也算入序列内只需对main开始的输入部分稍作修改即可。我写的是n不算入序列的最大子段和。

using namespace std;


//分治法
int MaxSubSum1(int arr[], int left, int right) {
    if (left == right) {
        // 只有一个元素时，返回该元素或0（如果是负数）
        return arr[left] > 0 ? arr[left] : 0;
    }

    int center = (left + right) / 2;

    // 递归求左右两部分的最大子段和
    int leftsum = MaxSubSum1(arr, left, center);
    int rightsum = MaxSubSum1(arr, center + 1, right);

    // 分别计算跨越中间的左右两部分的最大子段和
    int leftmidsum = 0, leftmaxsum = 0;
    for (int i = center, sum = 0; i >= left; i--) {
        sum += arr[i];
		if (sum > leftmaxsum) { // 若当前和大于最大和，则更新最大和
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
    // 跨越中间的最大子段和
    int crosssum = leftmaxsum + rightmaxsum;

    return max(max(leftsum, rightsum), crosssum);
}


//动态规划法
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
	arr[0] = n; // arr[0]存储序列长度n，arr[1]~arr[n]存储序列元素
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	int left = 1, right = n;
	int maxSubSum1 = MaxSubSum1(arr, left, right);
	int maxSubSumDP = MaxSubSumDP(arr, n);
	printf("（分治法）该序列最大字段和为：%d\n", maxSubSum1);
	printf("（动态规划法）该序列最大字段和为：%d\n", maxSubSumDP);

	return 0;
}