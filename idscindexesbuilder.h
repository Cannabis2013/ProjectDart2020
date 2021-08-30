#ifndef IDSCINDEXESBUILDER_H
#define IDSCINDEXESBUILDER_H

#include <idsindexservice.h>
#include <idscindexes.h>
#include <qbytearray.h>
#include <iindexesbuilder.h>

class IDSCIndexesBuilder : public IIndexesBuilder<DSCContext::IDSCIndexes,IDSIndexService>
{
public:
    virtual const DSCContext::IDSCIndexes* createIndexes(const QByteArray& json) const = 0;
    virtual const DSCContext::IDSCIndexes* createIndexes(const IDSIndexService* service) const = 0;
};

#endif // IDARTSCONTROLLERINDEXMODELBUILDER_H
