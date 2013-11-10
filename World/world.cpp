#include"world.h"
#include"stdafx.h"
namespace sets
{
	int element[MAXN*MAXM+1];
	int sets,roads;
	struct road//一条路有两个端点，这里定义的变量v的功能参考后边的注释
	{
		int x,y,v;
	}allroad[2*MAXN*MAXM];//保存所有可能被连的边，条数决不会超过这个数字
	int comp (const void *a,const void *b)
	{//因为不可能所有边都被连，所以就需要一个连接的顺序来决定谁可能先被连接
		//这个顺序是根据v的大小来确定的
		return ((road*)a)->v - ((road*)b)->v;
	}
	void init (int M,int N)
	{
		for (int i = 0; i <= M*N; ++i) element[i] = i;//M*N是所有要被连起来的点的个数，编号从0开始
		//点的编号与它们的坐标的对应关系：
		//假设一个点的编号是D
		//它的横坐标是D%M*2+1,               
		//纵坐标是D/M*2+1
		//反过来，如果已知坐标x,y
		//它的编号是(y-1)/2*M+(x-1)/2
		sets = M*N;
		roads = 0;
		srand((unsigned int)time(NULL));
		//下面是在将所有可能被连的边放入allroad数组，放完后排序
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M-1; ++j)
			{
				allroad[roads].x = i*M+j;
				allroad[roads].y = i*M+j+1;
				allroad[roads++].v = rand();//v的值是随机确定的，所以哪条先被连也是随机确定的
			}
		for (int i = 0; i < N-1; ++i)
			for (int j = 0; j < M; ++j)
			{
				allroad[roads].x = i*M+j;
				allroad[roads].y = (i+1)*M+j;
				allroad[roads++].v = rand();
			}
		roads = 0;
		qsort(allroad,N*(M-1)+M*(N-1),sizeof(road),comp);//排序，刚才说边的数量不可能超过2*M*N，实际上只有N*(M-1)+M*(N-1)条
	}

	int root (int a)
	{
		int p =a;
		while (element[p] != p)
			p = element[p];
		int k;
		while (a != p)
		{
			k = element[p];
			element[p] = p;
			a = k;
		}
		return p;
	}

	bool link (int a,int b)
	{
		if (root(a) != root(b))//如果点a点b所在的区域不连通
		{
			element[root(a)] = element[root(b)];//就把它们连起来
			--sets;//区域的数量减一
			++roads;
			return true;
		}
		return false;
	}
}
world::world (unsigned int a,unsigned int b)//创建迷宫区域
{
	M = a>MAXM?MAXM:a;
	N = b>MAXN?MAXN:b;
	p = new char*[2*N+1];
	for (int i = 0; i < 2*N+1; ++i)
		p[i] = new char[2*M+2];
}
//创建迷宫
void world::creatworld ()
{
	using namespace sets; 
	//第一步：所有位置设置为墙
	for (int i = 0; i < 2*N+1; ++i)
	{
		for (int j = 0; j < 2*M+1; ++j)
			p[i][j] = WALL;
		p[i][2*M+1] = '\0';
	}
	if (M*N == 0) return;
	//第二步，挖孔。。。。每一个孔就是一个“点”，将被选出的边连接起来，共M*N个
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			p[2*i-1][2*j-1] = ROAD;
	//第三步，把这些孔用N*M条边连起来，形成树形图
	init(M,N);
	for (int i = 0; sets::sets > 1; ++i)//如果迷宫区域中有超过一个连通区域就继续连接他们
		if (link(allroad[i].x,allroad[i].y))//如果这条边的两端处在同一个连通区域就跳过考虑下一条边
		{//否则就连接他们。连通区域的数量减一（link函数中实现）
			//在迷宫区域中将该边对应的点挖空，该点的坐标在边的两端点中间，根据前面所说的对应关系可求出下面的公式
			int y = allroad[i].x/M+allroad[i].y/M+1;
			int x = allroad[i].x%M+allroad[i].y%M+1;
			p[y][x] = ROAD;
		}
	//第四步：设置入口出口
	bool pass = false;
	while(!pass)
	{
		//从迷宫的四条边中随机选一个能做为入口的点点
		int S = rand()%(M*4-2+N*4-2)+1;
		if (S < 2*M)
		{
			if (p[1][S] == ROAD)
			{
				p[0][S] = ROAD;
				x = sx = S;
				y = sy = 0;
				pass = true;
			}
		}
		else if (S < 4*M-1)
		{
			S -= 2*M-1;
			if (p[2*N-1][S] == ROAD)
			{
				p[2*N][S] = ROAD;
				x = sx = S;
				y = sy = 2*N;
				pass = true;
			}
		}
		else if (S < 4*M+2*N-2)
		{
			S -= 4*M-2;
			if (p[S][1] == ROAD)
			{
				p[S][0] = ROAD;
				x = sx = 0;
				y = sy = S;
				pass = true;
			}
		}
		else
		{
			S -= 4*M+2*N-3;
			if (p[S][2*M-1] == ROAD)
			{
				p[S][2*M] = ROAD;
				x = sx = 2*M;
				y = sy = S;
				pass = true;
			}
		}
	}
	pass = false;
	//可行域中随机选一个作为终点的点
	while(!pass)
	{
		int X = rand()%(2*M-1)+1;
		int Y = rand()%(2*N-1)+1;
		if (p[Y][X] == ROAD)
		{
			p[Y][X] = EXIT;
			pass = true;
		}
	}
	rebuiltworld(5);//创建迷宫
	iwin = false;
}
char** world::getmap(int op)//这就是那个在类的外面极其重要的，反复被调用的getmap。。。。
{
	rebuiltworld(op);
	return p;
}
void world::rebuiltworld(int op)//这才是幕后的主角
{
	char ps = win()?EXIT:ROAD;//如果已经取胜，玩家当前所在位置就即将设为终点，否则就设为路
	iwin = false;
	p[y][x] = ps;
	switch (op)
	{
	case 8:
		if ((y-1 >= 0) && (p[y-1][x] == ROAD || p[y-1][x] == EXIT)) --y;
		break;
	case 4:
		if ((x-1 >= 0) && (p[y][x-1] == ROAD || p[y][x-1] == EXIT)) -- x;
		break;
	case 2:
		if ((y+1 <= 2*N) && (p[y+1][x] == ROAD || p[y+1][x] == EXIT)) ++ y;
		break;
	case 6:
		if (p[y][x+1] == ROAD || p[y][x+1] == EXIT) ++x;
		break;
	case 0://重置迷宫，将角色移回起点
		p[y][x] = ps;
		x = sx;
		y = sy;
	}
	if (p[y][x] == EXIT) iwin = true;
	p[y][x] = PLAY;
}
bool world::win()
{
	return iwin;
}
world::~world ()
{
	for (int i = 0; i < 2*N+1; ++i)
		delete []p[i];
	delete []p;
}