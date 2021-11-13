#ifndef IDCREQINPUTINDEXBUILDER_H
#define IDCREQINPUTINDEXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/IndexesSLAs/idcindexbuilder.h"
class IDCReqInputIndexBuilder
{
public:
    virtual IDartsIndex *index(IDartsIndex *index, const IDCIndexBuilder *indexBuilder) const = 0;
};
#endif // IDCREQINPUTINDEXBUILDER_H
