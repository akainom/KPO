#pragma once
#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE  1			//������������� ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX	-1			// ��� �������� ������� ���������������	
#define LEX_BOOL		't'			// ������� ��� bool
#define	LEX_UINT		't'			// ������� ��� UINT
#define	LEX_STRING		't'			// ������� ��� string
#define LEX_TRUE		'l'			// ������� ��� true
#define LEX_FALSE		'l'			// ������� ��� false
#define	LEX_ID			'i'			// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define LEX_CONDITION	'I'			// ������� ��� �������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define LEX_MAIN		'm'			// ������� ��� main
#define	LEX_DECLARE		'd'			// ������� ��� declare
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_PRINT		'p'			// ������� ��� print
#define	LEX_STRLEN		'e'			// ������� ��� strlen
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTBRACE	'{'			// ������� ��� {
#define	LEX_RIGHTBRACE	'}'			// ������� ��� }
#define	LEX_LEFTHESIS	'('			// ������� ��� (
#define	LEX_RIGHTHESIS	')'			// ������� ��� )
#define	LEX_PLUS		'v'			// ������� ��� +
#define	LEX_MINUS		'v'			// ������� ��� -
#define	LEX_STAR		'v'			// ������� ��� *
#define	LEX_DIRSLASH	'v'			// ������� ��� /
#define LEX_LESS_EQUAL	'v'			// ������� ��� <=
#define LEX_MORE_EQUAL	'v'			// ������� ��� >=
#define LEX_LESS		'v'			// ������� ��� <
#define LEX_MORE		'v'			// ������� ��� >
#define LEX_NOT_EQUAL	'v'			// ������� ��� !
#define	LEX_EQUAL_SIGN	'='			// ������� ��� =
#define LEX_COMPARER	'c'			// ������� ��� ������ ���������
#define LEX_EQUALS		'q'			// ������� ��� equals
#define LEX_STLC		's'			// ������� ��� ������ ����������� �������


// ����� >= � <= ����������� ������������ � lexema_parent ��� _ � : ��������������

#define LESS			'<'			
#define MORE			'>'
#define PLUS			'+'
#define MINUS			'-'
#define STAR			'*'
#define DIRSLASH		'/'


namespace LT									// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema;							// �������
		int sn;									// ����� ������ � �������� ������
		int idxLT;								// ������ � ������� ������
		int idxTI;								// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		char lexema_parent;
		Entry();
		Entry(const char lex, int str_n, int idxTI);
		Entry( char lex, int str_n, int idxLT, int idxTI);
		Entry(const char lex_parent, const char lex, int str_n, int idxTI);
	};

	struct LexTable								// �������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size;								// ������� ������ ������� ������ < maxsize
		Entry* table;							// ������ ����� ������� ������


		Entry GetEntry(								// �������� ������ ������� ������
			int n									// ����� ���������� ������
		);

		void PrintLexTable(const wchar_t* in);
		LexTable();
	};

	void Add(									// �������� ������ � ������� ������
		LexTable& lextable,						// ��������� ������� ������
		Entry entry								// ������ ������� ������
	);

	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
};