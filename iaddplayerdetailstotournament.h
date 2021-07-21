#ifndef IADDPLAYERDETAILSTOTOURNAMENT_H
#define IADDPLAYERDETAILSTOTOURNAMENT_H

#include "iaddplayerdetailstomodel.h"
#include "idartstournament.h"
#include "idbservice.h"
#include "iplayermodel.h"

class IAddPlayerDetailsToTournament : public IAddPlayerDetailsToModel<IModel<QUuid>,IModel<QUuid>,IDbService>
{
public:
    virtual void add(const IModel<QUuid> *tournament,const QVector<QUuid> &playerIds,
                     IDbService *dbService = nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament,
                     const QVector<QString> &playerNames,
                     IDbService *dbService = nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament,
                     const QUuid &winnerId,
                     IDbService *dbService= nullptr) const override = 0;
    virtual void add(const IModel<QUuid> *tournament, const QVector<const IModel<QUuid>*> &playerModels,
                     IDbService *dbService) const override = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
