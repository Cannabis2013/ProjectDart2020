#ifndef DARTSINDEXSERVICES_H
#define DARTSINDEXSERVICES_H
#include "idartsidxbuilder.h"
#include "iupdatedartsindexes.h"
#include "ModelSLAs/imodel.h"
class DartsIndexServices
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef IDartsIdxBuilder<IDartsIndex> IdxBuilder;
    IUpdateDartsIndexes<BaseModel> *updateIndex() const {return _updateIndexes;}
    void setUpdateIndexes(IUpdateDartsIndexes<BaseModel> *updateService) {_updateIndexes = updateService;}
    IdxBuilder *indexBuilder() const {return _indexBuilder;}
    void setIndexBuilder(IdxBuilder *newIndexBuilder) {_indexBuilder = newIndexBuilder;}
private:
    IUpdateDartsIndexes<BaseModel> *_updateIndexes;
    IdxBuilder *_indexBuilder;
};
#endif // DARTSINDEXSERVICES_H
