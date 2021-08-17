#ifndef IGETDATAFROMDATACONTEXT_H
#define IGETDATAFROMDATACONTEXT_H

#include <qvector.h>

template<typename TDataModel, typename TDataContext>
class IGetDataFromDataContext
{
public:
    typedef TDataModel Item;
    typedef TDataContext DataContext;
    virtual QVector<Item> itemsAtColumn(const int &column, const DataContext *context) const = 0;
    virtual QVector<Item> itemsAtRow(const int &row, const DataContext *context) const = 0;
};
#endif // IGETDATAFROMDATACONTEXT_H
