#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

const int MAXVEX = 20;

class Graph {
private:
    typedef struct edgeNode {  //边表结点
        int adjvex;
        int weight;
        struct edgeNode *next;
    }EdgeNode;

    typedef struct vertexNode {
        char data;
        EdgeNode *firstEdge;
    }vertexNode, adjList[MAXVEX];

    adjList list;
    int numVertexes, numEdges;
    vector<int> inDegree;
    vector<int> outDegree;

public:
    Graph() : inDegree(MAXVEX), outDegree(MAXVEX) { memset(list, 0, sizeof(list)); };
    void createGraph();
    void count();
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

        //无向图
        // e = new EdgeNode;
        // e->adjvex = x;
        // e->next = list[y].firstEdge;
        // list[i].firstEdge = e;
    }
}

void Graph::count() {
    EdgeNode *p;
    for(int i = 0; i < numVertexes; i++) {
        p = list[i].firstEdge;
        while(p != NULL) {
            inDegree[p->adjvex]++;
            outDegree[i]++;
            p = p->next;
        }
    }

    cout << "\n\nvertex   outDegree  inDegree\n\n";
    for(int i = 0; i < numVertexes; i++)
        cout << list[i].data << "      " << outDegree[i] << "      " << inDegree[i] << endl;
}



int main() {
    Graph G;
    G.createGraph();
    G.count();

    return 0;
}