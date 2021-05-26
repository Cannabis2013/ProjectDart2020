#ifndef IDARTSCONTROLLERPOINTSERVICE_H
#define IDARTSCONTROLLERPOINTSERVICE_H

namespace DartsPointSingleAttemptContext {
    template<typename TModelInterface, typename TString>
    class IDartsControllerModelsService
    {
    public:
        typedef TModelInterface DartsModelInterface;

        virtual const DartsModelInterface* addPlayerNameToModel(const DartsModelInterface* model, const TString& name) const = 0;
        virtual const DartsModelInterface* addPlayerScoreToModel(const DartsModelInterface* model, const int& score) const = 0;
    };
}

#endif // IDARTSCONTROLLERPOINTSERVICE_H
