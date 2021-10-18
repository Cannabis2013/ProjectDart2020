#ifndef IDCINDEXESBUILDER_H
#define IDCINDEXESBUILDER_H

#include <qbytearray.h>
#include "DartsController/DCIndexServices/dcindexes.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"

class IDCIndexesBuilder
{
public:
    virtual DCIndexes buildIndexes(const QByteArray& json) const = 0;
    virtual DCIndexes buildIndexes(const IDCIndexService* service) const = 0;
};

#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
