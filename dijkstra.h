#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "adjust.h"
#include "heap.h"

#define KNOWN 1
#define UNKNOWN 0
#define NotAVertex -1
#define FINITY 5000

typedef struct {
	int *path;                                    //第i个顶点的前驱
	int *distance;                                //起点到第i个点的最短距离
	int *known;
} PathInform;
void dijkstra(LinkedGraph *graph, PathInform *path_inform,int start);    //单源最短路径
void short_distance(LinkedGraph *graph, PathInform *inform, State_inform *state_inform, int end);          //计算最优可能性，存在为1.不存在返回0
#endif