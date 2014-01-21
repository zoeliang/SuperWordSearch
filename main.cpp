//
//  main.cpp
//  SuperWordSearch
//
//  Created by Yuan Liu on 14-1-17.
//  Copyright (c) 2014年 Yuan Liu. All rights reserved.
//
#include "SuperWordSearch.h"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{

	// solution factory instance
	SolutionFactory sf("/Users/yuanliu/Documents/C/input.txt");
	// get corresponding solution
	Solution *s=sf.getSolution();
	if(s){
		// print the board first, not necessary for grading
		s->printBoard();
		// do the search job
		s->wordSearch();
		// print the result to console
		s->printResult();
	}
	return 0;
}

