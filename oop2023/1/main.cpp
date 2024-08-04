#include "inputOutputMatrix.h"
#include "Matrix.h"

using namespace prog_1;

void Test1(Matrix&);
void Test2(Matrix&);
void Test3(Matrix&);

int main() {
    Matrix matrix = setRowColumn();
    
    try {
        while (true) {
            ChoiceCode choice = getChoice();
            if (!choice) break;

            switch (choice) {
            case SHOW_MATRIX:
                showMatrix(matrix);
                break;

            case INSERT_VALUE:
                insertValueIntoMatrix(matrix);
                break;

            case PROCESS:
                processing(matrix);
                break;

            default:
                throw std::runtime_error("Unknown ChoiceCode");
            }
        }
    }
    catch (const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}













void Test1(Matrix& matrix) {
    matrix.insertValue(0, 0, 1);
    matrix.insertValue(0, 1, 1);
    matrix.insertValue(0, 2, 0);
    matrix.insertValue(0, 3, 1);
    matrix.insertValue(0, 4, 0);
    matrix.insertValue(0, 5, 1);
    matrix.insertValue(0, 6, 1);
    matrix.insertValue(0, 7, 1);
    matrix.insertValue(0, 8, 0);
    matrix.insertValue(0, 9, 1);
}

void Test2(Matrix& matrix) {
    matrix.insertValue(2, 0, 0);
    matrix.insertValue(2, 1, -1);
    matrix.insertValue(2, 2, 0);
    matrix.insertValue(2, 3, -1);
    matrix.insertValue(2, 4, 100);
    matrix.insertValue(2, 5, -1);
    matrix.insertValue(2, 6, 100);
    matrix.insertValue(2, 7, 100);
}

void Test3(Matrix& matrix) {
    matrix.insertValue(3, 0, 100);
    matrix.insertValue(3, 1, -1);
    matrix.insertValue(3, 2, 0);
    matrix.insertValue(3, 3, 0);
    matrix.insertValue(3, 4, -1);
    matrix.insertValue(3, 5, 0);
    matrix.insertValue(3, 6, 100);
    matrix.insertValue(3, 7, -1);
}