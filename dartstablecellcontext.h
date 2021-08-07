#ifndef DARTSTABLECELLCONTEXT_H
#define DARTSTABLECELLCONTEXT_H

#include "itablecellcontext.h"

#include <QDebug>

class DartsTableCellContext : public ITableCellContext<QPair<int,int>>
{
public:
    int initialValue() const override
    {
        return _initialValue;
    }
    void setInitialValue(const int &value) override
    {
        _initialValue = value;
    }
    RowItem defaultValues() const override
    {
        return RowItem(-1,-1);
    }
    int indexOfLastDecoration(const int &row, const int &columnCount, const Rows &data) const override
    {
        try {
            checkIndexCompliance(row,data.count());
            auto rowData = data.at(row);
            for (int col = 0; col < columnCount; ++col) {
                auto columnData = rowData.at(col);
                auto point = columnData.first;
                if(point == -1)
                    return col - 1;
            }
            return columnCount - 1;
        }  catch (const char *msg) {
            qDebug() << msg;
            return false;
        }
    }
    bool isColumnEmpty(const int &column, const int &columnsCount, const Rows &data) const override
    {
        try {
            checkIndexCompliance(column,columnsCount);
            for (auto pairsRow : qAsConst(data)) {
                auto pair = pairsRow.at(column);
                auto point = pair.first;
                if(point != -1)
                    return false;
            }
            return true;
        }  catch (const char *msg) {
            qDebug() << msg;
            return false;
        }
    }
private:
    void checkIndexCompliance(const int &subject, const int &limit) const
    {
        if(subject >= limit || subject < 0)
            throw std::out_of_range(err);
    }
    int _initialValue = 0;
    const char *err = "Subject out of range";
};

#endif // DARTSTABLECELLCONTEXT_H
