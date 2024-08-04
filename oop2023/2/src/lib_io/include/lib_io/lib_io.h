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

            // ��������� ����� �����
            if (std::cin.eof())
                throw std::runtime_error("Failed to read number: EOF");
            // ���������� ��������������� ������ �������� ������
            else if (std::cin.bad())
                throw std::runtime_error(
                    std::string("Failed to read number")
                );
            // ������ ������ (������������ ������ �����)
            else if (std::cin.fail()) {
                // ������� ����� ��������� ������
                std::cin.clear();

                // ���������� ��� ������� �� ����� ������
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if (a >= min && a <= max) // ���� ����� ������ � �������� ��������
                return a;
            else std::cout << "try again >> ";
        }
    }
}



#endif // !_lib_io
