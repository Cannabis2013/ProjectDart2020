#ifndef DCMODELBUILDERSERVICES_H
#define DCMODELBUILDERSERVICES_H

#include <icreatedcturnvalues.h>
#include <idcplayermodelbuilder.h>
#include <idcindexesbuilder.h>
#include <iunaryservice.h>
#include <idcmodelcreator.h>

class DCBuilderServices
{
public:
    IDCModelCreator *inputModelBuilder() const
    {
        return _scoreModelBuilder;
    }
    void setInputModelBuilder(IDCModelCreator *newDartsScoreBuilder)
    {
        _scoreModelBuilder = newDartsScoreBuilder;
    }

    IDCIndexesBuilder *indexesBuilder() const
    {
        return _dartsIndexesBuilderService;
    }
    void setIndexesBuilder(IDCIndexesBuilder *newDartsIndexesBuilderService)
    {
        _dartsIndexesBuilderService = newDartsIndexesBuilderService;
    }

    IDCPlayerModelBuilder *playerBuilder() const
    {
        return _playerBuilderService;
    }
    void setPlayerBuilderService(IDCPlayerModelBuilder *newPlayerBuilderService)
    {
        _playerBuilderService = newPlayerBuilderService;
    }

    IUnaryService<const QUuid &, int> *determineControllerStateByWinnerId() const
    {
        return _determineControllerStateByWinnerId;
    }
    void setDetermineControllerStateByWinnerId(IUnaryService<const QUuid &, int> *newDetermineControllerStateByWinnerId)
    {
        _determineControllerStateByWinnerId = newDetermineControllerStateByWinnerId;
    }

    ICreateDCTurnValues *turnValuesBuilder() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(ICreateDCTurnValues *newTurnValuesBuilder)
    {
        _turnValuesBuilder = newTurnValuesBuilder;
    }
private:
    IDCModelCreator* _scoreModelBuilder;
    IDCIndexesBuilder* _dartsIndexesBuilderService;
    IDCPlayerModelBuilder* _playerBuilderService;
    IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
    ICreateDCTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
