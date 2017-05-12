#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

#define M 10000

typedef struct  node{
	int adjvex;
	int weight;
	struct node *next;
} EdgeNode;                           

typedef struct vnode{
	int vertex;
	EdgeNode *FirstEdge;
} VertexNode;                     //顶点

typedef struct{
	VertexNode *adjlist;
	long n, e;
} LinkedGraph;                     

int creat(LinkedGraph *graph, char *filename);
int search(LinkedGraph *graph, int NowState, int NExtState);      //判断两个点之间的权值，无穷大为0，否为返回w
void dele(VertexNode *adjlist, int node, int x);
#endif

