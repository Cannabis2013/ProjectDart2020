#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <quuid.h>

template<typename TModel>
class ITournamentRepair
{
public:
      typedef TModel Model;
      typedef QVector<Model *> Models;
      virtual bool repair(const QUuid &tournamentID,
                          DartsModelsServices *services) = 0;
};
#endif // ITOURNAMENTREPAIR_H
