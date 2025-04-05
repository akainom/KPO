#pragma once
#include "stdafx.h"

#define SPACE ' '
#define SEPARATOR '|'
#define LINE_FEED '\n'
#define token_size 256

namespace LA
{
	struct TypeOfVar
	{
		int LT_posititon = -1;
		enum { DEF = 0, UINT = 1, STR = 2, BOOL = 3 } type = DEF;
	};

	bool AnalyseIdentificator(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVar& flag_type_variable);
	void FindLex(const In::input& source, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool Analyse(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable);

}
