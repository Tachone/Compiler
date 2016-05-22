#ifndef _BASE_H_
#define _BASE_H_
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cmath>
#include <stack>
using namespace std;

struct node
{
	char left;
	string right;
};

class Base
{
protected:
	int T;
	node analy_str[100]; //输入文法解析

	set<char> first_set[100];//first集
	set<char> follow_set[100];//follow集
	vector<char> ter_copy; //去$终结符
	vector<char> ter_colt;//终结符
	vector<char> non_colt;//非终结符

public:
	Base() :T(0){}
	bool isNotSymbol(char c);
	int get_index(char target);//获得在终结符集合中的下标
	int get_nindex(char target);//获得在非终结符集合中的下标
	void get_first(char target); //得到first集合
	void get_follow(char target);//得到follow集合
	void inputAndSolve(); //处理得到first和follow
	void display(); //显示

};
#endif 
