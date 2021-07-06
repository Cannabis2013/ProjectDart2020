#ifndef IGETINPUTMODELSSERVICE_H
#define IGETINPUTMODELSSERVICE_H

#include <qvector.h>
#include "iplayerinput.h"
#include "idartsinputdb.h"

class IGetInputModelsService
{
public:
    // Pure methods
    virtual QVector<const IPlayerInput*> inputModels(const QUuid& tournamentId,
                                    const IDartsInputDb *dbService) const = 0;
    virtual QVector<const IPlayerInput*> inputModels(const QUuid& tournamentId, const int& hint,
                                    const IDartsInputDb *dbService) const = 0;

};

#endif // IGETINPUTMODELSSERVICE_H
