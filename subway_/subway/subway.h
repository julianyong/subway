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
#define MAX_VERTEX_NUM 1000	//��󶥵����
#define MAX_LINE_NUM 100		//�����·����
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

void Subway();	//��ʼ��
void printLine(char *line);  //���������·�ϵ�����վ
void Dijkstra(char *begin, char *end, bool state); //���s��e��վ��������·
void searchAll(char *begin); //��s��ʼ��������վ��
void Test(char *filename);  //���Դ��Ƿ�����Ҫ��