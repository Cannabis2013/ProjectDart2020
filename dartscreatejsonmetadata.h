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
        auto winnerPlayerModel = getPlayerData->playerModel(tournamentModel->winnerId(),playersDb);
        auto winnerName = getWinnerNameFromModel(winnerPlayerModel);
        auto json = jsonBuilder->createJson(tournamentModel);
        json = jsonManipulator->addPlayerNames(json,playerNames);
        json = jsonManipulator->addWinnerName(json,winnerName);
        return json;
    }
private:
    QString getWinnerNameFromModel(const DartsModelsContext::IPlayerModel *playerModel) const
    {
        if(playerModel != nullptr)
            return playerModel->playerName();
        else
            return "";
    }
};
#endif // CREATEDARTSMETADATA_H
