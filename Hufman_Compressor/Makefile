GTEST_FLAGS:=-pthread -lgtest -lgtest_main

#Hufman
Hufman_Test:Hufman_Test.o Hufman.o
	g++ -o Hufman_Test Hufman_Test.o Hufman.o $(GTEST_FLAGS)

Hufman_Test.o:Hufman_Test.cpp Hufman.hpp
	g++ -c Hufman_Test.cpp 

Hufman.o:Hufman.cpp Hufman.hpp BinTree.hpp BinNode.hpp
	g++ -c Hufman.cpp



#BINTREE
BinTree_Test:BinTree_Test.o
	g++ -o BinTree_Test BinTree_Test.o $(GTEST_FLAGS)

BinTree_Test.o:BinTree_Test.cpp BinTree.hpp BinNode.hpp
	g++ -c BinTree_Test.cpp

BinTree_Test-gdb:BinTree_Test.cpp BinTree.hpp BinNode.hpp
	g++ -g -o BinTree_Test_gdb BinTree_Test.cpp $(GTEST_FLAGS)
	gdb ./BinTree_Test_gdb

#BINNODE
BinNode_Test:BinNode_Test.o
	g++ -o BinNode_Test BinNode_Test.o $(GTEST_FLAGS)

BinNode_Test.o: BinNode_Test.cpp BinNode.hpp
	g++ -c BinNode_Test.cpp

clean:
	rm BinNode_Test BinTree_Test *.o 


