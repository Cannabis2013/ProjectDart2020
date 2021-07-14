#ifndef DARTSCREATEJSONMETADATA_H
#define DARTSCREATEJSONMETADATA_H

#include "idartscreatejsonmetadata.h"

class DartsCreateJsonMetaData : public IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const ITournament *tournamentModel,
                                               const IGetDartsPlayerModelsFromDb *getPlayerData,
                                               const IAddDetailsToTournamentJson *jsonManipulator,
                                               const IDartsTournamentJsonBuilder *jsonBuilder,
                                               const IPlayerModelsDb *playersDb) const override
    {
        auto playerNames = tournamentModel->assignedPlayerNames();
        auto playerModel = getPlayerData->playerModel(tournamentModel->winnerId(),playersDb);
        auto json = jsonBuilder->createJson(tournamentModel);
        json = jsonManipulator->addPlayerNames(json,playerNames);
        json = jsonManipulator->addWinnerName(json,playerModel->playerName());
        return json;
    }
};
#endif // CREATEDARTSMETADATA_H
