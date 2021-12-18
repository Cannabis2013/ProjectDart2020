#ifndef DARTSTABLEDATACONTEXT_H
#define DARTSTABLEDATACONTEXT_H

#include <qpair.h>
#include "DartsTableContext/DataContextSLAs/idartstabledatacontext.h"
#include <qdebug.h>
#include <QModelIndex>

class DartsTableDataContext : public IDartsTableDataContext
{
public:
    virtual void addItem(const Index &index, const Item &item) override;
    virtual Rows data() const override;
    virtual Rows &rows() override;
    virtual void replaceItem(const Index &index, const Item &model) override;
    virtual Row rowAt(const int &row) const override;
    virtual Item item(const Index &index) const override;
    virtual void clear() override;
    virtual int rowCount() const override;
    virtual void replaceRow(const int &row, const Row &data) override;
private:
    Rows _data;
};
#endif // DARTSTABLEDATACONTEXT_H
