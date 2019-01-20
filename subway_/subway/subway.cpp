#define _CRT_SECURE_NO_WARNINGS
#include "subway.h"
using namespace std;

#define INF 1999999999			//设定两个节点之间不可达的情况下距离为INF
int dist[MAX_VERTEX_NUM];			//dist[i]起始点到i的最短距离
bool visited[MAX_VERTEX_NUM];		//是否被访问
int node_num;   //站点总数
int arc_num;	//边的总数
int line_num;	//线路总数
int DFS_count;
int path[MAX_PATH_LENTH];
vNode node[MAX_VERTEX_NUM];
Line l[MAX_LINE_NUM];
arcNode arc[MAX_ARC_NUM];

//map<string, int> map_node;  //站点名称对应id
//map<string, int> map_line; //地铁线路名称对应id
alGraph graph[MAX_VERTEX_NUM];  //地铁线路图

struct cmp
{
	bool operator()(pair<int, int> a, pair<int, int> b) {
		return dist[a.first] > dist[b.first];
	}
};

int path_sta;   //输出路径，即走过点的个数
int transf_sta;    //换乘+3的附加点个数

//map<pair<int, int>, bool> judge_arc;
bool judge_node[MAX_VERTEX_NUM];

int locateStation(char *des_station) {
	bool flag = false;
	for (int i = 1; i <= node_num; i++)
	{
		if (strcmp(node[i].name, des_station) == 0)
		{
			flag = true;
			if (flag == true)
				return i;
		}
	}
	if (flag == false)
		return 0;
}

void Subway()
{
	FILE *fp;

	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph[i].rear = 0;
	}

	if (NULL == (fp = fopen("E:\\subway\\subway\\Debug\\beijing-subway.txt", "r")))//txt文件的绝对路径
	{
		printf("地铁信息文件读取失败\n");
		exit(1);
	}
	fscanf(fp, "%d %d %d", &line_num, &node_num, &arc_num);

	for (int i = 1; i <= node_num; i++)//读取站点信息
	{
		fscanf(fp, "%d %s", &node[i].id_node, node[i].name);
	}
	for (int i = 1; i <= line_num; i++)//读取线路信息
	{
		fscanf(fp, "%s", l[i].name);
		fscanf(fp, "%d", &l[i].station_num);
		l[i].id_line = i;
		for (int j = 1; j <= l[i].station_num; j++)
		{
			fscanf(fp, "%d", &l[i].stations[j]);
		}
	}
	for (int i = 1; i <= arc_num; i++ )//读取边的信息
	{
		int x, y, info;
		fscanf(fp, "%d %d %d", &x, &y, &info);
		graph[x].rear++;
		graph[x].arclist[graph[x].rear].from = x;
		graph[x].arclist[graph[x].rear].to = y;
		graph[x].arclist[graph[x].rear].line_info = info;
		
		graph[y].rear++;
		graph[y].arclist[graph[y].rear].from = y;
		graph[y].arclist[graph[y].rear].to = x;
		graph[y].arclist[graph[y].rear].line_info = info;
		
	}
	fclose(fp);
}

/*void Dijkstra(string begin, string end, bool state)//基于优先队列的Dijkstra算法
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> queue;

	memset(visited, false, sizeof(visited));  // 初始化visited
	memset(dist, INF, sizeof(dist));

	if (map_node.find(begin) == map_node.end() || map_node.find(end) == map_node.end()) {
		cout << "未找到站点，请检查站点名称！" << endl;
		return;
	}
	int count;
	int a, b, transf[MAX_VERTEX_NUM];
	a = map_node[begin];
	b = map_node[end];
	vector<pair<int, int>> path(MAX_VERTEX_NUM);
	
	dist[a] = 0;
	queue.push(make_pair(a, 0));
	path[a] = make_pair(a, 0);

	int transf_sta = 0;

	while (!queue.empty()) 
	{
		
		pair<int, int> top;
		top = queue.top();
		queue.pop();
		visited[top.first] = true;
		int size = graph[top.first].size();
		for (int i = 1; i <= size; i++) 
		{
			pair<int, int> to;
			to = graph[top.first][i];
			if (visited[to.first] == false) 
			{
				//计算经历过的站点数量
				count = dist[top.first] + 1;
				if (state && path[top.first].second != 0 && path[top.first].second != to.second)
					count += 3;
				if (count < dist[to.first]) 
				{
					dist[to.first] = count;//更新dist
					queue.push(to);

					//记录经过的路径和换乘信息
					path[to.first] = make_pair(top.first, to.second);
					if (path[top.first].second == 0 || path[top.first].second == to.second)  //不换乘
						transf[to.first] = 0;
					else  //换乘
						transf[to.first] = to.second;

					if (to.first == b)
						break;
				}
			}
		}
	}

	string str = "\n";
	int tmp = b;
	int path_sta = 0;
	while (tmp != a) {
		path_sta++;
		str = '\n' + node[tmp].name + str;
		if (transf[tmp]) {
			str = " 换乘" + l[path[tmp].second].name + str;
			transf_sta += 3;
		}
		tmp = path[tmp].first;
	}
	str = node[tmp].name + str;
	if (state)
		cout << transf_sta + path_sta + 1 << endl << str;
	else
		cout << path_sta + 1 << endl << str;
}*/

void DFS(int a)
{
	int b;
	visited[a] = true;
	
	DFS_count++;
	path[DFS_count] = a;
	for (int i = 1; i <= graph[a].rear; i++) {
		b = graph[a].arclist[i].to;
		if(visited[b] == false || graph[a].rear == 1)
			DFS(b);
	}
}

void searchAll(char *begin)
{
	DFS_count = 0;
	bool flag;
	flag = true;
	memset(visited, false, sizeof(visited));
	memset(dist, INF, sizeof(dist));
	for (int i = 1; i <= node_num; i++)
	{
		if (visited[i] == false)
		{
			flag = false;
		}
	}
	int a;
	a = locateStation(begin);
	if ( a == 0) {
		cout << "站点名称错误" << endl;
		return;
	}
	DFS(a);
	cout << DFS_count << endl;
	for (int i = 1; i <= DFS_count; i++)
	{
		cout << node[path[i]].name << endl;
	}
}

//输出线路des_line上的所有站点 
void printLine(char *des_line)
{
	int i;
	bool flag = false;
	for (i = 1; i <= line_num; i++)
	{
		if (strcmp(l[i].name, des_line) == 0) {
			flag = true;
			for (int j = 1; j <= l[i].station_num; j++) {
				printf("%s\n", node[l[i].stations[j]].name);
			}
		}
	}
	if (flag == false)
		cout << "线路名称错误！" << endl;
	return;
}

void Test(char *filename)
{
	FILE *fp;
	if (NULL == (fp = fopen(filename, "r")))
	{
		printf("文件读取失败\n");
		exit(1);
	}
	memset(judge_node, false, sizeof(judge_node));

	bool flag = true;
	int test_path_num;
	int pos;
	int begin = 0;
	int end = 0;
	int last_node = 0;
	int count = -1;
	char name[20];
	int tmp;

	//输入总站数
	fscanf(fp, "%d", &tmp);
	test_path_num = tmp;
	count++;
	//起点
	for (int i = 1; i <= tmp; i++) 
	{
		if (i == 1) 
		{
			fscanf(fp, "%s", name);
			pos = locateStation(name);
			judge_node[pos] = true;
			last_node = pos;
			begin = pos;
			count++;
		}
		else 
		{
			fscanf(fp, "%s", name);
			pos = locateStation(name);
			judge_node[pos] = true;
			//车站遍历次序不合理
			bool mm = false;
			for (int i = 1; i <= graph[last_node].rear; i++) {
				if (graph[last_node].arclist[i].to == pos)
				{
					mm = true;
				}
			}
			if (mm == false)
			{
				cout << "error:" << node[last_node].name << " " << name << endl;
				flag = false;
			}
			last_node = pos;
			end = pos;
			count++;
			if (end == last_node)
				break;
		}
	}
	
	fclose(fp);

	bool output = false;
	if (flag) {
		if (!output) 
		{
			bool m = true;
			if (test_path_num != count && m == true) { //车站的数量错误
				cout << "false" << endl;
				m = false;
			}
			else { //结果正确
				cout << "true" << endl;
			}
			for (int i = 1; i <= node_num; i++) 
			{
				if (judge_node[i] == false) 
				{
					if (m == true) {
						cout << "false:" << endl;
						m = false;
					}
					cout << node[i].name << endl;
				}
			}
			output = true;
		}
	}
}
