#include "dcaddinput.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"
#include "Models/dcplayer.h"

QByteArray DCAddInput::add(const QByteArray &byteArray, DCServices *services){
    auto input = toInputModel(byteArray,services);
    evaluateInput(input,services);
    updateModelsContext(input,services);
    updateControllerContext(input,services);
    return inputToByteArray(input,services);
}

DCInput DCAddInput::toInputModel(const QByteArray &byteArray, DCServices *services){
    auto index = services->indexServices()->indexController()->index();
    auto player = services->playerServices()->playerManager()->player(index.playerIndex);
    auto meta = services->metaServices()->metaManager()->meta();
    auto inputAsJson = QJsonDocument::fromJson(byteArray).object();
    auto input = services->inputServices()->inputConverter()->convert(inputAsJson);
    services->inputServices()->AddInputDetails()->add(input,player,meta,index);
    return input;
}

void DCAddInput::evaluateInput(DCInput &input, DCServices *services){
    auto meta = &services->metaServices()->metaManager()->meta();
    auto player = services->playerServices()->playerManager()->player(input.playerName);
    services->inputServices()->evaluateInput()->evaluate(input,meta,player);
}

void DCAddInput::updateModelsContext(DCInput &input, DCServices *services){
    auto index = services->indexServices()->indexController()->next();
    auto meta = services->metaServices()->metaManager()->meta();
    auto indexAsByteArray = indexToByteArray(index,services);
    auto inputAsByteArray = inputToByteArray(input,services);
    services->modelsContext()->addInput(meta.tournamentID,inputAsByteArray);
    services->modelsContext()->updateTournamentIndex(meta.tournamentID,indexAsByteArray);
    if(meta.status == WinnerDeclared)
        services->modelsContext()->setTournamentWinner(meta.tournamentID,meta.winnerName);
}

void DCAddInput::updateControllerContext(DCInput &input,DCServices *services){
    auto meta = services->metaServices()->metaManager()->meta();
    services->playerServices()->playerManager()->updateScore(input);
}

QByteArray DCAddInput::inputToByteArray(const DCInput &input, DCServices *services){
    auto inputAsJson = services->inputServices()->inputConverter()->convert(input);
    return QJsonDocument(inputAsJson).toJson();
}

QByteArray DCAddInput::indexToByteArray(const DCIndex &index, DCServices *services){
    auto indexAsJson = services->indexServices()->indexToJson()->convert(index);
    return QJsonDocument(indexAsJson).toJson();
}
