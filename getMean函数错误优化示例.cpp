#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<iostream>
using namespace std;
#define N 12
#define K 3
#define E 4//元素的个数

typedef struct
{
	int elements[E];
}Point;

Point point[9] = {
	{1,2,5,6},
    {3,4,7,9}
};
int main()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < E; j++)
		{
			cout << point[i].elements[j];
		}
		cout << endl;
	}
	return 0;
}
Point mean[K];

void getMean(int center[N])
{
	Point tep[K];
	int i, j;
	int count[K] = {0};
	{//k是聚类个数，这一循环里每次循环算出一个聚类中心，序号为i

		for (int m = 0; m<K; ++m)
		{
			for (int n = E-4; n >=0; n-=4)
			{
				tep[m].elements[n] = 0;
				tep[m].elements[n+1] = 0;
				tep[m].elements[n+2] = 0;
				tep[m].elements[n+3] = 0;
			}
			for (int n = (E % 4) - 1; n >= 0; --n)
			{
				tep[m].elements[n] = 0;
			}
			
		}


		for (j =0;j<N;++j)
		{
			Point* temp2 = &point[j];
			Point* temp = &tep[center[j]];//避免频繁访问，保存指针
			for (int m = E-4; m >= 0; m-=4)
			{
				temp->elements[m] += temp2->elements[m];
				temp->elements[m+1] += temp2->elements[m+1];
				temp->elements[m+2] += temp2->elements[m+2];
				temp->elements[m+3] += temp2->elements[m+3];
				count[center[j]]+=4;
			}
			for (int m = (E % 4) - 1; m >= 0; --m)
			{
				temp->elements[m] += temp2->elements[m];

			}

		}
		for (int i = 0; i < K; i++)
		{
			for (int m = E - 4; m >= 0; m -= 4)
			{
				mean[i].elements[m] = tep[i].elements[m] / count[i];
				mean[i].elements[m+1] = tep[i].elements[m+1] / count[i];
				mean[i].elements[m+2] = tep[i].elements[m+2] / count[i];
				mean[i].elements[m+3] = tep[i].elements[m+3] / count[i];
			}
			for (int m = (E % 4) - 1; m >= 0; --m)
			{
				mean[i].elements[m] = tep[i].elements[m] / count[i];
			}
		}
		
		
	
}