#ifndef POINTCONTROLLERSERVICEPROVIDER_H
#define POINTCONTROLLERSERVICEPROVIDER_H

#include "iunaryservice.h"
/*
 * Services
 */
#include "iaddtotalscoretodartsinputsjson.h"
#include "iaddplayernamestojsonentity.h"
#include "idartsplayermodelbuilderservice.h"
#include "ibuilddartspointturnvalues.h"
#include "ibytearrayjsonmerger.h"
#include "idartsinputsuggestion.h"
#include "IPointCalculatorService.h"
#include "ipointvalidator.h"
#include "iplayerpointservice.h"
#include "idartscontrollermodelsservice.h"
#include "idartscontrollerindexesbuilder.h"
#include "idartscontrollerpointbuilder.h"
#include "idartspointindexservice.h"
#include "iaddtotalscoretodartspoint.h"
#include "idartsmetadata.h"
// Json services
#include "iqtjsonbuilder.h"
#include "iqtjsonextractor.h"
#include "idartscontrollerjsonservice.h"
#include "igetordereddartspointsbyjson.h"
#include "idartsinputstojson.h"

namespace DartsPointControllerContext {
    class PointControllerServiceProvider
    {
    public:
        // Commonly used models typedefinitions
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
        typedef IDartsControllerPlayer<QUuid,QString,QByteArray> ControllerPlayer;
        typedef IDartsControllerpointBuilder<IControllerPoint,QByteArray,QUuid,QString> ControllerPointBuilder;
        // Build darts indexes by json service
        typedef IDartsPointControllerIndexes<QByteArray> DartsIndexes;
        typedef IDartsPointIndexService<DartsIndexes> DartsIndexService;
        typedef IDartsControllerIndexesBuilder<DartsIndexes,DartsIndexService,QByteArray> IIndexesBuilderService;
        typedef IDartscontrollerJsonService<IControllerPoint,DartsIndexes,QByteArray,QUuid> DartsJsonService;
        typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerPointService;
        typedef IDartsInputSuggestion<QString> LogisticService;
        typedef IBuildDartsPointTurnValues TurnValueBuilderService;
        typedef IDartsControllerModelsService<IDartsControllerPoint<QUuid,QString,QByteArray>,QString,QUuid> ControllerModelsService;
        typedef IPointCalculatorService<IControllerPoint> ScoreCalculatorService;
        typedef IDartsPlayerModelBuilderService<ControllerPlayer,QString,QUuid,QByteArray> PlayerModelBuilder;
        typedef IDartsInputsToJson<IControllerPoint,QByteArray> DartsInputsToJsonService;
        typedef IAddTotalScoreToDartsInputsJson<QByteArray> AddTotalScoresToJsonEntities;
        typedef IAddPlayerNamesToJsonEntity<QByteArray> AddPlayerNamesToJsonEntities;
    protected:
        // Services
        // Builder Services
        TurnValueBuilderService* _turnValuesBuilder;
        ControllerPointBuilder* _pointModelBuilder;
        PlayerModelBuilder* _playerModelBuilder;
        IIndexesBuilderService* _dartsIndexesBuilder;
        ControllerModelsService* _controllerModels;
        // Meta information
        IDartsMetaData *_metaData;
        // Model manipulating services
        IAddTotalScoreToDartsPoint *_addTotalScoreToPointModel;
        // Json
        IQtJsonBuilder *_jsonBuilder;
        IQtJsonExtractor *_jsonExtractor;
        IGetOrderedDartsPointByJson *_getOrderedDartsPointsByJson;
        AddTotalScoresToJsonEntities *_addTotalScoresToDartsModelsJson;
        DartsInputsToJsonService * _dartsPointsToJson;
        IByteArrayJsonMerger *_jsonMerger;
        AddPlayerNamesToJsonEntities *_addPlayerNamesToDartsModelsJson;
        // Calculate score
        ScoreCalculatorService* _calculateScoreByPointInput = nullptr;
        // Generate throwsuggestions
        LogisticService *_stringSuggestionService = nullptr;
        // Validator service
        IPointValidator* _inputEvaluator = nullptr;
        // Index service
        DartsIndexService* _indexService = nullptr;
        // Userscore service
        PlayerPointService* _inputService = nullptr;
        // Deterministic state services
        IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
    };
}

#endif // POINTCONTROLLERSERVICES_H
