#ifndef DARTSINPUTSERVICES_H
#define DARTSINPUTSERVICES_H

#include <icountinputmodels.h>
#include <idartsindexestojson.h>
#include <idartscreateindexes.h>
#include "DCInputsSLA/idartsinputmodelstojson.h"
#include "idartspointindexes.h"
#include "DCInputsSLA/idartsinputsethint.h"
#include "isetmodelhint.h"
#include "igetdartspointfromdb.h"
#include "igetinputmodelsservice.h"
#include "DCInputsSLA/iremovedartsinputsfromdb.h"
#include "isortinputmodels.h"
#include "idartscreateinput.h"
#include "idartscreatejsonfrommodel.h"
#include "idartsinput.h"
#include "idartsinput.h"

class DartsInputServices
{
public:
    typedef IPredicate<IModel<QUuid>> Predicate;
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
    IGetDartsPointFromDb *getInputFromDb() const;
    void setGetInputFromDb(IGetDartsPointFromDb *newGetPointFromDb);
    IDartsIndexesToJson *indexesToJson() const;
    void setIndexesToJsonService(IDartsIndexesToJson *newCreateJsonFromPointIndexes);
    IModelsDbContext *inputsDb() const;
    void setInputsDbService(IModelsDbContext *newDartsPointsDb);
    IDartsCreateInput *createInputModel() const;
    void setCreatePointModel(IDartsCreateInput *newCreatePointModel);
    IDartsCreateJsonFromModel<IModel<QUuid> > *inputToJson() const;
    void setInputToJsonService(IDartsCreateJsonFromModel<IModel<QUuid> > *newCreateJsonFromDartsPoint);
    IRemoveDartsInputsFromDb *removeInputsFromDb() const;
    void setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService);
    IDartsCreateIndexes<IDartsPointIndexes> *indexesBuilder() const;
    void setIndexesBuilder(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels);
private:
    IDartsInputModelsToJson* _inputsToJson;
    IDartsInputSetHint *_dartsPointSetHint;
    ISortInputModels* _sortInputs;
    IGetInputModelsService* _getInputsFromDb;
    IGetDartsPointFromDb *_getInputFromDb;
    ICountInputModels* _countInputs;
    Predicate* _sortPointInputsByIndexes;
    IDartsIndexesToJson *_indexesToJson;
    IRemoveDartsInputsFromDb* _removeDartsInputsFromDb;
    IDartsCreateInput *_createPointModel;
    IDartsCreateJsonFromModel<IModel<QUuid>> *_createJsonFromInputs;
    IDartsCreateIndexes<IDartsPointIndexes> *_createIndexesFromInputs;
    IModelsDbContext *_inputsDb;
};
#endif // DARTSINPUTSERVICES_H
