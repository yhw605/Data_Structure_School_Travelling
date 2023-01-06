#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "graphs.h"
#include "kmp.h"
#include "maxFlow.h"

void showInformation(char* t, Graph g, const vexNode* v); // ��ѯ��Ϣ

/****************չʾ����ͼ**********************
**********************************************/
void showGraph() { // չʾ����ͼ
	const char* pic_path = "schoolGraph.png";
	cv::Mat pic = cv::imread(pic_path, 1);
	cv::imshow("ѧУ����ͼ", pic);
	cv::waitKey(1);
	printf("\n");
}


int main() {
	char location[100][100];
	char startLoc[100], endLoc[100];
	char t[10000] = "\0";
	int startN, endN;
	FILE* fp = fopen("adjList.txt", "r");
	vexNode v[maxN]; // ��ʱmaxN��ͷ�ļ�graphs.h���Ѿ�����Ϊ1000
	Graph g = createGraph(fp, v); // ���ļ�����createAdjList()���������ڽӱ�
	int number;

	if (fp == NULL) {
		printf("�ļ���ʧ�ܣ�");
		exit(0);
	}
	//printAdjList(g, v);

	for (int i = 0; i < g.vexNum; i++) { // �����ַ���ƥ���㷨�ļ�����t
		strcat(t, "_");
		strcat(t, v[i].name);
		if (i == g.vexNum - 1) {
			strcat(t, "_"); // �ַ���t�Ľ�����־��'_'
		}
	}

menu:
	printf("��ӭ�����Ͼ�ʦ����ѧ����ѡ����Ҫ��ѯ����Ŀ��\n");
	printf("1.��������Ϣ\t2.ĳ���������Ϣ\t3.У�ڵ�ͼ\t4.����֮������·��");
	printf("\n��Ҫ�˳�������0\n");
	printf("�������ţ�");
	scanf("%d", &number);
	switch (number) {
		case 0: goto end; // ����0�ͽ���
		case 1: printAdjList(g, v);goto menu;
		case 2: showInformation(t, g, v); goto menu;
		case 3: showGraph(); goto menu;
		case 4: goto begin;
		default:
			printf("����������!\n"); goto menu;
	}
	//printf("�Ƿ��뿴У�ڵ�ͼ��\n");
	//printf("��visual studio���Ѿ�������opencv��ſ��Բ鿴ͼƬ��\n");
	//printf("��û��չʾ��ͼ���뽫����������opencvͷ�ļ���showGraph()�����Ĵ���ȡ��ע�͡�\n������[Y/n]��");

	begin:
	printf("�����������㣺");
	scanf("%s", startLoc);
	getchar(); // ����֮ǰ����Ļ��з�
	printf("�������Ƿ�Ϊ���µص㣺[Y/n]\n");
	startN = kmp(t, startLoc);
	//printf("����ţ�%d\n", startN + 1);
	char YesOrNo;
	scanf("%c", &YesOrNo);
	

	// ���Ϊy�����������Ϊ�������¿�ʼ
	if (tolower(YesOrNo) == 'y') {
		goto goAhead;
	} else if (tolower(YesOrNo) == 'n') {
		goto begin;
	}
	
goAhead:
	printf("����������ȥ�ĵط�: ");
	scanf("%s", endLoc);
	getchar(); // ����֮ǰ����Ļ��з�
	printf("�յ��Ƿ�Ϊ���µص㣺[Y/n]\n");
	endN = kmp(t, endLoc);
	//printf("�յ��ţ�%d\n", endN + 1);
	scanf("%c", &YesOrNo);
	getchar();
	// ͬ��
	if (tolower(YesOrNo) == 'y') { // ������y��˵��ƥ����ȷ��������һ��
		goto shortestWay;
	}
	else if (tolower(YesOrNo) == 'n') { // ������n�����½�������
		printf("\n");
		goto goAhead;
	}
		
shortestWay:
	dijkstra(startN, endN, g, v); // �õ�����·��
	fordFulkerson(&g, v, startN, endN);

recall:
	printf("\n�������������\n������[Y/n]��");
	//getchar();
	scanf("%c", &YesOrNo);
	if (tolower(YesOrNo) == 'y') {
		printf("\n");
		goto begin;
	} else if (tolower(YesOrNo) == 'n') {
		printf("����������\n\n");
		goto menu;
	} else {
		goto recall; // �����˲��Ե��ַ�������ȥ����һ��
	}

	destroyGraph(&g, v);
	
end:
	system("pause"); // ���������һ�У���ô����releaseģʽ������
	return 0;
}

void showInformation(char* t, Graph g, const vexNode* v) { // ��������������Ϣ
	char name[100], yOrN;

showInformationBegin:
	printf("\n��������Ҫ��ѯ�ľ�����Ϣ��");
	scanf("%s", name);
	getchar(); // ���ջ��з�
	int beginN;
	beginN = kmp(t, name);
	scanf("%c", &yOrN);
	getchar();
	if (tolower(yOrN) == 'y') {
		printf("��%d.%s���ڵľ����У�\n", beginN + 1, name);
		adjNode* p = v[beginN].link;
		int cnt = 0;
		while (p != NULL) {
			cnt++;
			printf("(%d)%s�������ǣ�%d\n", cnt, v[p->adjVex].name, p->weight);
			p = p->next;
		}
		printf("�Ƿ�Ҫ������ѯ[Y/n]��");
		scanf("%c", &yOrN);
		getchar();
		if (tolower(yOrN) == 'y') {
			printf("\n");
			goto showInformationBegin;
		}
		else {
			printf("\n");
			return;
		}
	}
	else {
		goto showInformationBegin; // ���¿�ʼ
	}
}
