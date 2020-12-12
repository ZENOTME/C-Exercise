#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define LEN 4000000

struct Point{
	size_t _x;
	size_t _y;
}array[LEN];
size_t y_array[LEN];

size_t invInside(size_t *array,long int begin,long int end);

/*****************************************/

size_t invBetween(size_t *array,long int begin,long int mid,long int end){
	size_t *l_array=new size_t[mid-begin];
	size_t res;
	for(int i=0;i<mid-begin;i++){
		l_array[i]=array[begin+i];
	}
	long int l=0,r=mid,l_end=mid-begin,r_end=end,index=begin;
	size_t inv_res=0;
	while(l<l_end){
		if(r_end==r||l_array[l]<array[r]){array[index++]=l_array[l++];inv_res+=r_end-r;}
		else{
			array[index++]=array[r++];
		}
	}
	
	delete[] l_array;
	return inv_res;
}


size_t invInside(size_t *array,long int begin,long int end){
	if(end-begin<2)return 0;
	size_t mid=(begin+end)>>1;
	size_t l_inv=invInside(array,begin,mid);
	size_t r_inv=invInside(array,mid,end);
	size_t b_inv=invBetween(array,begin,mid,end);
	return l_inv+r_inv+b_inv;
}
/******************************************/

int compare(const void* a,const void* b){
	Point* A=(Point*)a;
	Point* B=(Point*)b;
	return A->_x-B->_x;
}

void copy_y(Point* src,size_t* dst,long int n){
	for(int i=0;i<n;i++){
		dst[i]=src[i]._y;
	}
}


int main(){
	long int n=0;
	cin>>n;
	for(long int i=0;i<n;i++){
		size_t x,y;
		scanf("%ld %ld",&x,&y);
		array[i]._x=x;
		array[i]._y=y;
	}
	qsort(array,n,sizeof(Point),compare);
	/*
	for(long int i=0;i<n;i++){
		printf("%ld %ld\n",array[i]._x,array[i]._y);
	}*/
	copy_y(array,y_array,n);
	
	size_t res=invInside(y_array,0,n);
    printf("%ld\n",res);
/*for(int i=0;i<n;i++){
	printf("%ld\n",y_array[i]);
}*/	
	return 0;
	
}
