#include "dcaddinputtomodelscontext.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"

DCAddInputToModelsContext::DCAddInputToModelsContext(DCServices *services)
{
    _modelsContext = services->modelsContext();
    _metaService = services->metaServices()->metaManager();
    _inputEvaluator = services->routines()->evaluateInput();
    _inputConverter = services->inputServices()->createInput();
    _playerManager = services->playerServices()->playerManager();
    _indexController = services->indexServices()->indexController();
    _indexToByteArray = services->indexServices()->indexToByteArray();
}

DCInput DCAddInputToModelsContext::add(const QByteArray &byteArray)
{
    auto input = toInputModel(byteArray);
    _inputEvaluator->evaluate(input);
    updateModelsContext(input);
    _playerManager->updateScore(input);
    return input;
}

DCInput DCAddInputToModelsContext::toInputModel(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    if(!document.isObject())
        return DCInput();
    auto inputAsJson = document.object();
    auto input = _inputConverter->create(inputAsJson);
    return input;
}

void DCAddInputToModelsContext::updateModelsContext(DCInput &input)
{
    auto meta = _metaService->meta();
    auto status = meta.status;
    auto winnerName = meta.winnerName;
    auto tournamentID = meta.tournamentID;
    auto index = _indexController->index();
    auto indexAsByteArray = _indexToByteArray->convert(index);
    auto inputAsByteArray = QJsonDocument(_inputConverter->create(input)).toJson();
    _modelsContext->addInput(tournamentID,inputAsByteArray);
    _modelsContext->updateTournamentIndex(tournamentID,indexAsByteArray);
    if(status == _metaService->WinnerDeclared)
        _modelsContext->setTournamentWinner(tournamentID,winnerName);
}
