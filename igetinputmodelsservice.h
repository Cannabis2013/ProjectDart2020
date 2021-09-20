#ifndef IGETINPUTMODELSSERVICE_H
#define IGETINPUTMODELSSERVICE_H

#include <qvector.h>
#include "iplayerinput.h"
#include "ModelsContext/imodelsdbcontext.h"

class IGetInputModelsService
{
public:
    // Pure methods
    virtual QVector<const IModel<QUuid>*> inputModels(const QUuid& tournamentId,
                                    const IModelsDbContext *dbService) const = 0;
    virtual QVector<const IModel<QUuid>*> inputModels(const QUuid& tournamentId, const int& hint,
                                    const IModelsDbContext *dbService) const = 0;

};

#endif // IGETINPUTMODELSSERVICE_H
