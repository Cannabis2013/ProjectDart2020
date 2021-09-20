#ifndef DCMODELBUILDERSERVICES_H
#define DCMODELBUILDERSERVICES_H

#include <icreatedcturnvalues.h>
#include <idcplayermodelbuilder.h>
#include <idcindexesbuilder.h>
#include <idcmodelcreator.h>

#include <DartsController/idartsdeterminestatusbyid.h>

class DCBuilderServices
{
public:
    IDCModelCreator *inputModelBuilder() const
    {
        return _inputModelBuilder;
    }
    void setInputModelBuilder(IDCModelCreator *newDartsScoreBuilder)
    {
        _inputModelBuilder = newDartsScoreBuilder;
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
    ICreateDCTurnValues *turnValuesBuilder() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(ICreateDCTurnValues *newTurnValuesBuilder)
    {
        _turnValuesBuilder = newTurnValuesBuilder;
    }
    IDartsDetermineStatusById *determineStatusById() const
    {
        return _determineStatusById;
    }
    void setDetermineStatusById(IDartsDetermineStatusById *newDetermineStatusById)
    {
        _determineStatusById = newDetermineStatusById;
    }
private:
    IDCModelCreator* _inputModelBuilder;
    IDCIndexesBuilder* _dartsIndexesBuilderService;
    IDCPlayerModelBuilder* _playerBuilderService;
    IDartsDetermineStatusById* _determineStatusById;
    ICreateDCTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
