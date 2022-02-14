#include "dcinputbuilder.h"
#include <Models/dcinput.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

DCInputBuilder::Model DCInputBuilder::create() const
{
    return DCInput();
}

DCInputBuilder::Model DCInputBuilder::create(const QString &name, const int &remainingScore) const
{
    DCInput input;
    input.remScore = remainingScore;
    input.playerName = name;
    return input;
}
