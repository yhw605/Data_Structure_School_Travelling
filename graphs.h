#ifndef _GRAPHS_H
#define _GRAPHS_H

const int maxN = 1000; // ��󶥵����ͱ���������Ϊ1000��������������Ҳ��Ϊ����

typedef struct _adjNode {
	int adjVex; // �ڽӵ�
	_adjNode* next;// ָ����һ���ָ��
	int weight; // �ߵ�Ȩֵ
	int volume; // �ߵ�����
	// ����ϣ��ʵ�����������⣬���������volume����һ�����100*weight
}adjNode;

typedef struct {
	int vertex; // ����
	char name[1000]; // ���������
	int edgeNum; // ����
	adjNode* link; // �ڽӵ�ͷָ��
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