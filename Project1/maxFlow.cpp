#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <math.h>
#include <algorithm>
#include "graphs.h"
#include "maxFlow.h"
#include "queues.h"
using namespace std;

int matrix[maxN][maxN];

void getMatrix(const Graph* g, const vexNode* v);

void printVolume();

const int inf = 1e7; // 定义无穷大为一个很大的数，为10^7
int parent[maxN]; // maxN是graphs.h里定义的值
// parent[]记录前驱

void fordFulkerson(Graph* g, vexNode* v, int start, int end) {
	
/***以下试图使用邻接表进行bfs以及Edmonds-Karp算法，但没有实现*******************
	adjNode* qNode = (adjNode*)malloc(sizeof(adjNode));
	qNode = v[start].link;
	int maxFlow = 0;
	while (true) {
		int flow = bfs(g, v, qNode, start, end);
		if (flow == -1) {
			break; // 若没有找到增广路就退出循环
		}
		int current = end; // 更新路上的残留网络
		while (current != start) { // 回溯路径直到起点
			int father = parent[current];
			// 以下更新残留网络，正向减，反向加
			adjNode* p = v[father].link;
			while (p != NULL && p->adjVex != current) { // 找到正向网络
				p = p->next;
			}
			if (p == NULL) {
				continue;
			}
			p->volume -= flow;
			
			p = v[current].link;
			while (p != NULL && p->adjVex != father) {
				p = p->next;
			}
			if (p == NULL) {
				continue;
			}
			//p->volume = 0 - p->volume;
			p->volume += flow;

			current = father;
		}
		maxFlow += flow;
	}
*************************************************************************/
	
	getMatrix(g, v); // 将邻接表转化为邻接矩阵
	start += 1;
	end += 1;
	//以下使用邻接矩阵完成Edmonds-Karp算法
	int maxFlow = 0;
	while (1) {
		int flow = bfs(start, end, g->vexNum);
		if (flow == -1) break; // 说明已经找到了所有的增广路
		int cur = end; // 结点从结尾开始更新残留网络
		while (cur != start) { // 更新残留网络，直到结点到达起点
			int father = parent[cur]; // 将结点从前驱一直往前推
			matrix[father][cur] -= flow; // 正向减
			matrix[cur][father] += flow; // 反向加
			cur = father;
		}
		maxFlow += flow; // 每找到一条增广路就更新最大流的值
	}

	printf("从%s到%s的所有道路能承载的最大游览量（人流量）是%d\n", v[start - 1].name, v[end - 1].name, maxFlow);
}

int bfs(int start, int end, int vexNum) {
/***以下试图使用邻接表进行bfs以及Edmonds-Karp算法，但没有实现*******************
	qList* q = (qList*)malloc(sizeof(qList));
	int flow[maxN];
	memset(parent, -1, sizeof(parent));
	flow[start] = inf;
	parent[start] = 0;
	qInit(q);
	adjNode s;
	
	s.adjVex = start; s.next = v[start].link; s.volume = inf;
	
	// s.weight = inf;
	qPush(q, &s);
	while (qEmpty(*q) != true) {
		adjNode* u = q->top;
		qPop(q);
		if (u == NULL || u->adjVex == end) { // 搜索到一条增广路，跳出循环
			break; 
		}
		if (i != start && parent[i] == -1) {
			adjNode* tmp = v[i].link;
			parent[i] = tmp->adjVex;
			while (tmp != NULL) {
				qPush(q, tmp);
				if (flow[u->adjVex] >= tmp->volume) {
					flow[i] = tmp->volume;
				} else {
					flow[i] = flow[u->adjVex];
				}
				tmp = tmp->next;
			}
		}

	}
************************************************************************/
	
//以下使用邻接矩阵完成Edmonds-Karp算法的bfs步骤
	int flow[maxN];
	memset(parent, -1, sizeof parent);
	flow[start] = inf; parent[start] = 0;
	queue<int> q; q.push(start);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == end) break; // 如果结点u到达了终点end，那么退出循环，找到一条增广路
		for (int i = 1; i <= vexNum; ++i) {
			if (i != start && matrix[u][i] > 0 && parent[i] == -1) {
				parent[i] = u; // 记录前驱
				q.push(i);
				flow[i] = min(flow[u], matrix[u][i]); // 将流量更新为结点u和matrix[u][i]之间的最小值
			}
		}
	}
	if (parent[end] == -1) return -1;
	return flow[end];
}

void getMatrix(const Graph* g, const vexNode* v) {
	memset(matrix, 0, sizeof(matrix)); // 将邻接矩阵的值全部置为0
	//memset(residualNet, 0, sizeof(residualNet));
	for (int i = 0; i < g->vexNum; i++)	{
		adjNode* p = v[i].link;
		while (p != NULL) {
			matrix[i + 1][p->adjVex + 1] = p->volume;
			p = p->next;
		}
	}
}