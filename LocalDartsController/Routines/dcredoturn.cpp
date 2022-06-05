#include "dcredoturn.h"
#include <qjsondocument.h>
#include <DartsController/ServicesProvider/dcservices.h>
#include <DartsController/Meta/dcmetaservices.h>
#include <DartsController/Index/dcindexservices.h>
#include <DartsController/Inputs/dcinputsservices.h>
#include <DartsController/Inputs/idcinputadder.h>
#include <DartsController/Players/dcplayersservices.h>
#include <DartsController/Players/idcplayermanager.h>
#include <DartsController/Models/dcindex.h>
#include <DartsController/Models/dcmeta.h>
#include <DartsController/Models/dcplayer.h>
#include <DartsModelsContext/SLAs/abstractdartscontext.h>

DCRedoTurn::DCRedoTurn(DCServices *services)
{
        _modelsContext = services->modelsContext();
        _metaManager = services->metaServices()->metaManager();
        _indexToJson = services->indexServices()->indexToJson();
        _createInput = services->inputServices()->createInputModel();
        _convertInput = services->inputServices()->inputConverter();
        _playerManager = services->playerServices()->playerManager();
        _addInputDetails = services->inputServices()->AddInputDetails();
        _indexController = services->indexServices()->indexController();
}

QByteArray DCRedoTurn::redo()
{
        auto index = _indexController->index();
        auto meta = _metaManager->meta();
        auto tournamentID = meta.tournamentID;
        auto player = _playerManager->player(index.playerIndex);
        auto playerName = player.name;
        auto indexAsFormattedJson = indexAsByteArray(index);
        _modelsContext->revealInput(tournamentID,playerName,indexAsFormattedJson);
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

QByteArray DCRedoTurn::indexAsByteArray(const DCIndex &index)
{
        auto indexAsJson = _indexToJson->convert(index);
        auto jsonDoc = QJsonDocument(indexAsJson);
        return jsonDoc.toJson();
}

DCInput DCRedoTurn::getInputFromModelsContext(const DCIndex &index)
{
        auto meta = _metaManager->meta();
        auto tournamentId = meta.tournamentID;
        auto player = _playerManager->player(index.playerIndex);
        auto indexAsFormattedJson = indexAsByteArray(index);
        auto inputAsByteArray = _modelsContext->input(tournamentId,player.name,indexAsFormattedJson);
        QJsonObject inputAsJson;
        try {
                inputAsJson = toJson(inputAsByteArray);
        }  catch (std::exception *e) {
            throw e;
        }
        auto input = _convertInput->convert(inputAsJson);
        _addInputDetails->add(input,player,meta,index);
        return input;
}


