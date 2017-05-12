#ifndef _HEAP_H_
#define _HEAP_H_

#include "graph.h"
// 最小堆节点
typedef struct MinHeapNode {
	int v;  //下标
	int dist; //距离
} MinHeapNode;

// 最小堆
typedef struct MinHeap{
	int size;
	int capacity;
	int *pos;     // pos[i]表示顶点i所在的下标
	struct MinHeapNode **array;
} MinHeap;

// 创建一个最小堆节点
MinHeapNode* newMinHeapNode(int v, int distance);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode( MinHeapNode** a,  MinHeapNode** b);
void minHeapify( MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin( MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
int isInMinHeap( MinHeap *minHeap, int v);

#endif