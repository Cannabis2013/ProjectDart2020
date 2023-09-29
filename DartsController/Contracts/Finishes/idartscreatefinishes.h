#ifndef IDARTSCREATEFINISHES_H
#define IDARTSCREATEFINISHES_H

#include <QVector>

class IDartsCreateFinishes
{
public:
    typedef QMultiHash<int, QString> TargetRow;
    typedef QVector<TargetRow *> TargetRows;
    virtual TargetRows constructRows() const = 0;
};
#endif // IDARTSCONSTRUCTTARGETROW_H
