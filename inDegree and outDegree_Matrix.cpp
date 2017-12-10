#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int MAXVEX = 20;
const int INFINITY = 65535;
vector<bool> visited(MAXVEX, 0);  //标记是否已经访问过

class Graph {
private:
    vector<char> vertex;  //顶点表
    int arc[MAXVEX][MAXVEX] = {0};  //邻接矩阵
    int numVertex, numEdge;  //顶点数，边数
    vector<int> inDegree;  //入度
    vector<int> outDegree;  //出度

public:
    Graph() : inDegree(MAXVEX), outDegree(MAXVEX) {};
    void createGraph();  //构建邻接矩阵
    void count();
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
        // arc[y][x] = weight;  //该行为无向图对应代码，矩阵对称
    }
}

void Graph::count() {
	for(int i = 1; i < numVertex; i++) {
        for(int j = 0; j < numVertex; j++)
            cout << arc[i][j] << ' ';
		cout << endl;
	}


    for(int i = 0; i < numVertex; i++) {
        for(int j = 0; j < numVertex; j++) {
            if(arc[i][j]) {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }

    for(int i = 0; i < numVertex; i++)
        cout << vertex[i] << "  " << outDegree[i] << "  " << inDegree[i] << endl;
}

int main() {
	Graph G;
    G.createGraph();
    // G.dfsTraverse();

    G.count();
    cout << endl;

    return 0;
}