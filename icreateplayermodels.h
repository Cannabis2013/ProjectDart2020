#ifndef ICREATEPLAYERMODELS_H
#define ICREATEPLAYERMODELS_H

#include <igetdartsplayermodelsfromdb.h>


class ICreatePlayerModels
{
public:
    virtual QVector<const IModel<QUuid>*> createPlayerModels(const QByteArray &json,
                                                             const IGetDartsPlayerModelsFromDb* getPlayerModels,
                                                             const IDbService *dbService) const = 0;
};

#endif // ICREATEPLAYERMODELS_H


