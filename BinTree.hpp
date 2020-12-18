#include"BinNode.hpp"

template<typename T,typename Node=BinNode>
class BinTree{
	private:
		using TreePtr=BinTree<T,Node>*;
		using NodePtr=Node<T>*;
		NodePtr _root;
		size_t _size;
	public:
		BinTree():_size(0),_root(nullptr){}
		~BinTree(){if(_size>0)remove(_root);}
		size_t size()const{return _size;}
		bool empty(){return !_size;}
		NodePtr root()const{return _root;}
		NodePtr insertAsRoot(T data);
		NodePtr insertAsL(NodePtr x,T data);
		NodePtr insertAsR(NodePtr x,T data);
		NodePtr attachAsRoot(TreePtr t);
		NodePtr attachAsLc(NodePtr x,TreePtr t);
		NodePtr attachAsRc(TreePtr x,TreePtr t);
		void remove(NodePtr x);
		void removeAt(NodePtr x);
		TreePtr secede(NodePtr x);
		void print(){
			print(_root);
		}
		void print(NodePtr x){
			if(x){
				x.show();
				if(hasLChild(x))print(x->lc());
				if(hasRChild(x))print(x->rc());
			}
		}
}


template<typename T,typename Node=BinNode>
NodePtr BinTree::insertAsRoot(T data){
	return _root=new Node<T>(data);
}

template<typename T,typename Node=BinNode>
NodePtr BinTree::insertAsL(NodePtr x,T data){
	return x->insertAsL(data);
}

template<typename T,typename Node=BinNode>
NodePtr BinTree::insertAsR(NodePtr x,T data){
	return x->insertAsR(data);
}

template<typename T,typename Node=BinNode>
NodePtr BinTree::attachAsLc(NodePtr x,TreePtr t){
	if(x->insertAsL(t->root())){
		t->_root=nullptr;
		delete t;
	}
	return x;
}

template<typename T,typename Node=BinNode>
NodePtr BinTree::attachAsRc(TreePtr x,TreePtr t){
	if(x->insertAsL(t->root())){
		t->_root=nullptr;
		delete t;
	}
	return x;
}

template<typename T,typename Node=BinNode>
void BinTree::remove(NodePtr x){
	FromParentTo()=nullptr;
	removeAt(x);
}

template<typename T,typename Node=BinNode>
void BinTree::removeAt(NodePtr x){
	if(x){
		if(x->_lc)removeAt(x->_lc);
		if(x->_rc)removeAt(x->_rc);
		delete x
	}
}
		
template<typename T,typename Node=BinNode>
TreePtr secede(NodePtr x){
	FromParentTo()=nullptr;
	TreePtr T=new BinTree<T,Node>();
	x->_parent=NULL;T->_root=x;
	return T;
}

