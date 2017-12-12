#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
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
    vector<vertexNode> list;
    vector<int> inDegree;
    int numVertexes, numEdges;

public:
    Graph() : list(MAXVEX), inDegree(MAXVEX) {};
    void createGraph();
    void findInDegree();
    int topoSort();  //拓扑排序
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
        cout << "Enter No." << i+1 << " edge (x, y) : ";
        cin >> x >> y;

        //有向图
        e = new EdgeNode;
        e->adjvex = y;
        e->next = list[x].firstEdge;
        list[x].firstEdge = e;
    }
}

void Graph::findInDegree() {
    EdgeNode *p = NULL;
    
    for(int i = 0; i  < numVertexes; i++) {
        p = list[i].firstEdge;
        
        while(p) {
            inDegree[p->adjvex]++;
            p = p->next;
        }
    }
}

int Graph::topoSort() {
    findInDegree();
    queue<int> Q;  //队列，存储结点下标
    int count = 0;  //记录已经排序结点的个数
    int index;
    EdgeNode *p = NULL;

    //将所有入度为0的结点入队
    for(int i = 0; i < numVertexes; i++)
        if(!inDegree[i])
            Q.push(i);

    cout << "\n\nTopoSort Result:\n";
    while(!Q.empty()) {
        index = Q.front();
        cout << list[index].data << ' ';
        count++;
        Q.pop();

        p = list[index].firstEdge;
        while(p) {
            inDegree[p->adjvex]--;
            if(!inDegree[p->adjvex])
                Q.push(p->adjvex);
            p = p->next;
        }
    }
    cout << endl;

    //若存在未排序的结点，返回false，否则返回true
    if(count < numVertexes)
        return false;
    return true;
}

int main() {
    Graph G;
    G.createGraph();
    G.topoSort();

    return 0;
}