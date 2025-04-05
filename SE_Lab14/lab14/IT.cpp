#include "stdafx.h"


namespace IT
{
	IdTable::IdTable()
	{
		this->noname_lexema_count = 0;
		this->maxsize = TI_MAXSIZE;
		this->size = 0;
		this->table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		this->parrent_function[0] = '\0';
		this->id[0] = '\0';
		this->firstApi = 0;
		this->iddatatype = IT::IDDATATYPE::DEF;
		this->idtype = IT::IDTYPE::D;
		this->parmQuantity = 0;

	}

	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		this->value.vint = it;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str, 255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str, 255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(char* parrent_function, char* id, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}

	IdTable Create(int size)
	{
		IdTable id_table;
		id_table.size = size;
		id_table.maxsize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}
	void IdTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idtype != IDTYPE::F)
			throw ERROR_THROW(121);

		if (this->size < this->maxsize)
		{
			if (entry.idtype != IDTYPE::F)
				entry.id[5] = '\0';
			this->table[this->size] = entry;

			switch (entry.iddatatype)
			{
			case IDDATATYPE::BOOL:
			{
				this->table[this->size].value.vlogic = TI_BOOL_DEFAULT;
			}
			case IDDATATYPE::UINT:
			{
				this->table[this->size].value.vint = TI_INT_DEFAULT;
			}
			case IDDATATYPE::STR:
			{
				this->table[this->size].value.vstr.str[0] = TI_STR_DEFAULT;
				this->table[this->size].value.vstr.len = 0;
			}
			}
			this->size++;
		}
		else
			throw ERROR_THROW(122);

	}
	Entry IdTable::GetEntry(int n)
	{
		if (n < this->size && n >= 0)
			return this->table[n];
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int iter = 0; iter < this->size; iter++)
		{
			if (strcmp(this->table[iter].id, id) == 0)
				return iter;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5])
	{
		for (int i = 0; i < this->size; i++)
		{
			if ((strcmp(this->table[i].id, id) == 0) &&
				(strcmp(this->table[i].parrent_function, parrent_function) == 0))
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[3];
		char tempBuf[5];
		_itoa_s(this->noname_lexema_count, buffer, 10);
		this->noname_lexema_count++;
		tempBuf[0] = 'L';
		tempBuf[1] = '_';
		tempBuf[2] = buffer[0];
		tempBuf[3] = buffer[1];
		tempBuf[4] = buffer[2];
		return tempBuf;
	}

	void IdTable::PrintIdTable(const wchar_t* in)
	{
		std::ofstream* idStream = new std::ofstream;
		idStream->open(in);

		if (idStream->is_open())
		{
			bool flagForFirst = false;
			char buffer[3];
			char tempBuf[5];
			int lexema_count = 0;
			tempBuf[0] = 'L';
			tempBuf[1] = '_';

			*(idStream) << "\t\t\t------------------ Òàáëèöà èäåíòèôèêàòîðîâ ------------------" << std::endl;

			*(idStream) << "ÒÈÏ:" << std::setw(25) << "Èäåíòèôèêàòîð:" << std::setw(17) << "Òèï äàííûõ:" << std::setw(15) << "Çíà÷åíèå:" << std::setw(35) << "Êîë-âî ïåðåäàííûõ ïàðàìåòðîâ:" << std::setw(20) << "Ïåðâîå âõîæäåíèå:" << std::endl;

			list<int> literInt;
			list<string> literStr;
			list<bool> literbool;
			for (int i = 0; i < this->size; i++)
			{
				bool flagAgain = false;
				switch (this->table[i].idtype)
				{
				case IT::IDTYPE::P:
					std::cout.width(25);
					switch (this->table[i].iddatatype)
					{
					case 1:
						*(idStream) << "ÏÀÐÀÌÅÒÐ" << std::setw(14) << this->table[i].id << std::setw(18) << "UINT " << "\t\t" << 0 << std::setw(15) << "\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 2:
						*(idStream) << "ÏÀÐÀÌÅÒÐ" << std::setw(14) << this->table[i].id << std::setw(18) << "STR " << "\t    " << "   \"\"" << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 3:
						*(idStream) << "ÏÀÐÀÌÅÒÐ" << std::setw(14) << this->table[i].id << std::setw(18) << "BOOL " << "\t    " << "   \"\"" << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;

					}
					break;

				case IT::IDTYPE::V:
					std::cout.width(25);
					switch (this->table[i].iddatatype)
					{
					case 1:
						*(idStream) << "ÏÅÐÅÌÅÍÍÀß" << std::setw(12) << this->table[i].id << std::setw(18) << "UINT " << "\t\t" << 0 << std::setw(15) << "\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 2:
						*(idStream) << "ÏÅÐÅÌÅÍÍÀß" << std::setw(12) << this->table[i].id << std::setw(18) << "STR " << "\t    " << "   \"\"" << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 3:
						*(idStream) << "ÏÅÐÅÌÅÍÍÀß" << std::setw(12) << this->table[i].id << std::setw(18) << "BOOL " << "\t    " << "   \"\"" << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					break;
				case IT::IDTYPE::L:
					_itoa_s(lexema_count, buffer, 10);
					tempBuf[2] = buffer[0];
					tempBuf[3] = buffer[1];
					tempBuf[4] = buffer[2];

					switch (this->table[i].iddatatype)
					{
					case 1:
						for (int n : literInt)
						{
							if (n == this->table[i].value.vint) flagAgain = true;
						}
						if (!flagAgain)
						{
							*(idStream) << "ËÅÊÑÅÌÀ" << std::setw(16) << tempBuf << "\t\t   " << "UINT " << "\t\t" << this->table[i].value.vint << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
							literInt.insert(literInt.begin(), this->table[i].value.vint);
						}
						break;
					case 2:
						for (string str : literStr)
						{
							if (str == this->table[i].value.vstr.str) flagAgain = true;
						}
						if (!flagAgain)
						{
							*(idStream) << "ËÅÊÑÅÌÀ" << std::setw(16) << tempBuf << "\t\t   " << "STR " << "\t\t" << this->table[i].value.vstr.str << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
							literStr.insert(literStr.begin(), this->table[i].value.vstr.str);
						}
						break;
					case 3:
						for (bool x : literbool)
						{
							if (x == this->table[i].value.vlogic) flagAgain = true;
						}
						if (!flagAgain)
						{
							*(idStream) << "ËÅÊÑÅÌÀ" << std::setw(16) << tempBuf << "\t\t   " << "BOOL " << "\t\t" << this->table[i].value.vlogic << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
							literStr.insert(literStr.begin(), this->table[i].value.vstr.str);
						}
						break;
					}
					if (!flagAgain) lexema_count++;
					break;
				case IT::IDTYPE::F:
					switch (this->table[i].iddatatype)
					{
					case 1:
						*(idStream) << "ÔÓÍÊÖÈß" << std::setw(17) << this->table[i].id << std::setw(16) << "UINT " << "\t\t\t\t\t" << this->table[i].parmQuantity << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 2:
						*(idStream) << "ÔÓÍÊÖÈß" << std::setw(17) << this->table[i].id << std::setw(16) << "STR " << "\t\t\t\t\t" << this->table[i].parmQuantity << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					case 3:
						*(idStream) << "ÔÓÍÊÖÈß" << std::setw(17) << this->table[i].id << std::setw(16) << "BOOL " << "\t\t\t\t\t" << this->table[i].parmQuantity << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					break;
				}
			}
			*(idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;




		/*

						if (this->table[i].idtype == IT::IDTYPE::V)
			{


				switch (this->table[i].iddatatype)
				{
				case 1:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
					break;
				}
				case 2:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
					break;
				}
				}

				flagForFirst = true;
			}

			if (this->table[i].idtype == IT::IDTYPE::P)
			{

				switch (this->table[i].iddatatype)
				{
				case 1:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << std::setw(15) << "P" << "\t\t\t" << this->table[i].firstApi << std::endl;
					break;
				}
				case 2:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << std::setw(15) << "P" << "\t\t\t" << this->table[i].firstApi << std::endl;
					break;
				}
				}

				flagForFirst = true;
			}


		switch (this->table[i].iddatatype)
					{
						case 1:
							*(idStream) << "   " << this->table[i].id << "\t\t\t" << "INT " << "\t\t" << 0 << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
							break;
						case 2:
							*(idStream) << "   " << this->table[i].id << "\t\t\t" << "STR " << "\t    " << "    \"\"" << " \t\t\t\t\t\t" << this->table[i].firstApi << std::endl;
							break;
					}
					break;



		* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;

			*(idStream) << "------------------ Ôóíêöèè ------------------" << std::endl;

			*(idStream) << std::setw(15) << "Èäåíòèôèêàòîð:" << std::setw(26) << "Òèï äàííûõ âîçâðàòà:" << std::setw(36) << "Êîëè÷åñòâî ïåðåäàííûõ ïàðàìåòðîâ:" << std::setw(22) << "Ïåðâîå âõîæäåíèå:" << std::endl;


								case IT::I

								case IT::IDTYPE::V:
						switch (this->table[i].iddatatype)
						{
							case 1:
								*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
								break;
							case 2:
								*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
								break;
						}
						flagForFirst = true;
						break;


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "------------------ Ïåðåìåííûå ------------------" << std::endl;
			*(idStream) << std::setw(25) << "Èìÿ ðîäèòåëüñêîãî áëîêà:" << std::setw(20) << "Èäåíòèôèêàòîð:" << std::setw(16) << "Òèï äàííûõ:" << std::setw(24) << "Òèï èäåíòèôèêàòîðà:" << std::setw(21) << "Ïåðâîå âõîæäåíèå:" << std::endl;

			for (int i = 0; i < this->size; i++)
			{


			}
*/

	}
}