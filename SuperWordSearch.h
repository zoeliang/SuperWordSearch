//
//  SuperWordSearch.h
//  SuperWordSearch
//
//  Created by Yuan Liu on 14-1-17.
//  Copyright (c) 2014年 Yuan Liu. All rights reserved.
//

#ifndef __SuperWordSearch__SuperWordSearch__
#define __SuperWordSearch__SuperWordSearch__

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

// define constant
const string NO_WRAP="NO_WRAP";
const string WRAP="WRAP";

// Solution class definition
class Solution{
protected:
	// two-dimention vector to represent board
	vector<vector<char>> board;
	// all the waiting words 
	vector<string> word;
	// storing the result
	vector<string> res;
	
public:
	Solution(vector<vector<char>> b,vector<string> w);
	// virtual method to print board
	virtual void printBoard();
	// method to print result
	void printResult();
	// pure virtual method to search words
	virtual void wordSearch()=0;
};

Solution::Solution(vector<vector<char>> b,vector<string> w){
	board=b;
	word=w;
}

void Solution::printBoard(){
	int row=board.size();
	// empty board
	if (row==0) cout << "empty board!" << endl;
	else{
		int col=board[0].size();
		if(col==0) cout << "empty column!" << endl;
		else{
			cout << "The board is:" << endl;
			// traverse the board
			for(int i=0;i<row;i++){
				for(int j=0;j<col;j++){
					cout << board[i][j] << " ";
				}
				cout << endl;
			}
		}
	}
	// print the words waiting
	cout << "The words are:" << endl;
	for(string s:word) cout << s << endl;
}

void Solution::printResult(){
	cout << "The result is:" << endl;
	for(string s:res){
		cout << s << endl;
	}
}

// SolutionNowrap class, implementing no wrap mode
class SolutionNowrap:public Solution{
private:
	// map to store used positions
	map<string,int> used;
public:
	SolutionNowrap(vector<vector<char>> board,vector<string> word):Solution(board,word){};
	
	void printBoard(){
		// call father method
		Solution::printBoard();
		// then self to show mode
		cout << "The mode is " << NO_WRAP << endl;
	}
	
	// recursive funtion for word search
	void _nowrap(string s,int i,int j,int index,map<string,int> &used,string &one_res,bool &found){
		// find a result, update res
		string usedtest=to_string(i)+to_string(j);
		if(board[i][j]==s[index]&&index==s.size()-1&&used.find(usedtest)==used.end()&&!found){
			string end="("+to_string(i)+","+to_string(j)+")";
			found=true;
			res.push_back(one_res+end);
			return ;
			
		}
		// use BFS to search next possible character		
		if(board[i][j]==s[index]&&index!=s.size()-1&&used.find(usedtest)==used.end()&&!found){
			used[usedtest]=1;
			// go eight directions
			if(i>0) _nowrap(s, i-1, j, index+1,used,one_res,found);
			if(i<board.size()-1) _nowrap(s, i+1, j, index+1,used,one_res,found);
			if(j>0) _nowrap(s, i, j-1, index+1,used,one_res,found);
			if(j<board[0].size()-1) _nowrap(s, i, j+1, index+1,used,one_res,found);
			if(i>0&&j>0) _nowrap(s, i-1, j-1, index+1,used,one_res,found);
			if(i<board.size()-1&&j>0) _nowrap(s, i+1, j-1, index+1,used,one_res,found);
			if(i>0&&j<board[0].size()-1) _nowrap(s, i-1, j+1, index+1,used,one_res,found);
			if(i<board.size()-1&&j<board[0].size()-1) _nowrap(s, i+1, j+1, index+1,used,one_res,found);
		}
	}
	
	void wordSearch(){
		for(int w=0;w<word.size();w++){
			// for each word, clean the result
			//used.clear();
			string one_res="";
			bool found=false;
			for(int i=0;i<board.size();i++){
				for(int j=0;j<board[0].size();j++){
					// find the first character
					if(board[i][j]==word[w][0]){
						// clean the map
						used.clear();
						// record beginning position
						one_res="("+to_string(i)+","+to_string(j)+") ";
						// pass reference here, update used and one_res
						_nowrap(word[w],i,j,0,used,one_res,found);
						// if found, search next word
						if(found) break;
					}
				}
				// we only need one result per word
				if(found) break;
			}
			if(found) continue;
			else res.push_back("NOT FOUND");
		}
	}
};

class SolutionWrap:public Solution{
private:
	map<string,int> used;
public:
	SolutionWrap(vector<vector<char>> board,vector<string> word):Solution(board,word){};
	
	void printBoard(){
		Solution::printBoard();
		cout << "The mode is " << WRAP << endl;
	}
	void _wrap(string s,int i,int j,int index,map<string,int> &used,string &one_res,bool &found){
		string usedtest=to_string(i)+to_string(j);
		if(board[i][j]==s[index]&&index==s.size()-1&&used.find(usedtest)==used.end()&&!found){
			string end="("+to_string(i)+","+to_string(j)+")";
			found=true;
			res.push_back(one_res+end);
			return ;
			
		}
		// two modes differs here
		// under wrap mode, need to cover all the corner cases,
		// make sure it wraps well on the board for eight directions
		if(board[i][j]==s[index]&&index!=s.size()-1&&used.find(usedtest)==used.end()&&!found){
			used[usedtest]=1;
			if(i>0) _wrap(s, i-1, j, index+1,used,one_res,found);
			else _wrap(s,board.size()-1,j,index+1,used,one_res,found);
			if(i<board.size()-1) _wrap(s, i+1, j, index+1,used,one_res,found);
			else _wrap(s, 0, j, index+1, used, one_res,found);
			if(j>0) _wrap(s, i, j-1, index+1,used,one_res,found);
			else _wrap(s, i, board[0].size()-1, index+1, used, one_res,found);
			if(j<board[0].size()-1) _wrap(s, i, j+1, index+1,used,one_res,found);
			else _wrap(s, i, 0, index+1, used, one_res,found);
			if(i>0&&j>0) _wrap(s, i-1, j-1, index+1,used,one_res,found);
			else if(i>0) _wrap(s, i-1, board[0].size()-1, index+1, used, one_res,found);
			else if(j>0) _wrap(s, board.size()-1, j-1, index+1, used, one_res,found);
			else _wrap(s, board.size()-1, board[0].size()-1, index+1, used, one_res,found);
			if(i<board.size()-1&&j>0) _wrap(s, i+1, j-1, index+1,used,one_res,found);
			else if(i<board.size()-1) _wrap(s, i+1, board[0].size()-1, index+1, used, one_res,found);
			else if(j>0) _wrap(s, 0, j-1, index+1, used, one_res,found);
			else _wrap(s, 0, board[0].size()-1, index+1, used, one_res,found);
			if(i>0&&j<board[0].size()-1) _wrap(s, i-1, j+1, index+1,used,one_res,found);
			else if(i>0) _wrap(s, i-1, 0, index+1, used, one_res,found);
			else if(j<board[0].size()-1) _wrap(s, board.size()-1, j+1, index+1, used, one_res,found);
			else _wrap(s, board.size()-1, 0, index+1, used, one_res,found);
			if(i<board.size()-1&&j<board[0].size()-1) _wrap(s, i+1, j+1, index+1,used,one_res,found);
			else if(i<board.size()-1) _wrap(s, i+1, 0, index+1, used, one_res,found);
			else if(j<board[0].size()-1) _wrap(s, 0, j+1, index, used, one_res,found);
			else _wrap(s, 0, 0, index+1, used, one_res,found);
		}
	}
	
	void wordSearch(){
		for(int w=0;w<word.size();w++){
			string one_res="";
			bool found=false;
			for(int i=0;i<board.size();i++){
				for(int j=0;j<board[0].size();j++){
					if(board[i][j]==word[w][0]){
						used.clear();
						one_res="("+to_string(i)+","+to_string(j)+") ";
						_wrap(word[w],i,j,0,used,one_res,found);
						if(found) break;
					}
				}
				if(found) break;
			}
			if(!found){
				res.push_back("NOT FOUND");
			}
		}
	}
};

// SolutionFactory class, interacts with user
class SolutionFactory{
private:
	vector<vector<char>> board;
	string mode;
	vector<string> word;
	
protected:
	// read file and build board
	void init(string filename,vector<vector<char>> &board,string &mode,vector<string> &word){
		string line;
		ifstream myfile(filename);
		if(myfile.is_open()){
			// read row and column here
			getline(myfile,line);
			int i,row,column;
			i=row=column=0;
			while(isdigit(line[i])) row=row*10+(line[i++]-'0');
			while(isspace(line[i])) i++;
			while(isdigit(line[i])) column=column*10+(line[i++]-'0');
			// read the board here according to the row and col
			if(row!=0&&column!=0){
				for(i=0;i<row;i++){
					vector<char> col;
					getline(myfile, line);
					for(int j=0;j<line.size();j++) if(!isspace(line[j])) col.push_back(line[j]);
					board.push_back(col);
				}
			}
			// read mode
			getline(myfile, line);
			int k=line.size()-1;
			while(isspace(line[k])) k--;
			line=line.substr(0,k+1);
			mode=line;
			// read words needed to be searched
			getline(myfile, line);
			int num=atoi(line.c_str());
			for(i=0;i<num;i++){
				getline(myfile, line);
				int k=line.size()-1;
				while(isspace(line[k])) k--;
				line=line.substr(0,k+1);
				word.push_back(line);
			}
			cout << "Initialize finished" << endl;
			myfile.close();
		}
		else cout << "Unable to open file " << filename << endl;		
	}

public:
	SolutionFactory(string f){
		init(f,board,mode,word);
	}
		
	Solution *getSolution(){
		if(mode==NO_WRAP) return new SolutionNowrap(board,word);
		else if(mode==WRAP) return new SolutionWrap(board,word);
		else return NULL;
	}
};

#endif /* defined(__SuperWordSearch__SuperWordSearch__) */
