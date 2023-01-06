#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"
#include "queues.h"

void qPush(qList* q, adjNode* elem) { // ����
	adjNode* p = (adjNode*)malloc(sizeof(adjNode));
	bool j = qEmpty(*q);
	*p = *elem;
	q->back = p;
	q->back->next = NULL;
	//q->data = elem;
	if (j == true) {
		q->top = q->back;
	}
}

void qPop(qList* q) { // ����
	if (qEmpty(*q) == false) {
		if (q->top != NULL)
			q->top = q->top->next;
		if (qEmpty(*q) == true) {
			q->back = NULL;
		}
	}
}

bool qEmpty(qList q) { // �����Ƿ�Ϊ��
	if (q.back == NULL || q.top == NULL) {
		return true;
	} else 
		return false;
}

void qInit(qList* q) {
	q->back = NULL;
	q->top = NULL;
}