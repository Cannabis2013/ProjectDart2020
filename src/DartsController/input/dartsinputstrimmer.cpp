#include "dartsinputstrimmer.h"

#include "idartsinputs.h"
#include <src/DartsController/indexes/idartsindexes.h>

DartsInputsTrimmer::DartsInputsTrimmer(IDartsInputs* inputs,
    IDartsIndexes* indexes)
    : _inputs(inputs)
    , _indexes(indexes)
{
}

void DartsInputsTrimmer::trimInputs()
{
        auto index = _indexes->index();
        _inputs->remove([index](const Input& input) {
                return input.throwIndex() < index.throwIndex();
        });
}

void DartsInputsTrimmer::removeTurnInputs()
{
        auto indexModel = _indexes->index();
        auto index = indexModel.throwIndex() - indexModel.turnIndex();
        _inputs->remove([index](const Input& input) {
                return input.throwIndex() < index;
        });
}
