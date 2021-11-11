#ifndef IDCINDEXBUILDER_H
#define IDCINDEXBUILDER_H
#include <qbytearray.h>
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
class IDCIndexBuilder
{
public:
    virtual DCIndex index(const QJsonObject& obj) const = 0;
};
#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
