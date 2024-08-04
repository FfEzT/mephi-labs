#include "inputOutputMatrix.h"

#include <array>
namespace prog_1 {
    Matrix setRowColumn() {
        unsigned    countRow = ShowMessageGetNumber("Number of rows: ", 1);
        unsigned countColumn = ShowMessageGetNumber("Number of columns: ", 1);

        return Matrix(countRow, countColumn);
    }

    ChoiceCode getChoice() {
        std::array<std::string, NUM_OF_CHOICES> select = {
            "exit",
            "show matrix",
            "insert value",
            "process"
        };

        std::cout << '\n';
        for (int i = 0; i < NUM_OF_CHOICES; ++i) {
            std::string& str = select.at(i);

            std::cout << i << ": " << str << '\n';
        }

        ChoiceCode res = static_cast<ChoiceCode>(
            ShowMessageGetNumber("Make a choice >> ", 0, NUM_OF_CHOICES)
            );

        std::cout << '\n';

        return res;
    };

    void insertValueIntoMatrix(Matrix& matrix) {
        unsigned    row = ShowMessageGetNumber("Coordinate of rows: ",    0u, matrix.getRowCount()    - 1);
        unsigned column = ShowMessageGetNumber("Coordinate of columns: ", 0u, matrix.getColumnCount() - 1);

        unsigned  value = ShowMessageGetNumber<unsigned>("Value: ");

        matrix.insertValue(row, column, value);
    }

    void processing(const Matrix& matrix) {
        Matrix newMatrix = changeMinMax(matrix);

        std::cout << "Your matrix:\n";
        showMatrix(matrix);

        std::cout << "----------------\n";

        std::cout << "Changed matrix:\n";
        showMatrix(newMatrix);
    }
}