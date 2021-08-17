#ifndef DARTSTABLEDATACONTEXT_H
#define DARTSTABLEDATACONTEXT_H

#include <qpair.h>
#include "itabledatacontext.h"
#include <qdebug.h>

namespace TableDataContext {
    typedef QPair<int,int> DataRowItem;
    typedef LinkedList<DataRowItem> DataRow;
    typedef QVector<DataRow> DataRows;
}
#include <QModelIndex>
class DartsTableDataContext : public ITableDataContext<TableDataContext::DataRowItem,QModelIndex>
{
    typedef QPair<int,int> RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
public:
    virtual Rows data() const override;
    virtual Rows &rows() override;
    virtual void replaceItem(const Index &index, const Item &model) override;
    virtual Row rowAt(const int &row) const override;
    virtual Item item(const Index &index) const override;
    virtual void clear() override;
    virtual int rowCount() const override;
    virtual void replaceRow(const int &row, const Row &data) override;
    virtual int lastFilledCell(const int &row, const int &columnCount, const Rows &data) const override;
    virtual bool isColumnEmpty(const int &column, const int &columnsCount, const Rows &data) const override;
private:
    void checkIndexCompliance(const int &subject, const int &limit) const;
    const char *err = "Subject out of range";
    bool hasColumns(const int &column, const Row &r) const;
    Rows _data;
};



#endif // DARTSTABLEDATACONTEXT_H
