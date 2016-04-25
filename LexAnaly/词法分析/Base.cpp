#include "Base.h"

int Base::charkind(char c)
{
	if (characters(c) == 1)
	{
		return 1;
	}
	if (numbers(c) == 1)
	{
		return 2;
	}
	if (c == '$' || c == '_')
	{
		return 3;
	}
	if (c == '\\')
	{
		return 4;
	}
	if (c == '=')
	{
		return 5;
	}
	return 0;
}

int Base::spaces(char c)
{
	if ((c > 'z' || (c < 'a' && c > 'Z') || (c < 'A' && c > '9') || (c < '0')) && c != '_' && c != '$')
	{
		return 1;
	}
	return 0;
}
int Base::characters(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
	{
		return 1;
	}
	return 0;
}
int Base::keyword(char str[])
{
	int i;
	for (i = 0; i < 50; i++)
	{
		if (strcmp(str, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int Base::signwords(char str[])
{
	int i;
	if (str[0] == '$' || str[0] == '_' || characters(str[0]) == 1)
	{
		for (i = 0; str[i] != '\0'; i++)
		{
			if (spaces(str[i]) == 1)
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int Base::numbers(char c)
{
	if (c <= '9' && c >= '0')
	{
		return 1;
	}
	return 0;
}
int Base::integers(char str[])
{
	int i;
	if (str[0] == '-' || numbers(str[0]) == 1)
	{
		for (i = 0; i < strlen(str); i++)
		{
			if (str[i] == '.')
			{
				return 0;
			}
			if ((str[i] == 'x' || str[i] == 'X') && (((str[0] == '-' || str[0] == '+') && (str[1] != '0' || i > 2)) || (str[0] != '-' && str[0] != '+' && (str[0] != '0' || i > 1))))
			{
				return 0;
			}
			if ((i < strlen(str) - 1) && numbers(str[i]) == 0 && str[i] != 'x' && str[i] != 'X')
			{
				if (strlen(str) > 2 && strnicmp("0x", str, 2) == 0 || strnicmp("-0x", str, 3) == 0)
				{
					if (str[i] >= 'A' && str[i] <= 'F')
					{
						continue;
					}
				}
				return 0;
			}
			if ((i == strlen(str) - 1) && numbers(str[i]) == 0 && str[i] != 'L')
			{
				if (strlen(str) > 2 && strnicmp("0x", str, 2) == 0 || strnicmp("-0x", str, 3) == 0)
				{
					if (str[i] >= 'A' && str[i] <= 'F')
					{
						continue;
					}
				}
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int Base::floats(char str[])
{
	int i;
	int flag = 0;
	if (str[0] == '-' || numbers(str[0]) == 1)
	{
		for (i = 0; i < strlen(str); i++)
		{
			if (str[i] == '.')
			{
				if (flag == 0)
				{
					flag = 1;
					continue;
				}
				else
				{
					return 0;
				}
			}
			if ((str[i] == 'x' || str[i] == 'X') && (((str[0] == '-' || str[0] == '+') && (str[1] != '0' || i > 2)) || (str[0] != '-' && str[0] != '+' && (str[0] != '0' || i > 1))))
			{
				return 0;
			}
			if (numbers(str[i]) == 0 && str[i] != 'x' && str[i] != 'X')
			{
				if (strlen(str) > 2 && strnicmp("0x", str, 2) == 0 || strnicmp("-0x", str, 3) == 0)
				{
					if (str[i] >= 'A' && str[i] <= 'F')
					{
						continue;
					}
				}
				return 0;
			}
		}
		return flag;
	}
	return 0;
}
Base::~Base(){}