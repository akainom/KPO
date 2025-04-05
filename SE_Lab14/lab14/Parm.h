#pragma once
#define PARM_IN L"-in:" // Входной параметр
#define PARM_OUT L"-out:" // Выходной параметр
#define PARM_LOG L"-log:" // Параметр для логирования
#define PARM_MAX_SIZE 300 // Максимальный размер параметра
#define PARM_OUT_DEFAULT_EXT L".out" // Расширение по умолчанию для выходного файла
#define PARM_LOG_DEFAULT_EXT L".log" // Расширение по умолчанию для лог-файла

namespace Parm // Параметры
{
	struct PARM // Структура параметров
	{
		wchar_t in[PARM_MAX_SIZE]; // -in: входной файл
		wchar_t out[PARM_MAX_SIZE]; // -out: выходной файл
		wchar_t log[PARM_MAX_SIZE]; // -log: лог-файл
	};

	PARM getparm(int argc, wchar_t* argv[]); // Получение параметров из командной строки
};