#ifndef DCTURNVALUESSERVICES_H
#define DCTURNVALUESSERVICES_H
#include "DCTurnValuesSLAs/idccreateturnvalues.h"
#include "DCInputSLAs/idcinputadder.h"
class DCTurnValuesServices
{
public:
    IDCCreateTurnValues *turnValuesBuilder() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(IDCCreateTurnValues *service)
    {
        _turnValuesBuilder = service;
    }
private:
    IDCCreateTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
