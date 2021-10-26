#ifndef IGETINPUTMODELSSERVICE_H
#define IGETINPUTMODELSSERVICE_H

#include <qvector.h>
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"

class IGetInputModelsService
{
public:
    // Pure methods
    virtual QVector<IModel<QUuid>*> get(const QUuid& tournamentId, const IModelsDbContext *dbService) const = 0;
    virtual QVector<IModel<QUuid>*> get(const QUuid& tournamentId, const int& hint, const IModelsDbContext *dbService) const = 0;

};

#endif // IGETINPUTMODELSSERVICE_H
