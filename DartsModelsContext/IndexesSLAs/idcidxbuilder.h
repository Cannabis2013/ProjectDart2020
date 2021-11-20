#ifndef IDCIDXBUILDER_H
#define IDCIDXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDCIdxBuilder
{
public:
    virtual IDartsIndex *index() const = 0;
    virtual IDartsIndex *index(IDartsIndex *other) const = 0;
};
#endif // IDCIDXBUILDER_H
