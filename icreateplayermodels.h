#ifndef ICREATEPLAYERMODELS_H
#define ICREATEPLAYERMODELS_H

#include <idbgetindexesutility.h>
#include <igetdartsplayermodelsfromdb.h>


class ICreatePlayerModels
{
public:
    virtual QVector<const DartsModelsContext::IPlayerModel*> createPlayerModels(const QByteArray &json,
                                                                                const IDbGetIndexesUtility *getIndexes,
                                                                                const IGetDartsPlayerModelsFromDb* getPlayerModels,
                                                                                const IPlayerModelsDb *dbService) const = 0;
};

#endif // ICREATEPLAYERMODELS_H


