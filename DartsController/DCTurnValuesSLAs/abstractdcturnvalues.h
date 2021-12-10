#ifndef ABSTRACTDCTURNVALUES_H
#define ABSTRACTDCTURNVALUES_H
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
class AbstractDCTurnValues
{
public:
    virtual DCTurnValues create(const DCIndex &index, const DCPlayer &player, const QString &finish) const = 0;
};
#endif // IBUILDTURNVALUES_H
