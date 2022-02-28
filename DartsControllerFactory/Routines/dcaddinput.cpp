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
    _playerMng = services->playerServices()->playerManager();
    _indexCtrl = services->indexServices()->indexController();
    _indexToByteArray = services->indexServices()->indexToJson();
    _addInputDetails = services->inputServices()->AddInputDetails();
}

QByteArray DCAddInput::add(const QByteArray &byteArray)
{
    auto input = toInputModel(byteArray);
    evaluate(input);
    _indexCtrl->next();
    updateModelsContext(input);
    updateControllerContext(input);
    return inputToByteArray(input);
}

DCInput DCAddInput::toInputModel(const QByteArray &byteArray)
{
    auto index = _indexCtrl->index();
    auto player = _playerMng->player(index.playerIndex);
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject()) return DCInput();
    auto inputAsJson = document.object();
    auto input = _convertInput->convert(inputAsJson);
    _addInputDetails->add(input,player,_metaManager->meta(),index);
    return input;
}

void DCAddInput::evaluate(DCInput &input)
{
    auto meta = &_metaManager->meta();
    auto player = _playerMng->player(input.playerName);
    _inputEvaluator->evaluate(input,meta,player);
}

void DCAddInput::updateModelsContext(DCInput &input)
{
    auto index = _indexCtrl->index();
    auto meta = _metaManager->meta();
    auto indexAsByteArray = indexToByteArray(index);
    auto inputAsByteArray = inputToByteArray(input);
    _modelsContext->addInput(meta.tournamentID,inputAsByteArray);
    _modelsContext->updateTournamentIndex(meta.tournamentID,indexAsByteArray);
}

void DCAddInput::updateControllerContext(DCInput &input)
{
    auto meta = _metaManager->meta();
    _playerMng->updateScore(input);
    if(meta.status == _metaManager->WinnerDeclared)
        _modelsContext->setTournamentWinner(meta.tournamentID,meta.winnerName);
}

QByteArray DCAddInput::inputToByteArray(const DCInput &input)
{
    auto inputAsJson = _convertInput->convert(input);
    return QJsonDocument(inputAsJson).toJson();
}

QByteArray DCAddInput::indexToByteArray(const DCIndex &index)
{
    auto indexAsJson = _indexToByteArray->convert(index);
    return QJsonDocument(indexAsJson).toJson();
}
