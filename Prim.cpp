#include<iostream>
#include<vector>
using namespace std;

const int MAXVEX = 20;
const int INFINITY = 65535;

class Graph {
private:
    vector<char> vertex;  //顶点表
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numVertex, numEdge;  //顶点数，边数

public:
    void createGraph();  //构建邻接矩阵
    void prim();
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

    //初始化arc数组
    for(int i = 0; i < numVertex; i++) {
        for(int j = 0; j < numVertex; j++) {
            if(i == j)
                arc[i][j] = 0;
            else
                arc[i][j] = INFINITY;
        }
    }

    int x, y, weight;
    cout << "Enter the adjacency vertexes and weight (x, y, weight) :\n";
    for(int i = 0; i < numEdge; i++) {
        cin >> x >> y >> weight;
        arc[x][y] = weight;
        arc[y][x] = weight;  //该行为无向图对应代码，矩阵对称
    }
}

void Graph::prim() {
    vector<int> adjvex(MAXVEX, 0);  //存储结点下标
    vector<int> lowcost(MAXVEX, 0);  //存储邻接边的权值，值为0表示该点已经在生成树中

    for(int i = 1; i < numVertex; i++) {  //假设从第一个点开始生成树
        lowcost[i] = arc[0][i];
    }

    int min, current;  //current存储当前最小值的下标
    for(int i = 1; i < numVertex; i++) {
        min = INFINITY;
        current = 0;

        for(int j = 1; j < numVertex; j++) {
            if(lowcost[j] && lowcost[j] < min) {
                min = lowcost[j];
                current = j;
            }
        }

        cout << "( " << adjvex[current] << ", " << current << " )" << endl;
        lowcost[current] = 0;
        for(int j = 1; j < numVertex; j++) {
            if(lowcost[j] && arc[current][j] < lowcost[j]) {
                lowcost[j] = arc[current][j];
                adjvex[j] = current;
            }
        }
    }
}

int main() {
    Graph G;
    G.createGraph();

    cout << "\n\nMiniSpanTree is:\n";
    G.prim();

    return 0;
}