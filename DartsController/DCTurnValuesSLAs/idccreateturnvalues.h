#ifndef IDCCREATETURNVALUES_H
#define IDCCREATETURNVALUES_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "DCScoresSLAs/absdcplayersctx.h"
#include "DCFinishesSLAs/idcfinishbuilder.h"
#include "Models/dcturnvalues.h"
class IDCCreateTurnValues
{
public:
    virtual DCTurnValues create() const = 0;
};
#endif // IBUILDTURNVALUES_H
