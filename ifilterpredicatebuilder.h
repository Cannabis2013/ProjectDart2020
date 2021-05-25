#ifndef IFILTERPREDICATEBUILDER_H
#define IFILTERPREDICATEBUILDER_H


namespace DartsModelsContext {
    template<typename TPredicate, typename TUuid>
    class IFilterPredicateBuilder
    {
    public:
        virtual TPredicate* buildFilterByTournamentIdPredicate(const TUuid& id) const = 0;
        virtual TPredicate* buildFilterByPlayerIdPredicate(const TUuid& id) const = 0;
        virtual TPredicate* buildFilterByInputHintPredicate(const int& hint) const = 0;
        virtual TPredicate* buildFilterByRoundIndexPredicate(const int& roundIndex) const = 0;
    };
}

#endif // IFILTERPREDICATEBUILDER_H
