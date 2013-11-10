#include"world.h"
#include"stdafx.h"
namespace sets
{
	int element[MAXN*MAXM+1];
	int sets,roads;
	struct road//һ��·�������˵㣬���ﶨ��ı���v�Ĺ��ܲο���ߵ�ע��
	{
		int x,y,v;
	}allroad[2*MAXN*MAXM];//�������п��ܱ����ıߣ����������ᳬ���������
	int comp (const void *a,const void *b)
	{//��Ϊ���������б߶����������Ծ���Ҫһ�����ӵ�˳��������˭�����ȱ�����
		//���˳���Ǹ���v�Ĵ�С��ȷ����
		return ((road*)a)->v - ((road*)b)->v;
	}
	void init (int M,int N)
	{
		for (int i = 0; i <= M*N; ++i) element[i] = i;//M*N������Ҫ���������ĵ�ĸ�������Ŵ�0��ʼ
		//��ı�������ǵ�����Ķ�Ӧ��ϵ��
		//����һ����ı����D
		//���ĺ�������D%M*2+1,               
		//��������D/M*2+1
		//�������������֪����x,y
		//���ı����(y-1)/2*M+(x-1)/2
		sets = M*N;
		roads = 0;
		srand((unsigned int)time(NULL));
		//�������ڽ����п��ܱ����ı߷���allroad���飬���������
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M-1; ++j)
			{
				allroad[roads].x = i*M+j;
				allroad[roads].y = i*M+j+1;
				allroad[roads++].v = rand();//v��ֵ�����ȷ���ģ����������ȱ���Ҳ�����ȷ����
			}
		for (int i = 0; i < N-1; ++i)
			for (int j = 0; j < M; ++j)
			{
				allroad[roads].x = i*M+j;
				allroad[roads].y = (i+1)*M+j;
				allroad[roads++].v = rand();
			}
		roads = 0;
		qsort(allroad,N*(M-1)+M*(N-1),sizeof(road),comp);//���򣬸ղ�˵�ߵ����������ܳ���2*M*N��ʵ����ֻ��N*(M-1)+M*(N-1)��
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
		if (root(a) != root(b))//�����a��b���ڵ�������ͨ
		{
			element[root(a)] = element[root(b)];//�Ͱ�����������
			--sets;//�����������һ
			++roads;
			return true;
		}
		return false;
	}
}
world::world (unsigned int a,unsigned int b)//�����Թ�����
{
	M = a>MAXM?MAXM:a;
	N = b>MAXN?MAXN:b;
	p = new char*[2*N+1];
	for (int i = 0; i < 2*N+1; ++i)
		p[i] = new char[2*M+2];
}
//�����Թ�
void world::creatworld ()
{
	using namespace sets; 
	//��һ��������λ������Ϊǽ
	for (int i = 0; i < 2*N+1; ++i)
	{
		for (int j = 0; j < 2*M+1; ++j)
			p[i][j] = WALL;
		p[i][2*M+1] = '\0';
	}
	if (M*N == 0) return;
	//�ڶ������ڿס�������ÿһ���׾���һ�����㡱������ѡ���ı�������������M*N��
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			p[2*i-1][2*j-1] = ROAD;
	//������������Щ����N*M�������������γ�����ͼ
	init(M,N);
	for (int i = 0; sets::sets > 1; ++i)//����Թ��������г���һ����ͨ����ͼ�����������
		if (link(allroad[i].x,allroad[i].y))//��������ߵ����˴���ͬһ����ͨ���������������һ����
		{//������������ǡ���ͨ�����������һ��link������ʵ�֣�
			//���Թ������н��ñ߶�Ӧ�ĵ��ڿգ��õ�������ڱߵ����˵��м䣬����ǰ����˵�Ķ�Ӧ��ϵ���������Ĺ�ʽ
			int y = allroad[i].x/M+allroad[i].y/M+1;
			int x = allroad[i].x%M+allroad[i].y%M+1;
			p[y][x] = ROAD;
		}
	//���Ĳ���������ڳ���
	bool pass = false;
	while(!pass)
	{
		//���Թ��������������ѡһ������Ϊ��ڵĵ��
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
	//�����������ѡһ����Ϊ�յ�ĵ�
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
	rebuiltworld(5);//�����Թ�
	iwin = false;
}
char** world::getmap(int op)//������Ǹ���������漫����Ҫ�ģ����������õ�getmap��������
{
	rebuiltworld(op);
	return p;
}
void world::rebuiltworld(int op)//�����Ļ�������
{
	char ps = win()?EXIT:ROAD;//����Ѿ�ȡʤ����ҵ�ǰ����λ�þͼ�����Ϊ�յ㣬�������Ϊ·
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
	case 0://�����Թ�������ɫ�ƻ����
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