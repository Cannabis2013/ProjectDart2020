#include "getdartstournamentfromdb.h"

#include <DartsModelsContext/ModelSLAs/imodel.h>

GetDartsTournamentFromDb::Model *GetDartsTournamentFromDb::get(const QUuid &tournamentId, const Models &models) const
{
        return findModel(tournamentId,models);
}

GetDartsTournamentFromDb::Model *GetDartsTournamentFromDb::findModel(const QUuid &tournamentId, const Models &models) const
{
        for (const auto &model : models) {
                if(model->id() == tournamentId)
                        return model;
        }
        return nullptr;
}
