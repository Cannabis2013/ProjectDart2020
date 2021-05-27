#ifndef IDARTSCONTROLLERINDEXMODELBUILDER_H
#define IDARTSCONTROLLERINDEXMODELBUILDER_H

namespace DartsPointSingleAttemptContext {
    template<typename TTurnIndexes,
             typename TControllerIndexService,
             typename TJsonFormat>
    class IDartsControllerIndexesModelBuilder
    {
    public:
        typedef TJsonFormat JsonFormat;
        typedef TTurnIndexes TurnIndexes;
        typedef TControllerIndexService ControllerIndexService;
        virtual const TurnIndexes* assembleDartsControllerIndexesByJson(const JsonFormat& json) const = 0;
        virtual const TurnIndexes* buildTurnIndexesByValues(const ControllerIndexService*) const = 0;
    };
}

#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
