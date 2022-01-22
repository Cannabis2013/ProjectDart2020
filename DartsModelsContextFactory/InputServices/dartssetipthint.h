#ifndef DARTSSETIPTHINT_H
#define DARTSSETIPTHINT_H
#include "InputSLAs/IDartsSetIptHint.h"
class DartsMetaModel;
class IDartsIndex;
class QUuid;
template<typename T>
class IModel;
class DartsSetIptHint : public IDartsSetIptHint<IModel<QUuid>,IDartsIndex,DartsMetaModel>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual void setHidden(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const override;
    virtual void setVisible(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const override;
};
#endif // DARTSSETIPTHINT_H
