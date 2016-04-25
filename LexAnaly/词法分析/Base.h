#ifndef _Base_H_
#define _Base_H_

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>


//c语言关键字 
static char keywords[50][13] = { "short", "int", "long", "float", "double", "char"
, "struct", "union", "enum", "typedef", "const", "unsigned", "signed", "extern"
, "static", "void", "if", "else", "switch", "case", "for", "do", "while",
"goto", "continue", "break", "default", "sizeof", "return", "true", "false" };

class Base
{
public:
	int buffernum;

public:
	Base(){ buffernum = 0; }
	virtual ~Base();

	int charkind(char c);//判断字符类型
	int spaces(char c); //当前空格是否可以消除
	int characters(char c);//是否是字母
	int keyword(char str[]);//是否是关键字
	int signwords(char str[]);//是否是标识符
	int numbers(char c);//是否是数字
	int integers(char str[]);//是否是整数
	int floats(char str[]);//是否是浮点型
};

#endif
