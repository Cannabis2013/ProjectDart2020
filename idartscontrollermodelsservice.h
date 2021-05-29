#ifndef IDARTSCONTROLLERPOINTSERVICE_H
#define IDARTSCONTROLLERPOINTSERVICE_H

namespace DartsPointSingleAttemptContext {
    template<typename TModelInterface, typename TString, typename TUuid>
    class IDartsControllerModelsService
    {
    public:
        typedef TString StringFormat;
        typedef TUuid IdFormat;
        typedef TModelInterface DartsModelInterface;
        virtual void addTournamentIdToModel(const DartsModelInterface* model, const IdFormat& id) const = 0;
        virtual void addPlayerIdToModel(const DartsModelInterface* model, const IdFormat& id) const = 0;
        virtual void addPlayerNameToModel(const DartsModelInterface* model, const StringFormat& name) const = 0;
        virtual void addAccumulatedScoreToModel(const DartsModelInterface* model, const int& score) const = 0;
    };
}

#endif // IDARTSCONTROLLERPOINTSERVICE_H
