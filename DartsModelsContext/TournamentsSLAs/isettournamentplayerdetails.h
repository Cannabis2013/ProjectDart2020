#ifndef ISETTOURNAMENTPLAYERDETAILS_H
#define ISETTOURNAMENTPLAYERDETAILS_H

#include "DartsModelsContext/TournamentsSLAs/abstractdartstournament.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class ISetTournamentPlayerDetails
{
public:
    virtual void setDetails(IModel<QUuid> *tournament, const QVector<IModel<QUuid>*> &playerModels) const = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
