#pragma once
#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "Parm.h"

namespace Out
{
	struct OUt
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const OUt INITOUT = { L"", NULL };
	OUt getout(wchar_t outfile[]);
	void WriteLine(OUt out, const char* c, ...);
	void WriteLine(OUt out, const wchar_t* c, ...);
	void WriteIn(OUt out, In::input in);
	void WriteError(OUt out, Error::Error error);
	void Close(OUt out);
}
