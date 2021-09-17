#ifndef DPCSERVICESPROVIDER_H
#define DPCSERVICESPROVIDER_H

#include "iunaryservice.h"
#include "idartsplayermodelbuilderservice.h"
#include "icreatedcturnvalues.h"
#include "idartsinputfinishes.h"
#include "idartsinputvalidator.h"
#include "idartscontrollermodelsservice.h"
#include "idcindexesbuilder.h"
#include "idcmodelcreator.h"
#include "idcindexservice.h"
#include "idcmetadata.h"
#include <idcmodelcreator.h>
#include "idcwinnerservice.h"

class DPCServicesProvider
{
public:
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
    IDCModelCreator* _pointModelBuilder;
    PlayerModelBuilder* _playerModelBuilder;
    IDCIndexesBuilder* _dartsIndexesBuilder;
    // Meta information
    IDCMetaData *_metaData;
    // Model manipulating services
    // Generate throwsuggestions
    IDartsInputFinishes *_stringSuggestionService = nullptr;
    // Validator service
    IDartsInputValidator* _inputEvaluator = nullptr;
    // Index service
    IDCIndexService* _indexService = nullptr;
    // Deterministic state services
    IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
    IDCWinnerService *_winnerService;
};
#endif // POINTCONTROLLERSERVICES_H
