#ifndef CREATEDARTSTOURNAMENTFROMJSON_H
#define CREATEDARTSTOURNAMENTFROMJSON_H

#include "DartsModelsContext/DMCTournamentSLAs/ijsontodartstournamentmodel.h"
#include "dartstournament.h"

class CreateDartsTournamentFromJson : public IJsonToDartsTournamentModel
{
public:
    const AbstractDartsTournament *create(const QByteArray &json,
                                          const IDartsTournamentExtractor *extractor) const override
    {
        auto jsonObject = createJsonObject(json);
        auto tournamentModel = createModelFromJsonObject(jsonObject,extractor);
        return tournamentModel;
    }
private:
    QJsonObject createJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        return jsonObject;
    }
    const AbstractDartsTournament *createModelFromJsonObject(const QJsonObject &obj,
                                                             const IDartsTournamentExtractor *extractor) const
    {
        auto dartsTournamentModel = ModelsContext::DartsTournament::createInstance();
        dartsTournamentModel->setTitle(extractor->title(obj));
        dartsTournamentModel->setGameMode(extractor->gameMode(obj));
        dartsTournamentModel->setKeyPoint(extractor->keyPoint(obj));
        dartsTournamentModel->setDisplayHint(extractor->displayHint(obj));
        dartsTournamentModel->setInputMode(extractor->inputHint(obj));
        dartsTournamentModel->setStatus(extractor->status(obj));
        dartsTournamentModel->setWinnerId(extractor->winnerId(obj));
        dartsTournamentModel->setWinnerName(extractor->winnerName(obj));
        dartsTournamentModel->setId(QUuid::createUuid());
        return dartsTournamentModel;
    }
};

#endif // DARTSTOURNAMENTBUILDER_H
