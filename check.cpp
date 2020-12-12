#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
	int t=200;
    while(t)
    {
    	t--;
        system("DataGenerator.exe > data.txt");
        system("Train.exe < data.txt > biaoda.txt");
        system("test.exe < data.txt > test.txt");
        if(system("fc test.txt biaoda.txt"))   break;
    }
    if(t==0) cout<<"no error"<<endl;
    else cout<<"error"<<endl;
    //system("pause");
    return 0;
}

