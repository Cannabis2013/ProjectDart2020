#ifndef IBUILDCONTROLLERTURNVALUES_H
#define IBUILDCONTROLLERTURNVALUES_H

template<typename TModelInterface,typename TIndexesService,
         typename TInputService, typename TLogisticService>
class IBuildControllerTurnValues
{
public:
    typedef TModelInterface Model;
    typedef TIndexesService IndexService;
    typedef TInputService InputService;
    typedef TLogisticService LogisticService;

    virtual const Model* createTurnValues(const IndexService* indexService,
                                                    const InputService* playerScoreService,
                                                    const LogisticService* logisticService) const = 0;
};

#endif // IBUILDCONTROLLERTURNVALUES_H
