#include "graph.h"

int creat(LinkedGraph *graph, char *filename)
{
	int i, j, w, k;
	int flag = 0;
	EdgeNode *s;            //邻接结点
	FILE *fp;
	fp = fopen(filename, "r");
	s = NULL;
	if(fp){
		fscanf(fp, "%d%d", &i, &j);
		graph->adjlist = (VertexNode*)malloc(i*sizeof(VertexNode));

		graph->n = i;
		graph->e = j;
		for(i = 0; i < graph->n; i++){
			fscanf(fp, "%d", &graph->adjlist[i].vertex);   //读入顶点信息
			graph->adjlist[i].FirstEdge = NULL;               //空表
		}
		for(k = 0; k < graph->e; k++){
			fscanf(fp, "%d%d%d", &i, &j, &w);
			s = (EdgeNode*)malloc(sizeof(EdgeNode));
			s->adjvex = j;
			s->weight = w;
			/*************插入s******************/
			s->next = graph->adjlist[i].FirstEdge;
			graph->adjlist[i].FirstEdge = s;
			/************无向图******************/
			s = (EdgeNode*)malloc(sizeof(EdgeNode));
			s->adjvex = i;
			s->weight = w;
			s->next = graph->adjlist[j].FirstEdge;
			graph->adjlist[j].FirstEdge = s;
		}
		fclose(fp);
		flag = 1;
	}else {
		printf("文件不存在！\n");
		flag = 0;
	}
	return flag;
}
int search(LinkedGraph *graph, int NowState, int NExtState)      //判断两个结点是否连接，如果没有连接返回0，否则返回权值w
{
	EdgeNode *s;
	int weight = 0;
	s = NULL;
	s = graph->adjlist[NowState].FirstEdge;
	while(s){
		if(s->adjvex == NExtState){
			weight = s->weight;
			break;
		}
		s = s->next;
	}
	return weight;
}
void dele(VertexNode *adjlist, int node, int x)
{
	EdgeNode *pre = NULL;
	EdgeNode *pnode;
	if (adjlist[node].FirstEdge == NULL){
		return;
	}
	pnode = adjlist[node].FirstEdge;
	while (pnode && pnode->adjvex != x){
		pre = pnode;
		pnode = pnode->next;
	}
	if(!pre && pnode->adjvex == x){
		adjlist[node].FirstEdge = adjlist[node].FirstEdge->next;
	}else{
		pre->next = pnode->next;
	}
	free(pnode);
	return;
}