#ifndef DARTSINPUTBUILDER_H
#define DARTSINPUTBUILDER_H
#include "InputsDbSLAs/idartsinputbuilder.h"
#include "InputServices/dartsinput.h"
class DartsInputBuilder : public IDartsInputBuilder
{
    // IDartsInputBuilder interface
public:
    virtual IDartsInput *create() const override
    {
        auto input = new DartsInput;
        input->setId(QUuid::createUuid());
        return input;
    }
};




#endif // DARTSINPUTJSONEXTRACTOR_H
