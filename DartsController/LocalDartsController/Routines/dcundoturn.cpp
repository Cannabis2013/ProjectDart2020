#include "dcundoturn.h"
#include <qjsondocument.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/Contracts/Meta/dcmetaservices.h>
#include <DartsController/Contracts/Index/dcindexservices.h>
#include <DartsController/Contracts/Index/idcindexcontroller.h>
#include <DartsController/Contracts/Inputs/dcinputsservices.h>
#include <DartsController/Contracts/Inputs/idcinputadder.h>
#include <DartsController/Contracts/Players/dcplayersservices.h>
#include <DartsController/Contracts/Players/idcplayermanager.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>
#include <DartsModelsContext/Contracts/abstractdartscontext.h>

DCUndoTurn::DCUndoTurn(DCServices *services)
{
        _modelsContext = services->modelsContext();
        _metaManager = services->metaServices()->metaManager();
        _indexToJson = services->indexServices()->indexToJson();
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
         auto index = _indexController->index();
         auto player = _playerManager->player(index.playerIndex);
         auto playerName = player.name;
         auto indexAsByteArray = indexToFormattedJson(index);
         _modelsContext->hideInput(meta.tournamentID,playerName,indexAsByteArray);
         auto prevIndex = _indexController->prevIndex();
         auto input = getInputFromModelsContext(prevIndex);
         _playerManager->updateScore(input);
         auto inputAsByteArray = inputToFormattedJson(input);
         return inputAsByteArray;
}

QJsonObject DCUndoTurn::toJson(const QByteArray &byteArray)
{
        auto document = QJsonDocument::fromJson(byteArray);
        if(!document.isObject())
                throw new std::exception();
        auto jsonObj = document.object();
        if(jsonObj.isEmpty())
                throw new std::exception();
        return jsonObj;
}

QByteArray DCUndoTurn::inputToFormattedJson(const DCInput &input)
{
        auto inputAsJson = _convertInput->convert(input);
        auto document = QJsonDocument(inputAsJson);
        return document.toJson();
}

QByteArray DCUndoTurn::indexToFormattedJson(const DCIndex &index)
{
        auto inputAsJson = _indexToJson->convert(index);
        auto document = QJsonDocument(inputAsJson);
        return document.toJson();
}

DCInput DCUndoTurn::getInputFromModelsContext(const DCIndex &index)
{
        auto meta = _metaManager->meta();
        auto player = _playerManager->player(index.playerIndex);
        auto IndexAsFormattedJson = indexToFormattedJson(index);
        QByteArray inputAsByteArray;
        try {
                inputAsByteArray = _modelsContext->input(meta.tournamentID,player.name,IndexAsFormattedJson);
        }  catch (std::exception *e) {
                return _createInput->create(player.name,meta.initRemScore);
        }
        QJsonObject inputAsJson = toJson(inputAsByteArray);
        auto ipt = _convertInput->convert(inputAsJson);
        _addInputDetails->add(ipt,player,meta,index);
        return ipt;
}
