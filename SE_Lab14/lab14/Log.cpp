#include "stdafx.h"
#include "Log.h"
#pragma warning(disable:4996)
namespace Log {
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}
	void WriteLog(LOG log) {

		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);
		*log.stream << "--- �������� --- " << date << endl;

	}
	void WriteParm(LOG log, Parm::PARM parm) {

		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;

		*log.stream << "--- ��������� --- " << endl;
		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in : " << buff << endl;
		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buff << endl;
		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << buff << endl;
	}
	void WriteIn(LOG log, In::input in) {

		*log.stream << "--- �������� ������ --- " << endl;
		*log.stream << "���������� �������� : " << in.size << endl;
		*log.stream << "���������� �����    : " << in.lines << endl;
		*log.stream << "���������������     : " << in.ignore << endl;
	}
	void WriteError(LOG log, Error::Error error)
	{
		if (log.stream)
		{
			*log.stream << "--- ������!!! --- " << endl;
			*log.stream << "������ " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1)
			{
				*log.stream << "������: " << error.inext.line << endl << "�������: " << error.inext.col << endl << endl;
			}
		}
		else
			cout << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << endl << endl;
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}