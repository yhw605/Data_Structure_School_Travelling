#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "graphs.h"
#include "kmp.h"
#include "maxFlow.h"

void showInformation(char* t, Graph g, const vexNode* v); // 查询信息

/****************展示网络图**********************
**********************************************/
void showGraph() { // 展示网络图
	const char* pic_path = "schoolGraph.png";
	cv::Mat pic = cv::imread(pic_path, 1);
	cv::imshow("学校网络图", pic);
	cv::waitKey(1);
	printf("\n");
}


int main() {
	char location[100][100];
	char startLoc[100], endLoc[100];
	char t[10000] = "\0";
	int startN, endN;
	FILE* fp = fopen("adjList.txt", "r");
	vexNode v[maxN]; // 此时maxN在头文件graphs.h中已经定义为1000
	Graph g = createGraph(fp, v); // 将文件传入createAdjList()函数创建邻接表
	int number;

	if (fp == NULL) {
		printf("文件打开失败！");
		exit(0);
	}
	//printAdjList(g, v);

	for (int i = 0; i < g.vexNum; i++) { // 构造字符串匹配算法的检索串t
		strcat(t, "_");
		strcat(t, v[i].name);
		if (i == g.vexNum - 1) {
			strcat(t, "_"); // 字符串t的结束标志是'_'
		}
	}

menu:
	printf("欢迎来到南京师范大学，请选择你要查询的项目：\n");
	printf("1.各景点信息\t2.某个景点的信息\t3.校内地图\t4.景点之间的最短路径");
	printf("\n若要退出请输入0\n");
	printf("请输入编号：");
	scanf("%d", &number);
	switch (number) {
		case 0: goto end; // 输入0就结束
		case 1: printAdjList(g, v);goto menu;
		case 2: showInformation(t, g, v); goto menu;
		case 3: showGraph(); goto menu;
		case 4: goto begin;
		default:
			printf("请重新输入!\n"); goto menu;
	}
	//printf("是否想看校内地图？\n");
	//printf("若visual studio中已经配置了opencv库才可以查看图片。\n");
	//printf("若没有展示出图像，请将代码中引入opencv头文件和showGraph()函数的代码取消注释。\n请输入[Y/n]：");

	begin:
	printf("请输入你的起点：");
	scanf("%s", startLoc);
	getchar(); // 吸收之前输入的换行符
	printf("你的起点是否为以下地点：[Y/n]\n");
	startN = kmp(t, startLoc);
	//printf("起点编号：%d\n", startN + 1);
	char YesOrNo;
	scanf("%c", &YesOrNo);
	

	// 如果为y，则继续，若为否，则重新开始
	if (tolower(YesOrNo) == 'y') {
		goto goAhead;
	} else if (tolower(YesOrNo) == 'n') {
		goto begin;
	}
	
goAhead:
	printf("请输入你想去的地方: ");
	scanf("%s", endLoc);
	getchar(); // 吸收之前输入的换行符
	printf("终点是否为以下地点：[Y/n]\n");
	endN = kmp(t, endLoc);
	//printf("终点编号：%d\n", endN + 1);
	scanf("%c", &YesOrNo);
	getchar();
	// 同上
	if (tolower(YesOrNo) == 'y') { // 若输入y则说明匹配正确，进入下一步
		goto shortestWay;
	}
	else if (tolower(YesOrNo) == 'n') { // 若输入n则重新进行输入
		printf("\n");
		goto goAhead;
	}
		
shortestWay:
	dijkstra(startN, endN, g, v); // 得到最优路径
	fordFulkerson(&g, v, startN, endN);

recall:
	printf("\n还想继续游览吗？\n请输入[Y/n]：");
	//getchar();
	scanf("%c", &YesOrNo);
	if (tolower(YesOrNo) == 'y') {
		printf("\n");
		goto begin;
	} else if (tolower(YesOrNo) == 'n') {
		printf("结束游览！\n\n");
		goto menu;
	} else {
		goto recall; // 输入了不对的字符，返回去再问一遍
	}

	destroyGraph(&g, v);
	
end:
	system("pause"); // 如果不加这一行，那么会在release模式下闪退
	return 0;
}

void showInformation(char* t, Graph g, const vexNode* v) { // 输出单个景点的信息
	char name[100], yOrN;

showInformationBegin:
	printf("\n请输入你要查询的景点信息：");
	scanf("%s", name);
	getchar(); // 吸收换行符
	int beginN;
	beginN = kmp(t, name);
	scanf("%c", &yOrN);
	getchar();
	if (tolower(yOrN) == 'y') {
		printf("与%d.%s相邻的景点有：\n", beginN + 1, name);
		adjNode* p = v[beginN].link;
		int cnt = 0;
		while (p != NULL) {
			cnt++;
			printf("(%d)%s，距离是：%d\n", cnt, v[p->adjVex].name, p->weight);
			p = p->next;
		}
		printf("是否要继续查询[Y/n]：");
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
		goto showInformationBegin; // 重新开始
	}
}
