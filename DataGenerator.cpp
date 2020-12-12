#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<time.h>
using namespace std;
 
int main()
{
	srand(time(0));
	int n,m;
	n=rand()%1600000+1;
	m=rand()%1600000+1;
	printf("%d %d \n",n,m);
	int* buf=new int[n];
	for (int i=1;i<=n;i++){
		buf[i-1]=i;
	}
	int times=0;
	for(int i=0;i<n;i++){
		times=rand()%n;
		if(times!=i){
			buf[i]^=buf[times];
			buf[times]^=buf[i];
			buf[i]^=buf[times];
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",buf[i]);
	}
	
	return 0;
}
