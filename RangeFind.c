#include<stdio.h>
#include<stdlib.h>

#define MAX_LEN 500010


int a[MAX_LEN];



int find(int*a,int n,int tar){
	int low=0;
	int high=n;	
	while(low<high){
		int mid=(low+high)>>1;
		(tar<a[mid])?(high=mid):(low=mid+1); 
	}
	return --low;
}

int compare(const void* a,const void* b){
	return (*(int*)a-*(int*)b);
}

void swap(int* a,int* b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

int main(){
	int n,m;
	
	scanf("%d %d\n",&n,&m);

	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	qsort(a,n,sizeof(int),compare);

	for(int i=0;i<m;i++){
		int l,r;
		int count=0;
		scanf("%d %d\n",&l,&r);
		if(l>r){
			swap(&l,&r);
		}
		int li=find(a,n,l);
		int ri=find(a,n,r);
		if((ri-li)<0)
			count=0;
		else{
			count=ri-li;
			count=(li>=0&&l==a[li])?++count:count;
		}
		printf("%d\n",count);
	}

}
