#include "dartsinput.h"
#include "dartsinputbuilder.h"

IDartsInput *DartsInputBuilder::create() const
{
        auto input = new DartsInput;
        input->setId(QUuid::createUuid());
        return input;
}

