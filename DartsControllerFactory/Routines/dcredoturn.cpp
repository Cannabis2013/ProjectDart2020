#include "dcredoturn.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include <qjsondocument.h>

DCRedoTurn::DCRedoTurn(DCServices *services)
{
    _modelsContext = services->modelsContext();
    _metaManager = services->metaServices()->metaManager();
    _indexToByteArray = services->indexServices()->indexToByteArray();
    _createInput = services->inputServices()->createInputModel();
    _convertInput = services->inputServices()->inputConverter();
    _playerManager = services->playerServices()->playerManager();
    _addInputDetails = services->inputServices()->AddInputDetails();
    _indexController = services->indexServices()->indexController();
}

QByteArray DCRedoTurn::redo()
{
    auto meta = _metaManager->meta();
    auto tournamentID = meta.tournamentID;
    auto index = _indexController->index();
    auto player = _playerManager->player(index.playerIndex);
    auto playerName = player.name;
    auto indexAsByteArray = _indexToByteArray->convert(index);
    _modelsContext->revealInput(tournamentID,playerName,indexAsByteArray);
    auto input = getInputFromModelsContext(index);
    _playerManager->updateScore(input);
    auto inputAsByteArray = toByteArray(input);
    _indexController->redo();
    return inputAsByteArray;
}

QJsonObject DCRedoTurn::toJson(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject())
        throw new std::exception();
    return document.object();
}

QByteArray DCRedoTurn::toByteArray(const DCInput &input)
{
    auto inputAsJson = _convertInput->convert(input);
    auto document = QJsonDocument(inputAsJson);
    return document.toJson();
}

DCInput DCRedoTurn::getInputFromModelsContext(const DCIndex &index)
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
        throw e;
    }
    auto input = _convertInput->convert(inputAsJson);
    _addInputDetails->add(input,player,meta);
    return input;
}


