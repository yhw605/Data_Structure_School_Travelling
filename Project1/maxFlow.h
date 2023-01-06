#ifndef _MAX_FLOW_H
#define _MAX_FLOW_H
#include "queues.h"

void fordFulkerson(Graph* g, vexNode* v, int start, int end);

int bfs(int start, int end, int vexNum);

#endif // !_MAX_FLOW_H