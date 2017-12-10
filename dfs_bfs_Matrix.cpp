#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<string>
using namespace std;

const int MAXVEX = 20;
vector<bool> visited(MAXVEX, false);  //标记是否已经访问过

class Graph {
private:
    vector<char> vertex;  //顶点表
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numVertex, numEdge;  //顶点数，边数

public:
    Graph() { memset(arc, 0, sizeof(arc)); };
    void createGraph();  //构建邻接矩阵
    void dfsTraverse();  //遍历所有非连通子图
    void dfs(int);
    void bfsTraverse();  //bfs遍历
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

void Graph::bfsTraverse() {
    queue<int> Q;
    int index;

    for(int i = 0; i < numVertex; i++) {
        visited[i] = false;
    }

    for(int i = 0; i < numVertex; i++) {
        if(!visited[i]) {
            visited[i] = true;
            cout << vertex[i] << ' ';
            Q.push(i);

            while(!Q.empty()) {
                index = Q.front();
                Q.pop();
                for(int j = 0; j < numVertex; j++) {
                    if(arc[index][j] && !visited[j]) {
                        visited[j] = true;
                        cout << vertex[j] << ' ';
                        Q.push(j);
                    }
                }
            }
        }
    }
}

int main() {
    Graph G;
    G.createGraph();
    G.bfsTraverse();

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
