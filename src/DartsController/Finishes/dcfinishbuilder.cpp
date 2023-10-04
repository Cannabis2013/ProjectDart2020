#include "dcfinishbuilder.h"

DCFinishBuilder::DCFinishBuilder()
{
    auto allTargetRows = _constructRow->constructRows();
    _dbContext->add(allTargetRows);
}

QString DCFinishBuilder::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

QString DCFinishBuilder::getTargetRow(const int &turnIndex, const int &remainingScore) const
{
        auto i = turnIndex;
        try {
        auto list = _dbContext->model(i);
        auto valuesAtKey = list->values(remainingScore);
        auto count = valuesAtKey.count();
        if (count == 0)
            return QString();
        return valuesAtKey.at(0);
        }  catch (...) {
                return QString();
        }
}
