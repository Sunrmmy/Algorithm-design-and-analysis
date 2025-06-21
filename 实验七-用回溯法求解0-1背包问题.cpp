#include<iostream>
#include<vector>

using namespace std;

//����ȫ�ֱ���
int currentWeight = 0;		//��ǰ��������
int currentBagValue = 0;	//��ǰ������ֵ
int bestValue = 0;			//����ֵ
int goodsNum = 0;		//��Ʒ������input��
int bagMaxLimit = 0;	//���������أ�input��
	


//�����������
bool CheckData(int goodsNum, int bagMaxLimit, const vector<int>& weight, const vector<int>& value) {
	if (goodsNum <= 0 || bagMaxLimit <= 0) {
		cout << "���ݴ�������������" << endl;
		return 0;
	}
	for (int i = 0; i < goodsNum; i++) {
		if (weight[i] <= 0 || value[i] <= 0) {
			cout << "���ݴ�������������" << endl;
			return 0;
		}
	}
	return 1;
}

//��֦��������汾
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

 //��֦������ȷ����
 bool BetterBound(int i, const vector<int>& weight, const vector<int>& value) {
	int leftWt = bagMaxLimit - currentWeight; // ʣ������
	int cv = currentBagValue; // ��ǰ��ֵ

	if (currentWeight >= bagMaxLimit) {
		return false;
	}

	for (; i < goodsNum; i++) {
		if (weight[i] <= leftWt) {
			leftWt -= weight[i];
			cv += value[i];
		}
		else {
			cv += value[i] * (leftWt / (double)weight[i]); // �ָ����һ����Ʒ
			break;
		}
	}

	return cv > bestValue;
 }


//���ݷ����0-1��������
void KnapBacktrack(int i,const vector<int>& weight, const vector<int>& value) {
	//������ֹ����
	if (i > goodsNum) {
		bestValue = (bestValue < currentBagValue)?currentBagValue:bestValue; //��������ֵ
		return;
	}
	else {
		if (currentWeight + weight[i] <= bagMaxLimit) {		//��������
			currentWeight += weight[i];		//������Ʒi
			currentBagValue += value[i];	//������Ʒi�ļ�ֵ
			KnapBacktrack(i + 1, weight, value);	//�ݹ鵽��һ����Ʒ
			//���ݣ��ؼ���
			currentWeight -= weight[i];
			currentBagValue -= value[i];
		}
		if (BetterBound(i + 1, weight, value)) {
			KnapBacktrack(i + 1, weight, value);	//������������������Ʒi��
		}
	}
}


int main() {
	//����ϵͳ
	cout << "��������Ʒ��������";
	cin >> goodsNum;

	cout << "�����뱳���������أ�";
	cin >> bagMaxLimit;

	vector<int> weight(goodsNum,0);
	vector<int> value(goodsNum, 0);

	cout << "������ÿ����Ʒ��������";
	for (int i = 0; i < goodsNum; i++) {
		cin >> weight[i];
	}
	cout << "������ÿ����Ʒ�ļ�ֵ��";
	for (int i = 0; i < goodsNum; i++) {
		cin >> value[i];
	}

	//�������
	bool isDataCorrect = CheckData(goodsNum, bagMaxLimit, weight, value);
	if (!isDataCorrect) {
		return 0;
	}

	KnapBacktrack(0, weight, value);

	cout << "��������װ����Ʒ����ֵΪ��" << bestValue << endl;

	return 0;
}