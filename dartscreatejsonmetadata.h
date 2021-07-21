#ifndef DARTSCREATEJSONMETADATA_H
#define DARTSCREATEJSONMETADATA_H

#include "idartscreatejsonmetadata.h"
#include "iplayermodel.h"

class DartsCreateJsonMetaData : public IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *model,
                                               const IGetDartsPlayerModelsFromDb *getPlayerData,
                                               const IAddDetailsToTournamentJson *jsonManipulator,
                                               const IDartsTournamentJsonBuilder *jsonBuilder,
                                               const IDbService *playersDb) const override
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        auto playerNames = tournamentModel->assignedPlayerNames();
        auto winnerPlayerModel = getPlayerData->playerModel(tournamentModel->winnerId(),playersDb);
        auto winnerName = getWinnerNameFromModel(winnerPlayerModel);
        auto json = jsonBuilder->createJson(model);
        json = jsonManipulator->addPlayerNames(json,playerNames);
        json = jsonManipulator->addWinnerName(json,winnerName);
        return json;
    }
private:
    QString getWinnerNameFromModel(const IModel<QUuid> *model) const
    {
        if(model != nullptr)
            return dynamic_cast<const ModelsContext::IPlayerModel*>(model)->playerName();
        else
            return "";
    }
};
#endif // CREATEDARTSMETADATA_H
