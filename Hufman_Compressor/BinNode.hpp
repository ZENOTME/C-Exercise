#ifndef BINTREE_HPP_
#define BINTREE_HPP_
#include<iostream>
#include<stack>
using namespace std;
template<typename T>class BinNode;

template<typename T>
bool IsRoot(const BinNode<T>& x);
template<typename T>
bool IsLChild(const BinNode<T>& x);
template<typename T>
bool IsRChild(const BinNode<T>& x);
template<typename T>
bool hasParent(const BinNode<T>& x);
template<typename T>
bool hasRChild(const BinNode<T>& x);
template<typename T>
bool hasLChild(const BinNode<T>& x);
template<typename T>
bool hasChild(const BinNode<T>& x);
template<typename T>
bool hasBothChild(const BinNode<T>& x);
template<typename T>
bool IsLeaf(const BinNode<T>& x);
template<typename T>
ostream& operator<<(ostream& os,const BinNode<T>& x);
	

template <typename T>
struct BinNode{
	//性质判断
    friend bool IsRoot<T>(const BinNode<T>& x);
	friend bool IsLChild<T>(const BinNode<T>& x);
	friend bool IsRChild<T>(const BinNode<T>& x);
	friend bool hasParent<T>(const BinNode<T>& x);
	friend bool hasRChild<T>(const BinNode<T>& x);
	friend bool hasLChild<T>(const BinNode<T>& x);
    friend bool hasChild<T>(const BinNode<T>& x);
	friend bool hasBothChild<T>(const BinNode<T>& x);
	friend bool IsLeaf<T>(const BinNode<T>& x);
	friend ostream& operator<< <T> (ostream& os,const BinNode<T>& x);
	
	public:	
		T _data;
		BinNode<T>* _parent;
		BinNode<T>* _lc;
		BinNode<T>* _rc;
	public:
		//构造
		BinNode():_data(0),_parent(nullptr),_lc(nullptr),_rc(nullptr){}
		BinNode(T d,BinNode<T>* p=nullptr,BinNode<T>* l=nullptr,BinNode<T>* r=nullptr):_data(d),_parent(p),_lc(l),_rc(r){}
		//操作接口
		BinNode<T>* lc()const{return _lc;}
		BinNode<T>* rc()const{return _rc;}
		BinNode<T>* insertAsL(const T& d){
			if(_lc==nullptr)
					return _lc=new BinNode(d,this);
			return nullptr;
		}
		BinNode<T>* insertAsR(const T& d){
			if(_rc==nullptr)
					return _rc=new BinNode(d,this);
			return nullptr;
		
		}
		//比较器，判等器
		bool operator<(BinNode const& bn)const{return _data<bn._data;}
		bool operator==(BinNode const& bn)const{return _data==bn._data;}
		//返回对象
		BinNode<T>* sibling()const{
			return IsLChild(*this)?_parent->_rc:_parent->_lc;
		}
		/**使用前确保自身不是一个root节点**/
		BinNode<T>*& FromParentTo()const{
			if(IsLChild(*this))
				return _parent->_lc;
			else
				return _parent->_rc;
		}
	    //遍历器
		template<class Function>
		static void travLevel(BinNode<T>* x,Function visit);//层次遍历
		template<class Function>
		static void travPre(BinNode<T>* x,Function visit);  //前序遍历
		template<class Function>
		static void travIn(BinNode<T>* x,Function visit);   //中序遍历
		template<class Function>
		static void travPost(BinNode<T>* x,Function visit); //后序遍历
		template<class Function>
		static void travLevel_R(BinNode<T>* x,Function visit);//层次遍历
		template<class Function>
		static void travPre_R(BinNode<T>* x,Function visit);  //前序遍历
		template<class Function>
		static void travIn_R(BinNode<T>* x,Function visit);   //中序遍历
		template<class Function>
		static void travPost_R(BinNode<T>* x,Function visit); //后序遍历
};

//========================================= 
//
template<typename T>
inline bool IsRoot(const BinNode<T>& x){return !(x._parent);}
template<typename T>
inline bool IsLChild(const BinNode<T>& x){return !IsRoot(x)&&(x._parent->_lc==&x);}
template<typename T>
inline bool IsRChild(const BinNode<T>& x){return !IsRoot(x)&&(x._parent->_rc==&x);}
template<typename T>
inline bool hasParent(const BinNode<T>& x){return !IsRoot(x);}
template<typename T>
inline bool hasRChild(const BinNode<T>& x){return x._rc!=nullptr;}
template<typename T>
inline bool hasLChild(const BinNode<T>& x){return x._lc!=nullptr;}
template<typename T>
inline bool hasChild(const BinNode<T>& x){return hasLChild(x)||hasRChild(x);}
template<typename T>
inline bool hasBothChild(const BinNode<T>& x){return hasLChild(x)&&hasRChild(x);}
template<typename T>
inline bool IsLeaf(const BinNode<T>& x){return !hasChild(x);}
template<typename T>
ostream& operator<<(ostream& os,const BinNode<T>& x){
	os<<"D:"<<x._data<<" ";
	if(hasLChild(x)){
		os<<"L:"<<x._lc->_data<<" ";}
	if(hasRChild(x)){
		os<<"R:"<<x._rc->_data<<" ";
	}
	os<<endl;
	if(hasLChild(x))operator<<(os,*x._lc);
	if(hasRChild(x))operator<<(os,*x._rc);
	return os;
}

//遍历
template<typename T>
template<class Function>
void BinNode<T>::travPre(BinNode<T>* x,Function visit){
	stack<BinNode<T>*>S;
	S.push(x);
	while(!S.empty()){
		BinNode<T>*node=S.top();
		S.pop();
		do{
			if(hasRChild(*node))
				S.push(node->_rc);
			visit(*node);
			node=node->_lc;
		}while(node);
	}
}

template<typename T>
template<class Function>
void BinNode<T>::travPre_R(BinNode<T>* x,Function visit){
	if(!x)
		return;
	visit(*x);
	travPre_R(x->_lc,visit);
	travPre_R(x->_rc,visit);
}

template<typename T>
template<class Function>
void BinNode<T>::travIn(BinNode<T>* x,Function visit){
	stack<BinNode<T>*>S;
	BinNode<T>* node=x;
	while(true){
		while(node){
			S.push(node);
			node=node->_lc;
		}
		if(S.empty())return;
		node=S.top();visit(*node);S.pop();
		node=node->_rc;
	}
}

template<typename T>
template<class Function>
void BinNode<T>::travIn_R(BinNode<T>* x,Function visit){
	if(!x)
		return;
	travIn_R(x->_lc,visit);
	visit(*x);
	travIn_R(x->_rc,visit);
}

#endif
