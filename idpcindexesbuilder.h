#ifndef IDPCINDEXESBUILDER_H
#define IDPCINDEXESBUILDER_H

#include "iindexesbuilder.h"

#include <dcindexes.h>
#include <idartspointindexservice.h>

class IDPCIndexesBuilder : public IIndexesBuilder<DPCContext::DCIndexes,IDartsPointIndexService>
{
public:
    virtual const Indexes *createIndexes(const QByteArray &json) const = 0;
    virtual const Indexes *createIndexes(const IndexService *service) const = 0;
};

#endif // IDPCINDEXESBUILDER_H
