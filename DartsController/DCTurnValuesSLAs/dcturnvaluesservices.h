#ifndef DCTURNVALUESSERVICES_H
#define DCTURNVALUESSERVICES_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCPlayerSLAs/idcplayermodelbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexesbuilder.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"

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
private:
    ICreateDCTurnValues* _turnValuesBuilder;
    IDCTurnValuesToJson *_turnValuesToJson;
};
#endif // DCMODELBUILDERSERVICES_H
