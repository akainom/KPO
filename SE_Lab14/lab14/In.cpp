#include "stdafx.h"
#include "In.h" 
#include "Error.h" 

#define STRING_END_ZERO '\0' 
using namespace std;
int errorLines, errorPos;
bool readFailed = false;
int failedFileSize = -1;
namespace In
{

    input getin(wchar_t infile[])
    {
        input in;
        in.size = 0;
        in.lines = 1;
        in.ignore = 0;
        char* line = new char[input_MAX_LEN_TEXT];
        int cols = 1;
        bool insideStr = false;
        unsigned char* text = new unsigned char[input_MAX_LEN_TEXT];

        ifstream fin(infile);
        if (fin.fail())
            throw ERROR_THROW(110);
        while (in.size < input_MAX_LEN_TEXT)
        {
            char k;
            fin.get(k);
            unsigned char uc = k;

            if (k == '\'')
            {
                insideStr = !insideStr;
            }
            if (fin.eof())
            {
                text[in.size] = STRING_END_ZERO; // Установка конца строки
                break;
            }
            switch (in.code[uc])
            {
            case in.P:
            {
                if ((in.code[text[in.size - 1]] == in.P) and insideStr == false)
                {
                    text[in.size] = uc;
                    break;
                }
                if (in.code[text[in.size - 1]] == in.P and insideStr == true)
                {
                    text[in.size] = uc;
                    in.size++;
                    cols++;
                    break;
                }
                else
                {
                    text[in.size] = uc;
                    in.size++;
                    cols++;
                    break;
                }

            }
            case in.D:
            case in.O:
            case in.T:
            {
                text[in.size] = uc;
                in.size++;
                cols++;
                break;
            }
            case in.F:
            {
                text[in.size] = uc;
                in.size++;
                readFailed = true;
                errorLines = in.lines;
                errorPos = cols;
                in.text = text;
                failedFileSize = in.size;
                return in;
                break;
            }
            case in.I:
            {
                in.ignore++;
                break;
            }

            default:
            {
                text[in.size] = in.code[uc];
                in.size++;
                cols++;
                break;
            }


            if (uc == input_CODE_ENDL)
            {
                in.lines++;
                cols = 1;
            }
            }

        }
        text[in.size] = '\0';
        in.text = text;
        return in;
    }
}