#include<iostream>
#include<vector>

using namespace std;

//定义全局变量
int currentWeight = 0;		//当前背包重量
int currentBagValue = 0;	//当前背包价值
int bestValue = 0;			//最大价值
int goodsNum = 0;		//物品数量（input）
int bagMaxLimit = 0;	//背包最大承重（input）
	


//检查输入数据
bool CheckData(int goodsNum, int bagMaxLimit, const vector<int>& weight, const vector<int>& value) {
	if (goodsNum <= 0 || bagMaxLimit <= 0) {
		cout << "数据错误，请重新输入" << endl;
		return 0;
	}
	for (int i = 0; i < goodsNum; i++) {
		if (weight[i] <= 0 || value[i] <= 0) {
			cout << "数据错误，请重新输入" << endl;
			return 0;
		}
	}
	return 1;
}

//剪枝函数错误版本
// bool Bound(int i,const vector<int>& weight, const vector<int>& value, int currentBagValue) {
//	 int cv = currentBagValue;
//	 int cw = currentWeight;
//	 
//	 for (int j = i; j < goodsNum && cw <= bagMaxLimit; j++) {
//		 cv += value[j];
//		 cw += weight[j];
//		 if (cv > bestValue)
//			 return true;
//	 }
//	 return false;
//}

 //剪枝函数正确处理
 bool BetterBound(int i, const vector<int>& weight, const vector<int>& value) {
	int leftWt = bagMaxLimit - currentWeight; // 剩余容量
	int cv = currentBagValue; // 当前价值

	if (currentWeight >= bagMaxLimit) {
		return false;
	}

	for (; i < goodsNum; i++) {
		if (weight[i] <= leftWt) {
			leftWt -= weight[i];
			cv += value[i];
		}
		else {
			cv += value[i] * (leftWt / (double)weight[i]); // 分割最后一个物品
			break;
		}
	}

	return cv > bestValue;
 }


//回溯法求解0-1背包问题
void KnapBacktrack(int i,const vector<int>& weight, const vector<int>& value) {
	//设置终止条件
	if (i > goodsNum) {
		bestValue = (bestValue < currentBagValue)?currentBagValue:bestValue; //更新最大价值
		return;
	}
	else {
		if (currentWeight + weight[i] <= bagMaxLimit) {		//走左子树
			currentWeight += weight[i];		//加入物品i
			currentBagValue += value[i];	//加入物品i的价值
			KnapBacktrack(i + 1, weight, value);	//递归到下一个物品
			//回溯（关键）
			currentWeight -= weight[i];
			currentBagValue -= value[i];
		}
		if (BetterBound(i + 1, weight, value)) {
			KnapBacktrack(i + 1, weight, value);	//走右子树（不加入物品i）
		}
	}
}


int main() {
	//输入系统
	cout << "请输入物品的数量：";
	cin >> goodsNum;

	cout << "请输入背包的最大承重：";
	cin >> bagMaxLimit;

	vector<int> weight(goodsNum,0);
	vector<int> value(goodsNum, 0);

	cout << "请输入每个物品的重量：";
	for (int i = 0; i < goodsNum; i++) {
		cin >> weight[i];
	}
	cout << "请输入每个物品的价值：";
	for (int i = 0; i < goodsNum; i++) {
		cin >> value[i];
	}

	//检查数据
	bool isDataCorrect = CheckData(goodsNum, bagMaxLimit, weight, value);
	if (!isDataCorrect) {
		return 0;
	}

	KnapBacktrack(0, weight, value);

	cout << "背包所能装的物品最大价值为：" << bestValue << endl;

	return 0;
}