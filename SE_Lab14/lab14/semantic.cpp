#include "stdafx.h"

void SemAnalysis(LT::LexTable& lextable, IT::IdTable& idtable) {
    bool mainFound = false;
    bool lpo = true;
    for (int i = 0; i < lextable.size; i++) {

        if (lextable.GetEntry(i).lexema == LEX_MAIN) {
            mainFound = true;
        }


        if (lextable.GetEntry(i).lexema == LEX_EQUAL_SIGN &&
            lextable.GetEntry(i - 1).lexema == LEX_ID &&
            idtable.GetEntry(lextable.GetEntry(i - 1).idxTI).idtype == IT::IDTYPE::P) {
            throw ERROR_THROW(132);
        }


        if (lextable.GetEntry(i).lexema == LEX_EQUAL_SIGN &&
            lextable.GetEntry(i - 1).lexema == LEX_ID) {
            int idPosition = i - 1;
            int j = i + 1;

            while (lextable.GetEntry(j).lexema != LEX_SEMICOLON && j < lextable.size) {
                if (lextable.GetEntry(j).lexema == LEX_ID || lextable.GetEntry(j).lexema == LEX_LITERAL) {

                    if (lextable.GetEntry(idPosition).idxTI != 0 &&
                        idtable.GetEntry(lextable.GetEntry(idPosition).idxTI).iddatatype != idtable.GetEntry(lextable.GetEntry(j).idxTI).iddatatype
                        && !(idtable.GetEntry(lextable.GetEntry(idPosition).idxTI + 1).iddatatype == IT::IDDATATYPE::UINT && idtable.GetEntry(lextable.GetEntry(idPosition).idxTI + 1).idtype == IT::IDTYPE::SF)
                        ) {
                        throw ERROR_THROW(134, lextable.GetEntry(j).str_number, -1);
                    }
                }
                j++;
            }
        }

        if ((lextable.GetEntry(i).lexema == 'v' || lextable.GetEntry(i).lexema == 'c') && (lextable.GetEntry(i + 1).lexema != 'i' && lextable.GetEntry(i + 1).lexema != 'l'))
        {
            throw ERROR_THROW(136);
        }

        if ((lextable.GetEntry(i).lexema == '=') && (lextable.GetEntry(i + 1).lexema == 'v' || (lextable.GetEntry(i + 1).lexema == 'c')))
        {
            throw ERROR_THROW(136);
        }

        if (lextable.GetEntry(i).lexema == LEX_DIRSLASH) {
            int prevIdx = i - 1;
            int nextIdx = i + 1;


            if (prevIdx >= 0 && lextable.GetEntry(prevIdx).lexema == LEX_LITERAL &&
                idtable.GetEntry(lextable.GetEntry(prevIdx).idxTI).value.vint == 0) {
                throw ERROR_THROW(133, lextable.GetEntry(i).str_number, -1);
            }

            if (nextIdx < lextable.size) {
                if (lextable.GetEntry(nextIdx).lexema == LEX_LITERAL &&
                    idtable.GetEntry(lextable.GetEntry(nextIdx).idxTI).value.vint == 0) {
                    throw ERROR_THROW(133, lextable.GetEntry(i).str_number, -1);
                }
            }
        }



        if (lextable.GetEntry(i + 1).lexema == LEX_LEFTHESIS && lextable.GetEntry(i - 1).lexema != LEX_FUNCTION) {
            auto entry = idtable.GetEntry(lextable.GetEntry(i).idxTI);
            if (entry.idtype == IT::IDTYPE::F || lextable.GetEntry(i - 1).lexema == LEX_STLC && entry.idtype == IT::IDTYPE::SF) {
                short paramCounter = 0;
                int j = i + 1;
                while (lextable.GetEntry(j).lexema != LEX_RIGHTHESIS) {
                    if (lextable.GetEntry(j).lexema == LEX_ID || lextable.GetEntry(j).lexema == LEX_LITERAL) {
                        paramCounter++;
                        if (entry.parmQuantity == 0 && lextable.GetEntry(i - 1).lexema != LEX_STLC) {
                            break;
                        }
                    }
                    j++;
                }
                if (lextable.GetEntry(i - 1).lexema == LEX_STLC && entry.idtype == IT::IDTYPE::SF && (paramCounter != 2)) {
                    throw ERROR_THROW_IN(135, lextable.table[i].sn, -1);

                }
                if (entry.idtype == IT::IDTYPE::F && lextable.GetEntry(i - 1).lexema != LEX_STLC) {
                    if (paramCounter != entry.parmQuantity) {
                        lpo = false;
                        throw ERROR_THROW_IN(135, -1, -1);
                    }
                }
            }


        }

    }

    if (!mainFound) {
        throw ERROR_THROW_IN(131, -1, -1);
    }
}