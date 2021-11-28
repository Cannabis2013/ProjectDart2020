#ifndef IDCIDXCONVERTER_H
#define IDCIDXCONVERTER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
class IDCIdxConverter
{
public:
    virtual IDartsIndex *convert(const DCIndex &idx) const = 0;
    virtual DCIndex convert(IDartsIndex *index) const = 0;
};
#endif // IDCIDXCONVERTER_H
