#include <iostream>
extern "C"
{
	char* __stdcall strcp(char*, char*);
	int __stdcall stcmp(const char* str1, const char* str2);
	void __stdcall writestr(char* str);
	void __stdcall writeint(int v);
}
