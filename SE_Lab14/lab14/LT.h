#pragma once
#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE  1			//фиксированный размер лексемы
#define	LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем	
#define	LT_TI_NULLXDX	-1			// нет элемента таблицы идентификаторов	
#define LEX_BOOL		't'			// лексема для bool
#define	LEX_UINT		't'			// лексема для UINT
#define	LEX_STRING		't'			// лексема для string
#define LEX_TRUE		'l'			// лексема для true
#define LEX_FALSE		'l'			// лексема для false
#define	LEX_ID			'i'			// лексема для идентификатора
#define	LEX_LITERAL		'l'			// лексема для литерала
#define LEX_CONDITION	'I'			// лексема для условия
#define	LEX_FUNCTION	'f'			// лексема для function
#define LEX_MAIN		'm'			// лексема для main
#define	LEX_DECLARE		'd'			// лексема для declare
#define	LEX_RETURN		'r'			// лексема для return
#define	LEX_PRINT		'p'			// лексема для print
#define	LEX_STRLEN		'e'			// лексема для strlen
#define	LEX_SEMICOLON	';'			// лексема для ;
#define	LEX_COMMA		','			// лексема для ,
#define	LEX_LEFTBRACE	'{'			// лексема для {
#define	LEX_RIGHTBRACE	'}'			// лексема для }
#define	LEX_LEFTHESIS	'('			// лексема для (
#define	LEX_RIGHTHESIS	')'			// лексема для )
#define	LEX_PLUS		'v'			// лексема для +
#define	LEX_MINUS		'v'			// лексема для -
#define	LEX_STAR		'v'			// лексема для *
#define	LEX_DIRSLASH	'v'			// лексема для /
#define LEX_LESS_EQUAL	'v'			// лексема для <=
#define LEX_MORE_EQUAL	'v'			// лексема для >=
#define LEX_LESS		'v'			// лексема для <
#define LEX_MORE		'v'			// лексема для >
#define LEX_NOT_EQUAL	'v'			// лексема для !
#define	LEX_EQUAL_SIGN	'='			// лексема для =
#define LEX_COMPARER	'c'			// лексема для знаков сравнения
#define LEX_EQUALS		'q'			// лексема для equals
#define LEX_STLC		's'			// лексема для вызова стандартной функции


// знаки >= и <= расширяются записываются в lexema_parent как _ и : соответственно

#define LESS			'<'			
#define MORE			'>'
#define PLUS			'+'
#define MINUS			'-'
#define STAR			'*'
#define DIRSLASH		'/'


namespace LT									// таблица лексем
{
	struct Entry								// строка таблицы лексем
	{
		char lexema;							// лексема
		int sn;									// номер строки в исходном тексте
		int idxLT;								// индекс в таблице лексем
		int idxTI;								// индекс в таблице идентификаторов или LT_TI_NULLIDX
		char lexema_parent;
		Entry();
		Entry(const char lex, int str_n, int idxTI);
		Entry( char lex, int str_n, int idxLT, int idxTI);
		Entry(const char lex_parent, const char lex, int str_n, int idxTI);
	};

	struct LexTable								// экзепляр таблицы лексем
	{
		int maxsize;							// ёмкость таблицы лексем < LT_MAXSIZE
		int size;								// текущий размер таблицы лексем < maxsize
		Entry* table;							// массив строк таблицы лексем


		Entry GetEntry(								// получить строку таблицы лексем
			int n									// номер получаемой строки
		);

		void PrintLexTable(const wchar_t* in);
		LexTable();
	};

	void Add(									// добавить строку в таблицу лексем
		LexTable& lextable,						// экземпляр таблицы лексем
		Entry entry								// строка таблицы лексем
	);

	void Delete(LexTable& lextable);			// удалить таблицу лексем (освободить память)
};