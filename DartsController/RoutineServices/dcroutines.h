#ifndef DCROUTINES_H
#define DCROUTINES_H
#include "DCInputSLAs/idcaddtomdsctx.h"
#include "ServiceRoutineSLAs/idcresetservices.h"
class DCRoutines
{
public:
    IDCAddToMdsCtx *addToModelsService() const {return _addToModelsCtx;}
    void setUpdateModelsContext(IDCAddToMdsCtx *service) {_addToModelsCtx = service;}
    IDCResetServices *resetServices() const {return _resetServices;}
    void setResetServices(IDCResetServices *newResetServices) {_resetServices = newResetServices;}
private:
    IDCAddToMdsCtx *_addToModelsCtx;
    IDCResetServices *_resetServices;
};
#endif // DCROUTINES_H
