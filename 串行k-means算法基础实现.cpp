#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<iostream>
#include<immintrin.h>
using namespace std;
#define N 12//点的个数
#define K 3//聚类的个数
#define E 2//元素的个数

typedef struct
{
	float elements[E];
}Point;

int center[N];  ///  判断每个点属于哪个簇 center[k]=p，即第k个point位于第p聚类

Point point[N] = {
	{1,1},
	{1,2},
	{2,1},
	{2,2},
	{50,49},
	{50,51},
	{51,49},
	{100,99},
	{100,101},
	{101,99},
	{102,99},
	{98,101}
};

Point mean[K];  ///  保存每个簇的中心点
void printPointInfo(int index)
{
	cout << "点 :(";
	cout << point[index].elements[0];
	for (int i = 1; i < E; i++)
	{
		cout << "," << point[index].elements[i];
	}
	cout << ") 在聚类" << center[index] + 1 << "中" << endl;
}
void printCenterInfo(int index)
{
	cout << "聚类" << index + 1 << "的新中心点是:(";
	cout << mean[index].elements[0];
	for (int i = 1; i < E; i++)
	{
		cout << "," << mean[index].elements[i];
	}
	cout << ")" << endl;
}
float getDistance(Point point1, Point point2)//计算欧氏距离
{
	float d=0.0;
	for (int i = 0; i < E; i++)
	{
		d += (point1.elements[i] - point2.elements[i])* (point1.elements[i] - point2.elements[i]);
	}
	d = sqrt(d);
	return d;
}

/// 计算每个簇的中心点
void getMean(int center[N])
{
	Point tep;
	int i, j, count = 0;
	for (i = 0; i < K; ++i)
	{//k是聚类个数，这一循环里每次循环算出一个聚类中心，序号为i
		count = 0;

		for (int m = 0; m < E; ++m)
		{
			tep.elements[m] = 0;
		}

		for (j = 0; j < N; ++j)
		{
			if (center[j]==i)
			{
				count++;
				for (int m = 0; m < E; m++)
				{
					tep.elements[m] += point[j].elements[m];
				}
				
			}
		}
		for (int m = 0; m < E; m++)
		{
			tep.elements[m] /= count;
		}
		mean[i] = tep;
	}
	/*
	for (i = 0; i < K; ++i)
	{
		printCenterInfo(i);
		//printf("The new center point of %d is : \t( %f, %f )\n", i + 1, mean[i].x, mean[i].y);
	}
	*/
	
}


/// 计算平方误差函数
float getE()
{
	int i, j, k;
	float cnt = 0.0, sum = 0.0;
	for (i = 0; i < K; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (i == center[j])
			{
				//cnt = (point[j].x - mean[i].x) * (point[j].x - mean[i].x) + (point[j].y - mean[i].y) * (point[j].y - mean[i].y);
				for (k = 0; k < E; k++)
				{
					cnt += (point[j].elements[k] - mean[i].elements[k])*(point[j].elements[k] - mean[i].elements[k]);
				}
				sum += cnt;
			}
		}
	}
	return sum;
}

/// 把N个点聚类
void cluster()
{
	int i, j, q;
	float min;
	float distance[N][K];
	for (i = 0; i < N; ++i)
	{
		min = (float)INT_MAX;
		for (j = 0; j < K; ++j)
		{
			//distance[i][j] = getDistance(point[i], mean[j]);

			float d = 0.0;
			for (int k = 0; k < E; k++)
			{
				d += (point[i].elements[k] - mean[j].elements[k]) * (point[i].elements[k] - mean[j].elements[k]);
			}
			d = sqrt(d);
			distance[i][j] = d;
			/// printf("%f\n", distance[i][j]);  /// 可以用来测试对于每个点与3个中心点之间的距离
		}
		for (q = 0; q < K; ++q)
		{
			if (distance[i][q] < min)
			{
				min = distance[i][q];
				center[i] = q;
			}
		}
		//printPointInfo(i);
	}
	printf("-----------------------------\n");
}

void initPointSet()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < E; ++j)
		{
			point[i].elements[j] = rand() % 25;
		}
	}
}
bool checkFlag(int* flag, int j)//flag中没有j时返回真
{
	for (int i = 0; i < K; i++)
	{
		if (flag[i] == j)
		{
			return false;
		}
	}
	return true;
}
void initCenter()
{
	int i, j, n = 0;
	int flag[K];
	for (i = 0; i < K; i++)
	{
		flag[i] = -1;
	}
	srand((unsigned int)time(NULL));
	for (i = 0; i < K; ++i)
	{
		while(true)
		{
			j = rand() % N;//一开始错写为j = rand() % K，前k个点为中心，在数据量较大时会得到非常不符合预期的结果
			//这很大程度上说明了k-means算法中k值选取与中心点选取的重要性，也说明了普通k-means算法符合局部最优而非全局最优的特性。
			if (checkFlag(flag, j))
			{
				mean[i] = point[j];
				flag[i] = j;
				break;
			}
			
		}

		
		mean[i] = point[j];//上面完成后删掉这行

		for (int e = 0; e < E; ++e)
		{
			mean[i].elements[e] = point[j].elements[e];
		}


	}
}
int main()
{
	int i, j, n = 0;
	float temp1;
	float temp2, t;
	//initPointSet();
	printf("----------Data sets----------\n");
	for (i = 0; i < N; ++i)
	{
		printPointInfo(i);
	}
	printf("-----------------------------\n");

		//可以选择当前时间为随机数
	initCenter();
	
		/*
		* mean[0].x = point[0].x;      /// 初始化k个中心点
	mean[0].y = point[0].y;

	mean[1].x = point[3].x;
	mean[1].y = point[3].y;

	mean[2].x = point[6].x;
	mean[2].y = point[6].y;
		*/
	
	//计时开始
	cluster();          /// 第一次根据预设的k个点进行聚类
	temp1 = getE();        ///  第一次平方误差
	n++;                   ///  n计算形成最终的簇用了多少次

	printf("The E1 is: %f\n\n", temp1);

	getMean(center);
	cluster();
	temp2 = getE();        ///  根据簇形成新的中心点，并计算出平方误差
	n++;

	printf("The E2 is: %f\n\n", temp2);

	while (fabs(temp2 - temp1) != 0)   ///  比较两次平方误差 判断是否相等，不相等继续迭代
	{
		temp1 = temp2;
		getMean(center);
		cluster();
		temp2 = getE();
		n++;
		printf("The E%d is: %f\n", n, temp2);
	}

	printf("The total number of cluster is: %d\n\n", n);  /// 统计出迭代次数
	//计时结束

	system("pause");
	return 0;
}
