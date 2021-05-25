#ifndef FILTERPREDICATEDEFAULTBUILDER_H
#define FILTERPREDICATEDEFAULTBUILDER_H

#include "ifilterpredicatebuilder.h"
#include "abstractdartsfilterpredicate.h"
#include "quuid.h"

namespace DartsModelsContext {
    class TournamentIdPredicate : public AbstractDartsFilterPredicate
    {
    public:
        TournamentIdPredicate(const QUuid& id):
            _id(id){}
        bool match(const IDartsInput* input) const override
        {
            return input->tournamentId() == _id;
        }
    private:
        const QUuid _id;
    };
    class PlayerIdIdPredicate : public AbstractDartsFilterPredicate
    {
    public:
        PlayerIdIdPredicate(const QUuid& id):
            _id(id){}
        bool match(const IDartsInput* input) const override
        {
            return input->playerId() == _id;
        }
    private:
        const QUuid _id;
    };
    class InputHintIdPredicate : public AbstractDartsFilterPredicate
    {
    public:
        InputHintIdPredicate(const int& hint):
            _hint(hint){}
        bool match(const IDartsInput* input) const override
        {
            return input->hint() == _hint;
        }
    private:
        const int _hint;
    };
    class InputRoundIndexPredicate : public AbstractDartsFilterPredicate
    {
    public:
        InputRoundIndexPredicate(const int& roundIndex):
            _roundIndex(roundIndex){}
        bool match(const IDartsInput* input) const override
        {
            return input->roundIndex() == _roundIndex;
        }
    private:
        const int _roundIndex;
    };
    class FilterPredicateDefaultBuilder :
            public IFilterPredicateBuilder<AbstractDartsFilterPredicate,QUuid>
    {
    public:
        AbstractDartsFilterPredicate *buildFilterByTournamentIdPredicate(const QUuid &id) const override;
        AbstractDartsFilterPredicate *buildFilterByPlayerIdPredicate(const QUuid &id) const override;
        AbstractDartsFilterPredicate *buildFilterByInputHintPredicate(const int &hint) const override;
        AbstractDartsFilterPredicate *buildFilterByRoundIndexPredicate(const int &roundIndex) const override;
    };
}

#endif // FILTERPREDICATEDEFAULTBUILDER_H
