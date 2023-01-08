#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphs.h"

Graph g; // 建图

void printWay(int loc, int* parent, vexNode* v);

Graph createGraph(FILE* fp, vexNode* v) {
	int n, m; // n为顶点个数 m为边数
	fscanf(fp, "%d%d", &n, &m);
	
	g.vexNum = n;  g.arcNum = m; // 图g的顶点数和边数

	for (int i = 0; i < n; ++i) {
		v[i].vertex = i; // 顶点编号
		fscanf(fp, "%s", &v[i].name); // 输入顶点的名字
		fscanf(fp, "%d", &v[i].edgeNum); // 读入边数
		v[i].link = &g.vexList[i]; // 头指针指向第i条链表
		fscanf(fp, "%d%d", &g.vexList[i].adjVex, &g.vexList[i].weight);
		g.vexList[i].volume = 100 * g.vexList[i].weight;
		adjNode* q = &g.vexList[i]; // 容量
		for (int j = 1; j < v[i].edgeNum; ++j) {
			adjNode* p = (adjNode*)malloc(sizeof(adjNode));
			fscanf(fp, "%d%d", &(p->adjVex), &(p->weight)); 
			// 读入邻接点编号值和边的权重（或者说是长度）
			p->volume = 100 * p->weight; // 容量
			p->next = NULL;			
			q->next = p;
			q = p;
		}
	}

	return g;
}

void destroyGraph(Graph* g, vexNode* v) {
	for (int i = 0; i < g->vexNum; i++) {
		adjNode* p = (adjNode*)malloc(sizeof(adjNode)); 
		// 只有malloc的指针才能free，之前没注意到，一直出问题
		p = v[i].link->next; // p指向顶点连接的结点，遍历链表
		while (p != NULL && p->next != NULL) {
			adjNode* q = (adjNode*)malloc(sizeof(adjNode));
			q = p; // q是临时节点，用完就free
			p = p->next;
			q->next = NULL;
			free(q);
		}
		g->vexList[i].adjVex = 0;
		g->vexList[i].weight = g->vexList[i].volume = -1;
		g->vexList[i].next = NULL;
		// 将链表头的数据清零
		strcpy(v[i].name, "\0");
		v[i].edgeNum = 0; v[i].link = NULL; v[i].vertex = -1;
		// 将顶点数据清零
	}
	g->arcNum = g->vexNum = 0;
	// 将图的边数和顶点数清零
}

void dijkstra(int start, int end, Graph g, vexNode* v) {
	const int inf = 1e5; // 设置无穷大为1e5
	int dist[maxN], parent[maxN];
	bool visited[maxN]; 
	// dist[]记录其他顶点与源点的最短距离，parent[]记录前驱节点，visited[]记录顶点是否被访问
	for (int i = 0; i < g.vexNum; i++) {
		dist[i] = inf; 
		parent[i] = -1;
		visited[i] = false;
	}
	dist[start] = 0; // 与起点自己的距离为0
	int u = start;
	while (visited[u] == false) { 
		// 若visited[]数组全为true，说明遍历完成，可以退出循环
		visited[u] = true;
		adjNode* p = &g.vexList[u]; // 定义指针遍历邻接表
		for (;p != NULL;) {
			if (!visited[p->adjVex] && dist[p->adjVex] > dist[u] + p->weight) {
				dist[p->adjVex] = dist[u] + p->weight;
				parent[p->adjVex] = u;
			}
			p = p->next;
		}
		int least = inf;
		for (int i = 0; i < g.vexNum; ++i) {
			if (!visited[i] && least > dist[i]) {
				least = dist[i];
				u = i;
			}
		}
	}
	printf("最短距离是：%d\n", dist[end]);
	printf("路径是：");
	printWay(end, parent, v);
	printf("\n");
}

void printWay(int loc, int* parent, vexNode* v) {
	if (parent[loc] == -1) {
		printf("%d.%s", loc + 1, v[loc].name);
		return;
	}
	printWay(parent[loc], parent, v);
	printf("->%d.", loc + 1);
	printf("%s", v[loc].name);
}

void printAdjList(Graph g, const vexNode* v) {
	printf("\n校内各景点组成的的邻接表及路程如下：\n");
	for (int i = 0; i < g.vexNum; ++i) {
		printf("%d.%s，它与%d个地方相邻。\n", i + 1, v[i].name, v[i].edgeNum);
		adjNode* q = v[i].link;
		for (int j = 0; j < v[i].edgeNum; ++j) {
			if (j == 0) {
				printf("(%d)相邻处：%d.%s 路程：%d\t",	j + 1, v[i].link->adjVex + 1, v[v[i].link->adjVex].name, v[i].link->weight);
				q = v[i].link;
				q = q->next;
			} else {
				printf("(%d)相邻处：%d.%s 路程：%d\t", j + 1, q->adjVex + 1, v[q->adjVex].name, q->weight);
				q = q->next;
			}
		}
		printf("\n");
	}
	printf("\n各条边的最大流量设为权值（或边长）的100倍\n");
	printf("\n\n");
}