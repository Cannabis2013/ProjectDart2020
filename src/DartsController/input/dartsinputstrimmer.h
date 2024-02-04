#ifndef DARTSINPUTSTRIMMER_H
#define DARTSINPUTSTRIMMER_H

#include "idartsinputtrimmer.h"

class IDartsIndexes;
class IDartsInputs;

class DartsInputsTrimmer : public IDartsInputTrimmer
{
public:
        DartsInputsTrimmer(IDartsInputs* inputs, IDartsIndexes* indexes);

        void trimInputs() override;
        void removeTurnInputs() override;

private:
        IDartsInputs* const _inputs;
        IDartsIndexes* const _indexes;
};

#endif // DARTSINPUTSTRIMMER_H
