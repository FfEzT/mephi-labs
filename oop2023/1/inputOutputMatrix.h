#ifndef _inputOutputMatrix
#define _inputOutputMatrix

#include <iostream>
#include <string>
#include <limits>

#include "Matrix.h"
#include "lib_io.h"


namespace prog_1 {
    const int NUM_OF_CHOICES = 4;
    enum ChoiceCode {
        EXIT = 0,
        SHOW_MATRIX,
        INSERT_VALUE,
        PROCESS
    };

    template <typename T>
    T ShowMessageGetNumber (std::string str,
                            T min = std::numeric_limits<T>::min(),
                            T max = std::numeric_limits<T>::max()) {
        std::cout << str;

        return lib_io::getNum<T>(min, max);
        //return lib_io::getNum(min, max);
    }

    Matrix setRowColumn();
    ChoiceCode getChoice();
    void insertValueIntoMatrix(Matrix& matrix);
    void processing(const Matrix& matrix);

    inline void showMatrix(const Matrix& matrix) {
        std::cout << matrix << std::endl;
    }
}

#endif