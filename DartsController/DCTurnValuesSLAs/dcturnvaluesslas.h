#ifndef DCTURNVALUESSLAS_H
#define DCTURNVALUESSLAS_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCPlayerSLAs/idcplayermodelbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexesbuilder.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"
#include "iDCTurnValJsonKeys.h"

class DCTurnvaluesSLAs
{
public:
    ICreateDCTurnValues *createTurnValues() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(ICreateDCTurnValues *service)
    {
        _turnValuesBuilder = service;
    }
    IDCTurnValuesToJson *turnValuesToJson() const
    {
        return _turnValuesToJson;
    }
    void setTurnValuesToJsonService(IDCTurnValuesToJson *service)
    {
        _turnValuesToJson = service;
    }
    IDCTurnValJsonKeys *turnValKeys() const
    {
        return _turnValKeys;
    }
    void setTurnValKeys(IDCTurnValJsonKeys *service)
    {
        _turnValKeys = service;
    }

private:
    ICreateDCTurnValues* _turnValuesBuilder;
    IDCTurnValuesToJson *_turnValuesToJson;
    IDCTurnValJsonKeys *_turnValKeys;
};
#endif // DCMODELBUILDERSERVICES_H
