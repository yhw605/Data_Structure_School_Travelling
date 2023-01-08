#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphs.h"

Graph g; // ��ͼ

void printWay(int loc, int* parent, vexNode* v);

Graph createGraph(FILE* fp, vexNode* v) {
	int n, m; // nΪ������� mΪ����
	fscanf(fp, "%d%d", &n, &m);
	
	g.vexNum = n;  g.arcNum = m; // ͼg�Ķ������ͱ���

	for (int i = 0; i < n; ++i) {
		v[i].vertex = i; // ������
		fscanf(fp, "%s", &v[i].name); // ���붥�������
		fscanf(fp, "%d", &v[i].edgeNum); // �������
		v[i].link = &g.vexList[i]; // ͷָ��ָ���i������
		fscanf(fp, "%d%d", &g.vexList[i].adjVex, &g.vexList[i].weight);
		g.vexList[i].volume = 100 * g.vexList[i].weight;
		adjNode* q = &g.vexList[i]; // ����
		for (int j = 1; j < v[i].edgeNum; ++j) {
			adjNode* p = (adjNode*)malloc(sizeof(adjNode));
			fscanf(fp, "%d%d", &(p->adjVex), &(p->weight)); 
			// �����ڽӵ���ֵ�ͱߵ�Ȩ�أ�����˵�ǳ��ȣ�
			p->volume = 100 * p->weight; // ����
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
		// ֻ��malloc��ָ�����free��֮ǰûע�⵽��һֱ������
		p = v[i].link->next; // pָ�򶥵����ӵĽ�㣬��������
		while (p != NULL && p->next != NULL) {
			adjNode* q = (adjNode*)malloc(sizeof(adjNode));
			q = p; // q����ʱ�ڵ㣬�����free
			p = p->next;
			q->next = NULL;
			free(q);
		}
		g->vexList[i].adjVex = 0;
		g->vexList[i].weight = g->vexList[i].volume = -1;
		g->vexList[i].next = NULL;
		// ������ͷ����������
		strcpy(v[i].name, "\0");
		v[i].edgeNum = 0; v[i].link = NULL; v[i].vertex = -1;
		// ��������������
	}
	g->arcNum = g->vexNum = 0;
	// ��ͼ�ı����Ͷ���������
}

void dijkstra(int start, int end, Graph g, vexNode* v) {
	const int inf = 1e5; // ���������Ϊ1e5
	int dist[maxN], parent[maxN];
	bool visited[maxN]; 
	// dist[]��¼����������Դ�����̾��룬parent[]��¼ǰ���ڵ㣬visited[]��¼�����Ƿ񱻷���
	for (int i = 0; i < g.vexNum; i++) {
		dist[i] = inf; 
		parent[i] = -1;
		visited[i] = false;
	}
	dist[start] = 0; // ������Լ��ľ���Ϊ0
	int u = start;
	while (visited[u] == false) { 
		// ��visited[]����ȫΪtrue��˵��������ɣ������˳�ѭ��
		visited[u] = true;
		adjNode* p = &g.vexList[u]; // ����ָ������ڽӱ�
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
	printf("��̾����ǣ�%d\n", dist[end]);
	printf("·���ǣ�");
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
	printf("\nУ�ڸ�������ɵĵ��ڽӱ�·�����£�\n");
	for (int i = 0; i < g.vexNum; ++i) {
		printf("%d.%s������%d���ط����ڡ�\n", i + 1, v[i].name, v[i].edgeNum);
		adjNode* q = v[i].link;
		for (int j = 0; j < v[i].edgeNum; ++j) {
			if (j == 0) {
				printf("(%d)���ڴ���%d.%s ·�̣�%d\t",	j + 1, v[i].link->adjVex + 1, v[v[i].link->adjVex].name, v[i].link->weight);
				q = v[i].link;
				q = q->next;
			} else {
				printf("(%d)���ڴ���%d.%s ·�̣�%d\t", j + 1, q->adjVex + 1, v[q->adjVex].name, q->weight);
				q = q->next;
			}
		}
		printf("\n");
	}
	printf("\n�����ߵ����������ΪȨֵ����߳�����100��\n");
	printf("\n\n");
}