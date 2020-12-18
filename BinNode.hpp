#include<iostream>
using namespace std;


template <typename T>
class BinNode{
	//性质判断
    friend inline bool IsRoot(BinNode<T>* x){return !(x->parent);}
	friend inline bool IsLChild(BinNode<T>* x){return !!IsRoot(x)&&(x->_parent->_lc==x);}
	friend inline bool IsRChild(BinNode<T>* x){return !IsRoot(x)&&(x->_parent->_rc==x);}
	friend inline bool hasParent(BinNode<T>* x){return !IsRoot(x);}
	friend inline bool hasRChild(BinNode<T>* x){return x->_rc;}
	friend inline bool hasLChild(BinNode<T>* x){return x->_lc;}
    friend inline bool hasChild(BinNode<T>* x){return hasLChild(x)||hasRChild(x);}
	friend inline bool hasBothChild(BinNode<T>* x){return hasLChild(x)&&hasRChild(x);}
	friend inline bool IsLeaf(BinNode<T>* x){return !hasChild(x);}
	
	private:	
		T _data;
		BinNode<T>* _parent;
		BinNode<T>* _lc;
		BinNode<T>* _rc;
	public:
		//构造
		BinNode():_data(0),_parent(nullptr),_lc(nullptr),_rc(nullptr){}
		BinNode(T d,BinNode<T>* p=nullptr,BinNode<T>* l=nullptr,BinNode<T>* r=nullptr):_data(d),_parent(p),_lc(l),_rc(r){}
		T data(){return _data;}
		//操作接口
		const BinNode<T>* lc(){return _lc;}
		const BinNode<T>* rc(){return _rc;}
		BinNode<T>* insertAsL(const T& d);
		BinNode<T>* insertAsR(const T& d);
		BinNode<T>* insertAsL(const BinNode<T>* node);
		BinNode<T>* insertAsR(const BinNode<T>* node);
		void show();
		//比较器，判等器
		bool operator<(BinNode const& bn){return _data<bn._data;}
		bool operator==(BinNode const& bn){return _data==bn._data;}
		//指针
		BinNode<T>* FromParentTo(){
			return IsRoot(this)?nullptr:(IsLChild(this)?_parent->lc:_parent->rc);
		}
		BinNode<T>* sibling(){
			return IsLChild(this)?_parent->rc:_parent->lc;
		}
		
};

template <typename T>
BinNode<T>* BinNode::insertAsL(const T& d){
	if(_lc==nullptr)
		return _lc=new BinNode(d,this);
	return nullptr;
}

template <typename T>
BinNode<T>* BinNode::insertAsR(const T& d){
	if(_rc==nullptr)
		return _rc=new BinNode(d,this);
	return nullptr;
}

template <typename T>
BinNode<T>* BinNode::insertAsL(const BinNode<T>* node){
	if(_lc==nullptr){
		node->_parent=this;
		return _lc=node;
	}
	return nullptr;
}

template <typename T>
BinNode<T>* BinNode::insertAsR(const BinNode<T>* node){
	if(_rc==nullptr){
		node->_parent=this;
		return _rc=node;
	}
	return nullptr;
}

template <typename T>
void BinNode::show(){
	cout<<_data<<" ";
	if(hasLChild(this))cout<<"L:"<<_lc->data<<" ";
	if(hasRChild(this))cout<<"R:"<<_lc->data<<" ";
	cout<<endl;
}
