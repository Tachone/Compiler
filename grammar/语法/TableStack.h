#ifndef _TABLESTACK_H_
#define _TABLESTACK_H_

#include"Base.h"

class TableStack :public Base
{
protected:
	vector<char> to_any; //分析栈
	vector<char> left_any;//剩余输入串
	int tableMap[100][100];//预测表
public:
	TableStack(){ memset(tableMap, -1, sizeof(tableMap)); }

	void get_table(); //得到预测表
	void analyExp(string s); //分析栈的处理
	void print_out();//输出
	void getAns(); //结合处理
};
#endif
