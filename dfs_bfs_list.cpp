#include<iostream>
#include<vector>
using namespace std;

const int MAXVEX = 20;

struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;
};

struct vertexNode {
    char data;
    EdgeNode *firstEdge;
};

class Graph {
private:
    vector<vertexNode> list;  //邻接表
    vector<bool> visited;  //是否访问过
    int numVertexes, numEdges;

public:
    Graph() : list(MAXVEX), visited(MAXVEX) {};
    void createGraph();  //建立邻接表
    void dfsTraverse();
    void dfs(int);
    void bfsTraverse();
};

void Graph::createGraph() {
    cout << "Enter the number of vertexes and edges :\n";
    cin >> numVertexes >> numEdges;

    cout << "Enter vertexes :\n";
    for(int i = 0; i < numVertexes; i++) {
        cin >> list[i].data;
        list[i].firstEdge = NULL;
    }

    int x, y;
    EdgeNode *e;
    for(int i = 0; i < numEdges; i++) {  //建立边表
        cout << "Enter the edges (x, y) : ";
        cin >> x >> y;

        //有向图
        e = new EdgeNode;
        e->adjvex = y;
        e->next = list[x].firstEdge;
        list[x].firstEdge = e;
    }
}

void Graph::dfsTraverse() {
    for(int i = 0; i < numVertexes; i++)
        if(!visited[i])
            dfs(i);
}

void Graph::dfs(int i) {
    EdgeNode *p;
    p = list[i].firstEdge;
    visited[i] = true;
    cout << list[i].data << ' ';

    while(p) {
        if(!visited[p->adjvex])
            dfs(p->adjvex);
        p = p->next;
    }
}

void Graph::bfsTraverse() {
    
}

int main() {
    Graph G;
    G.createGraph();
    G.dfsTraverse();

    return 0;
}