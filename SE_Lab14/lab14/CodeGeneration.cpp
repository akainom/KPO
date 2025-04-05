#include "stdafx.h"
#include <sstream>
#include <string>
#include <stack>
#define CODESTART ".586P\n" \
".MODEL FLAT, STDCALL\n"    \
"includelib kernel32.lib\n"  \
"includelib msvcrtd.lib\n"  \
"includelib libucrt.lib\n"  \
"includelib \"C:/KPO/alt/SE_Lab14/Debug/StandartLibrary.lib\"\n" \
"ExitProcess PROTO:DWORD \n"\
"strcp PROTO :DWORD, :DWORD\n"\
"stcmp PROTO :DWORD, :DWORD\n"\
"writestr PROTO :DWORD\n"\
"writeint PROTO :SDWORD\n"\
".stack 4096\n"


#define CODE_END "push 0\ncall ExitProcess\nmain ENDP\nend main"
#define DATASEGMENT ".data\n\t\tbuffer db 256 dup(0)\n\t\tnumber dd 64 dup(0)"
#define CODESEGMENT ".code"


namespace Generation
{
    string GenerateFuncCall(LT::LexTable& lexTable, IT::IdTable& idTable, int iter)
    {
        string buff;
        IT::Entry funcname = idTable.table[lexTable.table[iter].idxTI];

        stack<IT::Entry> parameters;

        bool isStdFunc = false;
        if (funcname.idtype != IT::IDTYPE::F)
        {
            isStdFunc = true;
        }
        for (int j = iter + 1;; j++)
        {
            if ((lexTable.table[j].lexema == '@') or (lexTable.table[j].lexema_parent == ')'))
            {
                break;
            }
            if (lexTable.table[j].lexema == LEX_ID || lexTable.table[j].lexema == LEX_LITERAL)
            {
                int lex = lexTable.table[j].idxTI;
                char* id = idTable.table[lex].id;
                parameters.push(idTable.table[lexTable.table[j].idxTI]);
                
            }
        }
        buff += "\n";

        while (parameters.empty() == false)
        {
            if ((parameters.top().iddatatype == IT::IDDATATYPE::STR) and parameters.top().idtype == IT::IDTYPE::L)
            {
                buff = buff + "push offset " + parameters.top().id + "\n";
            }
            else
            {
                buff = buff + "push " + parameters.top().id + "\n";
            }
            parameters.pop();
        }
        if (isStdFunc == true)
        {

            buff += "call " + string(funcname.id) + "\nadd esp, 12\npush eax\ncall writeint\n";
        }
        else
        {
            buff += "call " + string(funcname.id) + "\n";
        }
        return buff;
    }
    void generation(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG& log, Parm::PARM& parms)
    {
        ofstream output("C:\\KPO\\alt\\SE_Lab14\\Debug\\output.asm");
        string functionname, buff;
        int params;

        vector <string> final;
        final.push_back(CODESTART);

        vector<string> forliterals;
        vector <string> forvariable;

        forliterals.push_back(".const\n\t\t");
        forvariable.push_back(DATASEGMENT);

        for (int i = 0; i < idTable.size; i++)
        {
            IT::Entry entry = idTable.table[i];

            string buffer = "\t\t" + string(entry.id);

            switch (idTable.table[i].idtype)
            {
            case IT::IDTYPE::L:
            {
                if (entry.iddatatype == IT::IDDATATYPE::STR)
                {
                    buffer += " byte " + string(entry.value.vstr.str) + ", 0";
                }
                if (entry.iddatatype == IT::IDDATATYPE::UINT)
                {

                    buffer += " sdword " + to_string(entry.value.vint);
                }
                forliterals.push_back(buffer);
                break;
            }
            case IT::IDTYPE::V:
            {
                if (entry.iddatatype == IT::IDDATATYPE::STR)
                {
                    buffer += " dword ?";
                }
                if (entry.iddatatype == IT::IDDATATYPE::UINT)
                {
                    buffer += " sdword 0";
                }
                forvariable.push_back(buffer);
                break;
            }
            }
        }
        final.insert(final.end(), forliterals.begin(), forliterals.end()); final.insert(final.end(), forvariable.begin(), forvariable.end());
        final.push_back(CODESEGMENT);
        string buff1;
        string funcname;
        for (int i = 0; i < lexTable.size; i++)
        {
            switch (lexTable.table[i].lexema)
            {
            case '=':
            {
                IT::Entry left = idTable.table[lexTable.table[i - 1].idxTI];
                switch (left.iddatatype)
                {
                case IT::IDDATATYPE::UINT:
                {
                    int j = i + 1;
                    while (lexTable.table[j].lexema != LEX_SEMICOLON)
                    {
                        char rightLexema = lexTable.table[j].lexema;
                        if (rightLexema == 'v')
                        {
                            rightLexema = lexTable.table[j].lexema_parent;
                        }
                        switch (rightLexema)
                        {
                        case PLUS:
                        {
                            buff1 += "pop ebx\npop eax\nadd eax, ebx\npush eax\n";
                            break;
                        }
                        case MINUS:
                        {
                            buff1 += "pop ebx\npop eax\nsub eax, ebx\npush eax\n";
                            break;
                        }
                        case STAR:
                        {
                            buff1 += "pop ebx\npop eax\nimul eax, ebx\npush eax";
                            break;
                        }
                        case DIRSLASH:
                        {
                            buff1 += "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n";
                            break;
                        }

                        case LEX_ID: {

                            if (idTable.table[lexTable.table[j].idxTI].idtype == IT::IDTYPE::F || idTable.table[lexTable.table[j].idxTI].idtype == IT::IDTYPE::SF)
                            {
                                buff1 += GenerateFuncCall(lexTable, idTable, j);
                                buff1 = buff1 + "push eax\n";
                                while (lexTable.table[j].lexema != LEX_SEMICOLON) j++;
                                // вызов функции сделать, мне лень)
                                j--;
                                break;
                            }
                            else {
                                buff1 = buff1 + "push " + idTable.table[lexTable.table[j].idxTI].id + "\n"; break;
                            }

                        }
                        case LEX_LITERAL:
                        {

                            buff1 = buff1 + "push " + idTable.table[lexTable.table[j].idxTI].id + "\n";
                            break;
                        }
                        }
                        j++;
                    }
                    buff1 = buff1 + "\npop ebx\nmov " + left.id + ", ebx\n";
                    break;
                }
                case IT::IDDATATYPE::STR:
                {
                    IT::Entry right = idTable.table[lexTable.table[i + 1].idxTI];
                    if (lexTable.table[i + 1].lexema == LEX_LITERAL)
                    {
                        buff1 = buff1 + "mov " + left.id + ", offset " + right.id + "\n";
                    }
                    if (lexTable.table[i + 1].lexema == LEX_ID and (right.idtype == IT::IDTYPE::F))
                    {
                        //вызов функции
                        buff1 += GenerateFuncCall(lexTable, idTable, i + 1);
                        buff1 = buff1 + "mov " + left.id + ", eax\n";
                    }
                    else
                    {
                        buff1 = buff1 + "mov ecx, offset " + right.id + "\nmov " + left.id + ", ecx\n";//прямое присваивание по регистру
                    }
                }
                break;
                }
            } while (lexTable.table[++i].lexema != LEX_SEMICOLON);
            break;
            case LEX_MAIN:
            {
                buff1 += "main PROC";
                funcname = "main";
                break;
            }
            case LEX_FUNCTION:
            {
                IT::Entry func = idTable.table[lexTable.table[i + 1].idxTI];
                funcname = string(func.id);
                buff1 = string(func.id) + string(" PROC,\n\t");

                int j = i + 3;
                while (lexTable.table[j].lexema != LEX_RIGHTHESIS)
                {
                    if (lexTable.table[j].lexema == LEX_ID)
                    {
                        buff1 = buff1 + string(idTable.table[lexTable.table[j].idxTI].id);
                        if (idTable.table[lexTable.table[j].idxTI].iddatatype == IT::IDDATATYPE::UINT)
                        {
                            buff1 += " : sdword, ";
                        }
                        else
                        {
                            buff1 += " : dword, ";
                        }
                    }
                    j++;
                }
                int find = buff1.rfind(',');
                if (find > 0)
                {
                    buff1[find] = ' ';
                }
                buff1 += "\npush ebx\npush edx";
                break;
            }

            case LEX_RETURN:
            {
                buff1 += "\npop edx\npop ebx\n";
                if (lexTable.table[i + 1].lexema != LEX_SEMICOLON)
                {
                    buff1 += "mov eax, " + string(idTable.table[lexTable.table[i + 1].idxTI].id) + "\n";
                }
                if (funcname != "main")
                {
                    buff1 += "ret\n";
                    buff1 += funcname + " ENDP\n";
                }
                break;
            }
            case LEX_CONDITION: {
                int j = i + 1;
                string conditionBuff;
                bool checked_Id = false;
                if (lexTable.table[j].lexema == LEX_LEFTHESIS) {
                    j++;
                    while (lexTable.table[j].lexema != LEX_RIGHTHESIS) {
                        if (lexTable.table[j].lexema == LEX_ID && !checked_Id) {
                            checked_Id = true;
                            conditionBuff += "mov eax, " + string(idTable.table[lexTable.table[j].idxTI].id) + "\n";
                            conditionBuff += "mov ebx, " + string(idTable.table[lexTable.table[j + 2].idxTI].id) + "\n";
                        }
                        else switch (lexTable.table[j].lexema)
                        {
                        case LEX_EQUALS:
                        {
                            conditionBuff += "cmp eax, ebx\npush eax\njne condition_end\n";
                            break;
                        }
                        default:
                        {
                            if (lexTable.table[j].lexema_parent == '!')
                            {
                                conditionBuff += "cmp eax, ebx\nje condition_end\n";
                                break;
                            }
                            if (lexTable.table[j].lexema_parent == '>')
                            {
                                conditionBuff += "cmp eax, ebx\njl condition_end\n";
                                break;
                            }
                            if (lexTable.table[j].lexema_parent == '<')
                            {
                                conditionBuff += "cmp eax, ebx\njg condition_end\n";
                                break;
                            }
                            if (lexTable.table[j].lexema_parent == ':')
                            {
                                conditionBuff += "cmp eax, ebx\njge condition_end\n";
                                break;
                            }
                            if (lexTable.table[j].lexema_parent == '_')
                            {
                                conditionBuff += "cmp eax, ebx\njle condition_end\n";
                                break;
                            }
                            else break;
                        }
                        }
                        i++; j++;
                    }
                }


                string trueLabel = "\ncondition:";


                while (lexTable.table[j].lexema != LEX_RIGHTBRACE)
                {
                    switch (lexTable.table[j].lexema) {
                    case LEX_ID:
                        if (lexTable.table[j + 1].lexema == LEX_EQUAL_SIGN) {
                            IT::Entry left = idTable.table[lexTable.table[j].idxTI];
                            j++;
                            if (lexTable.table[j + 1].lexema == LEX_LITERAL || lexTable.table[j + 1].lexema == LEX_ID) {
                                std::string rightId = idTable.table[lexTable.table[j].idxTI].id;
                                trueLabel += "\npush " + rightId + "\n";
                                trueLabel += "pop ebx\n";
                                trueLabel += "mov " + std::string(left.id) + ", ebx\n";
                            }
                        }
                        break;
                    }
                    i++; j++; ;
                }
                conditionBuff += trueLabel;
                conditionBuff += "condition_end:\n";
                buff1 += conditionBuff;
                break;
            }
            case LEX_ID:
            {
                if (lexTable.table[i - 1].lexema != LEX_FUNCTION and lexTable.table[i + 1].lexema == LEX_LEFTHESIS)
                {
                    buff1 += GenerateFuncCall(lexTable, idTable, i);
                }
                break;
            }
            case LEX_PRINT:
            {
                IT::Entry output = idTable.table[lexTable.table[i + 1].idxTI];
                switch (output.iddatatype)
                {
                case IT::IDDATATYPE::UINT:
                {
                    buff1 = buff1 + "push ecx\npush " + output.id + "\ncall writeint\npop ecx\n";
                    break;
                }
                case IT::IDDATATYPE::STR:
                {
                    if (output.idtype == IT::IDTYPE::L)
                    {
                        buff1 = buff1 + "\npush offset " + output.id + "\ncall writestr\n";
                    }
                    else
                    {
                        buff1 = buff1 + "\npush " + output.id + "\ncall writestr\n";
                    }
                    break;
                }
                break;
                }
            }


            }
            if (buff1.empty() == false)
            {
                final.push_back(buff1);
                buff1.clear();
            }
        }
        final.push_back(CODE_END);
        for (auto str : final)
        {
            output << str << endl;
        }
        output.close();

    }
}