#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define N 1000005
#define MAX(a,b) a>b?a:b
using namespace std;
struct Node;
struct Node{
	int data;
	Node* next;
	Node(int d):data(d),next(nullptr){}
};
struct List{
	Node* begin=nullptr;
	Node* end=nullptr;
	void insert(int d){
		Node* node=new Node(d);
		if(end==nullptr){
			begin=node;
			end=node;
		}
		else{
			end->next=node;
			end=node;
		}
	}
	~List(){
		Node* node=begin;
		while(node!=nullptr){
			Node* old=node;
			node=node->next;
			delete old;
		}
	}
};
//边集 
List E[N];
//入度 
int degree[N];
//节点长度
int depth[N];
int max_depth; 
//栈
int stack[N];
int top; 
//数量 
int v_n=0,e_n=0;

void TSort(){
	for(int i=0;i<v_n;i++){
		if(degree[i]==0){
			stack[top++]=i;
		//	depth[i]=1;
		}
	}
	//max_depth=1;
	while(top!=0){
		int v=stack[--top];
		for(Node* node=E[v].begin;node!=nullptr;node=node->next){
			degree[node->data]--;
			if(degree[node->data]==0)stack[top++]=node->data;
			depth[node->data]=MAX(depth[node->data],depth[v]+1);
//printf("%d = %d \n",node->data,depth[node->data]);
			if(depth[node->data]>max_depth)
			max_depth=depth[node->data];
		}
	}
}

int main(){
	scanf("%d %d",&v_n,&e_n);
	for(int i=0;i<e_n;i++){
		int b,e;
		scanf("%d %d",&b,&e);
		degree[e]++;
		E[b].insert(e);
	}
	TSort();
	printf("%d",max_depth+1);
	return 0;
}
