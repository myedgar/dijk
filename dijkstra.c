#include "dijkstra.h"

/*
void dijkstra(LinkedGraph *graph, PathInform *path_inform,int start)     //单源最短路径
{
int i, k, v;
int weight;
int min;

path_inform->distance = (int*)malloc(sizeof(int)*graph->n);
path_inform->known = (int*)malloc(sizeof(int)*graph->n);
path_inform->path = (int*)malloc(sizeof(int)*graph->n);
for(i = 0; i < graph->n; i++){
path_inform->known[i] = UNKNOWN;
if((weight = search(graph, start, i)) != 0){
path_inform->distance[i] = weight;
path_inform->path[i] = start;                 //i的前驱是start
}else{
path_inform->distance[i] = FINITY;           //i的前驱不存在
path_inform->path[i] = NotAVertex;
}
}
path_inform->known[start] = KNOWN;                     //初始时只有start一个结点
path_inform->distance[start] = 0;

for (i = 1; i < graph->n; i++){
min = FINITY;
for (k = 0; k < graph->n; k++){
if(path_inform->known[k] == UNKNOWN && path_inform->distance[k] < min){
v = k;
min = path_inform->distance[k];
}
}
if(min == FINITY)
return;
path_inform->known[v] = KNOWN;

for(k = 0; k < graph->n; k++){
if((weight = search(graph, v, k)) != 0){
if(path_inform->known[k] == UNKNOWN && (min + weight < path_inform->distance[k])){
path_inform->distance[k] = min + weight;
path_inform->path[k] = v;
}
}
}
}
}
*/

void dijkstra(LinkedGraph *graph, PathInform *path_inform,int start)
{

	int i, v;
	MinHeap* minHeap = NULL;

	if(graph->n == 0)
	{
		path_inform->distance = NULL;
		path_inform->known = NULL;
		path_inform->path = NULL;
		return;
	}
	path_inform->distance = (int*)malloc(sizeof(int)*graph->n);
	path_inform->known = (int*)malloc(sizeof(int)*graph->n);
	path_inform->path = (int*)malloc(sizeof(int)*graph->n);

	minHeap = createMinHeap(graph->n);

	// 初始化堆包含所有的顶点
	for (v = 0; v < graph->n; ++v) {
		path_inform->distance[v] = FINITY;
		path_inform->path[v] = NotAVertex;
		path_inform->known = UNKNOWN;

		minHeap->array[v] = newMinHeapNode(v, path_inform->distance[v]);
		minHeap->pos[v] = v;
	}

	// 把 源点 src 的距离设置为0，第一个取出的点即为源点
	minHeap->pos[start] = start;
	path_inform->distance[start] = 0;
	decreaseKey(minHeap, start, path_inform->distance[start]);

	minHeap->size = graph->n;

	// 这个循环中，minHeap包含的是所有未在SPT中的顶点
	while (!isEmpty(minHeap)) {
		// 取得堆顶节点，即最小距离的顶点
		MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v;

		// 只需要遍历和u相邻的顶点进行更新
		EdgeNode* pCrawl = graph->adjlist[u].FirstEdge;
		while (pCrawl != NULL) {
			int v = pCrawl->adjvex;
			// 松弛操作，更新距离
			if (isInMinHeap(minHeap, v) && path_inform->distance[u] != FINITY
				&& pCrawl->weight + path_inform->distance[u] < path_inform->distance[v]) {
					path_inform->distance[v] = path_inform->distance[u] + pCrawl->weight;
					//距离更新了之后，要调整最小堆
					decreaseKey(minHeap, v, path_inform->distance[v]);
					path_inform->path[v] = u;
			}
			pCrawl = pCrawl->next;
		}
	}
	free(minHeap);
}


void short_distance(LinkedGraph *graph, PathInform *inform, State_inform *state_inform,int end)          //计算最优可能性，存在为1.不存在返回0
{
	int i;
	int min = FINITY;
	int end_point;
	int j = 0;
	int temp;
	int *a;
	a = NULL;
	if(state_inform->step > 0){
		a = (int*)malloc(sizeof(int)*(state_inform->step+1));
	}
	for(i = 0; i < state_inform->step; i++){
		end_point = i*state_inform->state*state_inform->node+(state_inform->state-1)*state_inform->node+end;
		if((temp = inform->distance[end_point]) < min){
			min = temp;
			j = end_point;
		}
	}
	if(min >= FINITY){
		printf("该最大顶点数限制下，不存在符合条件路径\n");
		return;
	}
	i = 0;
	a[i] = j;
	while(1){
		if(j == NotAVertex)
			break;
		j = inform->path[j];
		i++;
		a[i] = j;
	}
	printf("上述限制条件下最优需要经过%d个顶点，其路径为：", i);
	for (j = i-1; j >= 0; j--)
	{
		printf("%d ", graph->adjlist[a[j]].vertex);
	}
	printf("\n");
	printf("该路径花费为%d\n", min);

	if(graph->adjlist != NULL){
		free(graph->adjlist);
		graph->adjlist = NULL;
	}
	if(inform->distance != NULL){
		free(inform->distance);
		inform->distance = NULL;
	}
	if(inform->known != NULL){
		free(inform->known);
		inform->known = NULL;
	}
	if(inform->path != NULL){
		free(inform->path);
		inform->path =NULL;
	}
	if(a != NULL){
		free(a);
		a = NULL;
	}
}