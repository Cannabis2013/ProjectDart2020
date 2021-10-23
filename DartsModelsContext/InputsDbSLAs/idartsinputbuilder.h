#ifndef IDARTSINPUTBUILDER_H
#define IDARTSINPUTBUILDER_H

#include <quuid.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class IDartsInputBuilder
{
public:
    virtual IModel<QUuid> *createInput(const QByteArray &json) const = 0;
    virtual IModel<QUuid> *createInput(const QUuid &tournamentId, const QUuid &playerId, const int &remainingScore) const = 0;
    virtual QVector<IModel<QUuid> *> createInputs(const QByteArray &json) const = 0;
};
#endif // IDARTSINPUTBUILDER_H
