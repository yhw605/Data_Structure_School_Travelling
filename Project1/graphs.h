#ifndef _GRAPHS_H
#define _GRAPHS_H

const int maxN = 1000; // 最大顶点数和边数均设置为1000，这样后续增加也较为方便

typedef struct _adjNode {
	int adjVex; // 邻接点
	_adjNode* next;// 指向下一点的指针
	int weight; // 边的权值
	int volume; // 边的容量
	// 由于希望实现网络流问题，因此增加了volume容量一项，等于100*weight
}adjNode;

typedef struct {
	int vertex; // 顶点
	char name[1000]; // 顶点的名字
	int edgeNum; // 边数
	adjNode* link; // 邻接点头指针
}vexNode;

typedef struct {
	adjNode vexList[maxN];
	int vexNum, arcNum;
}Graph;

Graph createGraph(FILE* fp, vexNode* v);

void destroyGraph(Graph* g, vexNode* v);

void dijkstra(int start, int end, Graph g, vexNode* v);

void printAdjList(Graph g, const vexNode* v);

#endif// !_GRAPHS_H