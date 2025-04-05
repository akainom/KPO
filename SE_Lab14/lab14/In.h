#pragma once
#define input_MAX_LEN_TEXT 1024*1024	
#define input_CODE_ENDL '\n'


#define input_CODE_TABLE {\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T,  '\n' , input::T, input::T,	input::I, input::T, input::T/*15*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*31*/,\
	input::P,	input::T, input::T, input::T, input::T,	input::T, input::T, input::D, input::D,	input::D, input::O, input::O, input::D,	input::O, input::T, input::O/*47*/,\
	input::T,	input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T,	input::T, input::T, input::D, input::T,	input::O, input::T, input::T/*63*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T, input::T, input::T, input::T/*79*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::I,	input::T, input::T, input::T, input::T, input::T, input::T, input::T/*95*/,\
	input::T,  input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T/*111*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T, input::T, input::T, input::D, input::T, input::D, input::T, input::T/*127*/,\
																													\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*143*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*159*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*175*/,\
	input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*191*/,\
    input::T,  input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T, input::T, input::T, input::T/*207*/,\
	input::T,  input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*223*/,\
    input::T,	input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T/*239*/,\
    input::T,  input::T, input::T, input::T, input::T, input::T, input::T, input::T, input::T,	input::T, input::T, input::T, input::T,	input::T, input::T, input::T/*255*/\
					}


namespace In
{
	struct input
	{
		enum { T = 1024, F = 2048, I = 4096, D = 8192, O = 16384, P = 32768 };
		int size;
		int lines;
		int ignore;
		unsigned char* text;
		int code[256] = input_CODE_TABLE;
	};
	input getin(wchar_t inputfile[]);
}