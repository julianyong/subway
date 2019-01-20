#pragma once
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

#define MAX_ARC_NUM 1500
#define MAX_PATH_LENTH 2000
#define MAX_VERTEX_NUM 1000	//最大顶点个数
#define MAX_LINE_NUM 100		//最大线路条数
using namespace std;

typedef struct vNode_type
{
	int id_node;
	char name[20];
} vNode;

typedef struct Line_type
{
	int id_line;
	int station_num;
	char name[20];
	int stations[MAX_VERTEX_NUM];
}Line;

typedef struct arcNode_type
{
	int from;
	int to;
	int line_info;
}arcNode;

typedef struct graph_type
{
	arcNode arclist[MAX_ARC_NUM];
	int rear;
}alGraph;

void Subway();	//初始化
void printLine(char *line);  //输出地铁线路上的所有站
void Dijkstra(char *begin, char *end, bool state); //求从s到e的站数最少线路
void searchAll(char *begin); //从s开始遍历所有站点
void Test(char *filename);  //测试答案是否满足要求