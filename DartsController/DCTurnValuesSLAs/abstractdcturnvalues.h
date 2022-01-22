#ifndef ABSTRACTDCTURNVALUES_H
#define ABSTRACTDCTURNVALUES_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "DCScoresSLAs/absdcplayersctx.h"
#include "DCFinishesSLAs/idcfinishbuilder.h"
#include "Models/dcturnvalues.h"
class AbstractDCTurnValues
{
public:
    virtual DCTurnValues create(const DCIndex &index, const DCPlayer &player, const QString &finish) const = 0;
};
#endif // IBUILDTURNVALUES_H
