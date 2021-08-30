#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H

template<typename TModel,typename TIndexesService,
         typename TInputService, typename TLogisticService>
class ICreateDCTurnValues
{
public:
    virtual TModel createTurnValues(TIndexesService indexService,
                                    TInputService playerScoreService,
                                    TLogisticService logisticService) const = 0;
};

#endif // IBUILDCONTROLLERTURNVALUES_H
