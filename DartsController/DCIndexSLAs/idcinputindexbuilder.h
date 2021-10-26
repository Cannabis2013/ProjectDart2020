#ifndef IDCINPUTINDEXBUILDER_H
#define IDCINPUTINDEXBUILDER_H
#include <qbytearray.h>
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
class IDCInputIndexBuilder
{
public:
    virtual DCIndex index(const QByteArray& json) const = 0;
};
#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
