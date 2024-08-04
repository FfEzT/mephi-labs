#include "Matrix.h"

#include <algorithm>
#include <iomanip>

using std::setw;
using std::cout;
using std::string;

using namespace prog_1;

namespace {
    void showFirstRow(const std::set<unsigned>& columnsNumber);
    void showRow(std::set<unsigned>& columnsNumber, const Map& row);
    void rowChangeMinMax(Matrix& result, const Map& rowMap, unsigned rowNumber);
    const int IO_WIDTH = 3;
}




namespace prog_1 {

    Matrix::Matrix(unsigned rowCount, unsigned columnCount)
        : columnCount(columnCount), rowCount(rowCount) {
        rows.reserve(rowCount);

        for (unsigned i = 0; i < rowCount; ++i)
            rows.push_back(Map());
    }

    void Matrix::insertValue(unsigned row, unsigned column, int value) {
        if (row >= getRowCount() ||
            column >= getColumnCount())
            return;

        Map& mapRow = rows.at(row);
        mapRow[column] = value;

    }

    Matrix changeMinMax(const Matrix& matrix) {
        Matrix result(
            matrix.getRowCount(),
            matrix.getColumnCount()
        );

        for (unsigned rowNumber = 0; rowNumber < matrix.getRowCount(); ++rowNumber) {
            const Map& rowMap = matrix.rows.at(rowNumber);
            if (!rowMap.size())
                continue;

            rowChangeMinMax(result, rowMap, rowNumber);
        }

        return result;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        cout << std::setfill('.');

        std::set<unsigned> columnsNumber;
        for (const Map& map : matrix.rows)
            for (const auto& pair : map)
                columnsNumber.insert(pair.first);

        showFirstRow(columnsNumber);
        for (unsigned rowNumber = 0; rowNumber < matrix.rowCount; ++rowNumber) {
            const auto& row = matrix.rows.at(rowNumber);
            if (row.empty()) continue;

            cout << setw(IO_WIDTH - 1) << rowNumber << '|';
            showRow(columnsNumber, row);
        }

        return os;
    };
}



namespace {
    void showFirstRow(const std::set<unsigned>& columnsNumber) {
        cout << string(IO_WIDTH, ' ');

        int prevColumnNumber = -1;
        for (auto it : columnsNumber) {
            cout << ' ' << setw(IO_WIDTH);

            if (it != prevColumnNumber + 1)
                cout << string(IO_WIDTH, '.') << ' ' << setw(IO_WIDTH);
            cout << it << ' ';

            prevColumnNumber = it;
        }
        cout << '\n';
    }

    void showRow(std::set<unsigned>& columnsNumber, const Map& row) {
        auto mapIt = row.begin();

        int prevColumnNumber = -1;
        for (auto it : columnsNumber) {
            cout << ' ' << setw(IO_WIDTH);

            if (it != prevColumnNumber + 1)
                cout << string(IO_WIDTH, '.') << ' ' << setw(IO_WIDTH);

            if (mapIt != row.end() && mapIt->first == it) {
                cout << mapIt->second;
                ++mapIt;
            }
            else cout << string(IO_WIDTH, '.');

            cout << ' ';

            prevColumnNumber = it;
        }
        cout << '\n';
    }

    std::tuple<int, int, int, int> getMinMax(const Map& rowMap) {
        int minValue = rowMap.begin()->second;
        int maxValue = rowMap.begin()->second;
        int minCount = 0, maxCount = 0;

        for (const auto& mapIt : rowMap) {
            if (mapIt.second < minValue) {
                minValue = mapIt.second;
                minCount = 1;
            }
            else if (mapIt.second > maxValue) {
                maxValue = mapIt.second;
                maxCount = 1;
            }
            else {
                if (mapIt.second == minValue)
                    ++minCount;
                if (mapIt.second == maxValue)
                    ++maxCount;
            }
        }
        return std::tie(minValue, maxValue, minCount, maxCount);
    }

    void rowChangeMinMax(Matrix& result, const Map& rowMap, unsigned rowNumber) {
        auto [minValue, maxValue, currentMinCount, currentMaxCount] = getMinMax(rowMap);
        int maxCount = currentMaxCount;
        int minCount = currentMinCount;

        for (const auto& mapIt : rowMap) {
            unsigned columnNuber = mapIt.first;

            int currentValue = mapIt.second;
            bool isCurrentValueMinMax = currentValue == maxValue ||
                currentValue == minValue;

            if (currentMaxCount && currentMinCount && isCurrentValueMinMax) {
                if (mapIt.second == minValue) {
                    result.insertValue(rowNumber, columnNuber, maxValue);
                    --currentMaxCount;
                }
                else if (mapIt.second == maxValue) {
                    result.insertValue(rowNumber, columnNuber, minValue);
                    --currentMinCount;
                }
            }
            else if (currentMaxCount &&
                currentValue == minValue && currentMaxCount > maxCount - minCount) {
                result.insertValue(rowNumber, columnNuber, maxValue);
                --currentMaxCount;
            }
            else if (currentMinCount &&
                currentValue == maxValue && currentMinCount > minCount - maxCount) {
                result.insertValue(rowNumber, columnNuber, minValue);
                --currentMinCount;
            }
            else result.insertValue(
                rowNumber, columnNuber, currentValue
            );
        }
    }
}