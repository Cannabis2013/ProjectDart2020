#include "dcinitialize.h"
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/Contracts/Meta/dcmetaservices.h>
#include <DartsController/Contracts/Players/dcplayersservices.h>
#include <DartsController/Contracts/Players/idcplayermanager.h>
#include <DartsController/Contracts/Inputs/dcinputsservices.h>
#include <DartsController/Contracts/Index/dcindexservices.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>
#include <DartsModelsContext/Contracts/abstractdartscontext.h>

DCInitialize::DCInitialize(DCServices *services)
{
         _metaManager = services->metaServices()->metaManager();
         _playerManager = services->playerServices()->playerManager();
         _jsonToInput = services->inputServices()->inputConverter();
         _jsonToInputs = services->inputServices()->jsonToInputModels();
         _modelsContext = services->modelsContext();
         _jsonToPlayer = services->playerServices()->jsonToPlayer();
         _byteArrayToPlayers = services->playerServices()->jsonToPlayers();
         _jsonToMeta = services->metaServices()->metaConverter();
         _indexController = services->indexServices()->indexController();
}

int DCInitialize::init(const QUuid &tournamentID){
        initMeta(tournamentID);
        initPlayerDetails();
        initPlayerScores();
        initStatus();
        return _metaManager->status();
}

void DCInitialize::initMeta(const QUuid &tournamentID){
        auto tnmVals = _modelsContext->tournament(tournamentID);
        auto meta = _jsonToMeta->convert(tnmVals);
        _metaManager->setMeta(meta);
        _indexController->init(meta);
}

void DCInitialize::initPlayerDetails()
{
         auto meta = _metaManager->meta();
         auto tournamentValues = _modelsContext->tournament(meta.tournamentID);
         auto players = _byteArrayToPlayers->convert(tournamentValues,_jsonToPlayer);
         updatePlayers(players,meta.initRemScore);
         _playerManager->addPlayers(players);
}

void DCInitialize::initPlayerScores()
{
    auto meta = _metaManager->meta();
    auto inputsAsByteArray = _modelsContext->inputs(meta.tournamentID);
    auto inputs = _jsonToInputs->convert(inputsAsByteArray,_jsonToInput);
    _playerManager->updateScores(inputs);
}

void DCInitialize::initStatus()
{
    auto meta = &_metaManager->meta();
    if(meta->winnerName == QString())
        meta->status = IDCMetaManager<DCMeta>::Initialized;
    else
        meta->status = IDCMetaManager<DCMeta>::WinnerDeclared;
}

void DCInitialize::updatePlayers(QVector<DCPlayer> &players, const int &remScore)
{
        for (auto &player : players)
                player.remaining =  remScore;
}
