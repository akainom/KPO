#pragma once

#define ID_MAXSIZE		15					// максимальное количество символов в идентификаторе 
#define TI_MAXSIZE		4096				// максимальное количество строк в таблице идентификаторов
#define TI_BOOL_DEFAULT	NULL				//	значение по умолчанию для типа BOOL
#define TI_INT_DEFAULT  0x00000000			// значение по умолчанию для типа uint
#define TI_STR_DEFAULT  0x00				// значение по умолчанию для типа string
#define TI_NULLIDX		0xffffffff			// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE  255					// максимальная длина строки

#define PARM_ID L".id.txt"

namespace IT
{
	enum IDDATATYPE { DEF = 0, UINT = 1, STR = 2, BOOL = 3 };				// типы данных идентификаторов: UINT, string
	enum IDTYPE { D = 0, V = 1, F = 2, P = 3, L = 4, PF = 5, SF = 6 };			// типы идентификаторов: переменная, функция, параметр, литерал, прототип функции, функция стандартной библиотеки

	struct Entry
	{
		char parrent_function[ID_MAXSIZE + 5];
		int firstApi;
		char id[ID_MAXSIZE + 5];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			bool vlogic;
			int vint;
			char operation = '\0';
			struct
			{

				unsigned char len;
				char str[TI_STR_MAXSIZE];
			} vstr;
			struct {
				int paramcount = 0;
				IDDATATYPE* types;
			}params;
		} value;
		int parmQuantity;
		Entry();
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* str);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* str);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, bool logic);
		Entry(char* parrentFunc, char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable
	{
		int noname_lexema_count;
		int maxsize;
		int size;
		Entry* table;
		Entry GetEntry(int n);
		int IsId(const char id[ID_MAXSIZE]);
		int IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5]);
		void Add(Entry entry);
		void PrintIdTable(const wchar_t* in);
		IdTable();
		char* GetLexemaName();
	};
	void Delete(IdTable& idtable);
};

