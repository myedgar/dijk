#include "heap.h"

// 创建一个最小堆节点
MinHeapNode* newMinHeapNode(int v, int distance) 
{
	MinHeapNode* minHeapNode = (MinHeapNode*) malloc(
		sizeof(MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = distance;
	return minHeapNode;
}

// A utility function to create a Min Heap
MinHeap* createMinHeap(int capacity) 
{
	MinHeap* minHeap = ( MinHeap*) malloc(sizeof(MinHeap));
	minHeap->pos = (int *) malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (MinHeapNode**) malloc(
		capacity * sizeof(MinHeapNode*));
	return minHeap;
}

// 交换两个最小堆的节点
void swapMinHeapNode( MinHeapNode** a,  MinHeapNode** b) 
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

//在位置 idx 调整堆
void minHeapify( MinHeap* minHeap, int idx) 
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->dist < minHeap->array[smallest]->dist)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->dist < minHeap->array[smallest]->dist)
		smallest = right;

	if (smallest != idx) {
		// 需要交换的节点
		MinHeapNode *smallestNode = minHeap->array[smallest];
		MinHeapNode *idxNode = minHeap->array[idx];

		//交换下标
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		//交换节点
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// 推是否为空
int isEmpty(struct MinHeap* minHeap) 
{
	return minHeap->size == 0;
}

// 弹出堆顶的节点(即最小的节点)
MinHeapNode* extractMin( MinHeap* minHeap)
{
	MinHeapNode* root = NULL;
	MinHeapNode* lastNode =NULL;

	if (isEmpty(minHeap))
		return NULL;

	root = minHeap->array[0];

	lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// 更新下标
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// 记得减少堆的大小
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// 当节点v的距离更新后(变小了)调整堆
void decreaseKey(MinHeap* minHeap, int v, int dist)
{
	//获取节点 v 在 堆中的下标
	int i = minHeap->pos[v];

	minHeap->array[i]->dist = dist;

	// 因为是变小了，自下向上调整堆即可。 O(Logn)
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

// 判断节点v是否在堆中
int isInMinHeap( MinHeap *minHeap, int v) 
{
	if (minHeap->pos[v] < minHeap->size)
		return 1;
	return 0;
}

