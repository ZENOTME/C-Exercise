#include<iostream>
#include<map>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	int n,a,b;
	long long sum=0;
	map<int,int >vecA;
	cin>>n>>a>>b;
	for(int i=0;i<a;i++){
		int first,second;
		cin>>first>>second;
		if(first>0&&first<=n)
			vecA[first]=second;		
	}
	map<int,int >::iterator item;
	for(int i=0;i<b;i++){
		int first,second;
		cin>>first>>second;
		if(first>0&&first<=n){
			item=vecA.find(first);
			if(item!=vecA.end()){
				sum+=second*(item->second);
			}
		}		
	}
	printf("%lld",sum);
	return 0;
}
