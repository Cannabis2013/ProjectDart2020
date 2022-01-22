#include "dartssetipthint.h"
#include "InputsDbSLAs/igetinputs.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "InputModelsSLAs/idartsinput.h"

void DartsSetIptHint::setHidden(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const
{
    auto model = getInputs->get(meta,index,models);
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(HiddenHint);
}

void DartsSetIptHint::setVisible(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const
{
    auto model = getInputs->get(meta,index,models);
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(DisplayHint);
}
