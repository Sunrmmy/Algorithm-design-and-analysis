#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//����ȫ�ֱ���
int goodsNum = 0;           //��Ʒ������input��
int bagMaxLimit = 0;        //���������أ�input��
int bestValue = 0;          //����ֵ

//��Ʒ�ṹ�壬�������ȶ���
struct Node {
    int level;      //��ǰ�������Ʒ�㼶
    int weight;     //��ǰ��������
    int value;      //��ǰ������ֵ
    float bound;    //��ǰ�ڵ�ļ�ֵ�Ͻ�

    // ������������������ȶ��бȽϣ���bound�������У�
    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};

//�����������
bool CheckData(int goodsNum, const vector<int> weight, const vector<int> value) {
    if (goodsNum <= 0 || bagMaxLimit <= 0) {
        cout << "�����������" << endl;
        return false;
    }
    for (int i = 0; i < goodsNum; i++) {
        if (weight[i] <= 0 || value[i] <= 0) {
            cout << "�����������" << endl;
            return false;
        }
    }
    return true;
}

//�޽纯��
float Bound(int i, int currentWeight, int currentBagValue, const vector<int>& weight, const vector<int>& value) {    //iΪ��ǰ��Ʒ�±�����
    if (currentWeight > bagMaxLimit) return 0;    //��ǰ�����Ѿ��������������أ�����0
    float j = i + 1;    //jΪ��һ����Ʒ������
    float cv = currentBagValue;
    int cw = currentWeight;
    while (j < goodsNum && (cw + weight[j]) <= bagMaxLimit) {
        cw += weight[j];
        cv += value[j];
        j++;
    }
    if (j < goodsNum && cw < bagMaxLimit) {    //������ûװ����ʹ��̰��˼��װ������
        cv += (bagMaxLimit - cw) * (value[j] / (float)weight[j]);
    }
    return cv;
}

//���ȶ��з�֧�޽編
int knapsackPriorityQueue(const vector<int>& weight, const vector<int>& value, int goodsNum, int bagMaxLimit) {
    //���յ�λ��ֵ����������Ʒ
    vector<pair<int, int>> items(goodsNum);
    for (int i = 0; i < goodsNum; i++) {
        items[i] = { weight[i], value[i] };
    }

    //����λ��ֵ��������
    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return (float)a.second / a.first > (float)b.second / b.first;
        });

    //��������weight��value����
    vector<int> sortedWeight(goodsNum);
    vector<int> sortedValue(goodsNum);
    for (int i = 0; i < goodsNum; i++) {
        sortedWeight[i] = items[i].first;
        sortedValue[i] = items[i].second;
    }

    //��ʼ������ֵ
    int bestValue = 0;

    //�������ȶ���
    priority_queue<Node> pq;

    //��ʼ�ڵ�
    Node u;
    u.level = 0;
    u.weight = 0;
    u.value = 0;
    u.bound = Bound(0, u.weight, u.value, sortedWeight, sortedValue);
    pq.push(u);

    while (!pq.empty()) {
        //ȡ����ǰ���Žڵ�
        u = pq.top();
        pq.pop();

        //�����ǰ�ڵ���Ͻ�С�ڵ�ǰ����ֵ�����֦
        if (u.bound <= bestValue) {
            continue;
        }

        // ����Ѿ�������������Ʒ
        if (u.level == goodsNum) {
            continue;
        }
        else {
            // ������ӽڵ㣨ѡ��ǰ��Ʒ��
            int nextLevel = u.level + 1;
            if (u.weight + sortedWeight[nextLevel - 1] <= bagMaxLimit) {
                // ���н�
                int newWeight = u.weight + sortedWeight[nextLevel - 1];
                int newValue = u.value + sortedValue[nextLevel - 1];
             
                if (newValue > bestValue)   bestValue = newValue;   // �������Ž�

                // �������ӽڵ�
                Node leftNode;
                leftNode.level = nextLevel;
                leftNode.weight = newWeight;
                leftNode.value = newValue;
                leftNode.bound = Bound(nextLevel, newWeight, newValue, sortedWeight, sortedValue);
                pq.push(leftNode);
            }

            // ������ӽڵ㣨��ѡ��ǰ��Ʒ��
            Node rightNode;
            rightNode.level = nextLevel;
            rightNode.weight = u.weight;
            rightNode.value = u.value;
            rightNode.bound = Bound(nextLevel, u.weight, u.value, sortedWeight, sortedValue);

            // ������������ܰ������Ž�
            if (rightNode.bound > bestValue) {
                pq.push(rightNode);
            }
        }
    }

    return bestValue;
}

int main() {
    //����
    cout << "��������Ʒ������" << endl;
    cin >> goodsNum;
    cout << "�����뱳�������أ�" << endl;
    cin >> bagMaxLimit;

    vector<int> weight(goodsNum, 0);
    vector<int> value(goodsNum, 0);
    cout << "������ÿ����Ʒ��������" << endl;
    for (int i = 0; i < goodsNum; i++) {
        cin >> weight[i];
    }
    cout << "������ÿ����Ʒ�ļ�ֵ��" << endl;
    for (int i = 0; i < goodsNum; i++) {
        cin >> value[i];
    }

    //�������
    bool isDataCorrect = CheckData(goodsNum, weight, value);
    if (!isDataCorrect) {
        cout << "��������������������롣" << endl;
        return 0;
    }

    //�������ȶ��з�֧�޽編
    bestValue = knapsackPriorityQueue(weight, value, goodsNum, bagMaxLimit);

    cout << "����ֵΪ��" << bestValue << endl;

    return 0;
}
