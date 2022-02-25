#include "dcaddinput.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"
#include "Models/dcplayer.h"

DCAddInput::DCAddInput(DCServices *services)
{
    _modelsContext = services->modelsContext();
    _metaManager = services->metaServices()->metaManager();
    _inputEvaluator = services->inputServices()->evaluateInput();
    _convertInput = services->inputServices()->inputConverter();
    _playerManager = services->playerServices()->playerManager();
    _indexController = services->indexServices()->indexController();
    _indexToByteArray = services->indexServices()->indexToJson();
    _addInputDetails = services->inputServices()->AddInputDetails();
}

QByteArray DCAddInput::add(const QByteArray &byteArray)
{
    auto input = toInputModel(byteArray);
    evaluate(input);
    _indexController->next();
    updateModelsContext(input);
    updateControllerContext(input);
    return inputToByteArray(input);
}

DCInput DCAddInput::toInputModel(const QByteArray &byteArray)
{
    auto meta = _metaManager->meta();
    auto index = _indexController->index();
    auto player = _playerManager->player(index.playerIndex);
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject()) return DCInput();
    auto inputAsJson = document.object();
    auto input = _convertInput->convert(inputAsJson);
    _addInputDetails->add(input,player,meta,index);
    return input;
}

void DCAddInput::evaluate(DCInput &input)
{
    auto meta = &_metaManager->meta();
    auto player = _playerManager->player(input.playerName);
    _inputEvaluator->evaluate(input,meta,player);
}

void DCAddInput::updateModelsContext(DCInput &input)
{
    auto index = _indexController->index();
    auto meta = _metaManager->meta();
    auto indexAsByteArray = indexToByteArray(index);
    auto inputAsByteArray = inputToByteArray(input);
    _modelsContext->addInput(meta.tournamentID,inputAsByteArray);
    _modelsContext->updateTournamentIndex(meta.tournamentID,indexAsByteArray);
}

void DCAddInput::updateControllerContext(DCInput &input)
{
    auto meta = _metaManager->meta();
    _playerManager->updateScore(input);
    if(meta.status == _metaManager->WinnerDeclared)
        _modelsContext->setTournamentWinner(meta.tournamentID,meta.winnerName);
}

QByteArray DCAddInput::inputToByteArray(const DCInput &input)
{
    auto inputAsJson = _convertInput->convert(input);
    auto jsonDoc = QJsonDocument(inputAsJson);
    auto byteArray = jsonDoc.toJson();
    return byteArray;
}

QByteArray DCAddInput::indexToByteArray(const DCIndex &index)
{
    auto indexAsJson = _indexToByteArray->convert(index);
    auto jsonDoc = QJsonDocument(indexAsJson);
    auto byteArray = jsonDoc.toJson();
    return byteArray;
}
