#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qvector.h>
#include <quuid.h>
#include "iplayermodel.h"

class IModelsDbContext
{
public:
    // Public types
    virtual ~IModelsDbContext() = default;
    virtual void addPlayerModel(const IPlayerModel*) = 0;
    virtual const IPlayerModel* playerModel(const int&) = 0;
    virtual QVector<const IPlayerModel*> playerModels() = 0;
    virtual void removePlayerModel(const QUuid&) = 0;
    virtual void removePlayerModel(const int&) = 0;
    virtual int indexOfPlayerModel(const IPlayerModel*) = 0;
    virtual void replacePlayerModel(const int&, const IPlayerModel*) = 0;
};

#endif // IMODELDBCONTEXT_H
