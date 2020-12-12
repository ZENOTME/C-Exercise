#include<iostream>
#include<memory>
using namespace std;
int main(){
	int* p=new int;
	unique_ptr<int>sp=p;
}

