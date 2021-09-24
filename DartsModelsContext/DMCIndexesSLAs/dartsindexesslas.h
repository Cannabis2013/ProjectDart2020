#ifndef DARTSINDEXESSLAS_H
#define DARTSINDEXESSLAS_H

#include "idartscreateindexes.h"
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexestojson.h"

class DartsIndexesSLAs
{
public:
    IDartsCreateIndexes<IDartsIndexes> *indexesBuilder() const
    {
        return _createIndexesFromInputs;
    }
    void setIndexesBuilder(IDartsCreateIndexes<IDartsIndexes> *service)
    {
        _createIndexesFromInputs = service;
    }
    IDartsIndexesToJson *indexesToJson() const
    {
        return _indexesToJson;
    }
    void setIndexesToJsonService(IDartsIndexesToJson *newCreateJsonFromPointIndexes)
    {
        _indexesToJson = newCreateJsonFromPointIndexes;
    }
private:
    IDartsIndexesToJson *_indexesToJson;
    IDartsCreateIndexes<IDartsIndexes> *_createIndexesFromInputs;
};

#endif // IDARTSINDEXESSLAS_H
