#ifndef DMCINPUTSLAS_H
#define DMCINPUTSLAS_H

#include "DartsModelsContext/DMCInputSLAs/icountinputmodels.h"
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexestojson.h"
#include "DartsModelsContext/DMCIndexesSLAs/idartscreateindexes.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinputmodelstojson.h"
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinputsethint.h"
#include "DartsModelsContext/DMCInputSLAs/igetdartsinputfromdb.h"
#include "DartsModelsContext/DMCInputSLAs/igetinputmodelsservice.h"
#include "DartsModelsContext/DMCInputSLAs/iremovedartsinputsfromdb.h"
#include "DartsModelsContext/DMCInputSLAs/isortinputmodels.h"
#include "DartsModelsContext/DMCInputSLAs/idartscreateinput.h"
#include "DartsModelsContext/DMCInputSLAs/idartscreatejsonfrommodel.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"

class DMCInputSLAs
{
public:
    typedef IModelPredicate<IModel<QUuid>> Predicate;
    typedef IDbContext<IPlayerInput> DbService;
    IDartsInputModelsToJson *inputsToJSon() const;
    void setInputsToJsonService(IDartsInputModelsToJson *newDartsPointsJsonService);
    IDartsInputSetHint *dartsPointInputHint() const;
    void setDartsPointSetHint(IDartsInputSetHint *newDartsPointSetHint);
    ISortInputModels *sortInputs() const;
    void setSortInputs(ISortInputModels *newSortInputs);
    IGetInputModelsService *getInputsFromDb() const;
    void setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb);
    ICountInputModels *countInputs() const;
    void setCountInputs(ICountInputModels *newCountInputs);
    Predicate *sortInputsByIndexes() const;
    void setSortInputsByIndexes(Predicate *newSortPointInputsByIndexes);
    IGetDartsInputFromDb *getInputFromDb() const;
    void setGetInputFromDb(IGetDartsInputFromDb *newGetPointFromDb);
    IModelsDbContext *inputsDb() const;
    void setInputsDbService(IModelsDbContext *newDartsPointsDb);
    IDartsCreateInput *createInputModel() const;
    void setCreatePointModel(IDartsCreateInput *newCreatePointModel);
    IDartsCreateJsonFromModel<IModel<QUuid> > *inputToJson() const;
    void setInputToJsonService(IDartsCreateJsonFromModel<IModel<QUuid> > *newCreateJsonFromDartsPoint);
    IRemoveDartsInputsFromDb *removeInputsFromDb() const;
    void setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService);
private:
    IDartsInputModelsToJson* _inputsToJson;
    IDartsInputSetHint *_dartsPointSetHint;
    ISortInputModels* _sortInputs;
    IGetInputModelsService* _getInputsFromDb;
    IGetDartsInputFromDb *_getInputFromDb;
    ICountInputModels* _countInputs;
    Predicate* _sortPointInputsByIndexes;
    IRemoveDartsInputsFromDb* _removeDartsInputsFromDb;
    IDartsCreateInput *_createPointModel;
    IDartsCreateJsonFromModel<IModel<QUuid>> *_createJsonFromInputs;
    IModelsDbContext *_inputsDb;
};
#endif // DARTSINPUTSLAS_H
