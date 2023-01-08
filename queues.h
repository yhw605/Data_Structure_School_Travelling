#ifndef _QUEUES_H
#define _QUEUES_H
#include "graphs.h"

typedef struct {
	adjNode* top, * back;
	int data;
}qList;

void qPush(qList* q, adjNode* elem);

void qPop(qList* q);

bool qEmpty(qList q);

void qInit(qList* q);

#endif // !_QUEUES_H