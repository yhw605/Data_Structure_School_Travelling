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

const int inf = 1e7; // ���������Ϊһ���ܴ������Ϊ10^7
int parent[maxN]; // maxN��graphs.h�ﶨ���ֵ
// parent[]��¼ǰ��

void fordFulkerson(Graph* g, vexNode* v, int start, int end) {
	
/***������ͼʹ���ڽӱ����bfs�Լ�Edmonds-Karp�㷨����û��ʵ��*******************
	adjNode* qNode = (adjNode*)malloc(sizeof(adjNode));
	qNode = v[start].link;
	int maxFlow = 0;
	while (true) {
		int flow = bfs(g, v, qNode, start, end);
		if (flow == -1) {
			break; // ��û���ҵ�����·���˳�ѭ��
		}
		int current = end; // ����·�ϵĲ�������
		while (current != start) { // ����·��ֱ�����
			int father = parent[current];
			// ���¸��²������磬������������
			adjNode* p = v[father].link;
			while (p != NULL && p->adjVex != current) { // �ҵ���������
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
	
	getMatrix(g, v); // ���ڽӱ�ת��Ϊ�ڽӾ���
	start += 1;
	end += 1;
	//����ʹ���ڽӾ������Edmonds-Karp�㷨
	int maxFlow = 0;
	while (1) {
		int flow = bfs(start, end, g->vexNum);
		if (flow == -1) break; // ˵���Ѿ��ҵ������е�����·
		int cur = end; // ���ӽ�β��ʼ���²�������
		while (cur != start) { // ���²������磬ֱ����㵽�����
			int father = parent[cur]; // ������ǰ��һֱ��ǰ��
			matrix[father][cur] -= flow; // �����
			matrix[cur][father] += flow; // �����
			cur = father;
		}
		maxFlow += flow; // ÿ�ҵ�һ������·�͸����������ֵ
	}

	printf("��%s��%s�����е�·�ܳ��ص����������������������%d\n", v[start - 1].name, v[end - 1].name, maxFlow);
}

int bfs(int start, int end, int vexNum) {
/***������ͼʹ���ڽӱ����bfs�Լ�Edmonds-Karp�㷨����û��ʵ��*******************
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
		if (u == NULL || u->adjVex == end) { // ������һ������·������ѭ��
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
	
//����ʹ���ڽӾ������Edmonds-Karp�㷨��bfs����
	int flow[maxN];
	memset(parent, -1, sizeof parent);
	flow[start] = inf; parent[start] = 0;
	queue<int> q; q.push(start);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == end) break; // ������u�������յ�end����ô�˳�ѭ�����ҵ�һ������·
		for (int i = 1; i <= vexNum; ++i) {
			if (i != start && matrix[u][i] > 0 && parent[i] == -1) {
				parent[i] = u; // ��¼ǰ��
				q.push(i);
				flow[i] = min(flow[u], matrix[u][i]); // ����������Ϊ���u��matrix[u][i]֮�����Сֵ
			}
		}
	}
	if (parent[end] == -1) return -1;
	return flow[end];
}

void getMatrix(const Graph* g, const vexNode* v) {
	memset(matrix, 0, sizeof(matrix)); // ���ڽӾ����ֵȫ����Ϊ0
	//memset(residualNet, 0, sizeof(residualNet));
	for (int i = 0; i < g->vexNum; i++)	{
		adjNode* p = v[i].link;
		while (p != NULL) {
			matrix[i + 1][p->adjVex + 1] = p->volume;
			p = p->next;
		}
	}
}