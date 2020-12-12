#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>
class Zuma{
private:
	T* _array;
	size_t _len;
	size_t _cap;
	void _recap(){
		_cap=2*_len;
		T* temp=new T[2*_len];
		for(size_t i=0;i<_len;i++){
			temp[i]=_array[i];
		}
		delete[] _array;
		_array=temp;
	}
	void _rangedel(size_t begin,size_t end){
		size_t reduce_len=end-begin+1;
		size_t new_begin=end+1;
		for(;new_begin<_len;new_begin++){
//cout<<"swap "<<begin<<" "<<new_begin<<endl;
			_array[begin++]=_array[new_begin];
		}
		_len-=reduce_len;
	}
	void hit(size_t pos){
		int count=1;
		//hit left
		int l_end=pos-1;
		while(l_end>=0&&_array[l_end]==_array[pos]){
			count++;
			l_end--;
		}
		l_end++;
		//hit right
		int r_end=pos+1;
		while(r_end<_len&&_array[r_end]==_array[pos]){
			count++;
			r_end++;
		}
		r_end--;
//cout<<"count"<<count<<endl;
		//
		if(count>=3){
//cout<<"del "<<l_end<<" "<<r_end<<endl;
			_rangedel(l_end,r_end);
			return hit(l_end); 
		}
		return;
	}
public:
	Zuma():_len(0),_cap(20){
		_array=new T[20];
	};
	~Zuma(){
		delete[] _array;
	}

	void insert(size_t pos,T val){
		if(pos<=_len){
			if(pos==_len)_array[_len++]=val;
			else{
				for(int i=_len-1;i>=int(pos);i--){
					_array[i+1]=_array[i];
				}
				_array[pos]=val;
				_len++;
			}
			if(_len==_cap)
				_recap();
			hit(pos);
		}	
	}

	void show(){
		if(_len==0){
			cout<<"-"<<endl;
			return;
		}
		for(int i=0;i<_len;i++){
			cout<<_array[i];
		}
		cout<<endl;		
	}

	size_t size(){
		return _len;
	}
};

int main(){
	Zuma<char> game;
	string s;
	getline(cin,s);
	for(int i=0;i<s.length();i++){
		game.insert(game.size(),s[i]);
	}
	
	int n;
	cin>>n;
	
	for(int i=0;i<n;i++){
		int index;
		char c;
		scanf("%d %c",&index,&c);
		game.insert(index,c);
		game.show();
	}



}

