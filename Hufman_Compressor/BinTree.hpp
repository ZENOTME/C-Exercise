#ifndef BINNODE_HPP_
#define BINNODE_HPP_
#include"BinNode.hpp"
#include"memory"
template<typename T,template<typename U>typename Node=BinNode>
class BinTree{
	using TreePtr=BinTree<T,Node>*;
	using NodePtr=Node<T>*;
	private:
		NodePtr _root;
		size_t _size;
	public:
		BinTree():_size(0),_root(nullptr){}
		~BinTree(){remove(this);}
		size_t size()const{return _size;}
		bool empty()const{return !_size;}
		NodePtr root()const{return _root;}
		NodePtr insertAsRoot(const T& data);
		NodePtr insertAsL(NodePtr x,const T& data);
		NodePtr insertAsR(NodePtr x,const T& data);
		NodePtr attachAsRoot(TreePtr t);
		NodePtr attachAsL(NodePtr x,TreePtr& t);
		NodePtr attachAsR(NodePtr x,TreePtr& t);
		NodePtr attachAsL(NodePtr x,shared_ptr<BinTree<T,Node>>& t);
		NodePtr attachAsR(NodePtr x,shared_ptr<BinTree<T,Node>>& t);
		shared_ptr<BinTree<T,Node>> secede(NodePtr x);
		static void remove(TreePtr x);
		static void removeAt(NodePtr x);
	public:
		//Alorigthn
};


template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::insertAsRoot(const T& data){
	return _root=new Node<T>(data);
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::insertAsL(NodePtr x,const T& data){
	if(!x)
		return nullptr;
	return x->insertAsL(data);
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::insertAsR(NodePtr x,const T& data){
	if(!x)
		return nullptr;
	return x->insertAsR(data);
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::attachAsL(NodePtr x,TreePtr& t){
	if(!x)
		return nullptr;
	if(!x->_lc){
		x->_lc=t->_root;
		x->_lc->_parent=x;
		t->_root=nullptr;
		delete t;
		t=nullptr;
	}
	return x;
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::attachAsR(NodePtr x,TreePtr& t){
	if(!x)
		return nullptr;
	if(!x->_rc){
		x->_rc=t->_root;
		x->_rc->_parent=x;
		t->_root=nullptr;
		delete t;
		t=nullptr;
	}
	return x;
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::attachAsL(NodePtr x,shared_ptr<BinTree<T,Node>>& t){
	if(!x)
		return nullptr;
	if(!x->_lc){
		x->_lc=t->_root;
		x->_lc->_parent=x;
		t->_root=nullptr;
		t.reset();
		t=nullptr;
	}
	return x;
}

template<typename T,template<typename U>typename Node>
typename BinTree<T,Node>::NodePtr BinTree<T,Node>::attachAsR(NodePtr x,shared_ptr<BinTree<T,Node>>& t){
	if(!x)
		return nullptr;
	if(!x->_rc){
		x->_rc=t->_root;
		x->_rc->_parent=x;
		t->_root=nullptr;
		t.reset();
		t=nullptr;
	}
	return x;
}


template<typename T,template<typename U>typename Node>
shared_ptr<BinTree<T,Node>> BinTree<T,Node>::secede(NodePtr x){
	if(!x)
		return nullptr;
	if(!IsRoot(*x)){
		auto& p=x->FromParentTo();
		p=nullptr;
	}
	auto t=make_shared<BinTree<T,Node>>();
	x->_parent=nullptr;t->_root=x;
	return t;
}

template<typename T,template<typename U>typename Node>
void BinTree<T,Node>::remove(TreePtr x){
	removeAt(x->_root);
}

template<typename T,template<typename U>typename Node>
void BinTree<T,Node>::removeAt(NodePtr x){
	if(x){
		if(x->_lc)removeAt(x->_lc);
		if(x->_rc)removeAt(x->_rc);
		if(!IsRoot(*x)){
			auto &p=x->FromParentTo();
			p=nullptr;
		}
		delete x;
	}
}
		
#endif
