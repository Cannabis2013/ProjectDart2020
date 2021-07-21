#ifndef IGETINPUTMODELSSERVICE_H
#define IGETINPUTMODELSSERVICE_H

#include <qvector.h>
#include "iplayerinput.h"
#include "idbservice.h"

class IGetInputModelsService
{
public:
    // Pure methods
    virtual QVector<const IModel<QUuid>*> inputModels(const QUuid& tournamentId,
                                    const IDbService *dbService) const = 0;
    virtual QVector<const IModel<QUuid>*> inputModels(const QUuid& tournamentId, const int& hint,
                                    const IDbService *dbService) const = 0;

};

#endif // IGETINPUTMODELSSERVICE_H
