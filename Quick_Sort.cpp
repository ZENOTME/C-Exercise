#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

template<typename Iter>
void _swap(Iter a,Iter b){
	*a^=*b;
	*b^=*a;
	*a^=*a;
}

template<typename Iter>
Iter partition(Iter begin,Iter end){
	auto& base=*begin;
	auto lo=begin+1;
	auto hi=end-1;
	while(lo<hi){
		while(*(lo)<base){lo++;if(lo==end-1)break;}
		while(*(hi)>=base){hi--;if(hi==begin)break;}
		cout<<"lo="<<*lo<<" "<<"hi="<<*hi<<endl;
		if(lo>=hi)break;
		swap(*lo,*hi);
		cout<<"lo="<<*lo<<" "<<"hi="<<*hi<<endl;
	}
	cout<<"lo="<<*lo<<" "<<"begin="<<*begin<<endl;
	swap(*hi,*begin);
	cout<<"lo="<<*lo<<" "<<"begin="<<*begin<<endl;
	return hi;
}

template<typename Iter>
void quick_sort(Iter begin,Iter end){
	if(end-begin<=1)
		return;
	auto mid=partition(begin,end);
	quick_sort(begin,mid);
	quick_sort(mid+1,end);	
}

int main(){
	vector<int>array={4,3,2,1};
	quick_sort(array.begin(),array.end());
	for(auto item:array){
		cout<<item<<" ";
	}
	cout<<endl;
}
