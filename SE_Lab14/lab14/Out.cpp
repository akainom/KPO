#include "stdafx.h"
#include "Out.h"
#pragma warning(disable:4996)

namespace Out
{
	OUt getout(wchar_t outfile[])
	{
		OUt out;
		out.stream = new ofstream;
		out.stream->open(outfile);
		if (out.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(out.outfile, outfile);
		return out;
	}

	void WriteLine(OUt out, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*out.stream << ptr[i++];
		*out.stream << endl;
	}
	void WriteLine(OUt out, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*out.stream << temp;
		}
		*out.stream << endl;
	}

	void WriteIn(OUt out, In::input in)
	{
		*out.stream << in.text << std::endl;
	}

	void WriteError(OUt out, Error::Error error)
	{
		if (out.stream)
		{
			*out.stream << "--- ������!!! --- " << endl;
			*out.stream << "������ " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1)
			{
				*out.stream << "������: " << error.inext.line << endl << "�������: " << error.inext.col << endl << endl;
			}
		}
	}
	void Close(OUt out) {
		out.stream->close();
		delete out.stream;
	}
}