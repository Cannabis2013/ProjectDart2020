#ifndef DCTURNVALUESSERVICES_H
#define DCTURNVALUESSERVICES_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCPlayerSLAs/idcplayermodelbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexesbuilder.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"
#include "iDCTurnValJsonKeys.h"

class DCTurnvaluesServices
{
public:
    ICreateDCTurnValues *createTurnValues() const
    {
        return _turnValuesBuilder;
    }
    void setTurnValuesBuilder(ICreateDCTurnValues *newTurnValuesBuilder)
    {
        _turnValuesBuilder = newTurnValuesBuilder;
    }
    IDCTurnValuesToJson *turnValuesToJson() const
    {
        return _turnValuesToJson;
    }
    void setTurnValuesToJsonService(IDCTurnValuesToJson *newTurnValuesToJson)
    {
        _turnValuesToJson = newTurnValuesToJson;
    }
    IDCTurnValJsonKeys *turnValKeys() const
    {
        return _turnValKeys;
    }
    void setTurnValKeys(IDCTurnValJsonKeys *newTurnValKeys)
    {
        _turnValKeys = newTurnValKeys;
    }

private:
    ICreateDCTurnValues* _turnValuesBuilder;
    IDCTurnValuesToJson *_turnValuesToJson;
    IDCTurnValJsonKeys *_turnValKeys;
};
#endif // DCMODELBUILDERSERVICES_H
