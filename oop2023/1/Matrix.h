#ifndef _Matrix
#define _Matrix

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using Pair = std::pair<unsigned, int>;
using Map = std::map<unsigned, int>;
using RowVector = std::vector<Map>;

namespace prog_1 {
    class Matrix {
    public:
        Matrix(unsigned rowCount, unsigned columnCount);

        void insertValue(unsigned row, unsigned column, int value);

        inline unsigned getRowCount() const    { return rowCount; }
        inline unsigned getColumnCount() const { return columnCount; }

    private:
        unsigned columnCount, rowCount;
        RowVector rows;



        friend std::ostream& operator<<(std::ostream& os, const Matrix& oldMatrix);
        friend Matrix changeMinMax(const Matrix& matrix);
    };

}

#endif // !_Matrix