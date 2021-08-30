#ifndef DPCSERVICESPROVIDER_H
#define DPCSERVICESPROVIDER_H

#include "iunaryservice.h"
#include "idartsplayermodelbuilderservice.h"
#include "icreatedpcturnvalues.h"
#include "idartsinputsuggestion.h"
#include "IPointCalculatorService.h"
#include "ipointvalidator.h"
#include "idartscontrollermodelsservice.h"
#include "idscindexesbuilder.h"
#include "idcmodelcreator.h"
#include "idartspointindexservice.h"
#include "iaddtotalscoretodartspoint.h"
#include "idartsmetadata.h"
#include <idpcindexesbuilder.h>
#include <idpcmodelcreator.h>
#include "idcwinnerservice.h"

class DPCServicesProvider
{
public:
    typedef DPCContext::ICreateDPCTurnValues TurnValueBuilderService;
    typedef DPCContext::IDartsControllerModelsService<DPCContext::IDPCModel,QString,QUuid> ControllerModelsService;
    typedef IPointCalculatorService<DPCContext::IDPCModel> ScoreCalculatorService;
    typedef DPCContext::IDartsPlayerModelBuilderService<DCContext::IDCPlayer,QString,QUuid,QByteArray> PlayerModelBuilder;
    IDCWinnerService *winnerService() const
    {
        return _winnerService;
    }
    void setWinnerService(IDCWinnerService *newWinnerService)
    {
        _winnerService = newWinnerService;
    }
protected:
    // Services
    // Builder Services
    TurnValueBuilderService* _turnValuesBuilder;
    IDPCModelCreator* _pointModelBuilder;
    PlayerModelBuilder* _playerModelBuilder;
    IDPCIndexesBuilder* _dartsIndexesBuilder;
    ControllerModelsService* _controllerModels;
    // Meta information
    IDartsMetaData *_metaData;
    // Model manipulating services
    IAddTotalScoreToDartsPoint *_addTotalScoreToPointModel;
    // Calculate score
    ScoreCalculatorService* _calculateScoreByPointInput = nullptr;
    // Generate throwsuggestions
    IDartsInputSuggestion *_stringSuggestionService = nullptr;
    // Validator service
    IPointValidator* _inputEvaluator = nullptr;
    // Index service
    IDartsPointIndexService* _indexService = nullptr;
    // Deterministic state services
    IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
    IDCWinnerService *_winnerService;
};
#endif // POINTCONTROLLERSERVICES_H
