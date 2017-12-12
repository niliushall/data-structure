#include<iostream>
#include<vector>
#include<queue>
#include<stack>
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
    vector<int> etv;  //事件最早发生时间
    vector<int> ltv;  //事件最晚发生时间
    stack<int> S;  //存储逆拓扑排序序列
    int numVertexes, numEdges;

public:
    Graph() : list(MAXVEX), inDegree(MAXVEX), etv(MAXVEX), ltv(MAXVEX) {};
    void createGraph();
    void findInDegree();
    int topologicalSort();  //拓扑排序,并求得事件最早发生时间
    void criticalPath();  //求解关键路径
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
        cout << "Enter No." << i+1 << " edge (x, y), weight : ";
        cin >> x >> y >> weight;

        //有向图
        e = new EdgeNode;
        e->weight = weight;
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

int Graph::topologicalSort() {
    findInDegree();
    queue<int> Q;  //队列，存储结点下标
    int count = 0;  //记录已经排序结点的个数
    int index, current;
    EdgeNode *p = NULL;

    //将所有入度为0的结点入队
    for(int i = 0; i < numVertexes; i++)
        if(!inDegree[i])
            Q.push(i);

    while(!Q.empty()) {
        index = Q.front();
        count++;
        Q.pop();
        S.push(index);  //将刚排序的结点下标入栈，逆拓扑排序的顺序栈

        p = list[index].firstEdge;
        while(p) {
            current = p->adjvex;  //存储当前结点的下标
            inDegree[current]--;
            if(!inDegree[current])  //入度为0,则入队
                Q.push(current);
            if(etv[index] + p->weight > etv[current])
                etv[current] = etv[index] + p->weight;  //更新最早发生时间
            p = p->next;
        }
    }
    cout << endl;

    //若存在未排序的结点，返回false，否则返回true
    if(count < numVertexes)
        return false;
    return true;
}

void Graph::criticalPath() {
    
}

int main() {
    Graph G;
    G.createGraph();
    G.topoSort();

    return 0;
}