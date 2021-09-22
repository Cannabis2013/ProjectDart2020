#ifndef DCTURNVALUESSERVICES_H
#define DCTURNVALUESSERVICES_H

#include "icreatedcturnvalues.h"
#include "idcplayermodelbuilder.h"
#include "DCIndexSLA/idcindexesbuilder.h"
#include "idccreateinputmodel.h"

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
private:
    ICreateDCTurnValues* _turnValuesBuilder;
};
#endif // DCMODELBUILDERSERVICES_H
