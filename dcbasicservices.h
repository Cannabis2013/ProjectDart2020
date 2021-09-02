#ifndef DCBASICSERVICES_H
#define DCBASICSERVICES_H

#include "idartsinputsuggestion.h"
#include "idcwinnerservice.h"
#include "idcmodeltojson.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idcindexesbuilder.h"
#include "idcplayermodelbuilder.h"
#include "igenericjsonbuilder.h"
#include "idartsmetadata.h"
#include <idcindexservice.h>
#include <ipointvalidator.h>
#include "idcinitializeindexes.h"
class DCBasicServices
{
public:
    typedef QVector<const DCContext::IDCModel*> DartsScores;
    typedef QVector<const DCContext::IDCPlayer*> DartsPlayers;
    IDCInitializeIndexes *initializeIndexes() const
    {
        return _initializeIndexes;
    }
    void setInitializeIndexes(IDCInitializeIndexes *newInitializeIndexes)
    {
        _initializeIndexes = newInitializeIndexes;
    }
    IDCWinnerService *winnerService() const
    {
        return _winnerService;
    }
    void setWinnerService(IDCWinnerService *newWinnerService)
    {
        _winnerService = newWinnerService;
    }
protected:
    //Services
    // Generate throwsuggestions
    IDartsInputSuggestion *_scoreLogisticInterface = nullptr;
    // Validator service
    IPointValidator* _inputEvaluator = nullptr;
    // Index service
    IDCIndexService* _indexService = nullptr;
    // Userscore service
    IDCWinnerService* _winnerService = nullptr;
    // Meta data service
    IDartsMetaData *_metaData;
private:
    IDCInitializeIndexes *_initializeIndexes;
};
#endif // DSCSERVICESPROVIDER_H
