#ifndef IINDEXESBUILDER_H
#define IINDEXESBUILDER_H

#include <qbytearray.h>

template<typename TIndexes, typename TIndexService, typename TJson = QByteArray>
class IIndexesBuilder
{
public:
    typedef TIndexes Indexes;
    typedef TIndexService IndexService;
    virtual const Indexes* createIndexes(const TJson& json) const = 0;
    virtual const Indexes* createIndexes(const IndexService* service) const = 0;
};

#endif // IINDEXESBUILDER_H
