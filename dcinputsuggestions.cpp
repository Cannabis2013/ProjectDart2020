#include "dcinputsuggestions.h"

DCInputSuggestions *DCInputSuggestions::createInstance(IDartsConstructRow *constructRows, IDCLogisticDb *dbContext)
{
    return new DCInputSuggestions(constructRows,dbContext);
}

DCInputSuggestions::DCInputSuggestions(IDartsConstructRow *constructRows, IDCLogisticDb *dbContext):
    _dbContext(dbContext),
    _constructRow(constructRows)
{
    auto allTargetRows = constructTargetRows()->constructRows();
    this->dbContext()->add(allTargetRows);
}

QString DCInputSuggestions::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

IDCLogisticDb *DCInputSuggestions::dbContext() const
{
    return _dbContext;
}

void DCInputSuggestions::setDbContext(IDCLogisticDb *service)
{
    _dbContext = service;
}

QString DCInputSuggestions::getTargetRow(const int &turnIndex, const int &remainingScore) const
{
    auto i = turnIndex;
    try {
        auto list = dbContext()->model(i);
        auto valuesAtKey = list->values(remainingScore);
        auto count = valuesAtKey.count();
        if(count == 0)
            return QString();
        auto S = valuesAtKey.at(0);
        return S;
    }  catch (...) {
        return QString();
    }
}

IDartsConstructRow *DCInputSuggestions::constructTargetRows() const
{
    return _constructRow;
}

void DCInputSuggestions::setConstructRow(IDartsConstructRow *newConstructRow)
{
    _constructRow = newConstructRow;
}
