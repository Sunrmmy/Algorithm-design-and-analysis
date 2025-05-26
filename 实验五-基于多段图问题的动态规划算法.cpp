#include <iostream>
#include <string>
#include <limits> // 用于 numeric_limits
/*
实验(五)基于多段图问题的动态规划算法设计
1. 实验目的
（1）掌握动态规划策略求解问题的基本原理、基本设计流程。
（2）能够利用合适的数据结构去表示求解问题的数据输入与输出，实现该数据结构。
（3）能够利用蛮力法求解多段图问题，具有设计并实现该算法的能力。
（4）能够利用动态规划策略求解多段图问题，具有设计并实现该算法的能力。
（5）分析与总结重叠子问题在该实验中的特点、应用、作用。
（6）理解动态规划策略求解多段图问题的时间复杂度分析；
（7）理解动态规划策略求解多段图问题的空间复杂度分析；
2. 实验内容
利用动态规划策略设计具有数据输入、处理和输出功能的多段图规划问题：求源点 S
到汇点 T 的最小成本路径的求解算法，实现算法的编译和运行，记录实验过程并整理实验
结果。根据原理图，连接实验线路。
*/


using namespace std;

#define MAXVEX 100
#define FLOAT_MAX numeric_limits<float>::max()

//图的邻接表结构定义
struct ArcNode {
    int adjvex;         //该弧所指向的顶点的位置
    int weight;         //弧的权值
    ArcNode* nextArc;   //指向下一个弧结点的指针
};

struct VertexNode {
    int vertex;         //顶点名称
    string step;        //所在阶段
    ArcNode* firstArc;
};

struct ALGraph {
    VertexNode adjList[MAXVEX];
};


void PrintShortestPath(ALGraph& G, int* d, int start);
void PrintGraph(ALGraph& G, int node);
void FreeGraph(ALGraph& G, int node);

//创建多段图
void CreatGraph(ALGraph& G, int node, int edge) {
    for (int i = 0; i < node; i++) {
        int nodeName = 0;
        string step;
        cout << "请输入第" << i + 1 << "个顶点的名称和所在阶段：" << endl;
        cin >> nodeName >> step;
        G.adjList[i].vertex = nodeName;     //命名顶点( 1(s), 2, 3..., 
        G.adjList[i].step = step;           //顶点所在阶段( V1, V2, V3, V4, V5 )
        G.adjList[i].firstArc = nullptr;
    }

    for (int i = 0; i < edge; i++) {
        int fromName = 0, toName = 0, weight = 0;
        cout << "请输入每条边的起点、终点和权值：" << endl;
        cin >> fromName >> toName >> weight;


        //查找起点名称和终点名称对应的adjList[Index]
        /*
        adjList下标是从0开始，考虑到我们创建的多段图起点名称（标识）为1，而不是0.
        这样创建多段图时虽然增加了查找步骤降低了效率，但是提高了程序的易用性和通用性，哪怕多段图顶点名称不是从0开始顺序的也能处理
        */
        int fromIndex = -1, toIndex = -1;
        for (int j = 0; j < node; j++)
            if (G.adjList[j].vertex == fromName) fromIndex = j;
        for (int j = 0; j < node; j++)
            if (G.adjList[j].vertex == toName) toIndex = j;

        if (fromIndex == -1 || toIndex == -1) {
            cout << "起点或终点名称不存在！" << endl;
            return;
        }

        ArcNode* arc = new ArcNode{ toIndex, weight, G.adjList[fromIndex].firstArc };
        G.adjList[fromIndex].firstArc = arc;    //每个新的弧节点都放在链表的头部
    }
}

//打印邻接表
void PrintGraph(ALGraph& G, int node) {
    for (int i = 0; i < node; i++) {
        cout << G.adjList[i].step << ":" << G.adjList[i].vertex << " -> ";
        for (ArcNode* arc = G.adjList[i].firstArc; arc; arc = arc->nextArc)
            cout << G.adjList[arc->adjvex].vertex << "(" << arc->weight << ") -> ";
        cout << "NULL" << endl;
    }
}

//动态规划求最小路径
float DP_MultiStageGraph(ALGraph& G, int node) {
    float* cost = new float[node];
    int* d = new int[node];     //d[i]保存Vi到下一阶段的最优连接点

    for (int i = 0; i < node; ++i) {
        cost[i] = FLOAT_MAX;
        d[i] = -1;
    }

    cost[node - 1] = 0;     //汇点到自己的最小成本为0

    for (int i = node - 2; i >= 0; i--) {
        for (ArcNode* arc = G.adjList[i].firstArc; arc; arc = arc->nextArc) {
            int j = arc->adjvex;    //该弧所指向的顶点的位置
            if (arc->weight + cost[j] < cost[i]) {
                cost[i] = arc->weight + cost[j];
                d[i] = j;   //保存最优连接点
            }
        }
    }

    PrintShortestPath(G, d, 0);
    float result = cost[0];

    delete[] cost;
    delete[] d;
    return result;
}

// 打印最短路径
void PrintShortestPath(ALGraph& G, int* d, int start) {
    cout << "最短路径为：";
    int current = start;
    while (current != -1) {
        cout << G.adjList[current].vertex;
        current = d[current];
        if (current != -1)
            cout << " -> ";
    }
    cout << endl;
}

// 释放动态分配的图内存
void FreeGraph(ALGraph& G, int node) {
    for (int i = 0; i < node; i++) {
        ArcNode* p = G.adjList[i].firstArc;
        while (p) {
            ArcNode* temp = p;
            p = p->nextArc;
            delete temp;
        }
    }
}


int main() {
    ALGraph G;
    int node = 0, edge = 0;
    cout << "请输入顶点个数和边的个数：";
    cin >> node >> edge;

    CreatGraph(G, node, edge);
    cout << "\n图的邻接表如下：" << endl;
    PrintGraph(G, node);

    float minCost = DP_MultiStageGraph(G, node);
    cout << "源点到汇点的最小成本为：" << minCost << endl;

    FreeGraph(G, node);
    return 0;
}