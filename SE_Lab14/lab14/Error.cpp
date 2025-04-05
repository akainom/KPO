#include "stdafx.h"

namespace Error
{
    // серии ошибок: 0 - 99 - системные ошибки 
    //				100 - 109 - ошибки параметров 
    //				110 - 119 - ошибки открытия и чтения файлов
    Error errors[ERROR_MAX_ENTRY]
    {
        ERROR_ENTRY(0, "Неопределенная ошибка"),
        ERROR_ENTRY(1, "Ошибка ввода"),
        ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
        ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
        ERROR_ENTRY(100, "Ошибка -in при использовании командной строки"),
        ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
        ERROR_ENTRY_NODEF(104, "Ошибка при использовании командной строки"),
        ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
        ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
        ERROR_ENTRY(110, "Ошибка при использовании командной строки и неправильного параметра (-in)"),
        ERROR_ENTRY(111, "Неопределенная ошибка в командной строке и неправильного параметра (-in)"),
        ERROR_ENTRY(112, "Ошибка при использовании параметра -log"),
        ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
        ERROR_ENTRY(120, "Таблица лексем: превышен допустимый размер таблицы"),
        ERROR_ENTRY(121, "Превышена длина имя переменной или недопустимое имя переменной"),
        ERROR_ENTRY(122, "Таблица идентификаторов: превышен допустимый размер таблицы"),
        ERROR_ENTRY(123, "Лексический анализ: нераспознанная лексема"),
        ERROR_ENTRY(124, "Лексический анализ: нарушен формат строкового литерала"),
        ERROR_ENTRY(125, "Лексический анализ: перезапись идентификатора"),
        ERROR_ENTRY(126, "Лексический анализ: неизвестная переменная"),
        ERROR_ENTRY(127, "Лексический анализ: превышена длина строкового литерала"),
        ERROR_ENTRY(128, "Не удалось создать файл с таблицами лексем и идентификаторов"),
        ERROR_ENTRY(129, "Лексический анализ: найдено несколько точек входа (main)"),
        ERROR_ENTRY(130, "Лексический анализ: отсутствие ключевого слова declare при объявлении переменной"),
        ERROR_ENTRY(131, "Семантический анализ: не обнаружено точки входа(main)"),
        ERROR_ENTRY(132, "Семантический анализ: присвоение значения параметру"),
        ERROR_ENTRY(133, "Семантический анализ: деление на 0"),
        ERROR_ENTRY(134, "Семантический анализ: несоответствие типов в выражении"),
        ERROR_ENTRY(135, "Cемантический анализ: несовпадение фактических и формальных параметров функции"),
        ERROR_ENTRY(136, "Cемантический анализ: неверная структура выражения"), ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),
        ERROR_ENTRY_NODEF10(140),
        ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
        ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500), ERROR_ENTRY(600,"Неверная структура программы"),
        ERROR_ENTRY(601,"Ошибочный оператор"),
        ERROR_ENTRY(602,"Ошибка в выражении"),
        ERROR_ENTRY(603,"Ошибка в параметрах функции"),
        ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"), ERROR_ENTRY(605,"Ошибка в условии входа в блок(if)"), ERROR_ENTRY_NODEF10(700), ERROR_ENTRY_NODEF10(800), ERROR_ENTRY_NODEF10(900),
    };

    Error geterror(int id) // Функция для получения ошибки по идентификатору
    {
        if (id > 0 && id < ERROR_MAX_ENTRY) // Проверка, находится ли ID в допустимом диапазоне
            return errors[id]; // Возврат ошибки по указанному ID
        else
            return errors[0]; // Возвращает неопределенную ошибку по умолчанию
    }

    Error geterrorin(int id, int line = -1, int col = -1) // Функция для получения ошибки с указанием строки и столбца (по умолчанию -1)
    {
        if (id > 0 && id < ERROR_MAX_ENTRY) { // Проверка, находится ли ID в допустимом диапазоне
            errors[id].inext.col = col; // Установка столбца для ошибки
            errors[id].inext.line = line; // Установка строки для ошибки
            return errors[id]; // Возврат ошибки с обновленной информацией
        }
        else {
            return errors[0]; // Возвращает неопределенную ошибку по умолчанию
        }
    }
}
