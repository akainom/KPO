#pragma once
#define ERROR_THROW(id) Error::geterror(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c)
#define ERROR_ENTRY(id, m) {id, m, {-1, -1}}
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(-id, "Неопределенная ошибка")

#define ERROR_ENTRY_NODEF10(id)   ERROR_ENTRY_NODEF(id+0), ERROR_ENTRY_NODEF(id+1), ERROR_ENTRY_NODEF(id+2), ERROR_ENTRY_NODEF(id+3), \
                                  ERROR_ENTRY_NODEF(id+4), ERROR_ENTRY_NODEF(id+5), ERROR_ENTRY_NODEF(id+6), ERROR_ENTRY_NODEF(id+7), \
                                  ERROR_ENTRY_NODEF(id+8), ERROR_ENTRY_NODEF(id+9)
#define ERROR_ENTRY_NODEF100(id)  ERROR_ENTRY_NODEF(id+0), ERROR_ENTRY_NODEF(id+10), ERROR_ENTRY_NODEF(id+20), ERROR_ENTRY_NODEF(id+30), \
                                  ERROR_ENTRY_NODEF(id+40), ERROR_ENTRY_NODEF(id+50), ERROR_ENTRY_NODEF(id+60), ERROR_ENTRY_NODEF(id+70), \
                                  ERROR_ENTRY_NODEF(id+80), ERROR_ENTRY_NODEF(id+90)

#define ERROR_MAX_ENTRY 1000

namespace Error 
{
    struct Error 
    {
        int id; 
        char message[200]; 
        struct In // Вложенная структура для хранения информации о местоположении ошибки
        {
            short line; 
            short col;  
        } inext; // Поле для хранения информации о местоположении ошибки
    };

    Error geterror(int id); // Функция для получения ошибки по идентификатору
    Error geterrorin(int id, int line, int col); // Функция для получения ошибки с указанием строки и столбца
}