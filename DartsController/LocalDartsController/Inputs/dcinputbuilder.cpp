#include "dcinputbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <DartsController/Contracts/Models/dcinput.h>

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
