#include<iostream>
#include<stdio.h>
using namespace std;
#define MAX 1600005
int buf[MAX];
int jumpBuf[MAX];
bool output[2*MAX];
int jB_endPos=0;
int jB_size=0;

void push(int temp){
	if(jB_endPos<MAX){
		jumpBuf[jB_endPos++]=temp;
		jB_size++;
	}
}
int top(){
	if(jB_size>0)
		return jumpBuf[jB_endPos-1];
	else
		return 0;	
}
void pop(){
	if(jB_size>0){
		jB_endPos--;
		jB_size--;
	}
}


int main(){
	//init
	int maxNumOfCache=0;
	int length=0;
	scanf("%d %d",&length,&maxNumOfCache);
	for(int i=0;i<length;i++){
		int temp;
		scanf("%d",&temp);
		buf[i]=temp;
	}
	//main
	int k=0;
	for(int i=1,j=0;i<=length&&j<length;i++){
		if(jB_size>=maxNumOfCache){
			printf("No");
			return 0;
		}
		push(i);
		output[k++]=1;
		if(i==buf[j]){
			output[k++]=0;
			pop();
			j++;
			while(jB_size>0&&buf[j]==top()){
				output[k++]=0;
				pop();
				j++;
			}
		}
	}
	if(jB_size>0){
		printf("No");
		return 0;
	}
	for(int i=0;i<k;i++){
		if(output[i])
			printf("push\n");
		else
			printf("pop\n");
	}	
	return 0;
}

