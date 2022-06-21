#ifndef DARTSINDEXSERVICES_H
#define DARTSINDEXSERVICES_H

#include "idartsindexbuilder.h"

class IDartsIndex;
class QUuid;

class DartsIndexServices
{
public:
    typedef IDartsIndexBuilder<IDartsIndex> IdxBuilder;
    IdxBuilder *indexBuilder() const {return _indexBuilder;}
    void setIndexBuilder(IdxBuilder *newIndexBuilder) {_indexBuilder = newIndexBuilder;}
private:
    IdxBuilder *_indexBuilder;
};
#endif // DARTSINDEXSERVICES_H
