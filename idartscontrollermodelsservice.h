#ifndef IDARTSCONTROLLERPOINTSERVICE_H
#define IDARTSCONTROLLERPOINTSERVICE_H

namespace DartsPointControllerContext {
    template<typename TModelInterface, typename TString, typename TUuid>
    class IDartsControllerModelsService
    {
    public:
        typedef TString StringFormat;
        typedef TUuid IdFormat;
        typedef TModelInterface DartsModelInterface;
        virtual void addPlayerIdToModel(const DartsModelInterface* model, const IdFormat& id) const = 0;
        virtual void addAccumulatedScoreToModel(const DartsModelInterface* model, const int& score) const = 0;
    };
}

#endif // IDARTSCONTROLLERPOINTSERVICE_H
