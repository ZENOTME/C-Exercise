#include"Hufman.hpp"
#include<gtest/gtest.h>

int main(int argc,char ** argv){
	assert(argc==2);
	HufProssor prossor(argv[1]);
	prossor.test();
	prossor.Save();
}



