#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"
#include "queues.h"

void qPush(qList* q, adjNode* elem) { // 进队
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

void qPop(qList* q) { // 出队
	if (qEmpty(*q) == false) {
		if (q->top != NULL)
			q->top = q->top->next;
		if (qEmpty(*q) == true) {
			q->back = NULL;
		}
	}
}

bool qEmpty(qList q) { // 队列是否为空
	if (q.back == NULL || q.top == NULL) {
		return true;
	} else 
		return false;
}

void qInit(qList* q) {
	q->back = NULL;
	q->top = NULL;
}