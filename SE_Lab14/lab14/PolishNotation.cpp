#include "stdafx.h"

LT::LexTable PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable)
{
    int j = 0;
    LT::LexTable NewLexTable;
    bool isComplete = true;

    for (int i = 0; i < lextable.size; i++)
    {
        if (lextable.table[i].lexema == LEX_EQUAL_SIGN || lextable.table[i].lexema == LEX_RETURN || lextable.table[i].lexema == LEX_PRINT)
        {
            int parm_counter = 0;
            bool is_funcparm = false;
            std::stack<char> stackOfOperators;

            while (lextable.table[i].lexema != LEX_SEMICOLON)
            {
                if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
                {
                    if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_LEFTHESIS)
                    {
                        LT::Add(NewLexTable, { lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
                        stackOfOperators.push('@');
                        is_funcparm = true;
                        i++;
                        continue;
                    }
                    else
                    {
                        if (is_funcparm)
                            parm_counter++;
                        LT::Add(NewLexTable, { lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
                        i++;
                        continue;
                    }
                }

                if (lextable.table[i].lexema == LEX_RIGHTHESIS)
                {
                    while (stackOfOperators.top() != LEX_LEFTHESIS)
                    {
                        LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
                        stackOfOperators.pop();
                    }
                    stackOfOperators.pop();
                    if (!stackOfOperators.empty() && (stackOfOperators.top() == '*' || stackOfOperators.top() == '/'))
                    {
                        LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
                        stackOfOperators.pop();
                    }
                    else if (!stackOfOperators.empty() && stackOfOperators.top() == '@')
                    {
                        LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
                        LT::Add(NewLexTable, { static_cast<char>(parm_counter + '0'), lextable.table[i].sn, idtable.size });
                        parm_counter = 0;
                        is_funcparm = false;
                        stackOfOperators.pop();
                    }
                    i++;
                    continue;
                }

                if (lextable.table[i].lexema == LEX_COMMA)
                {
                    i++;
                    continue;
                }

                if (lextable.table[i].lexema == LEX_EQUAL_SIGN || lextable.table[i].lexema == LEX_RETURN || lextable.table[i].lexema == LEX_PRINT)
                {
                    LT::Add(NewLexTable, { lextable.table[i++].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
                    continue;
                }

                if ((lextable.table[i].lexema_parent == PLUS || lextable.table[i].lexema_parent == MINUS || lextable.table[i].lexema == LEX_COMPARER) && !stackOfOperators.empty())
                {
                    while (!stackOfOperators.empty() && (stackOfOperators.top() == STAR || stackOfOperators.top() == DIRSLASH))
                    {
                        LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
                        stackOfOperators.pop();
                    }
                    stackOfOperators.push(lextable.table[i++].lexema_parent);
                }
                else
                {
                    stackOfOperators.push(lextable.table[i++].lexema_parent);
                }   
            }

            while (!stackOfOperators.empty())
            {
                LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
                stackOfOperators.pop();
            }

            LT::Add(NewLexTable, { LEX_SEMICOLON, lextable.table[i].sn, lextable.table[i].idxTI });
        }
        else
        {
            if (lextable.table[i].lexema == 'c')
            {
                LT::Add(NewLexTable, { lextable.table[i].lexema_parent, lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
            }
            else
            {
                LT::Add(NewLexTable, {lextable.table[i].lexema_parent, lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
            }
        }
    }

    NewLexTable.PrintLexTable(L"PolishTable.txt");
    return NewLexTable;
}