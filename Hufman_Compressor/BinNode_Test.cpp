#include"BinNode.hpp"
#include<gtest/gtest.h>
#include<iostream>
using namespace std;

TEST(BinNode,BaseOpt){
	BinNode<int>node;
	node.insertAsL(1);
	node.insertAsR(2);
	cout<<node<<endl;
}

TEST(BinNode,checkOpt){
	BinNode<int>node;
	EXPECT_EQ(IsRoot(node),true);
	EXPECT_EQ(IsRChild(node),false);
	EXPECT_EQ(IsLChild(node),false);
	EXPECT_EQ(hasParent(node),false);
	EXPECT_EQ(hasChild(node),false);
	EXPECT_EQ(IsLeaf(node),true);
	node.insertAsL(1);
	EXPECT_EQ(hasChild(node),true);
	EXPECT_EQ(hasBothChild(node),false);
	node.insertAsR(1);
	EXPECT_EQ(hasBothChild(node),true);
	EXPECT_EQ(IsLeaf(node),false);
}

TEST(BinNode,though){
	BinNode<int>node(0);
	node.insertAsL(1);
	node.insertAsR(2);
	node._lc->insertAsL(3);
	node._lc->insertAsR(4);
	//==============Pre Order
	vector<int>pre_expect_res={0,1,3,4,2};
	vector<int>pre_act_res;
	node.travPre_R(&node,[&pre_act_res](const auto& item){pre_act_res.push_back(item._data);});
	EXPECT_EQ(pre_act_res==pre_expect_res,true);
	pre_act_res.clear();
	node.travPre(&node,[&pre_act_res](const auto& item){pre_act_res.push_back(item._data);});
	EXPECT_EQ(pre_act_res==pre_expect_res,true);
	//==============In Ordder
	vector<int>in_expect_res={3,1,4,0,2};
	vector<int>in_act_res;
	node.travIn_R(&node,[&in_act_res](const auto& item){in_act_res.push_back(item._data);});
	EXPECT_EQ(in_act_res==in_expect_res,true);
	in_act_res.clear();
	node.travIn(&node,[&in_act_res](const auto& item){in_act_res.push_back(item._data);});
	EXPECT_EQ(in_act_res==in_expect_res,true);

}
