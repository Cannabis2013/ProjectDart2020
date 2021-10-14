#include "DartsController/DCFinishesServices/dcinputfinishes.h"

DCInputFinishes *DCInputFinishes::createInstance(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext)
{
    return new DCInputFinishes(constructRows,dbContext);
}

DCInputFinishes::DCInputFinishes(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext):
    _dbContext(dbContext),
    _constructRow(constructRows)
{
    auto allTargetRows = constructTargetRows()->constructRows();
    this->dbContext()->add(allTargetRows);
}

QString DCInputFinishes::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

IDartsFinishesDb *DCInputFinishes::dbContext() const
{
    return _dbContext;
}

void DCInputFinishes::setDbContext(IDartsFinishesDb *service)
{
    _dbContext = service;
}

QString DCInputFinishes::getTargetRow(const int &turnIndex, const int &remainingScore) const
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

IDartsCreateFinishes *DCInputFinishes::constructTargetRows() const
{
    return _constructRow;
}

void DCInputFinishes::setConstructRow(IDartsCreateFinishes *service)
{
    _constructRow = service;
}
