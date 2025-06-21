#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//定义全局变量
int goodsNum = 0;           //物品数量（input）
int bagMaxLimit = 0;        //背包最大承重（input）
int bestValue = 0;          //最大价值

//物品结构体，用于优先队列
struct Node {
    int level;      //当前处理的物品层级
    int weight;     //当前背包重量
    int value;      //当前背包价值
    float bound;    //当前节点的价值上界

    // 重载运算符，用于优先队列比较（按bound降序排列）
    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};

//检查输入数据
bool CheckData(int goodsNum, const vector<int> weight, const vector<int> value) {
    if (goodsNum <= 0 || bagMaxLimit <= 0) {
        cout << "数据输入错误" << endl;
        return false;
    }
    for (int i = 0; i < goodsNum; i++) {
        if (weight[i] <= 0 || value[i] <= 0) {
            cout << "数据输入错误" << endl;
            return false;
        }
    }
    return true;
}

//限界函数
float Bound(int i, int currentWeight, int currentBagValue, const vector<int>& weight, const vector<int>& value) {    //i为当前物品下标索引
    if (currentWeight > bagMaxLimit) return 0;    //当前重量已经超过背包最大承重，返回0
    float j = i + 1;    //j为下一个物品的索引
    float cv = currentBagValue;
    int cw = currentWeight;
    while (j < goodsNum && (cw + weight[j]) <= bagMaxLimit) {
        cw += weight[j];
        cv += value[j];
        j++;
    }
    if (j < goodsNum && cw < bagMaxLimit) {    //背包还没装满，使用贪心思想装满背包
        cv += (bagMaxLimit - cw) * (value[j] / (float)weight[j]);
    }
    return cv;
}

//优先队列分支限界法
int knapsackPriorityQueue(const vector<int>& weight, const vector<int>& value, int goodsNum, int bagMaxLimit) {
    //按照单位价值降序排序物品
    vector<pair<int, int>> items(goodsNum);
    for (int i = 0; i < goodsNum; i++) {
        items[i] = { weight[i], value[i] };
    }

    //按单位价值降序排序
    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return (float)a.second / a.first > (float)b.second / b.first;
        });

    //重新排列weight和value数组
    vector<int> sortedWeight(goodsNum);
    vector<int> sortedValue(goodsNum);
    for (int i = 0; i < goodsNum; i++) {
        sortedWeight[i] = items[i].first;
        sortedValue[i] = items[i].second;
    }

    //初始化最优值
    int bestValue = 0;

    //创建优先队列
    priority_queue<Node> pq;

    //初始节点
    Node u;
    u.level = 0;
    u.weight = 0;
    u.value = 0;
    u.bound = Bound(0, u.weight, u.value, sortedWeight, sortedValue);
    pq.push(u);

    while (!pq.empty()) {
        //取出当前最优节点
        u = pq.top();
        pq.pop();

        //如果当前节点的上界小于当前最优值，则剪枝
        if (u.bound <= bestValue) {
            continue;
        }

        // 如果已经处理完所有物品
        if (u.level == goodsNum) {
            continue;
        }
        else {
            // 检查左子节点（选择当前物品）
            int nextLevel = u.level + 1;
            if (u.weight + sortedWeight[nextLevel - 1] <= bagMaxLimit) {
                // 可行解
                int newWeight = u.weight + sortedWeight[nextLevel - 1];
                int newValue = u.value + sortedValue[nextLevel - 1];
             
                if (newValue > bestValue)   bestValue = newValue;   // 更新最优解

                // 创建左子节点
                Node leftNode;
                leftNode.level = nextLevel;
                leftNode.weight = newWeight;
                leftNode.value = newValue;
                leftNode.bound = Bound(nextLevel, newWeight, newValue, sortedWeight, sortedValue);
                pq.push(leftNode);
            }

            // 检查右子节点（不选择当前物品）
            Node rightNode;
            rightNode.level = nextLevel;
            rightNode.weight = u.weight;
            rightNode.value = u.value;
            rightNode.bound = Bound(nextLevel, u.weight, u.value, sortedWeight, sortedValue);

            // 如果右子树可能包含最优解
            if (rightNode.bound > bestValue) {
                pq.push(rightNode);
            }
        }
    }

    return bestValue;
}

int main() {
    //输入
    cout << "请输入物品数量：" << endl;
    cin >> goodsNum;
    cout << "请输入背包最大承重：" << endl;
    cin >> bagMaxLimit;

    vector<int> weight(goodsNum, 0);
    vector<int> value(goodsNum, 0);
    cout << "请输入每个物品的重量：" << endl;
    for (int i = 0; i < goodsNum; i++) {
        cin >> weight[i];
    }
    cout << "请输入每个物品的价值：" << endl;
    for (int i = 0; i < goodsNum; i++) {
        cin >> value[i];
    }

    //检查数据
    bool isDataCorrect = CheckData(goodsNum, weight, value);
    if (!isDataCorrect) {
        cout << "数据输入错误，请重新输入。" << endl;
        return 0;
    }

    //调用优先队列分支限界法
    bestValue = knapsackPriorityQueue(weight, value, goodsNum, bagMaxLimit);

    cout << "最大价值为：" << bestValue << endl;

    return 0;
}
