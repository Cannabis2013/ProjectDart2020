#ifndef DCTURNVALUESSLAS_H
#define DCTURNVALUESSLAS_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCPlayerSLAs/idcplayerbuilder.h"
#include "DartsController/DCIndexSLAs/idcinputindexbuilder.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"

class DCTurnvaluesSLAs
{
public:
    ICreateDCTurnValues *turnValuesBuilder() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(ICreateDCTurnValues *service)
    {
        _turnValuesBuilder = service;
    }
private:
    ICreateDCTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
