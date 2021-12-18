#include "dcfinishbuilder.h"

DCFinishBuilder *DCFinishBuilder::createInstance(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext)
{
    return new DCFinishBuilder(constructRows,dbContext);
}

DCFinishBuilder::DCFinishBuilder(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext):
    _dbContext(dbContext),
    _constructRow(constructRows)
{
    auto allTargetRows = constructTargetRows()->constructRows();
    this->dbContext()->add(allTargetRows);
}

QString DCFinishBuilder::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

IDartsFinishesDb *DCFinishBuilder::dbContext() const
{
    return _dbContext;
}

void DCFinishBuilder::setDbContext(IDartsFinishesDb *service)
{
    _dbContext = service;
}

QString DCFinishBuilder::getTargetRow(const int &turnIndex, const int &remainingScore) const
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

IDartsCreateFinishes *DCFinishBuilder::constructTargetRows() const
{
    return _constructRow;
}

void DCFinishBuilder::setConstructRow(IDartsCreateFinishes *service)
{
    _constructRow = service;
}
