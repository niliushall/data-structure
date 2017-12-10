/*************************************************************************
	> File Name: Dijkstra.cpp
	> Author: wang liang
	> Mail: sdwllinux@gmail.com
	> Created Time: Sun 10 Dec 2017 02:37:54 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAXVEX = 20;
const int INFINITY = 65535;

class Graph {
private:
	vector<char> vertex;
	int arc[MAXVEX][MAXVEX];  //存储邻接矩阵
	int numVertexes, numEdges;

public:
	void createGraph();
	void dijkstra(int);
	void showDijkstra();
};
void Graph::createGraph() {
    cout << "Enter the number of vertexes and edges :\n";
    cin >> numVertexes >> numEdges;
    cout << "Enter " << numVertexes << " vertexes:\n";
    char t;
    for(int i = 0; i < numVertexes; i++) {
        cin >> t;
        vertex.push_back(t);
    }

	for(int i = 0; i < numVertexes; i++)
		for(int j = 0; j < numVertexes; j++)
			if(i == j)
				arc[i][j] = 0;
			else
				arc[i][j] = INFINITY;

    int x, y, weight;
    cout << "Enter the adjacency vertexes and weight :\n";
    for(int i = 0; i < numEdges; i++) {
        cin >> x >> y >> weight;
        arc[x][y] = weight;
    }
}

void Graph::dijkstra(int v0) {
	vector<int> dis(MAXVEX, 0);  //记录起点到该点权值
	vector<int> path(MAXVEX, 0);  //记录最短路径
	vector<bool> book(MAXVEX, false);  //标记是否已经找到最短路径

	//初始化dis数组
	for(int i = 0; i < numVertexes; i++) {
		dis[i] = arc[v0][i];
	}

	book[v0] = true;  //起点标记为true
	int k, min;

	//每次循环求得v0到某顶点的最短路径
	for(int i = 1; i < numVertexes; i++) {
		min = INFINITY;

		//找出未找到最短路径中点的最小值
		for(int j = 0; j < numVertexes; j++) {
			if(!book[j] && dis[j] < min) {
				min = dis[j];
				k = j;
			}
		}

		book[k] = true;  //将找到的点标记为true
		for(int i = 0; i < numVertexes; i++) {
			if(!book[i] && min + arc[k][i] < dis[i]) {
				dis[i] = min + arc[k][i];
				path[i] = k;
			}
		}
	}

	cout << "\n\nThe closest path is :\n";
	for(int i = 1, p; i < numVertexes; i++) {
		p = i;
		while(p) {
			cout << vertex[p] << " - ";
			p = path[p];
		}
		cout << vertex[p] << endl;
	}
}

int main() {
	Graph G;
	G.createGraph();
	G.dijkstra(0);

    return 0;
}

/*
0 1 1
0 2 12
1 2 9
1 3 3
3 2 4
2 4 5
3 4 13
3 5 15
4 5 4
*/