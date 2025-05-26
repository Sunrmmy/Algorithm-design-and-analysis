#include <iostream>
#include <string>
#include <limits> // ���� numeric_limits
/*
ʵ��(��)���ڶ��ͼ����Ķ�̬�滮�㷨���
1. ʵ��Ŀ��
��1�����ն�̬�滮�����������Ļ���ԭ������������̡�
��2���ܹ����ú��ʵ����ݽṹȥ��ʾ�����������������������ʵ�ָ����ݽṹ��
��3���ܹ����������������ͼ���⣬������Ʋ�ʵ�ָ��㷨��������
��4���ܹ����ö�̬�滮���������ͼ���⣬������Ʋ�ʵ�ָ��㷨��������
��5���������ܽ��ص��������ڸ�ʵ���е��ص㡢Ӧ�á����á�
��6����⶯̬�滮���������ͼ�����ʱ�临�Ӷȷ�����
��7����⶯̬�滮���������ͼ����Ŀռ临�Ӷȷ�����
2. ʵ������
���ö�̬�滮������ƾ����������롢�����������ܵĶ��ͼ�滮���⣺��Դ�� S
����� T ����С�ɱ�·��������㷨��ʵ���㷨�ı�������У���¼ʵ����̲�����ʵ��
���������ԭ��ͼ������ʵ����·��
*/


using namespace std;

#define MAXVEX 100
#define FLOAT_MAX numeric_limits<float>::max()

//ͼ���ڽӱ�ṹ����
struct ArcNode {
    int adjvex;         //�û���ָ��Ķ����λ��
    int weight;         //����Ȩֵ
    ArcNode* nextArc;   //ָ����һ��������ָ��
};

struct VertexNode {
    int vertex;         //��������
    string step;        //���ڽ׶�
    ArcNode* firstArc;
};

struct ALGraph {
    VertexNode adjList[MAXVEX];
};


void PrintShortestPath(ALGraph& G, int* d, int start);
void PrintGraph(ALGraph& G, int node);
void FreeGraph(ALGraph& G, int node);

//�������ͼ
void CreatGraph(ALGraph& G, int node, int edge) {
    for (int i = 0; i < node; i++) {
        int nodeName = 0;
        string step;
        cout << "�������" << i + 1 << "����������ƺ����ڽ׶Σ�" << endl;
        cin >> nodeName >> step;
        G.adjList[i].vertex = nodeName;     //��������( 1(s), 2, 3..., 
        G.adjList[i].step = step;           //�������ڽ׶�( V1, V2, V3, V4, V5 )
        G.adjList[i].firstArc = nullptr;
    }

    for (int i = 0; i < edge; i++) {
        int fromName = 0, toName = 0, weight = 0;
        cout << "������ÿ���ߵ���㡢�յ��Ȩֵ��" << endl;
        cin >> fromName >> toName >> weight;


        //����������ƺ��յ����ƶ�Ӧ��adjList[Index]
        /*
        adjList�±��Ǵ�0��ʼ�����ǵ����Ǵ����Ķ��ͼ������ƣ���ʶ��Ϊ1��������0.
        �����������ͼʱ��Ȼ�����˲��Ҳ��轵����Ч�ʣ���������˳���������Ժ�ͨ���ԣ����¶��ͼ�������Ʋ��Ǵ�0��ʼ˳���Ҳ�ܴ���
        */
        int fromIndex = -1, toIndex = -1;
        for (int j = 0; j < node; j++)
            if (G.adjList[j].vertex == fromName) fromIndex = j;
        for (int j = 0; j < node; j++)
            if (G.adjList[j].vertex == toName) toIndex = j;

        if (fromIndex == -1 || toIndex == -1) {
            cout << "�����յ����Ʋ����ڣ�" << endl;
            return;
        }

        ArcNode* arc = new ArcNode{ toIndex, weight, G.adjList[fromIndex].firstArc };
        G.adjList[fromIndex].firstArc = arc;    //ÿ���µĻ��ڵ㶼���������ͷ��
    }
}

//��ӡ�ڽӱ�
void PrintGraph(ALGraph& G, int node) {
    for (int i = 0; i < node; i++) {
        cout << G.adjList[i].step << ":" << G.adjList[i].vertex << " -> ";
        for (ArcNode* arc = G.adjList[i].firstArc; arc; arc = arc->nextArc)
            cout << G.adjList[arc->adjvex].vertex << "(" << arc->weight << ") -> ";
        cout << "NULL" << endl;
    }
}

//��̬�滮����С·��
float DP_MultiStageGraph(ALGraph& G, int node) {
    float* cost = new float[node];
    int* d = new int[node];     //d[i]����Vi����һ�׶ε��������ӵ�

    for (int i = 0; i < node; ++i) {
        cost[i] = FLOAT_MAX;
        d[i] = -1;
    }

    cost[node - 1] = 0;     //��㵽�Լ�����С�ɱ�Ϊ0

    for (int i = node - 2; i >= 0; i--) {
        for (ArcNode* arc = G.adjList[i].firstArc; arc; arc = arc->nextArc) {
            int j = arc->adjvex;    //�û���ָ��Ķ����λ��
            if (arc->weight + cost[j] < cost[i]) {
                cost[i] = arc->weight + cost[j];
                d[i] = j;   //�����������ӵ�
            }
        }
    }

    PrintShortestPath(G, d, 0);
    float result = cost[0];

    delete[] cost;
    delete[] d;
    return result;
}

// ��ӡ���·��
void PrintShortestPath(ALGraph& G, int* d, int start) {
    cout << "���·��Ϊ��";
    int current = start;
    while (current != -1) {
        cout << G.adjList[current].vertex;
        current = d[current];
        if (current != -1)
            cout << " -> ";
    }
    cout << endl;
}

// �ͷŶ�̬�����ͼ�ڴ�
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
    cout << "�����붥������ͱߵĸ�����";
    cin >> node >> edge;

    CreatGraph(G, node, edge);
    cout << "\nͼ���ڽӱ����£�" << endl;
    PrintGraph(G, node);

    float minCost = DP_MultiStageGraph(G, node);
    cout << "Դ�㵽������С�ɱ�Ϊ��" << minCost << endl;

    FreeGraph(G, node);
    return 0;
}