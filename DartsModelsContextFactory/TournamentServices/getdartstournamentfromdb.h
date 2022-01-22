#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H
#include "TournamentsDbSLAs/igetdartstournament.h"
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include <quuid.h>
#include <qvector.h>
#include "DbSLAs/idbcontext.h"
class GetDartsTournamentFromDb : public IGetDartsTournament<IModel<QUuid>>
{
public:
    virtual Model *get(const QUuid &tournamentId, const Models &models) const override
    {
        return findModel(tournamentId,models);
    }
private:
    Model *findModel(const QUuid &tournamentId, const Models &models) const
    {
        for (const auto &model : models) {
            if(model->id() == tournamentId)
                return model;
        }
        return nullptr;
    }
};
#endif // GETDARTSTOURNAMENTDATA_H
