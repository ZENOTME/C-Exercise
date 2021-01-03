#include"Hufman.hpp"
#include<stdio.h>

HufProssor::HufProssor(string name){
	ifstream in(name);
	if(!in.is_open()){
		throw runtime_error("File can't open");
	}
	FileName=name;
	FileContent.assign(istreambuf_iterator<char>(in),istreambuf_iterator<char>());
}

void HufProssor::_statistics(){
	for_each(FileContent.begin(),FileContent.end(),[this](auto item){this->ST[item]++;});
}

void HufProssor::_initForest(){
	for(const auto& item:ST){
		HufForest.push_front(shared_ptr<HufTree>(new HufTree()));
		HufForest.front()->insertAsRoot(HufChar(item.first,item.second));
	}
}

void HufProssor::_generateTree(){
	auto cmp=[](const auto&lhs,const auto& rhs){return lhs->root()->_data.weight<rhs->root()->_data.weight;};
	HufForest.sort(cmp);
	
	while(HufForest.size()>1){
		auto LT_Ptr=shared_ptr<HufTree>(HufForest.front());
		HufForest.pop_front();
		auto RT_Ptr=shared_ptr<HufTree>(HufForest.front());
		HufForest.pop_front();
		
		HufForest.push_front(shared_ptr<HufTree>(new HufTree()));
		auto& tree=*HufForest.front();
		tree.insertAsRoot(HufChar('\0',LT_Ptr->root()->_data.weight+RT_Ptr->root()->_data.weight));
		tree.attachAsL(tree.root(),LT_Ptr);
		tree.attachAsR(tree.root(),RT_Ptr);
		HufForest.sort(cmp);
		
	}
	
}

template<typename T>
void HufProssor::_generateCT(vector<bool>& bitmap,size_t length,BinNode<T>* node){
	bitmap.resize(length+1);
	if(IsLeaf(*node)){
		string str;
		str.assign(bitmap.begin(),bitmap.end()-1);
		for_each(str.begin(),str.end(),[](auto& item){item=item?'1':'0';});
		CT[node->_data.ch]=str;
		return;
	}
	if(hasLChild(*node)){
		bitmap[length]=0;_generateCT(bitmap,length+1,node->_lc);
	}
	if(hasRChild(*node)){
		bitmap[length]=1;_generateCT(bitmap,length+1,node->_rc);
	}
}

void HufProssor::_generateTable(){
	vector<bool>bitmap;
	_generateCT(bitmap,0,HufForest.front()->root());
}


void HufProssor::_encode(){
	size_t sz=FileContent.length();
	//主编码
	//将每八个01合并为一个字符
	string str;
	for_each(FileContent.begin(),FileContent.end(),[this,&str](const auto& ch){str+=CT[ch];});
	string res;
	size_t remind=0;
	bitToChar(str,res,remind);
	
	//测试解码过程
	string res_test="";
	_decode_main(res,res_test,remind);
	assert(FileContent.compare(res_test)==0);

	//写入头信息
	code+=to_string(sz);code+=" ";code+=to_string(remind);code+="\n";
	//写入表
	for(const auto &item:ST){
		code+=item.first;
		code+=" ";
		code+=to_string(item.second);
		code+="\n";
	}
	//写入主编码
	code+=res;
}


//核心解码过程，假设树已经构建完毕
void HufProssor::_decode_main(string& ori,string& res,size_t remind){
	auto& tree=HufForest.front();
	//字符串码化为二进制码
	string str;
	CharToBit(ori,str,remind);
	size_t index=0;
	while(index<str.length()){
		auto node=tree->root();
		while(!IsLeaf(*node)&&node!=nullptr&&index<str.length()){
			assert(str[index]=='0'||str[index]=='1');
			if(str[index++]=='0'){
				node=node->_lc;
			}else{
				node=node->_rc;
			}
		}
		res+=node->_data.ch;
	}
}


//=========================================================================s
ostream& operator<<(ostream& os,const HufChar& hc){
	os<<"(char:"<<hc.ch<<" "<<"weight:"<<hc.weight<<")";
	return os;
}

void bitToChar(string& ori,string& res,size_t& remind){
	char ch=0;
	size_t sum_time=ori.length()/8;
	remind=ori.length()%8;
	for(int i=0;i<sum_time;i++){
		for(int j=0,off=7;j<8;j++,off--){
			assert(ori[i*8+j]=='1'||ori[i*8+j]=='0');
			ch|=(ori[i*8+j]=='1'?1<<off:0<<off);
		}
		res+=ch;
		ch=0;
	}
	for(int i=0,off=7;i<remind;i++,off--){
		assert(ori[sum_time*8+i]=='1'||ori[sum_time*8+i]=='0');
		ch|=(ori[sum_time*8+i]=='1'?1<<off:0<<off);
	}
	res+=ch;
	return;
}

void CharToBit(string& ori,string& res,size_t& remind){
	auto readBit=[](char ch,size_t n){return (ch&(1<<n))==0?0:1;};
	auto transBit=[readBit,&res](const auto& ch){
		for(int i=7;i>-1;i--){
			res+=readBit(ch,i)?'1':'0';			
		}
	};
	for_each(ori.begin(),ori.end()-1,transBit);

	
	for(int i=0,j=7;i<remind;i++,j--){
		res+=readBit(*(ori.end()-1),j)?'1':'0';
	}
}


