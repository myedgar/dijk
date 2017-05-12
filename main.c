#include "dijkstra.h"
#include <stdlib.h>
int main()
{
	LinkedGraph graph;
	LinkedGraph ad_g;
	PathInform inform;
	State_inform state_inform;
	int start, end;
	int result;
	char filename[30];

	printf("*********************************************************\n");
	printf("***文件名包括后缀名              case.txt          *****\n");
	printf("***文件存放在程序目录下                            *****\n");
	printf("***格式如下                                        *****\n");
	printf("***第一行                 结点总数     边总数       *****\n");
	printf("***第二行                 各顶点信息               ******\n");
	printf("***第三行及一下以下       各边信息     权值         ******\n");
	printf("*********************************************************\n");
	printf("输入文件名：");
	scanf("%s", filename);
	printf("**********************************************\n");
	if((result = creat(&graph, filename)) == 0)
	{
		return 1;
	}
	printf("起点：");
	scanf("%d", &start);
	printf("**********************************************\n");
	printf("终点：");
	scanf("%d", &end);
	printf("**********************************************\n");

	adjust_graph(&graph, &ad_g, &state_inform);   //对原图进行扩展 
	dijkstra(&ad_g, &inform,start);       //单源最短路径
	short_distance(&ad_g, &inform, &state_inform,end);          //计算最优可能性，存在为1.不存在返回0
	system("pause");
	return 0;
}