#ifndef IADDPLAYERDETAILSTOTOURNAMENT_H
#define IADDPLAYERDETAILSTOTOURNAMENT_H

#include "iaddplayerdetailstomodel.h"
#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IAddPlayerDetailsToTournament : public IAddPlayerDetailsToModel<IModel<QUuid>,IModel<QUuid>,IModelsDbContext>
{
public:
    virtual void add(const IModel<QUuid> *tournament, const QVector<QUuid> &playerIds,
                     IModelsDbContext *dbService = nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament, const QVector<QString> &playerNames,
                     IModelsDbContext *dbService = nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament, const QUuid &winnerId, const QString &winnerName,
                     IModelsDbContext *dbService= nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament, const QVector<const IModel<QUuid>*> &playerModels,
                     IModelsDbContext *dbService) const override = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
