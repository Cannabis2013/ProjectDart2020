#ifndef DARTSINPUTSTRIMMER_H
#define DARTSINPUTSTRIMMER_H

#include "idartsinputtrimmer.h"

class ServiceCollection;
class IDartsIndexes;
class IDartsInputs;

class DartsInputsTrimmer : public IDartsInputTrimmer
{
public:
        DartsInputsTrimmer(ServiceCollection* services);

        void trimInputs() override;
        void removeTurnInputs() override;

private:
        IDartsInputs* const _inputs;
        IDartsIndexes* const _indexes;
};

#endif // DARTSINPUTSTRIMMER_H
