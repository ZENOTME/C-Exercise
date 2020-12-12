#include<stdio.h>

#define N 4000005
int pre_order[N];
int post_order[N];
int mid_order[N];

void rebuild(int preB,int preE,int postB,int postE,int midB){
	//check
	if(preE-preB==1&&postE-postB==1){
		mid_order[midB]=pre_order[preB];
//printf("a%d=%d\n",midB,pre_order[preB]);
		return;
	}
	//main
	int left_preB=0,left_preE=0;
	int left_postB=0,left_postE=0;
	int right_preB=0,right_preE=0;
	int right_postB=0,right_postE=0;
	int mid_num=0,left_num=0,left_len=0;
	mid_num=pre_order[preB];
	left_num=pre_order[preB+1];
	
	for(int i=postB;i<postE;i++){
		if(post_order[i]==left_num){
			left_len=i-postB+1;
		}
	}
/*	
	if(mid_order[midB+left_len]!=0){
		printf("%d",midB+left_len);
		printf("Error\n");
		return;
	}*/
	left_preB=preB+1;
	left_preE=left_preB+left_len;
	left_postB=postB;
	left_postE=postB+left_len;
	right_preB=left_preB+left_len;
	right_preE=preE;
	right_postB=postB+left_len;
	right_postE=postE-1;
	mid_order[midB+left_len]=mid_num;
//printf("%d=%d\n",midB+left_len,mid_num);
	rebuild(left_preB,left_preE,left_postB,left_postE,midB);
	rebuild(right_preB,right_preE,right_postB,right_postE,midB+left_len+1);
	return;
}

int main(){
	int n=0;
	scanf("%d",&n);	
	for(int i=0;i<n;i++){
		scanf("%d",&pre_order[i]);
	}
	for(int i=0;i<n;i++){
		scanf("%d",&post_order[i]);
	}
	rebuild(0,n,0,n,0);
	for(int i=0;i<n;i++){
		printf("%d ",mid_order[i]);
	}
	return 0;
}
