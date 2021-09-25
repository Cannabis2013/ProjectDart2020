#ifndef IDARTSFINISHESDB_H
#define IDARTSFINISHESDB_H

#include <QMultiHash>
#include "ModelsContext/MCDbSLAs/idbcontext.h"
class IDartsFinishesDb : public IDbContext<QMultiHash<int,QString>>
{
public:
    typedef QMultiHash<int,QString> TargetRows;
    virtual void add(const TargetRows *item) = 0;
    virtual void add(const QVector<const TargetRows*> item) = 0;
    virtual const TargetRows *model(const int &index) const = 0;
    virtual QVector<const TargetRows*> models() const = 0;
    virtual bool remove(const int &index) = 0;
    virtual int indexOf(const TargetRows*) const = 0;
    virtual void replace(const int &index, const TargetRows *model) = 0;
    virtual void fetchModels() = 0;
    virtual void saveState() = 0;
};
#endif // IDARTSSUGGESTIONDB_H
