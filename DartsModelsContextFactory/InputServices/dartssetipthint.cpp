#include "dartssetipthint.h"
#include "InputsDbSLAs/igetinputs.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "InputModelsSLAs/idartsinput.h"

void DartsSetIptHint::setHidden(Index *index, const Meta &meta, const Inputs &models, GetInputs *getInputs) const
{
    auto model = getInputs->get(meta,index,models);
    if(model != nullptr)
        setHint(model,HiddenHint);
}

void DartsSetIptHint::setVisible(Index *index, const Meta &meta, const Inputs &models, GetInputs *getInputs) const
{
    auto model = getInputs->get(meta,index,models);
    if(model != nullptr)
        setHint(model,DisplayHint);
}

void DartsSetIptHint::setVisible(Input *input) const
{
    setHint(input,DisplayHint);
}

void DartsSetIptHint::setHint(Input *model, const ModelDisplayHint &hint) const
{
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(hint);
}
