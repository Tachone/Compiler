#ifndef _LEXAN_H_
#define _LEXAN_H_
#include"Base.h"
class LexAn : public Base
{
	private:
		FILE *fin;
		FILE *fout;
		char bufferin[2][256];
		char bufferscan[256];
	public:
		LexAn()
		{
			fin = fopen("in.txt", "r");
			fout = fopen("out.txt", "w");
		}
		virtual ~LexAn();
		void scanwords(); //处理每一行
		void clearnotes();//清除注释和多余的空格
		void getwords(int state);//处理出单词
		void wordkind(char str[]);//判断单词类型并且输出
};
#endif 
