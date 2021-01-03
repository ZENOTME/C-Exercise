#ifndef HUFMAN_HPP_
#define HUFMAN_HPP_
#include"BinTree.hpp"
#include<iostream>
#include<memory>
#include<string>
#include<list>
#include<unordered_map>
#include<algorithm>
#include<fstream>
#include<streambuf>
#include<cassert>
#include<vector>
using namespace std;


void bitToChar(string& ori,string& res,size_t& remind);//二进制字符串化为字符串
void CharToBit(string& ori,string& res,size_t& remind);//字符串化为二进制字符串

struct HufChar{
	char ch;
	size_t weight;
	HufChar(char c,size_t w):ch(c),weight(w){}
	//op
	bool operator<(const HufChar& rhs)const{
		return this->weight<rhs.weight;
	}
	bool operator==(const HufChar& rhs)const{
		return this->weight==rhs.weight;
	}
};
ostream& operator<<(ostream& os,const HufChar& hc);


//======编码方式=======
//CT编码：字符的100 从 0-》0-》1
//字符串：00001111 -》 0F

using HufTree=BinTree<HufChar>;
class HufProssor{
private:
	string FileName="";
	string FileContent="";
	list<shared_ptr<HufTree>>HufForest;
	unordered_map<char,size_t>ST;
	unordered_map<char,string>CT;
	string code="";
private:
	void _statistics();    //统计
	void _initForest();    //初始化森林
	void _generateTree();  //生成编码树
    template<typename T>void _generateCT(vector<bool>&,size_t,BinNode<T>*);    
	void _generateTable(); //生成编码表
	void _encode();		   //编码
	void _decode_main(string&,string&,size_t);	//解码
public:	
	HufProssor()=default;
	//压缩
	HufProssor(string name);
	//保存
	bool Save(string name){
		if(code.empty())return false;
		ofstream out(name,ios::out|ios::binary);
		out.write(code.c_str(),code.length());
		out.close();
		return true;
	}
	bool Save(){
		return Save(FileName+".huf");
	}
	//测试
	void test(){
		//========File Read
		cout<<"Filename:"<<FileName<<endl;
		cout<<"FileContent:"<<endl;
		cout<<FileContent<<endl;
		//========File Statistics
		_statistics();
		for_each(ST.begin(),ST.end(),[](const auto& item){cout<<item.first<<":"<<item.second<<endl;});
		//========Init Forest
		_initForest();
		cout<<"Forest:"<<endl;
		for_each(HufForest.begin(),HufForest.end(),[](const auto& item){cout<<*(item->root())<<endl;});
		//========Generate Tree
		_generateTree();
		assert(HufForest.size()==1);
		cout<<*(HufForest.front()->root());
		//========Generate CT
		_generateTable();
		for_each(CT.begin(),CT.end(),[](const auto& item){cout<<item.first<<" "<<item.second<<endl;});
		//========encode
		_encode();
		cout<<"code:\n"<<code<<endl;
		//========


	}
};
#endif
