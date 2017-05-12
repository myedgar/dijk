#include "adjust.h"


void ban_edge(BanEdge *b_e)
{
	int i;
	b_e->number = -1;
	printf("输入禁止边总数：");
	scanf("%d", &b_e->number);
	if(b_e->number == 0){
		b_e->edge = NULL;
	}else{

		b_e->edge = (BanSingleEdge*)malloc(sizeof(BanSingleEdge)*b_e->number);
		printf("输入禁止边（例如 1-2）：");
		for(i = 0; i < b_e->number; i++){
			scanf("%d-%d", &b_e->edge[i].point[0], &b_e->edge[i].point[1]);
		}
	}
	printf("**********************************************\n");
	return;
}
void delete_edge_from_graph(LinkedGraph *graph, BanEdge b_e)
{
	int i;
	for(i = 0; i < b_e.number; i++){
		dele(graph->adjlist, b_e.edge[i].point[0], b_e.edge[i].point[1]);
		dele(graph->adjlist, b_e.edge[i].point[1], b_e.edge[i].point[0]);
	}
	return;
}
int point_total()          //顶点限制总数
{
	int total;
	printf("输入限制经过节点总数：");
	scanf("%d", &total);
	printf("**********************************************\n");
	return total;
}
void fixed_edge(FixedEdge *f_d)       //返回必须过的边总数
{
	int i;
	f_d->number = -1;
	printf("输入必过边总数：");
	scanf("%d", &f_d->number);
	if(f_d->number == 0){
		f_d->edge = NULL;
	} else{
		f_d->edge = (SingleEdge*)malloc(sizeof(SingleEdge)*f_d->number);
		printf("输入必过边（例如 3-6）：");
		for(i = 0; i < f_d->number; i++){
			scanf("%d-%d", &f_d->edge[i].point[0], &f_d->edge[i].point[1]);
		}
	}
	printf("**********************************************\n");
	return;
}
void fixed_point(Fixed_point *f_p)     //返回必须过得点综述
{
	int i;
	f_p->number = -1;
	printf("输入必过节点总数：");
	scanf("%d", &f_p->number);
	if(f_p->number == 0){
		f_p->point = NULL;
	}else{
		f_p->point = (int*)malloc(sizeof(int)*f_p->number);
		printf("输入必过节点：");
		for (i = 0; i < f_p->number; i++){
			scanf("%d", &f_p->point[i]);
		}
	}
	printf("**********************************************\n");
	return;
}
int check_point(Fixed_point TotalPoint, int key)
{
	int i;
	int flag = 0;
	for(i = 0; i < TotalPoint.number; i++){
		if(key == TotalPoint.point[i]){
			flag = 1;
			break;
		}
	}
	return flag;
}
int check_edge(FixedEdge TotalEdge, int point1, int point2)
{
	int i;
	int flag = 0;
	for (i = 0; i < TotalEdge.number; i++){
		if((TotalEdge.edge[i].point[0] == point1 && TotalEdge.edge[i].point[1] == point2)||(TotalEdge.edge[i].point[0] == point2 && TotalEdge.edge[i].point[1] == point1)){
			flag = 1;
			break;
		}
	}
	return flag;
}
int point_changed(Fixed_point TotalPoint, int key, int j,int bit_map)
{
	int  i;
	int flag = 0;
	for(i = 0; i < TotalPoint.number; i++){
		if(key == TotalPoint.point[i]){
			if((j >> (bit_map-TotalPoint.number + i) & 1) == 1){
				flag = 1;
			}
			break;
		}
	}
	return flag;
}
int edge_changed(FixedEdge TotalEdge, int point1, int point2, int j)  //判断两个点在边上，也状态为1,如果不在或者没过为0
{
	int i;
	int flag = 0;
	for (i = 0; i < TotalEdge.number; i++){
		if((TotalEdge.edge[i].point[0] == point1 && TotalEdge.edge[i].point[1] == point2)||(TotalEdge.edge[i].point[0] == point2 && TotalEdge.edge[i].point[1] == point1)){
			if(((j >> i) & 1) == 1){
				flag = 1;
			}
			break;
		}
	}
	return flag;
}
//判断状态j和状态0之间需要多少变化，也就是j的二进制中1的个数
int state_change(int j)
{
	int count = 0;
	while(j){
		++count;
		j = (j-1)&j;
	}
	return count;
}
void next_state(LinkedGraph *graph, LinkedGraph *ad_g, int bit_map, int i, int j, int state, FixedEdge TotalEdge, Fixed_point TotalPoint)
{
	int n, w;
	int v;        
	int k, Next_k;
	int count;
	int Next_State;
	EdgeNode *s;            //邻接结点
	n = graph->n;

	// k不是固定点  没有状态变化，无论是0还是1
	// 现在状态： (i,j)   下一步状态（i+1，j）
	Next_State = j;
	for(k = 0; k < graph->n; k++){
		if(check_point(TotalPoint, k) == 0 ||point_changed(TotalPoint, k, j, bit_map) == 1){   //k不是固定点或者是固定点但是已经是1
			for(Next_k = 0; Next_k < graph->n; Next_k++){
				if(k != Next_k && (w = search(graph, k, Next_k)) != 0){
					if((check_point(TotalPoint, Next_k) == 0 && check_edge(TotalEdge, k, Next_k) == 0) || point_changed(TotalPoint, Next_k, j, bit_map) == 1 || (edge_changed(TotalEdge, k, Next_k, j) == 1 && check_edge(TotalEdge, k, Next_k) == 1)){     //Next_k不是固定点且，两个不是固定边顶点
						//将 k和Next_k的两个状态连接。
						s = (EdgeNode*)malloc(sizeof(EdgeNode));
						s->adjvex = (i+1)*state*n+j*n+Next_k;
						s->weight = w;
						s->next = ad_g->adjlist[i*state*n+j*n+k].FirstEdge;
						ad_g->adjlist[i*state*n+j*n+k].FirstEdge = s;
					}
				}
			}
		}
	}
	for(count = 0; count < bit_map; count++){
		Next_State = 0;
		if(((j>>count) & 1 )== 0){
			Next_State = j |(1<<count);  
			/******************************************
			*  将状态Next_State加入到状态j的邻接表
			*  （i，j）时候的位置： i*state*n+j*n+k
			*  (i+1,Next_State)时候的位置： （i+1）*state*n+Next_State*n+k
			*  判断：
			*        1：Nest_State属于固定边还是固定点，前面count为边，count到bit_map为点；
			*           固定边，将固定边的两个顶点分别与下一个状态连接，其他点不和任何点连接，
			*			固定点：和和固定点相连
			*                   不相连或者固定点
			*                   将和固定点连接的点的与下一个状态固定点连接，其他状态不连接（包括现有状态固定点）
			*******************************************/
			/**********状态没有改变******************/
			if(count < TotalEdge.number){     //属于边
				//状态变化 只把count数组对应的边两点连接
				w = search(graph, TotalEdge.edge[count].point[0], TotalEdge.edge[count].point[1]);

				s = (EdgeNode*)malloc(sizeof(EdgeNode));
				s->adjvex = (i+1)*state*n+Next_State*n+TotalEdge.edge[count].point[1];
				s->weight = w;
				s->next = ad_g->adjlist[i*state*n+j*n+TotalEdge.edge[count].point[0]].FirstEdge;
				ad_g->adjlist[i*state*n+j*n+TotalEdge.edge[count].point[0]].FirstEdge = s;

				s = (EdgeNode*)malloc(sizeof(EdgeNode));
				s->adjvex = (i+1)*state*n+Next_State*n+TotalEdge.edge[count].point[0];
				s->weight = w;
				s->next = ad_g->adjlist[i*state*n+j*n+TotalEdge.edge[count].point[1]].FirstEdge;
				ad_g->adjlist[i*state*n+j*n+TotalEdge.edge[count].point[1]].FirstEdge = s;

			}else{                        //属于点
				for(k = 0; k < graph->n; k++){
					w = search(graph, k, TotalPoint.point[count-TotalEdge.number]);
					if(check_point(TotalPoint, k) == 0 && w != 0){
						s = (EdgeNode*)malloc(sizeof(EdgeNode));
						s->adjvex = (i+1)*state*n+Next_State*n+TotalPoint.point[count-TotalEdge.number];
						s->weight = w;
						s->next = ad_g->adjlist[i*state*n+j*n+k].FirstEdge;
						ad_g->adjlist[i*state*n+j*n+k].FirstEdge = s;
					}
				}
			}   
		}
	}
}
void adjust_graph(LinkedGraph *graph, LinkedGraph *ad_g, State_inform *state_inform)   //对原图进行扩展 
{
	int i, j, k;              //步数，状态，点数
	int n, TotalStep;
	int bit_map;
	long state;
	int all_n;
	FixedEdge TotalEdge;
	Fixed_point TotalPoint;
	BanEdge b_e;

	TotalStep = point_total();
	ban_edge(&b_e);
	fixed_edge(&TotalEdge);
	fixed_point(&TotalPoint);
	delete_edge_from_graph(graph, b_e);

	n = graph->n;
	bit_map = TotalEdge.number+TotalPoint.number;
	state = pow((float)2, bit_map);

	ad_g->adjlist = NULL;
	all_n = state*n*TotalStep;
	if(all_n != 0)
	{
		ad_g->adjlist = (VertexNode*)malloc(all_n*sizeof(VertexNode));
	}
	ad_g->n = all_n;

	state_inform->step = TotalStep;
	state_inform->state = state;
	state_inform->node = n;
	state_inform->n = ad_g->n;

	/******************初始化扩展后的邻接表**********/
	for(i = 0; i < TotalStep; i++){
		for (j = 0; j < state; j++){
			for (k = 0; k < n; k++)
			{
				ad_g->adjlist[i*state*n+j*n+k].vertex = graph->adjlist[k].vertex;   //读入顶点信息
				ad_g->adjlist[i*state*n+j*n+k].FirstEdge = NULL;               //空表
			}
		}
	}
	/************************************************
	* 图中添加约束
	* 约束一：只有第i和第i+1之间有可能从在权值存在情况；同一步数下各个点不相连，也就是路径权值为无穷大
	* 约束二：步数i和状态j之间必须满足 i>=j状态变化次数 ; 因为状态转移也需要步数。
	* 约束三：若（i，j）到下一个状态，i增加，j只改变一次状态，则必过点或者必过边
	*         否则，i加1，但是状态不变。
	*************************************************/
	for(i = 0; i < TotalStep-1; i++){
		for (j = 0; j < state; j++){     //状态j
			if(i >= state_change(j)){
				next_state(graph,ad_g, bit_map, i, j, state, TotalEdge, TotalPoint);
			}
		}
	}

	if(graph->adjlist != NULL){
		free(graph->adjlist);
		graph->adjlist = NULL;
	}
	if(TotalEdge.edge != NULL){
		free(TotalEdge.edge);
		TotalEdge.edge = NULL;
	}
	if(TotalPoint.point != NULL){
		free(TotalPoint.point);
		TotalPoint.point = NULL;
	}
}

