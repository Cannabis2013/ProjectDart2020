#include "dcaddinputtomodelscontext.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"
#include "Models/dcplayer.h"

DCAddInputToModelsContext::DCAddInputToModelsContext(DCServices *services)
{
    _modelsContext = services->modelsContext();
    _metaManager = services->metaServices()->metaManager();
    _inputEvaluator = services->inputServices()->evaluateInput();
    _convertInput = services->inputServices()->inputConverter();
    _playerManager = services->playerServices()->playerManager();
    _indexController = services->indexServices()->indexController();
    _indexToByteArray = services->indexServices()->indexToByteArray();
    _addInputDetails = services->inputServices()->AddInputDetails();
}

QByteArray DCAddInputToModelsContext::add(const QByteArray &byteArray)
{
    auto input = toInputModel(byteArray);
    auto meta = _metaManager->meta();
    auto playerIndex = _indexController->index().playerIndex;
    auto player = _playerManager->player(playerIndex);
    _addInputDetails->add(input,player,meta);
    auto alteredMeta = _inputEvaluator->evaluate(input,meta,player);
    _metaManager->setMeta(alteredMeta);
    updateModelsContext(input);
    _playerManager->updateScore(input);
    auto inputAsByteArray = inputToByteArray(input);
    _indexController->next();
    return inputAsByteArray;
}

DCInput DCAddInputToModelsContext::toInputModel(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject())
        return DCInput();
    auto inputAsJson = document.object();
    auto input = _convertInput->convert(inputAsJson);
    return input;
}

void DCAddInputToModelsContext::updateModelsContext(DCInput &input)
{
    auto meta = _metaManager->meta();
    auto status = meta.status;
    auto winnerName = meta.winnerName;
    auto tournamentID = meta.tournamentID;
    auto index = _indexController->index();
    auto indexAsByteArray = _indexToByteArray->convert(index);
    auto inputAsByteArray = QJsonDocument(_convertInput->convert(input)).toJson();
    _modelsContext->addInput(tournamentID,inputAsByteArray);
    _modelsContext->updateTournamentIndex(tournamentID,indexAsByteArray);
    if(status == _metaManager->WinnerDeclared)
        _modelsContext->setTournamentWinner(tournamentID,winnerName);
}

QByteArray DCAddInputToModelsContext::inputToByteArray(const DCInput &input)
{
    auto inputAsJson = _convertInput->convert(input);
    auto jsonDoc = QJsonDocument(inputAsJson);
    auto byteArray = jsonDoc.toJson();
    return byteArray;
}
