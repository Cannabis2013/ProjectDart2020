#ifndef DCBASICSERVICES_H
#define DCBASICSERVICES_H
#include "idartsinputfinishes.h"
#include "idcwinnerservice.h"
#include "idcinputstojson.h"
#include "idcindexesbuilder.h"
#include "idcplayermodelbuilder.h"
#include "idcinitialscore.h"
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
    void setInitializeIndexes(IDCInitializeIndexes *service)
    {
        _initializeIndexes = service;
    }
    IDCWinnerService *winnerService() const
    {
        return _winnerService;
    }
    void setWinnerService(IDCWinnerService *service)
    {
        _winnerService = service;
    }
    IDartsInputValidator *inputEvaluator() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(IDartsInputValidator *service)
    {
        _inputEvaluator = service;
    }
    IDartsInputFinishes *suggestFinishes() const
    {
        return _suggestFinishes;
    }
    void setSuggestFinishes(IDartsInputFinishes *service)
    {
        _suggestFinishes = service;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    IDartsInputValidator* _inputEvaluator = nullptr;
    IDCWinnerService *_winnerService = nullptr;
    IDCInitializeIndexes *_initializeIndexes;
};
#endif // DSCSERVICESPROVIDER_H
