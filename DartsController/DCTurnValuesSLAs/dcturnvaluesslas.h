#ifndef DCTURNVALUESSLAS_H
#define DCTURNVALUESSLAS_H
#include "DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
class DCTurnvaluesSLAs
{
public:
    AbstractDCTurnValues *turnValuesBuilder() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(AbstractDCTurnValues *service)
    {
        _turnValuesBuilder = service;
    }
private:
    AbstractDCTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
