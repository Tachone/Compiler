#include "Base.h"

bool Base::isNotSymbol(char c)
{
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}
int Base::get_index(char target)
{
	for (int i = 0; i<non_colt.size(); i++)
	{
		if (target == non_colt[i])
			return i;
	}
	return -1;
}
int Base::get_nindex(char target)
{
	for (int i = 0; i<ter_copy.size(); i++)
	{
		if (target == ter_copy[i])
			return i;
	}
	return -1;
}
void Base::get_first(char target)
{
	int tag = 0;
	int flag = 0;
	for (int i = 0; i<T; i++)
	{
		if (analy_str[i].left == target)//匹配产生式左部
		{
			if (!isNotSymbol(analy_str[i].right[0]))//对于终结符，直接加入first
			{
				first_set[get_index(target)].insert(analy_str[i].right[0]);
			}
			else
			{
				for (int j = 0; j<analy_str[i].right.length(); j++)
				{
					if (!isNotSymbol(analy_str[i].right[j]))//终结符结束
					{
						first_set[get_index(target)].insert(analy_str[i].right[j]);
						break;
					}
					get_first(analy_str[i].right[j]);//递归
					//	cout<<"curr :"<<analy_str[i].right[j];
					set<char>::iterator it; 
					for (it = first_set[get_index(analy_str[i].right[j])].begin(); it != first_set[get_index(analy_str[i].right[j])].end(); it++)
					{
						if (*it == '$')
							flag = 1;
						else
							first_set[get_index(target)].insert(*it);//将FIRST(Y)中的非$就加入FIRST(X)
					}
					if (flag == 0)
						break;
					else
					{
						tag += flag;
						flag = 0;
					}
				}
				if (tag == analy_str[i].right.length())//所有右部first(Y)都有$,将$加入FIRST(X)中
					first_set[get_index(target)].insert('$');
			}
		}
	}

}
void Base::get_follow(char target)
{
	for (int i = 0; i<T; i++)
	{
		int index = -1;
		int len = analy_str[i].right.length();
		for (int j = 0; j<len; j++)
		{
			if (analy_str[i].right[j] == target)
			{
				index = j;
				break;
			}
		}
		if (index != -1 && index < len - 1)
		{
			char nxt = analy_str[i].right[index + 1];
			if (!isNotSymbol(nxt))
			{
				follow_set[get_index(target)].insert(nxt);
			}
			else
			{
				int isExt = 0;
				set<char>::iterator it;
				for (it = first_set[get_index(nxt)].begin(); it != first_set[get_index(nxt)].end(); it++)
				{
					if (*it == '$')
						isExt = 1;
					else
						follow_set[get_index(target)].insert(*it);
				}

				if (isExt && analy_str[i].left != target)
				{
					get_follow(analy_str[i].left);
					set<char>::iterator it;
					char tmp = analy_str[i].left;
					for (it = follow_set[get_index(tmp)].begin(); it != follow_set[get_index(tmp)].end(); it++)
						follow_set[get_index(target)].insert(*it);
				}
			}
		}

		else if (index != -1 && index == len - 1 && target != analy_str[i].left)
		{
			get_follow(analy_str[i].left);
			set<char>::iterator it;
			char tmp = analy_str[i].left;
			for (it = follow_set[get_index(tmp)].begin(); it != follow_set[get_index(tmp)].end(); it++)
				follow_set[get_index(target)].insert(*it);
		}

	}
}
void Base::inputAndSolve()
{
	string s;
	cout << "输入的产生式的个数：" << endl;
	cin >> T;
	for (int index = 0; index<T; index++)
	{
		cin >> s;
		string temp = "";
		for (int i = 0; i<s.length(); i++)
		{
			if (s[i] != ' ')
				temp += s[i];
		}
		analy_str[index].left = temp[0];
		for (int i = 3; i<temp.length(); i++)
			analy_str[index].right += temp[i];


		for (int i = 0; i<temp.length(); i++)
		{
			if (temp[i] != '-' && temp[i] != '>')
			{
				if (isNotSymbol(temp[i]))
				{
					int flag = 0;
					for (int j = 0; j<non_colt.size(); j++)
					{
						if (non_colt[j] == temp[i])
						{
							flag = 1;
							break;
						}
					}
					if (!flag)
						non_colt.push_back(temp[i]);

				}
				else
				{
					int flag = 0;
					for (int j = 0; j<ter_colt.size(); j++)
					{
						if (ter_colt[j] == temp[i])
						{
							flag = 1;
							break;
						}
					}
					if (!flag)
						ter_colt.push_back(temp[i]);
				}
			}
		}

	}
	ter_colt.push_back('#');
	//first
	for (int i = 0; i<non_colt.size(); i++)
	{
		get_first(non_colt[i]);
	}

	for (int i = 0; i<non_colt.size(); i++)
	{
		if (i == 0)
			follow_set[0].insert('#');
		get_follow(non_colt[i]);
	}

	for (int i = 0; i<ter_colt.size(); i++)
	{
		if (ter_colt[i] != '$')
			ter_copy.push_back(ter_colt[i]);
	}
}

void Base::display()
{
	cout << "FIRST集合" << endl;
	for (int i = 0; i<non_colt.size(); i++)
	{
		cout << non_colt[i] << ": ";
		set<char>::iterator it;
		for (it = first_set[i].begin(); it != first_set[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}

	cout << "FOLLOW集合" << endl;
	for (int i = 0; i<non_colt.size(); i++)
	{
		cout << non_colt[i] << ": ";
		set<char>::iterator it;
		for (it = follow_set[i].begin(); it != follow_set[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
}