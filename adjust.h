#ifndef _ADJUST_H_
#define _ADJUST_H_

#include <math.h>
#include "graph.h"

typedef struct 
{
	int point[2];
} BanSingleEdge;

typedef struct 
{
	BanSingleEdge *edge;
	int number;
} BanEdge;

typedef struct {
	int point[2];
} SingleEdge;

typedef struct {
	SingleEdge *edge;
	int number;
} FixedEdge;

typedef struct {
	int *point;
	int number;
} Fixed_point;

typedef struct {
	int step;
	int state;
	int node;
	int n;
} State_inform;

void ban_edge(BanEdge *b_e);
void delete_edge_from_graph(LinkedGraph *graph, BanEdge b_e);
int point_total();          //顶点限制总数
void fixed_edge(FixedEdge *f_d);       //返回必须过的边总数
void fixed_point(Fixed_point *f_p);     //返回必须过得点综述
int state_change(int j);
int check_point(Fixed_point TotalPoint, int key);       //key如果在返回1，不是固定点返回0
int check_edge(FixedEdge TotalEdge, int point1, int point2);  //point1和point2如果在返回1, 如果连个不是边顶点返回0
int point_changed(Fixed_point TotalPoint, int key, int j,int bit_map);
int edge_changed(FixedEdge TotalEdge, int point1, int point2, int j);
void next_state(LinkedGraph *graph, LinkedGraph *ad_g, int bit_map, int i, int j, int state, FixedEdge TotalEdge, Fixed_point TotalPoint);
void adjust_graph(LinkedGraph *graph, LinkedGraph *ad_g, State_inform *state_inform);   //对原图进行扩展 

#endif