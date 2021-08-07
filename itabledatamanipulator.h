#ifndef ITABLEDATAMANIPULATOR_H
#define ITABLEDATAMANIPULATOR_H

template<typename T>
class ITableDataManipulator
{
public:
    virtual void removeRows(T &data, const int &row, const int &count) const = 0;
    virtual void removeColumns(T &data, const int &column, const int &count) = 0;
};
#endif // ITABLEDATAMANIPULATOR_H
