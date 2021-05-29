#ifndef IDARTSCONTROLLERINDEXMODELBUILDER_H
#define IDARTSCONTROLLERINDEXMODELBUILDER_H

template<typename TTurnIndexes,
         typename TControllerIndexService,
         typename TJsonFormat>
class IDartsControllerIndexesBuilder
{
public:
    typedef TJsonFormat JsonFormat;
    typedef TTurnIndexes TurnIndexes;
    typedef TControllerIndexService ControllerIndexService;
    virtual const TurnIndexes* buildControllerIndexesByJson(const JsonFormat& json) const = 0;
    virtual const TurnIndexes* buildControllerIndexesByIndexService(const ControllerIndexService* service) const = 0;
};

#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
