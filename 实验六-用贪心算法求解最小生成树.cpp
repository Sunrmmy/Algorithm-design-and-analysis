#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// �ڽӾ����ʾ������ͨ��Ȩͼ
class Graph {
private:
    int V;		//������
    vector<vector<int>> adjMatrix;	// ��άvector

public:
    Graph(int vertices) : V(vertices), adjMatrix(vertices, vector<int>(vertices, INT_MAX)) {};

    //��ӱ�
    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    const vector<vector<int>>& getMatrix() {
        return adjMatrix;
    }

    int getVertice() {
        return V;
    }
};

void Prim(vector<vector<int>>& adjMatrix, int V) {
    vector<bool> inMST(V, false);  //��Ƕ����Ƿ��Ѽ���MST
    vector<pair<int, pair<int, int>>> mstEdges;  // �洢MST�ı߼���

    // ʹ����С���Ż����洢��ʽ��{weight, {u, parent}}
    priority_queue<pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>>> pq;

    // �Ӷ���0��ʼ����MST��Ȩ��Ϊ0�����ڵ�Ϊ-1��ʾ���ڵ㣩
    pq.push({ 0, {0, -1} });

    while (!pq.empty()) {
        // ��ȡ��ǰ��СȨ�صı�
        int weight = pq.top().first;
        int u = pq.top().second.first;
        int parent = pq.top().second.second;
        pq.pop();

        //�����������MST��������
        if (inMST[u]) continue;

        inMST[u] = true;  //���������MST

        //���Ǹ��ڵ㣬��¼MST�ߣ����������ʼ������ߣ�
        if (parent != -1) {
            mstEdges.push_back({ weight, {parent, u} });
        }

        //������ǰ����������ڽӶ���
        for (int v = 0; v < V; ++v) {
            // ������ڱ�(u,v)��v����MST��
            if (adjMatrix[u][v] != INT_MAX && !inMST[v]) {
                // ���߼������ȶ��У�Ȩ��, {�ڽӶ���, ��ǰ����}��
                pq.push({ adjMatrix[u][v], {v, u} });
            }
        }
    }

    //���MST�ı�
    cout << "Prim�㷨����С�������ߣ�" << endl;
    for (auto& edge : mstEdges) {
        cout << edge.second.first + 1 << " - " << edge.second.second + 1
            << " : " << edge.first << endl;
    }
}




//�߽ṹ��
struct Edge {
    int src, dest, weight;       //Դ���㡢Ŀ�궥�㡢Ȩ��
};

//��ѯx,y������ͨ��֧
int find(vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]); //�ݹ���Ҹ��ڵ�
}

void Union(vector<int>& parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if (xset != yset)
        parent[xset] = yset; // ���x��y����ͬһ�������У��ϲ�����
}

bool CompareEdges(Edge& a, Edge& b) {
    return a.weight < b.weight;
}


void Kruskal(vector<Edge>& edges, int V) {
    vector<Edge> result;
    vector<int> parent(V, -1);

    // ��Ȩ�ش�С���������
    sort(edges.begin(), edges.end(), CompareEdges);


    for (auto& edge : edges) {
        int x = find(parent, edge.src);     //����Դ����ĸ��ڵ�
        int y = find(parent, edge.dest);    //����Ŀ�궥��ĸ��ڵ�

        if (x != y) {
            result.push_back(edge); //����MST
            Union(parent, x, y);    //�ϲ�����
        }
    }


    // ���MST�ı�
    cout << "Kruskal�㷨����С�������ߣ�" << endl;
    for (auto& edge : result) {
        cout << edge.src + 1 << " - " << edge.dest + 1 // ����ߵ��������㣬��1��ƥ��ԭʼ�����еı��
            << " : " << edge.weight << endl; // ����ߵ�Ȩ��
    }
}




int main() {
    Graph g(7);
    g.addEdge(0, 1, 6);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 5);
    g.addEdge(2, 4, 6);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 6);

    vector<vector<int>> gM = g.getMatrix();
    int V = g.getVertice();

    Prim(gM, V);

    vector<Edge> edges;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V;j++) {
            if (gM[i][j] != INT_MAX) {
                edges.push_back({ i, j, gM[i][j] });
            }
        }
    }

    Kruskal(edges,V);

    return 0;
}



