#ifndef DCTURNVALUESSERVICES_H
#define DCTURNVALUESSERVICES_H

#include "DCTurnValuesSLAs/idcturnvaluestojson.h"
#include "DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DCPlayerSLAs/idcplayermodelbuilder.h"
#include "DCIndexSLAs/idcindexesbuilder.h"
#include "DCInputSLAs/idccreateinputmodel.h"

class DCTurnvaluesServices
{
public:
    ICreateDCTurnValues *turnValuesBuilder() const
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
