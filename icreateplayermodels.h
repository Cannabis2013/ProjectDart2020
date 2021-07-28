#ifndef ICREATEPLAYERMODELS_H
#define ICREATEPLAYERMODELS_H

#include <igetplayerfromdb.h>


class ICreatePlayerModels
{
public:
    virtual QVector<const IModel<QUuid>*> createPlayerModels(const QByteArray &json,
                                                             const IGetPlayersFromDb* getPlayerModels,
                                                             const IModelsDbContext *dbService) const = 0;
};

#endif // ICREATEPLAYERMODELS_H


