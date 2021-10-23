#ifndef IDCREQINPUTINDEXBUILDER_H
#define IDCREQINPUTINDEXBUILDER_H
#include "idcindexcontroller.h"
#include "DartsController/DCIndexServices/dcindex.h"
class IDCReqInputIndexBuilder
{
public:
    virtual DCIndex indexes(const IDCIndexController* indexService) const = 0;
};
#endif // IDCREQINPUTINDEXBUILDER_H
