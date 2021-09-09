#ifndef DCBASICSERVICES_H
#define DCBASICSERVICES_H

#include "idartsinputsuggestion.h"
#include "idcwinnerservice.h"
#include "idcinputstojson.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idcindexesbuilder.h"
#include "idcplayermodelbuilder.h"
#include "idartsmetadata.h"
#include <idcindexservice.h>
#include <idartsinputvalidator.h>
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
    IDartsMetaData *metaData() const
    {
        return _metaData;
    }
    void setMetaData(IDartsMetaData *newMetaData)
    {
        _metaData = newMetaData;
    }
    IDartsInputValidator *inputEvaluator() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(IDartsInputValidator *newInputEvaluator)
    {
        _inputEvaluator = newInputEvaluator;
    }
    IDartsInputSuggestion *scoreLogisticInterface() const
    {
        return _scoreLogisticInterface;
    }
    void setScoreLogisticInterface(IDartsInputSuggestion *newScoreLogisticInterface)
    {
        _scoreLogisticInterface = newScoreLogisticInterface;
    }
private:
    IDartsInputSuggestion *_scoreLogisticInterface = nullptr;
    IDCWinnerService *_winnerService = nullptr;
    IDartsInputValidator* _inputEvaluator = nullptr;
    IDartsMetaData *_metaData;
    IDCInitializeIndexes *_initializeIndexes;
};
#endif // DSCSERVICESPROVIDER_H
