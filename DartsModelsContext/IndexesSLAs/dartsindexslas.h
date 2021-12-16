#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H
#include "idartsidxbuilder.h"
#include "iupdatedartsindexes.h"
#include "DartsModelsContext/ModelSLAs/imodel.h"
class TnmVals;
class DartsIndexSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef IDartsIdxBuilder<IDartsIndex,TnmVals> IdxBuilder;
    IUpdateDartsIndexes<BaseModel> *updateIndexes() const {return _updateIndexes;}
    void setUpdateIndexes(IUpdateDartsIndexes<BaseModel> *updateService) {_updateIndexes = updateService;}
    IdxBuilder *indexBuilder() const {return _indexBuilder;}
    void setIndexBuilder(IdxBuilder *newIndexBuilder) {_indexBuilder = newIndexBuilder;}
private:
    IUpdateDartsIndexes<BaseModel> *_updateIndexes;
    IdxBuilder *_indexBuilder;
};
#endif // DARTSINDEXSLAS_H
