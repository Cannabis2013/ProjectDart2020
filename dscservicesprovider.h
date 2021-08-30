#ifndef DSCSERVICESPROVIDER_H
#define DSCSERVICESPROVIDER_H

#include "idartsinputsuggestion.h"
#include "iscorevalidator.h"
#include "idsindexservice.h"
#include "idcwinnerservice.h"
#include "idsjsonbuilder.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idscmodel.h"
#include "dartsscoreturnvalues.h"
#include "iternaryservice.h"
#include "idsmodelsbuilder.h"
#include "idscindexesbuilder.h"
#include "idscmodelbuilder.h"
#include "ibytearrayjsonmerger.h"
#include "icreatedscturnvalues.h"
#include "igenericjsonbuilder.h"
#include "imhjsonextractor.h"
#include "idartsmetadata.h"

class DSCServicesProvider
{
public:
    typedef QVector<const DSCContext::IDSCModel*> DartsScores;
    typedef QVector<const DCContext::IDCPlayer*> DartsPlayers;
    typedef IDSCModelBuilder<DCContext::IDCPlayer,QUuid,QString,QByteArray> PlayerBuilderService;
protected:
    //Services
    // Generate throwsuggestions
    IDartsInputSuggestion *_scoreLogisticInterface = nullptr;
    // Validator service
    IScoreValidator* _inputEvaluator = nullptr;
    // Index service
    IDSIndexService* _indexService = nullptr;
    // Userscore service
    IDCWinnerService* _winnerService = nullptr;
    // Builder services
    IDSModelsBuilder* _dartsScoreBuilder;
    IDSCIndexesBuilder* _dartsIndexesBuilderService;
    PlayerBuilderService* _playerBuilderService;
    IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
    ICreateDSCTurnValues* _turnValuesBuilder;
    // Meta data service
    IDartsMetaData *_metaData;
};

#endif // DSCSERVICESPROVIDER_H
