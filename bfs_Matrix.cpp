#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int MAXVEX = 20;
vector<bool> visited(MAXVEX， 0);  //标记是否已经走过

class Graph {
private:
    vector<char> vertex;  //顶点表
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numVertex, numEdge;  //顶点数，边数

public:
    Graph() { memset(arc, 0, sizeof(arc)); };
    void createGraph();  //构建邻接矩阵
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

    return 0;
}