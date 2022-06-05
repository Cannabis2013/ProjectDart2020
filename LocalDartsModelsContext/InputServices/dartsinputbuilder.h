#ifndef DARTSINPUTBUILDER_H
#define DARTSINPUTBUILDER_H

#include <DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h>

class DartsInputBuilder : public IDartsInputBuilder
{
    // IDartsInputBuilder interface
public:
    virtual IDartsInput *create() const override;
};




#endif // DARTSINPUTJSONEXTRACTOR_H
