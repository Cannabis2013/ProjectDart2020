#ifndef IDBSERVICE_H
#define IDBSERVICE_H

#include <qvector.h>
#include "iplayerinput.h"
#include "imodelsdbcontext.h"

class IDbService : public IModelsDbContext<IModel<QUuid>>
{
public:
    virtual void add(const IModel<QUuid> *inputModel) override = 0;
    virtual const IModel<QUuid> *model(const int &index) const override = 0;
    virtual QVector<const IModel<QUuid>*> models() const override = 0;
    virtual bool remove(const int &index) override = 0;
    virtual int indexOf(const IModel<QUuid> *inputModel) const override = 0;
    virtual void replace(const int &index, const IModel<QUuid> *inputModel) override = 0;
};


#endif // IDARTSSCOREDB_H
