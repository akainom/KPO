#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Rus");

    Log::LOG log = Log::INITLOG;
    Out::OUt out = Out::INITOUT;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        out = Out::getout(parm.out);
        Log::WriteLine(log, "����: ", "��� ������ ", "");
        Log::WriteLine(log, L"����: ", L"��� ������\n ", L"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::input in = In::getin(parm.in);
        Log:WriteIn(log, in);
        Out::WriteIn(out, in);
        LT::LexTable lexTable;
        IT::IdTable	idTable;

        LA::FindLex(in, lexTable, idTable);

        lexTable.PrintLexTable(L"TableOfLexems.txt");
        idTable.PrintIdTable(L"TableOfIdentificators.txt");

        MFST_TRACE_START                                    
        MFST::Mfst mfst(lexTable, GRB::getGreibach(), log);      
        mfst.start();                                       
        mfst.savededucation();                             
        mfst.printrules();

        /*SemAnalysis(lexTable, idTable);*/
        LT::LexTable PolishTable = PolishNotation(lexTable, idTable);
        Generation::generation(PolishTable, idTable, log, parm);
        lexTable.PrintLexTable(L"TableOfLexems.txt");
        idTable.PrintIdTable(L"TableOfIdentificators.txt");
        LT::Delete(lexTable);
        IT::Delete(idTable);
        Log::Close(log);
        Out::Close(out);

        
    }
    catch (Error::Error e)
    {
        Log::WriteError(log, e);
        Out::WriteError(out, e);
        cout << "������" << endl;
    }
    system("pause");
    return 0;
}
