#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// 邻接矩阵表示无向连通带权图
class Graph {
private:
    int V;		//顶点数
    vector<vector<int>> adjMatrix;	// 二维vector

public:
    Graph(int vertices) : V(vertices), adjMatrix(vertices, vector<int>(vertices, INT_MAX)) {};

    //添加边
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
    vector<bool> inMST(V, false);  //标记顶点是否已加入MST
    vector<pair<int, pair<int, int>>> mstEdges;  // 存储MST的边集合

    // 使用最小堆优化，存储格式：{weight, {u, parent}}
    priority_queue<pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>>> pq;

    // 从顶点0开始构建MST（权重为0，父节点为-1表示根节点）
    pq.push({ 0, {0, -1} });

    while (!pq.empty()) {
        // 获取当前最小权重的边
        int weight = pq.top().first;
        int u = pq.top().second.first;
        int parent = pq.top().second.second;
        pq.pop();

        //如果顶点已在MST中则跳过
        if (inMST[u]) continue;

        inMST[u] = true;  //将顶点加入MST

        //若非根节点，记录MST边（避免包含初始的虚拟边）
        if (parent != -1) {
            mstEdges.push_back({ weight, {parent, u} });
        }

        //遍历当前顶点的所有邻接顶点
        for (int v = 0; v < V; ++v) {
            // 如果存在边(u,v)且v不在MST中
            if (adjMatrix[u][v] != INT_MAX && !inMST[v]) {
                // 将边加入优先队列（权重, {邻接顶点, 当前顶点}）
                pq.push({ adjMatrix[u][v], {v, u} });
            }
        }
    }

    //输出MST的边
    cout << "Prim算法的最小生成树边：" << endl;
    for (auto& edge : mstEdges) {
        cout << edge.second.first + 1 << " - " << edge.second.second + 1
            << " : " << edge.first << endl;
    }
}




//边结构体
struct Edge {
    int src, dest, weight;       //源顶点、目标顶点、权重
};

//查询x,y所属连通分支
int find(vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]); //递归查找根节点
}

void Union(vector<int>& parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if (xset != yset)
        parent[xset] = yset; // 如果x和y不在同一个集合中，合并它们
}

bool CompareEdges(Edge& a, Edge& b) {
    return a.weight < b.weight;
}


void Kruskal(vector<Edge>& edges, int V) {
    vector<Edge> result;
    vector<int> parent(V, -1);

    // 按权重从小到大排序边
    sort(edges.begin(), edges.end(), CompareEdges);


    for (auto& edge : edges) {
        int x = find(parent, edge.src);     //查找源顶点的根节点
        int y = find(parent, edge.dest);    //查找目标顶点的根节点

        if (x != y) {
            result.push_back(edge); //加入MST
            Union(parent, x, y);    //合并集合
        }
    }


    // 输出MST的边
    cout << "Kruskal算法的最小生成树边：" << endl;
    for (auto& edge : result) {
        cout << edge.src + 1 << " - " << edge.dest + 1 // 输出边的两个顶点，加1以匹配原始输入中的编号
            << " : " << edge.weight << endl; // 输出边的权重
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



