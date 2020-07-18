#ifndef LOCALDBCONTEXT_H
#define LOCALDBCONTEXT_H

#include "abstractdbcontext.h"
#include "modelbuildercollection.h"

#include <qhash.h>
/*
class LocalDBContext : public AbstractDBContext<IModel<QUuid>,QUuid>
{
public:
    IModel<QUuid> getModelFromID(const QUuid &id);
    void removeModel(const QUuid &id);
private:
    QHash<QUuid,IModel<QUuid>> _models;
};
*/
#endif // LOCALDBCONTEXT_H
