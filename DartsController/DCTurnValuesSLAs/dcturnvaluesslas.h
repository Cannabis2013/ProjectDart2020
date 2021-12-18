#ifndef DCTURNVALUESSLAS_H
#define DCTURNVALUESSLAS_H
#include "DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DCInputSLAs/abstractdcinputbuilder.h"
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
