#pragma once
#ifndef _lib_io
#define _lib_io

#include <limits>
#include <iostream>
#include <string>

namespace lib_io {
    template<typename T>
    T getNum(T min, T max)
    {
        T a;
        while (true) {
            std::cin >> a;

            // обнаружен конец файла
            if (std::cin.eof())
                throw std::runtime_error("Failed to read number: EOF");
            // обнаружена невосстановимая ошибка входного потока
            else if (std::cin.bad())
                throw std::runtime_error(
                    std::string("Failed to read number")
                );
            // прочие ошибки (неправильный формат ввода)
            else if (std::cin.fail()) {
                // очищаем флаги состояния потока
                std::cin.clear();

                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if (a >= min && a <= max) // если число входит в заданный диапазон
                return a;
            else std::cout << "try again >> ";
        }
    }
}



#endif // !_lib_io
