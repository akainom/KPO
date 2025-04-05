#include "pch.h"
extern "C"
{
	char* __stdcall strcp(char* destination, char* string)
	{
		if (string == NULL || destination == NULL)
		{
			return NULL;
		}
		while (*string != '\0')
		{
			*destination = *string;
			destination++;
			string++;
		}
	}


	int __stdcall stcmp(const char* str1, const char* str2)
	{
		if (str1 == NULL && str2 == NULL)
		{
			return 0;
		}
		if (str1 == NULL)
		{
			return -1;
		}
		if (str2 == NULL)
		{
			return 1;
		}

		while (*str1 != '\0' && *str2 != '\0')
		{
			if (*str1 != *str2)
			{
				return (*str1 < *str2) ? -1 : 1;
			}
			str1++;
			str2++;
		}

		return (*str1 == '\0') ? 1 : -1;
	}

	void __stdcall writestr(char* str)
	{
		int lentstr = 0;
		if (str == NULL)
		{
			std::cout << std::endl;
		}
		for (int i = 0; str[i] != '\0'; i++)
		{
			std::cout << str[i];
		}
		std::cout << "\n";
	}
	void __stdcall writeint(int v)
	{
		std::cout << v << "\n";
	}
}