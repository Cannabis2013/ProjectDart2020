#include "dartsinputstrimmer.h"

DartsInputsTrimmer::DartsInputsTrimmer(IDartsInputs* inputs, IDartsIndexes* indexes)
    : _inputs(inputs)
    , _indexes(indexes)
{
}

void DartsInputsTrimmer::trimInputs()
{
        auto throwIndex = _indexes->index().throwIndex();
        _inputs->remove([throwIndex](const Input& input) {
                return input.throwIndex() < throwIndex;
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
