#ifndef IDCINDEXBUILDER_H
#define IDCINDEXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDCIndexBuilder
{
public:
    virtual IDartsIndex *index() const = 0;
    virtual IDartsIndex *index(IDartsIndex *other) const = 0;
};
#endif // IDCINDEXBUILDER_H
