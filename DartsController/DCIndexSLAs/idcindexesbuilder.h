#ifndef IDCINDEXESBUILDER_H
#define IDCINDEXESBUILDER_H

#include <qbytearray.h>
#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCIndexSLAs/idcindexes.h"

class IDCIndexesBuilder
{
public:
    virtual const DCContext::IDCIndexes* createIndexes(const QByteArray& json) const = 0;
    virtual const DCContext::IDCIndexes* createIndexes(const IDCIndexService* service) const = 0;
};

#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
