#include"BinTree.hpp"
#include<gtest/gtest.h>
#include<iostream>
#include<memory>
using namespace std;

TEST(BinTree,BaseOpt){
	//Create Tree
	auto l_tree=make_shared<BinTree<int>>();
	l_tree->insertAsRoot(1);
	l_tree->insertAsL(l_tree->root(),2);
	l_tree->insertAsR(l_tree->root(),2);
	cout<<"\nL_TREE:\n";
	cout<<*l_tree->root();

	auto r_tree=make_shared<BinTree<int>>();
	r_tree->insertAsRoot(1);
	r_tree->insertAsL(r_tree->root(),3);
	r_tree->insertAsR(r_tree->root(),3);
	cout<<"\nR_TREE:\n";
	cout<<*r_tree->root();

	auto tree=make_shared<BinTree<int>>();
	tree->insertAsRoot(1);
	tree->attachAsL(tree->root(),l_tree);
	tree->attachAsR(tree->root(),r_tree);
	cout<<"\nTREE:\n";
	cout<<*tree->root();
	//Secede
	r_tree=tree->secede(tree->root()->_rc);
	cout<<"\nTREE\n";
	cout<<*tree->root();
	cout<<"\nR_TREE\n";
	cout<<*r_tree->root();
	//Remove
	tree->removeAt(tree->root()->_lc);
	cout<<"\nTREE\n";
	cout<<*tree->root();
}
