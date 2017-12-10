#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

const int MAXVEX = 20;
// const int INFINITY = 65535;
vector<bool> visited(MAXVEX, 0);  //标记是否已经访问过

class Graph {
private:
    vector<char> vertex;  //顶点表
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numVertex, numEdge;  //顶点数，边数

public:
    Graph() : inDegree(MAXVEX), outDegree(MAXVEX) {};
    void createGraph();  //构建邻接矩阵
    void dfsTraverse();  //遍历所有非连通子图
    void dfs(int);
    void bfsTraverse();  //bfs遍历
    void count();  //记录出度、入度
    void f();
};

void Graph::createGraph() {
    cout << "Enter the number of vertexes and edges :\n";
    cin >> numVertex >> numEdge;
    cout << "Enter " << numVertex << " vertexes:\n";
    char t;
    for(int i = 0; i < numVertex; i++) {
        cin >> t;
        vertex.push_back(t);
    }
    
    int x, y, weight;
    cout << "Enter the adjacency vertexes and weight :\n";
    for(int i = 0; i < numEdge; i++) {
        cin >> x >> y >> weight;
        arc[x][y] = weight;
        arc[y][x] = weight;  //该行为无向图对应代码，矩阵对称
    }
}

void Graph::dfsTraverse() {
    for(int i = 0 ; i < numVertex; i++)
        if(!visited[i])
            dfs(i);
}

void Graph::dfs(int index) {
    cout << vertex[index] << ' ';
    visited[index] = true;

    for(int i = 0; i < numVertex; i++) {
        if(arc[index][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    Graph G;
    G.createGraph();
    G.dfsTraverse();

    // G.count();
    cout << endl;

    return 0;
}

/*
0 1 1
0 2 1
1 3 1
1 5 1
3 4 1
4 5 1

*/