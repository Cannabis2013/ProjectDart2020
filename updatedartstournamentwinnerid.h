#ifndef UPDATEDARTSTOURNAMENTWINNERID_H
#define UPDATEDARTSTOURNAMENTWINNERID_H

#include "ibinary.h"
#include "idartstournament.h"
#include <quuid.h>

class UpdateDartsTournamentWinnerId : public IBinary<const QUuid&,
        const IDartsTournament<QUuid,QString>*,
        const IDartsTournament<QUuid,QString>*>
{
public:

    // IBinary interface
public:
    const IDartsTournament<QUuid,QString>* service(const QUuid& newWinnerId, const IDartsTournament<QUuid,QString>* model) override
    {
        auto nonConstModel = const_cast<IDartsTournament<QUuid,QString>*>(model);
        nonConstModel->setWinnerId(newWinnerId);
        return nonConstModel;
    }
};

#endif // UPDATEDARTSTOURNAMENTWINNERID_H
