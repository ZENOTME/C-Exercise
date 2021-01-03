#include<iostream>
#include<memory>
using namespace std;
//#include<stdio.h>
#define PID(P,I,D,V_P,V_I,V_D) (P*V_P+I*V_I+D*V_D)

int i=0;

int main(){
	int* j=new int(1);
	int* k=0x7ffff7789eb0;
	cout<<i<<" "<<*j<<endl;
	cout<<"addr"<<"i:"<<&i;
	cout<<" "<<"j:"<<j<<endl;
}

