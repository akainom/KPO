#include "stdafx.h" 
#include "Parm.h"   
#include "Error.h"  

namespace Parm {
    
    PARM getparm(int argc, wchar_t* argv[]) {
        PARM parm; 
        bool in = false, out = false, log = false; 

        
        for (int i = 0; i < argc; i++) {
            // Проверка на превышение максимального размера параметра
            if (wcslen(argv[i]) > PARM_MAX_SIZE) {
                throw ERROR_THROW(104); // Генерация ошибки, если размер превышен
            }

            // Проверка наличия параметра входных данных
            if (wcsstr(argv[i], PARM_IN) != nullptr) {
                wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN)); // Копирование входного параметра
                in = true; // Установка флага наличия входного параметра
            }

            // Проверка наличия параметра выходных данных
            if (wcsstr(argv[i], PARM_OUT) != nullptr) {
                wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT)); 
                out = true; 
            }

            // Проверка наличия параметра логирования
            if (wcsstr(argv[i], PARM_LOG) != nullptr) {
                wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG)); 
                log = true; 
            }
        }

        
        if (!in) {
            throw ERROR_THROW(100); 
        }

        
        if (!out) {
            wcscpy_s(parm.out, parm.in); // Копирование входного параметра в выходной
            wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT); 
        }

  
        if (!log) {
            wcscpy_s(parm.log, parm.in); // Копирование входного параметра в лог-файл
            wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT); 
        }

        return parm; 
    }
}