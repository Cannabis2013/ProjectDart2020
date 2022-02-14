#include "dcundoturn.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"

#include <qjsondocument.h>

DCUndoTurn::DCUndoTurn(DCServices *services)
{
    _modelsContext = services->modelsContext();
    _metaManager = services->metaServices()->metaManager();
    _indexToByteArray = services->indexServices()->indexToByteArray();
    _createInput = services->inputServices()->createInputModel();
    _playerManager = services->playerServices()->playerManager();
    _addInputDetails = services->inputServices()->AddInputDetails();
    _indexController = services->indexServices()->indexController();
    _convertInput = services->inputServices()->inputConverter();
}

QByteArray DCUndoTurn::undo()
{
    _indexController->undo();
    auto meta = _metaManager->meta();
    auto tournamentID = meta.tournamentID;
    auto index = _indexController->index();
    auto player = _playerManager->player(index.playerIndex);
    auto playerName = player.name;
    auto indexAsByteArray = _indexToByteArray->convert(index);
    _modelsContext->hideInput(tournamentID,playerName,indexAsByteArray);
    auto prevIndex = _indexController->prevIndex();
    auto input = getInputFromModelsContext(prevIndex);
    _playerManager->updateScore(input);
    auto inputAsByteArray = toByteArray(input);
    return inputAsByteArray;
}

QJsonObject DCUndoTurn::toJson(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject())
        throw new std::exception();
    return document.object();
}

QByteArray DCUndoTurn::toByteArray(const DCInput &input)
{
    auto inputAsJson = _convertInput->convert(input);
    auto document = QJsonDocument(inputAsJson);
    return document.toJson();
}

DCInput DCUndoTurn::getInputFromModelsContext(const DCIndex &index)
{
    auto meta = _metaManager->meta();
    auto tournamentId = meta.tournamentID;
    auto player = _playerManager->player(index.playerIndex);
    auto idxBa = _indexToByteArray->convert(index);
    auto inputAsByteArray = _modelsContext->input(tournamentId,player.name,idxBa);
    QJsonObject inputAsJson;
    try {
        inputAsJson = toJson(inputAsByteArray);
    }  catch (std::exception *e) {
        return _createInput->create(player.name,meta.initRemScore);
    }
    auto ipt = _convertInput->convert(inputAsJson);
    _addInputDetails->add(ipt,player,meta);
    return ipt;
}
