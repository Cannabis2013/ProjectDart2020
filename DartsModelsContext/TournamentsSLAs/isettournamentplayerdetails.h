#ifndef ISETTOURNAMENTPLAYERDETAILS_H
#define ISETTOURNAMENTPLAYERDETAILS_H

#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"

class ISetTournamentPlayerDetails
{
public:
    virtual void setDetails(IModel<QUuid> *tournament, const QVector<IModel<QUuid>*> &playerModels) const = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
