#include "filterpredicatedefaultbuilder.h"

DartsModelsContext::AbstractDartsFilterPredicate *DartsModelsContext::FilterPredicateDefaultBuilder::buildFilterByTournamentIdPredicate(const QUuid &id) const
{
    auto t = new TournamentIdPredicate(id);
    return t;
}

DartsModelsContext::AbstractDartsFilterPredicate *DartsModelsContext::FilterPredicateDefaultBuilder::buildFilterByPlayerIdPredicate(const QUuid &id) const
{
    auto t = new PlayerIdIdPredicate(id);
    return t;
}

DartsModelsContext::AbstractDartsFilterPredicate *DartsModelsContext::FilterPredicateDefaultBuilder::buildFilterByInputHintPredicate(const int &hint) const
{
    auto t = new InputHintIdPredicate(hint);
    return t;
}

DartsModelsContext::AbstractDartsFilterPredicate *DartsModelsContext::FilterPredicateDefaultBuilder::buildFilterByRoundIndexPredicate(const int &roundIndex) const
{
    auto t = new InputRoundIndexPredicate(roundIndex);
    return t;
}
