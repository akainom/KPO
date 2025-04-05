#include "stdafx.h"

namespace LA
{
	int ConvertToDecimal(const char* num, const int base)
	{
		// Пропускаем префикс b8 или b2, если он есть
		if ((strncmp(num, "b8", 2) == 0) || strncmp(num, "b2", 2) == 0)
		{
			num += 2;
		}

		int length = strlen(num);
		unsigned int result = 0;

		for (int i = 0; i < length; i++)
		{
			int digit;
			if (base == 8)
			{
				digit = num[length - 1 - i] - '0'; // Преобразуем символ в число для цифр 0-7
			}
			if (base == 2)
			{
				digit = num[length - 1 - i] - '0'; // Преобразуем символ в число для цифр 0-1
			}
			if (base == 8)
			{
				result += digit * static_cast<int>(std::pow(8, i));
			}
			if (base == 2)
			{
				result += digit * static_cast<int>(std::pow(2, i));
			}
		}
		if (base == 10)
		{
			result = atoi(num);
		}
		if (result > 4294967295)
		{
			return 4294967295;
		}

		return result;
	}

	void FindLex(const In::input& source, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		char* temp = new char[token_size] {};
		int str_number = 1;
		int str_position = 1;
		In::input in;

		for (int i = 0, j = 0; i < source.size; i++)
		{
			if (in.code[(source.text[i])] != in.D && in.code[(source.text[i])] != in.O && (source.text[i]) != '\n' and in.code[(source.text[i])] != in.P)
			{
				temp[j++] = source.text[i];
				str_position++;
				continue;
			}
			else
			{
				if (j != 0)
				{
					i--;
					temp[j] = '\0';
					if ((temp[0] == '!' && (source.text[i + 1] == '=')) || temp[0] == '<' && (source.text[i + 1] == '=') || temp[0] == '>' && (source.text[i + 1] == '='))
					{
						temp[1] = '=';
						temp[2] = '\0';
						if (Analyse(temp, str_number, lexTable, idTable))
						{
							temp[0] = '\0'; j = 0;
							i++;
							continue;
						}
						else
							throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);
					}
					if (Analyse(temp, str_number, lexTable, idTable))
					{
						temp[0] = '\0'; j = 0;
						continue;
					}
					else
						throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);
				}
				else
				{
					if (source.text[i] == '\'')
					{
						temp[j++] = source.text[i++];

						for (int c = 0; source.text[i] != '\''; c++)
						{
							if (c <= TI_STR_MAXSIZE)
							{
								temp[j++] = source.text[i++];
							}
							else
								throw ERROR_THROW_IN(127, str_number, str_position - strlen(temp) + 1);
						}

						if (source.text[i] == '\'')
						{
							temp[j++] = source.text[i];
							temp[j] = '\0';
							if (Analyse(temp, str_number, lexTable, idTable))
							{
								temp[0] = '\0'; j = 0;
								continue;
							}
							else
								throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);
						}
						else
							throw ERROR_THROW_IN(124, str_number, str_position - strlen(temp) + 1);
					}

					if (source.text[i] != '\n')
					{
						if (source.text[i] == ' ' || source.text[i] == '\t')
						{
							str_position++;
							continue;
						}

						temp[0] = source.text[i];
						temp[1] = '\0';
						if (Analyse(temp, str_number, lexTable, idTable))
							str_position++;
						else
							throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);

						temp[0] = '/0'; j = 0;
					}
				}
			}
			if (source.text[i] == '\n')
			{
				str_number++;
				str_position = 0;
			}
		}
		delete[] temp;
	}

	bool Analyse(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		static TypeOfVar flag_type_variable;
		int lp = idTable.IsId(token);
		switch (token[0])
		{
		case LEX_COMMA:
		{
			Add(lexTable, { ',', LEX_COMMA ,str_number, LT_TI_NULLXDX});
			return true;
		}

		case LEX_LEFTBRACE:
		{
			Add(lexTable, {  '{', LEX_LEFTBRACE,str_number,LT_TI_NULLXDX});
			return true;
		}

		case LEX_RIGHTBRACE:
		{
			Add(lexTable, { '}', LEX_RIGHTBRACE,str_number,LT_TI_NULLXDX});
			return true;
		}

		case LEX_LEFTHESIS:
		{
			Add(lexTable, { '(', LEX_LEFTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_RIGHTHESIS:
		{
			Add(lexTable, { ')', LEX_RIGHTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_SEMICOLON:
		{
			Add(lexTable, { ';', LEX_SEMICOLON,str_number,LT_TI_NULLXDX});
			return true;
		}

		case '+':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, lexTable.size,'+' });
			Add(lexTable, { '+', LEX_PLUS,str_number,idTable.size - 1 });
			return true;
		}

		case '-':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '-' });
			Add(lexTable, { '-', LEX_MINUS, str_number, idTable.size - 1 });
			return true;
		}

		case '*':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '*' });
			Add(lexTable, { '*', LEX_STAR, str_number, idTable.size - 1 });
			return true;
		}

		case '/':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '/' });
			Add(lexTable, { '/', LEX_DIRSLASH, str_number, idTable.size - 1 });
			return true;
		}

		case LEX_EQUAL_SIGN:
		{
			Add(lexTable, { '=', LEX_EQUAL_SIGN, str_number, LT_TI_NULLXDX});
			return true;
		}
		case '!':
		{
			if (token[1] == '=')
			{
				Add(lexTable, { '!', LEX_COMPARER , str_number, LT_TI_NULLXDX });
				return true;
			}
			else
			{
				throw ERROR_THROW_IN(123, str_number, lexTable.table[lexTable.size].sn);
			}
		}
		case '>':
		{
			if (token[1] == LEX_EQUAL_SIGN)
			{
				Add(lexTable, { '_', LEX_COMPARER, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
			{
				idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '>' });
				Add(lexTable, { '>', LEX_COMPARER, str_number, LT_TI_NULLXDX });
				return true;
			}
		}
		case '<':
		{
			if (token[1] == LEX_EQUAL_SIGN)
			{
				Add(lexTable, { ':', LEX_COMPARER, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
			{
				idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '<' });
				Add(lexTable, { '<', LEX_COMPARER, str_number, LT_TI_NULLXDX });
				return true;
			}
		}


		case 'b':
		{
			FST::FST* BOOL = new FST::FST(BOOL(token));
			if (FST::execute(*BOOL))
			{
				Add(lexTable, { 'b', LEX_BOOL, str_number, LT_TI_NULLXDX});

				delete BOOL;
				BOOL = NULL;
				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::BOOL;
				return true;
			}
			int decimalValue;
			FST::FST* OCT = new FST::FST(OCT_LITERAL(token));
			if (FST::execute(*OCT))
			{
				decimalValue = ConvertToDecimal(token, 8);
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
				{
					Add(lexTable, { 'l', LEX_LITERAL, str_number, i});
				}
				else
				{
					idTable.Add({ "\0",idTable.GetLexemaName() , IT::IDDATATYPE::UINT, IT::IDTYPE::L, lexTable.size });

					idTable.table[idTable.size - 1].value.vint = decimalValue;
					Add(lexTable, { 'l', LEX_LITERAL, str_number, idTable.size - 1 });
				}
				delete OCT;
				OCT = NULL;
				return true;
			}
			FST::FST* BINARY = new FST::FST(BINARY_LITERAL(token));
			if (FST::execute(*BINARY))
			{
				decimalValue = ConvertToDecimal(token, 2);
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
				{
					Add(lexTable, { 'l', LEX_LITERAL, str_number, i });
				}
				else
				{
					idTable.Add({ "\0",idTable.GetLexemaName() , IT::IDDATATYPE::UINT, IT::IDTYPE::L, lexTable.size });
					idTable.table[idTable.size - 1].value.vint = decimalValue;
					Add(lexTable, { 'l', LEX_LITERAL, str_number, idTable.size - 1 });
				}
				delete BINARY;
				BINARY = NULL;
				return true;
			}
			else
			{
				delete BOOL;
				BOOL = NULL;
				delete OCT; 
				OCT = NULL; 
				delete BINARY;
				BINARY = NULL;
				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		case 's':
		{
			FST::FST* string = new FST::FST(STRING(token));
			if (FST::execute(*string))
			{
				Add(lexTable, { 't', LEX_STRING, str_number,LT_TI_NULLXDX});

				delete string;
				string = NULL;
				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::STR;
				return true;
			}
			FST::FST* _STL_CALL = new FST::FST(STL_CALL(token));
			if (FST::execute(*_STL_CALL))
			{
				Add(lexTable, { 's', LEX_STLC, str_number, LT_TI_NULLXDX});

				delete _STL_CALL;
				_STL_CALL = NULL;

				return true;
			}
			else
			{
				delete string;
				string = NULL;
				delete _STL_CALL;
				_STL_CALL = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'u':
		{
			FST::FST* UINT = new FST::FST(UINT(token));
			if (FST::execute(*UINT))
			{
				Add(lexTable, {'t', LEX_UINT, str_number, LT_TI_NULLXDX});
				delete UINT;
				UINT = NULL;
				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::UINT;
				return true;
			}
			else
			{
				delete UINT;
				UINT = NULL;
				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 't':
		{
			FST::FST* _TRUE = new FST::FST(TRUE(token));
			if (FST::execute(*_TRUE))
			{
				idTable.Add({ "\0", idTable.GetLexemaName(), IT::IDDATATYPE::BOOL, IT::IDTYPE::L, lexTable.size });
				idTable.table[idTable.size - 1].value.vlogic = true;
				Add(lexTable, { 'l', LEX_TRUE, str_number, idTable.size - 1});
				delete _TRUE;
				_TRUE = NULL;
				return true;
			}
			else
			{
				delete _TRUE;
				_TRUE = NULL;
				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'f':
		{
			FST::FST* function = new FST::FST(FUNCTION(token));
			if (FST::execute(*function))
			{
				Add(lexTable, { 'f', LEX_FUNCTION, str_number, lp});

				delete function;
				function = NULL;
				return true;
			}
			FST::FST* _FALSE = new FST::FST(FALSE(token));
			if (FST::execute(*_FALSE))
			{
				idTable.Add({ "\0", idTable.GetLexemaName(), IT::IDDATATYPE::BOOL, IT::IDTYPE::L, lexTable.size });
				idTable.table[idTable.size - 1].value.vlogic = false;
				Add(lexTable, { 'l', LEX_FALSE, str_number, idTable.size - 1});
				delete _FALSE;
				_FALSE = NULL;
				return true;
			}
			else
			{
				delete _FALSE;
				delete function;
				_FALSE = NULL;
				function = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}

		}
		case 'i':
		{
			if (token[1] == 'f')
			{
				FST::FST* auto_value = new FST::FST(IF(token));
				if (FST::execute(*auto_value))
				{
					LT::Add(lexTable, {'I', LEX_CONDITION, str_number,LT_TI_NULLXDX});
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else
				{
					delete auto_value;
					auto_value = NULL;
					return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
				}
			}
		}

		case 'd':
		{
			FST::FST* declare = new FST::FST(DECLARE(token));
			if (FST::execute(*declare))
			{
				Add(lexTable, {'d', LEX_DECLARE, str_number, LT_TI_NULLXDX});
				delete declare;
				declare = NULL;
				return true;
			}
			else
			{
				delete declare;
				declare = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		case 'r':
		{
			FST::FST* _return = new FST::FST(RETURN(token));
			if (FST::execute(*_return))
			{
				Add(lexTable, { 'r', LEX_RETURN, str_number,LT_TI_NULLXDX});

				delete _return;
				_return = NULL;
				return true;
			}
			else
			{
				delete _return;
				_return = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'p':
		{
			FST::FST* _print = new FST::FST(PRINT(token));
			if (FST::execute(*_print))
			{
				Add(lexTable, { 'p', LEX_PRINT, str_number,LT_TI_NULLXDX});

				delete _print;
				_print = NULL;
				return true;
			}
			else
			{
				delete _print;
				_print = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'e':
		{
			FST::FST* equal = new FST::FST(EQUALS(token));
			if (FST::execute(*equal))
			{
				Add(lexTable, {'q', LEX_EQUALS, str_number, LT_TI_NULLXDX});
				return true;
			}
		}

		case '\'':
		{
			FST::FST* string_literal = new FST::FST(STRING_LITERAL(token));
			if (FST::execute(*string_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { 'l', LEX_LITERAL, str_number, i});
				else
				{
					if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::IDDATATYPE::STR)
					{
						idTable.Add({ "\0", idTable.GetLexemaName(), IT::IDDATATYPE::STR, IT::IDTYPE::L, lexTable.size });
					}
					int i = 0, j = 0;
					for (; token[i] != '\0'; i++)
					{
						idTable.table[idTable.size - 1].value.vstr.str[j] = token[i];
						idTable.table[idTable.size - 1].value.vstr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vstr.str[j] = '\0';

					Add(lexTable, { 'l', LEX_LITERAL, str_number,idTable.size - 1 });
				}

				delete string_literal;
				string_literal = NULL;
				return true;
			}
		}
		default:
		{
			FST::FST* number_literal = new FST::FST(UINT_LITERAL(token));
			if (FST::execute(*number_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
				{
					Add(lexTable, { 'l', LEX_LITERAL, str_number, i });
				}
				else
				{
					int decimalValue = ConvertToDecimal(token, 10);
					idTable.Add({ "\0",idTable.GetLexemaName() , IT::IDDATATYPE::UINT, IT::IDTYPE::L, lexTable.size });
					idTable.table[idTable.size - 1].value.vint = decimalValue;
					Add(lexTable, { 'l', LEX_LITERAL,str_number, idTable.size - 1 });
				}
				delete number_literal;
				number_literal = NULL;
				return true;
			}
			else
			{
				delete number_literal;
				number_literal = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		}
	}


	bool AnalyseIdentificator(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVar& flag_type_variable)
	{
		FST::FST* id = new FST::FST(IDENTIFICATOR(token));

		if (FST::execute(*id))
		{
			bool Checked_id = false;
			if (strcmp(token, "main") == 0)
			{
				if (strcmp(token, "main") == 0)
				{
					for (int iter = 0; iter < idTable.size; iter++)
					{
						if (strcmp(idTable.GetEntry(iter).id, "main") == 0)
						{
							throw ERROR_THROW_IN(129, str_number, -1);
						}
					}
				}
				if (idTable.IsId(token) == -1) {
					idTable.Add({ "\0", token, IT::IDDATATYPE::UINT, IT::IDTYPE::F ,lexTable.size });
					flag_type_variable.LT_posititon = -1;
					flag_type_variable.type = TypeOfVar::DEF;
					Add(lexTable, { 'm', LEX_MAIN, str_number, idTable.size - 1});
					Checked_id = true;
				}

			}
			//Функция
			if (
				((lexTable.GetEntry(lexTable.size - 1).lexema == LEX_FUNCTION &&
					lexTable.GetEntry(lexTable.size - 2).lexema == 't') &&
					flag_type_variable.LT_posititon == lexTable.size - 2))
			{
				if (idTable.IsId(token) == -1)
				{
					if (flag_type_variable.type == TypeOfVar::UINT)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::UINT, IT::IDTYPE::F ,lexTable.size });
					}
					if (flag_type_variable.type == TypeOfVar::STR)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F ,lexTable.size });
					}
					if (flag_type_variable.type == TypeOfVar::BOOL)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::BOOL, IT::IDTYPE::F ,lexTable.size });
					}
					flag_type_variable.LT_posititon = -1;
					flag_type_variable.type = TypeOfVar::DEF;

					Add(lexTable, {'i', LEX_ID, str_number, idTable.size - 1});
					Checked_id = true;
				}
				else
					throw ERROR_THROW_IN(123, str_number, -1);
			}
			else if (lexTable.table[lexTable.size - 1].lexema == LEX_STLC)
			{
				if (!strcmp("strcp", token))
				{
					idTable.Add({ "\0",token, IT::IDDATATYPE::STR,IT::IDTYPE::SF,lexTable.size });
				}
				if (!strcmp("stcmp", token))
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::UINT, IT::IDTYPE::SF, lexTable.size });
				}
				Add(lexTable, {'i', LEX_ID, str_number, idTable.size - 1});
				return true;
			}

			//Переменная
			if (!Checked_id && (lexTable.GetEntry(lexTable.size - 1).lexema == 't' && lexTable.GetEntry(lexTable.size - 2).lexema == LEX_DECLARE && flag_type_variable.LT_posititon == lexTable.size - 1))
			{
				bool LeftBrace = false;
				for (int i = lexTable.size - 1; i >= 0; i--)
				{
					if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
						LeftBrace = true;
					if (LeftBrace &&
						lexTable.GetEntry(i).lexema == LEX_ID &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F || lexTable.GetEntry(i).lexema == LEX_MAIN &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
					{
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
						{
							if (flag_type_variable.type == TypeOfVar::UINT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::UINT, IT::IDTYPE::V, lexTable.size });
							}
							if (flag_type_variable.type == TypeOfVar::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token , IT::IDDATATYPE::STR, IT::IDTYPE::V, lexTable.size });
							}
							if (flag_type_variable.type == TypeOfVar::BOOL)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token , IT::IDDATATYPE::BOOL, IT::IDTYPE::V, lexTable.size });
							}
							flag_type_variable.LT_posititon = -1;
							flag_type_variable.type = TypeOfVar::DEF;

							Add(lexTable, {'i', LEX_ID, str_number, idTable.size - 1});
							Checked_id = true;
							break;
						}
						else
							throw ERROR_THROW_IN(125, str_number, -1);
					}


				}
			}

			//Параметр функции
			if (!Checked_id &&
				(lexTable.GetEntry(lexTable.size - 1).lexema == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
			{
				for (int i = lexTable.size - 1; i > 0; i--)
				{
					LT::Entry entry_minus_one = lexTable.GetEntry(i - 1);
					LT::Entry entry_minus_two = lexTable.GetEntry(i - 2);
					LT::Entry entry = lexTable.GetEntry(i);
					bool type_check = (idTable.GetEntry(entry.idxTI).idtype == IT::IDTYPE::F);
					if (entry.lexema == LEX_ID && type_check)
					{
						if (entry_minus_one.lexema == LEX_FUNCTION && entry_minus_two.lexema == 't')
						{
							if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
							{
								if (flag_type_variable.type == TypeOfVar::UINT)
								{
									idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,token , IT::IDDATATYPE::UINT, IT::IDTYPE::P, lexTable.size });
									idTable.table[(lexTable.GetEntry(i).idxTI)].value.params.types[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::UINT;
									idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
								}
								if (flag_type_variable.type == TypeOfVar::STR)
								{
									idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,token  , IT::IDDATATYPE::STR, IT::IDTYPE::P, lexTable.size });
									idTable.table[(lexTable.GetEntry(i).idxTI)].value.params.types[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::STR;
									idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
								}
								if (flag_type_variable.type == TypeOfVar::BOOL)
								{
									idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,token  , IT::IDDATATYPE::BOOL, IT::IDTYPE::P, lexTable.size });
									idTable.table[(lexTable.GetEntry(i).idxTI)].value.params.types[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::BOOL;
									idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
								}
								flag_type_variable.LT_posititon = -1;
								flag_type_variable.type = TypeOfVar::DEF;

								Add(lexTable, {'i', LEX_ID, str_number, idTable.size - 1});
								Checked_id = true;
								break;
							}
							else
								throw ERROR_THROW_IN(125, str_number, -1);
						}
					}
				}
			}

			//Идентификаторы с учётом области видимости
			if (!Checked_id)
			{
				bool LeftBrace = false;
				for (int i = lexTable.size - 1; i >= 0; i--)
				{
					if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
						LeftBrace = true;
					if (LeftBrace && lexTable.GetEntry(i).lexema == LEX_ID &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F || lexTable.GetEntry(i).lexema == LEX_MAIN &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
					{
						int temp = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id);
						if (temp != -1)
						{
							Add(lexTable, {'i', LEX_ID,str_number,temp});
							break;
						}
						else
						{
							temp = idTable.IsId(token);
							if (idTable.GetEntry(temp).idtype != IT::IDTYPE::F)
							{
								token[10] = '\0';
							}
							if (temp != -1 && idTable.GetEntry(temp).idtype == IT::IDTYPE::F)
							{
								Add(lexTable, { 'i', LEX_ID,str_number,temp});
								break;
							}


							else throw ERROR_THROW_IN(126, str_number, -1);
						}
					}
				}
			}

			delete id;
			id = NULL;
			return true;
		}
		else
		{
			delete id;
			id = NULL;
			return false;
		}
	}
}