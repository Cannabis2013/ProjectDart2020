#include "dcaddinputtomodelscontext.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"

DCAddInputToModelsContext::DCAddInputToModelsContext(DCServices *services)
{
    _byteArrayToInput = services->createInputModel();
    _modelsContext = services->modelsContext();
    _metaService = services->metaService();
    _inputEvaluator = services->evaluateInput();
    _inputToJson = services->iptBuilder();
    _playerManager = services->playerManager();
    _indexController = services->indexController();
    _indexToByteArray = services->indexToByteArray();
}

DCInput DCAddInputToModelsContext::add(const QByteArray &inputByteArray)
{
    auto input = _byteArrayToInput->convert(inputByteArray);
    _inputEvaluator->evaluate(input);
    updateModelsContext(input);
    _playerManager->updateScore(input);
    return input;
}

void DCAddInputToModelsContext::updateModelsContext(DCInput &input)
{
    auto meta = _metaService->meta();
    auto status = meta.status;
    auto winnerName = meta.winnerName;
    auto tournamentID = meta.tournamentId;
    auto index = _indexController->index();
    auto indexAsByteArray = _indexToByteArray->convert(index);
    auto inputAsByteArray = QJsonDocument(_inputToJson->create(input)).toJson();
    _modelsContext->addInput(tournamentID,inputAsByteArray);
    _modelsContext->updateTournamentIndex(tournamentID,indexAsByteArray);
    if(status == _metaService->WinnerDeclared)
        _modelsContext->setTournamentWinner(tournamentID,winnerName);
}

